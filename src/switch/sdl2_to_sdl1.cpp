#ifdef USE_SDL2
#include <SDL.h>
#include <switch.h>
#include <sdl2_to_sdl1.h>

static SDL_Window* window = NULL;
static SDL_Texture* texture = NULL;
static SDL_Texture* prescaled = NULL;
static SDL_Renderer* renderer = NULL;
static int prescaled_width = 320;
static int prescaled_height = 240;
static int surface_width = 320;
static int surface_height = 240;

static int currently_docked = -1;

static int x_offset;
static int y_offset;
static int scaled_height;
static int scaled_width;
static int display_width;
static int display_height;

extern int mainMenu_shader;
extern int mainMenu_displayedLines;
extern int mainMenu_displayHires;
extern int visibleAreaWidth;
extern int displaying_menu;
//uint32_t *texture_pixels=NULL;

extern void update_joycon_mode(void);

#define MIN(a,b) ((a) < (b) ? (a) : (b))

int isDocked() {
	switch (appletGetOperationMode()) {
		case AppletOperationMode_Handheld:
			return 0;
			break;
		case AppletOperationMode_Console:
			return 1;
			break;
		default:
			return 0;
	}
}

void updateResolution() {
	int docked = isDocked();
	if ((docked && !currently_docked) || (!docked && currently_docked)) {
		// docked mode has changed, update window size etc.
		if (docked) {
			display_width = 1920;
			display_height = 1080;
			currently_docked = 1;
		} else {
			display_width = 1280;
			display_height = 720;
			currently_docked = 0;
		}
		// remove leftover-garbage on screen
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_SetWindowSize(window, display_width, display_height);
		SDL_SetVideoModeScaling(0, 0, 0, 0);
	}
}

SDL_Surface *SDL_SetVideoMode(int w, int h, int bpp, int flags) {
	if (currently_docked == -1) {
		if (isDocked()) {
			display_width = 1920;
			display_height = 1080;
			currently_docked = 1;
		} else {
			display_width = 1280;
			display_height = 720;
			currently_docked = 0;
		}
	}

	if (!renderer) {
		window = SDL_CreateWindow("uae4all2", 0, 0, display_width, display_height, 0);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
		SDL_RenderClear(renderer);
	}

	SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 16, SDL_PIXELFORMAT_RGB565);
	surface_width = w;
	surface_height = h;
	return surface;
}

void SDL_SetVideoModeScaling(int x, int y, float sw, float sh) {
	if (!displaying_menu) {
		if (mainMenu_shader == 0) {
			// integer scaling
			int screen_width;
			int screen_height;
			screen_width = visibleAreaWidth;
			if (mainMenu_displayHires)
				screen_height = 2 * mainMenu_displayedLines;			
			else
				screen_height = mainMenu_displayedLines;
			int scale_factor = MIN(display_height / screen_height, display_width / screen_width);
			scaled_height = scale_factor * screen_height;
			scaled_width = scale_factor * screen_width;
		} else {
			// scale to fit, preserve aspect ratio
			scaled_height = display_height;
			if (mainMenu_displayHires)
					scaled_width = ((visibleAreaWidth * display_height) / (float) (2 * mainMenu_displayedLines));
			else
					scaled_width = ((visibleAreaWidth * display_height) / (float) (mainMenu_displayedLines));
		}
		// centering
		x_offset = (display_width - scaled_width) / 2;
		y_offset = (display_height - scaled_height) / 2;
		if (mainMenu_shader == 1) {
			// find integer prescaled sizes to use later
			int prescale_factor_x = scaled_width / surface_width;
			int prescale_factor_y = scaled_height / surface_height;
			prescaled_width = prescale_factor_x * surface_width;
			prescaled_height = prescale_factor_y * surface_height;
		}
	} else {
		// menu (size 854 * 480) can be prescaled by half-integers without distortion
		// because everything displayed there is prescaled by 2x already
		// (apart from the thumbnails, but that doesn't look too bad)
		if (!currently_docked) {
			// handheld mode: the menu fits perfectly with a 1.5x scaling
			prescaled_width = 1281;
			prescaled_height = 720;
			scaled_width = 1281;
			scaled_height = 720;
		} else {
			// docked mode: the menu can be prescaled by 2x
			// but then needs some non-integer scaling to fill the screen
			prescaled_width = 1708;
			prescaled_height = 960;
			scaled_width = display_width;
			scaled_height = display_height;
		}
		x_offset = 0;
		y_offset = 0;
	}
	if (prescaled) {
		SDL_DestroyTexture(prescaled);
		prescaled = NULL;
	}
	if (mainMenu_shader == 1 || displaying_menu) {
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		prescaled = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, prescaled_width, prescaled_height);
	}
}

void SDL_SetVideoModeBilinear(int value) {
	if (value && (mainMenu_shader != 3)) // no linear filtering when shader = SHADER_POINT
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	else
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
}

void SDL_SetVideoModeSync(int value) {
	if (1)
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	else
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
}

void SDL_Flip(SDL_Surface *surface) {
	update_joycon_mode();
	if (surface && renderer && window) {
		updateResolution();
		if (texture) {
			SDL_DestroyTexture(texture);
			texture = NULL;
		}
		if (mainMenu_shader == 1 || displaying_menu) {
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			
			SDL_SetRenderTarget(renderer, prescaled);
			SDL_Rect dst_rect_prescale = { 0, 0, prescaled_width, prescaled_height };
			SDL_RenderCopy(renderer, texture, NULL, &dst_rect_prescale);

			SDL_SetRenderTarget(renderer, NULL);
			SDL_Rect dst_rect = { x_offset, y_offset, scaled_width , scaled_height };
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			SDL_RenderCopy(renderer, prescaled, NULL, &dst_rect);
			SDL_RenderPresent(renderer);
		} else {
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_Rect dst_rect = { x_offset, y_offset, scaled_width, scaled_height };
			SDL_Rect *src_rect = NULL;
			SDL_RenderCopy(renderer, texture, src_rect, &dst_rect);
			SDL_RenderPresent(renderer);
		}
	}
}
#endif