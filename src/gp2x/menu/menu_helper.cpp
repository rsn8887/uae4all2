#include "sysconfig.h"
#include "sysdeps.h"
#include "config.h"

#include "uae.h"
#include "options.h"
#include "menu.h"
#include "menu_config.h"
#include "sound.h"
#include "disk.h"
#include "memory-uae.h"
#include "custom.h"
#include "xwin.h"
#include "drawing.h"

#if defined(ANDROID)
#include <SDL_screenkeyboard.h>
#include <android/log.h>
#endif

#ifdef USE_SDL2
#include "sdl2_to_sdl1.h"
#endif

#if defined(__PSP2__) // NOT __SWITCH__
#include "psp2_shader.h"
#include "vita2d_fbo/includes/vita2d.h"
PSP2Shader *shader = NULL;
extern int mainMenu_shader;
#ifndef PRIVATE_HW_DATA
#define PRIVATE_HW_DATA
typedef struct private_hwdata {
	vita2d_texture *texture;
	SDL_Rect dst;
} private_hwdata;
#endif //PRIVATE_HW_DATA
#endif

#ifdef __SWITCH__
#include <switch.h>
#endif

#if defined(__PSP2__) // NOT __SWITCH__
//Allow locking PS Button
#include <psp2/shellutil.h>
#endif

extern int screenWidth;
extern int mainMenu_case;

extern int lastCpuSpeed;
extern int ntsc;

extern char launchDir[300];
extern char currentDir[300];

extern int displaying_menu;

extern void gp2x_stop_sound(void);

#ifdef __SWITCH__
extern void update_joycon_mode();
#endif


int saveAdfDir() {
    char path[300];
    snprintf(path, 300, "%s/conf/adfdir.conf", launchDir);
    FILE *f = fopen(path, "w");
    if (!f) return 0;
    char buffer[310];
    snprintf((char *) buffer, 310, "path=%s\n", currentDir);
    fputs(buffer, f);
    fclose(f);
    return 1;
}

void extractFileName(char *str, char *buffer) {
    char *p = str + strlen(str) - 1;
    while (*p != '/')
        p--;
    p++;
    strcpy(buffer, p);
}

void stateFilenameToThumbFilename(char *src, char *dst) {
    char buffer[255] = "";
    extractFileName(src, buffer);
    char *p = buffer + strlen(buffer) - 4;
    *p = 0;
    p--;
    strcat(p, ".png");
    strcpy(dst, THUMB_PREFIX);
    strcat(dst, buffer);
}

void exit_safely(int quit_via_home) {
#ifndef USE_SDLSOUND
	gp2x_stop_sound();
#endif
    saveAdfDir();	
    
#if defined(__PSP2__) // NOT __SWITCH__
    //unlock PS Button
    sceShellUtilUnlock(SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN);
#endif
    
    leave_program();

#if !defined(__PSP2__) && !defined(__SWITCH__)
    sync();
#endif
#ifdef __SWITCH__
    mainMenu_singleJoycons = 0;
    update_joycon_mode();
#endif
    exit(0);
}

#ifdef ANDROIDSDL
void update_onscreen()
{
    SDL_ANDROID_SetScreenKeyboardFloatingJoystick(mainMenu_FloatingJoystick);
    if (mainMenu_case != MAIN_MENU_CASE_DISPLAY && mainMenu_case != MAIN_MENU_CASE_MEMDISK && mainMenu_onScreen==0)
    {
      SDL_ANDROID_SetScreenKeyboardShown(0);
    }
    else
    {
      SDL_ANDROID_SetScreenKeyboardShown(1);
        SDL_Rect pos_textinput, pos_dpad, pos_button1, pos_button2, pos_button3, pos_button4, pos_button5, pos_button6;
        pos_textinput.x = mainMenu_pos_x_textinput*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_textinput.y = mainMenu_pos_y_textinput*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_textinput.h=SDL_ListModes(NULL, 0)[0]->h / (float)10 * mainMenu_button_size;
        pos_textinput.w=pos_textinput.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_TEXT, &pos_textinput);
        pos_dpad.x = mainMenu_pos_x_dpad*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_dpad.y = mainMenu_pos_y_dpad*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_dpad.h=SDL_ListModes(NULL, 0)[0]->h / (float)2.5 * mainMenu_button_size;
        pos_dpad.w=pos_dpad.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_DPAD, &pos_dpad);
        pos_button1.x = mainMenu_pos_x_button1*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button1.y = mainMenu_pos_y_button1*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button1.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button1.w=pos_button1.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_0, &pos_button1);
        pos_button2.x = mainMenu_pos_x_button2*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button2.y = mainMenu_pos_y_button2*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button2.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button2.w=pos_button2.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_1, &pos_button2);
        pos_button3.x = mainMenu_pos_x_button3*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button3.y = mainMenu_pos_y_button3*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button3.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button3.w=pos_button3.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_2, &pos_button3);
        pos_button4.x = mainMenu_pos_x_button4*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button4.y = mainMenu_pos_y_button4*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button4.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button4.w=pos_button4.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_3, &pos_button4);
        pos_button5.x = mainMenu_pos_x_button5*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button5.y = mainMenu_pos_y_button5*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button5.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button5.w=pos_button5.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_4, &pos_button5);
        pos_button6.x = mainMenu_pos_x_button6*(SDL_ListModes(NULL, 0)[0]->w/(float)480);
        pos_button6.y = mainMenu_pos_y_button6*(SDL_ListModes(NULL, 0)[0]->h/(float)360);
        pos_button6.h=SDL_ListModes(NULL, 0)[0]->h / (float)5 * mainMenu_button_size;
        pos_button6.w=pos_button6.h;
        SDL_ANDROID_SetScreenKeyboardButtonPos(SDL_ANDROID_SCREENKEYBOARD_BUTTON_5, &pos_button6);

        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_TEXT, mainMenu_onScreen_textinput);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_DPAD, mainMenu_onScreen_dpad);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_0, mainMenu_onScreen_button1);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_1, mainMenu_onScreen_button2);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_2, mainMenu_onScreen_button3);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_3, mainMenu_onScreen_button4);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_4, mainMenu_onScreen_button5);
        SDL_ANDROID_SetScreenKeyboardButtonShown(SDL_ANDROID_SCREENKEYBOARD_BUTTON_5, mainMenu_onScreen_button6);
    }
}
#endif

void update_display() {
    char layersize[20];
    snprintf(layersize, 20, "%dx480", screenWidth);

#ifndef WIN32
#if !defined(__PSP2__) && !defined(__SWITCH__)
    setenv("SDL_OMAP_LAYER_SIZE",layersize,1);
#endif
#endif

    char bordercut[20];
    snprintf(bordercut, 20, "%d,%d,0,0", mainMenu_cutLeft, mainMenu_cutRight);

#ifndef WIN32
#if !defined(__PSP2__) && !defined(__SWITCH__)
    setenv("SDL_OMAP_BORDER_CUT",bordercut,1);
#endif
#endif

#ifdef ANDROIDSDL
    update_onscreen();
#endif

#if defined(__PSP2__) || defined(__SWITCH__)
    if (prSDLScreen != NULL) {
        // clear old screen
        for (int i=0; i<4; i++)
		{
			SDL_FillRect(prSDLScreen,NULL,SDL_MapRGB(prSDLScreen->format, 0, 0, 0));
			SDL_Flip(prSDLScreen);
		}
#ifdef __PSP2__ // NOT __SWITCH__
		vita2d_wait_rendering_done();
		vita2d_free_texture(prSDLScreen->hwdata->texture);
		SDL_free(prSDLScreen->hwdata);
		prSDLScreen->hwdata = NULL;
		prSDLScreen->pixels = NULL;
#endif
		SDL_FreeSurface(prSDLScreen);
      prSDLScreen = NULL;
    }

#ifdef __PSP2__ // NOT __SWITCH__
	// speed up rendering
	vita2d_texture_set_alloc_memblock_type(SCE_KERNEL_MEMBLOCK_TYPE_USER_RW);
#endif

	displaying_menu = 0;

    prSDLScreen = SDL_SetVideoMode(visibleAreaWidth, mainMenu_displayedLines, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    printf("update_display: SDL_SetVideoMode(%i, %i, 16)\n", visibleAreaWidth, mainMenu_displayedLines);

    float sh;
    float sw;
    int x;
    int y;

    //is a shader active?
    if (mainMenu_shader != 0)
    {
    	sh = 544;
      if (mainMenu_displayHires)
      	sw = (0.5f*(float)visibleAreaWidth*((float)544/(float)mainMenu_displayedLines));
      else
      	sw = ((float)visibleAreaWidth*((float)544/(float)mainMenu_displayedLines));
    	x = (960 - sw) / 2;
    	y = (544 - sh) / 2;

    	//This requires a recent SDL-Vita branch SDL12 for example
    	//https://github.com/rsn8887/SDL-Vita/tree/SDL12
    	//to compile
   	SDL_SetVideoModeScaling(x, y, sw, sh);
   	SDL_SetVideoModeBilinear(1);
    }
    else //otherwise do regular integer 2* scaling without filtering to ensure good picture quality
    {
    	sh = (float) (2 * mainMenu_displayedLines);
    	if (mainMenu_displayHires)
    		sw = (float) (1 * visibleAreaWidth);
    	else
    		sw = (float) (2 * visibleAreaWidth);
    	x = (960 - sw) / 2;
      y = (544 - sh) / 2;
      SDL_SetVideoModeScaling(x, y, sw, sh);
      SDL_SetVideoModeBilinear(0);
	 }
	 printf("update_display: SDL_SetVideoModeScaling(%i, %i, %i, %i)\n", x, y, (int)sw, (int)sh);

    SDL_SetVideoModeSync(1);

#ifdef __PSP2__ // NOT __SWITCH__
    // set vita2d shader
    if(shader != NULL) {
        delete(shader);
        shader = NULL;
    }
    shader = new PSP2Shader((PSP2Shader::Shader)mainMenu_shader);
#endif

    // clear new screen
    for (int i=0; i<4; i++)
	{
		SDL_FillRect(prSDLScreen,NULL,SDL_MapRGB(prSDLScreen->format, 0, 0, 0));
		SDL_Flip(prSDLScreen);
	}

#else
#if defined(PANDORA) && !(defined(WIN32) || defined(AROS))
    prSDLScreen = SDL_SetVideoMode(visibleAreaWidth, mainMenu_displayedLines, 16, SDL_SWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
#elif defined(PANDORA) && (defined(WIN32) || defined(AROS))
    prSDLScreen = SDL_SetVideoMode(visibleAreaWidth, mainMenu_displayedLines, 16, SDL_SWSURFACE|SDL_DOUBLEBUF);
#else
    prSDLScreen = SDL_SetVideoMode(visibleAreaWidth, mainMenu_displayedLines, 16, SDL_SWSURFACE|SDL_FULLSCREEN);
#endif
#endif
    SDL_ShowCursor(SDL_DISABLE);

    if (mainMenu_displayHires)
        InitDisplayArea(visibleAreaWidth >> 1);
    else
        InitDisplayArea(visibleAreaWidth);
}


static bool cpuSpeedChanged = false;

void setCpuSpeed() {
#if !defined(__PSP2__) && !defined(__SWITCH__)
    char speedCmd[128];

    if(mainMenu_cpuSpeed != lastCpuSpeed)
    {
        snprintf((char*)speedCmd, 128, "unset DISPLAY; echo y | sudo -n /usr/pandora/scripts/op_cpuspeed.sh %d", mainMenu_cpuSpeed);
        system(speedCmd);
        lastCpuSpeed = mainMenu_cpuSpeed;
        cpuSpeedChanged = true;
    }
    if(mainMenu_ntsc != ntsc)
    {
        ntsc = mainMenu_ntsc;
        if(ntsc)
            system("sudo /usr/pandora/scripts/op_lcdrate.sh 60");
        else
            system("sudo /usr/pandora/scripts/op_lcdrate.sh 50");
    }
    update_display();
#endif
}


#ifdef PANDORA

void resetCpuSpeed(void) {
    if (cpuSpeedChanged) {
        FILE *f = fopen("/etc/pandora/conf/cpu.conf", "rt");
        if (f) {
            char line[128];
            for (int i = 0; i < 6; ++i) {
                fscanf(f, "%s\n", &line);
                if (strncmp(line, "default:", 8) == 0) {
                    int value = 0;
                    sscanf(line, "default:%d", &value);
                    if (value > 500 && value < 1200) {
                        lastCpuSpeed = value - 10;
                        mainMenu_cpuSpeed = value;
                        setCpuSpeed();
                        printf("CPU speed reset to %d\n", value);
                    }
                }
            }
            fclose(f);
        }
    }
}

#endif
