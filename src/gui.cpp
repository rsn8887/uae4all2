 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Interface to the Tcl/Tk GUI
  *
  * Copyright 1996 Bernd Schmidt
  */

#define _GUI_CPP

#include "sysconfig.h"
#include "sysdeps.h"
#include "config.h"
#include "uae.h"
#include "options.h"
#include "gui.h"
#include "menu.h"
#include "menu_config.h"
#ifdef USE_UAE4ALL_VKBD
#include "vkbd.h"
#endif
#include "debug_uae4all.h"
#include "custom.h"
#include "memory-uae.h"
#include "xwin.h"
#include "drawing.h"
#include "sound.h"
#include "audio.h"
#include "keybuf.h"
#include "keyboard.h"
#include "disk.h"
#include "savestate.h"
#include <SDL.h>

#define VIDEO_FLAGS_INIT SDL_SWSURFACE|SDL_FULLSCREEN
#ifdef ANDROIDSDL
#define VIDEO_FLAGS VIDEO_FLAGS_INIT
#else
#define VIDEO_FLAGS VIDEO_FLAGS_INIT | SDL_DOUBLEBUF
#endif

#include "gp2x.h"
#include "gp2xutil.h"

#if defined(__PSP2__) // NOT __SWITCH__
#include <psp2/shellutil.h>
#endif

#ifdef __SWITCH__
#include <switch.h>
#endif

#ifdef USE_SDL2
#include "sdl2_to_sdl1.h"
#endif

#ifdef ANDROIDSDL
#include <android/log.h>
#endif

extern int gp2xMouseEmuOn, gp2xButtonRemappingOn;
extern bool switch_autofire;
int justMovedUp[MAX_NUM_CONTROLLERS]={};
int justMovedDown[MAX_NUM_CONTROLLERS]={};
int justMovedLeft[MAX_NUM_CONTROLLERS]={}; 
int justMovedRight[MAX_NUM_CONTROLLERS]={};
int justLComma=0, justLPeriod=0;
#ifdef USE_UAE4ALL_VKBD
int justLK=0;
#endif
int justMovedStickUp[MAX_NUM_CONTROLLERS]={};
int justMovedStickDown[MAX_NUM_CONTROLLERS]={};
int justMovedStickLeft[MAX_NUM_CONTROLLERS]={};
int justMovedStickRight[MAX_NUM_CONTROLLERS]={};
int justPressedA[MAX_NUM_CONTROLLERS]={};
int justPressedB[MAX_NUM_CONTROLLERS]={};
int justPressedX[MAX_NUM_CONTROLLERS]={};
int justPressedY[MAX_NUM_CONTROLLERS]={};
int justPressedL[MAX_NUM_CONTROLLERS]={};
int justPressedR[MAX_NUM_CONTROLLERS]={};
#ifdef __SWITCH__
int justPressedL2[MAX_NUM_CONTROLLERS]={};
int justPressedR2[MAX_NUM_CONTROLLERS]={};
int justPressedL3[MAX_NUM_CONTROLLERS]={};
int justPressedR3[MAX_NUM_CONTROLLERS]={};
#endif
int justPressedQ=0;
int stylusClickOverride=0;
int stylusAdjustX=0, stylusAdjustY=0;
int screenWidth = 640;

static int customAutofireDelay[MAX_NUM_CONTROLLERS]={};

extern int mainMenu_autofire;

extern int nr_joysticks;

extern struct gui_info gui_data;

static char _show_message_str[40]={
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

int show_message=0;
char *show_message_str=(char *)&_show_message_str[0];

extern SDL_Surface *prSDLScreen;

extern SDL_Joystick *uae4all_joy0, *uae4all_joy1, *uae4all_joy2, *uae4all_joy3, *uae4all_joy4, *uae4all_joy5, *uae4all_joy6, *uae4all_joy7;

#if defined(__PSP2__) || defined(__SWITCH__)
//Predefined quick switch resolutions to select via TRIGGER R+START+DPAD LEFT/RIGHT
static int can_change_quickSwitchModeID = 1;
static int can_change_custom_controlSet = 1;
static int quickSwitchModeID=1;
struct myRes
{
		int num_lines;
		int top_pos;
};
static myRes quickSwitchModes[] = {
	{192, 18},
	{200, 18},
	{216, 18},
	{224, 18},
	{240, 18},
	{256, 18},
	{270, 18},
	{286, 0},
	{192, 30},
	{200, 30},
	{216, 30},
	{224, 30},
	{240, 30},
	{256, 30},
	{270, 30},
};
extern int moveY;

//analog stick values for mouse emulation on Vita
int lAnalogX=0;
int lAnalogY=0;
int rAnalogX=0;
int rAnalogY=0;
int lAnalogXCenter[MAX_NUM_CONTROLLERS]={};
int lAnalogYCenter[MAX_NUM_CONTROLLERS]={};
int rAnalogXCenter[MAX_NUM_CONTROLLERS]={};
int rAnalogYCenter[MAX_NUM_CONTROLLERS]={};
int haveJoysticksBeenCentered=0;
extern int mainMenu_leftStickMouse;
#endif // __PSP2__

#ifdef USE_UAE4ALL_VKBD
extern int keycode2amiga(SDL_keysym *prKeySym);
#endif
extern int uae4all_keystate[];

int emulating=0;
char uae4all_image_file0[256]  = { 0, };
char uae4all_image_file1[256] = { 0, };
char uae4all_image_file2[256]  = { 0, };
char uae4all_image_file3[256] = { 0, };

char uae4all_hard_dir[256] = { 0, };
char uae4all_hard_file0[256] = { 0, };
char uae4all_hard_file1[256] = { 0, };
char uae4all_hard_file2[256] = { 0, };
char uae4all_hard_file3[256] = { 0, };

int drawfinished=0;

int moved_x = 0;
int moved_y = 0;

int dpadUp[MAX_NUM_CONTROLLERS]={};
int dpadDown[MAX_NUM_CONTROLLERS]={};
int dpadLeft[MAX_NUM_CONTROLLERS]={};
int dpadRight[MAX_NUM_CONTROLLERS]={};
int stickUp[MAX_NUM_CONTROLLERS]={};
int stickDown[MAX_NUM_CONTROLLERS]={};
int stickLeft[MAX_NUM_CONTROLLERS]={};
int stickRight[MAX_NUM_CONTROLLERS]={};
int buttonA[MAX_NUM_CONTROLLERS]={}; // Vita Square, GP2X_BUTTON_B
int buttonB[MAX_NUM_CONTROLLERS]={}; // Vita Circle, GP2X_BUTTON_A
int buttonX[MAX_NUM_CONTROLLERS]={}; // Vita Cross, GP2X_BUTTON_X
int buttonY[MAX_NUM_CONTROLLERS]={}; // Vita Triangle, GP2X_BUTTON_Y
int triggerL[MAX_NUM_CONTROLLERS]={};
int triggerR[MAX_NUM_CONTROLLERS]={};
#ifdef __SWITCH__
int triggerL2[MAX_NUM_CONTROLLERS]={};
int triggerR2[MAX_NUM_CONTROLLERS]={};
int triggerL3[MAX_NUM_CONTROLLERS]={};
int triggerR3[MAX_NUM_CONTROLLERS]={};
#endif
int buttonSelect[MAX_NUM_CONTROLLERS]={};
int buttonStart[MAX_NUM_CONTROLLERS]={};

extern int mainMenu_case;
#ifdef WITH_TESTMODE
int no_limiter = 0;
#endif

#ifdef __SWITCH__
int singleJoycons = 0;  // are single Joycons being used at the moment?
void update_joycon_mode() {
	int handheld = hidGetHandheldMode();
	if (!handheld) {
		if (mainMenu_singleJoycons) {
			if (!singleJoycons) {
				singleJoycons = 1;
				for (int id=0; id<8; id++) {
					hidSetNpadJoyHoldType(HidNpadJoyHoldType_Horizontal);
					hidScanInput();
					hidSetNpadJoyAssignmentModeSingleByDefault((HidNpadIdType) id);
				}
			}
		} else if (singleJoycons) {
			singleJoycons = 0;

			// find all left/right single JoyCon pairs and join them together
			for (int id = 0; id < 8; id++) {
				hidSetNpadJoyHoldType(HidNpadJoyHoldType_Vertical);
			}
			int lastRightId = 8;		
			for (int id0 = 0; id0 < 8; id0++) {
				if (hidGetNpadStyleSet((HidNpadIdType) id0) & HidNpadStyleTag_NpadJoyLeft ) {
					for (int id1=lastRightId-1; id1>=0; id1--) {
						if (hidGetNpadStyleSet((HidNpadIdType) id1) & HidNpadStyleTag_NpadJoyRight ) {
							lastRightId=id1;
							// prevent missing player numbers
							if (id0 < id1) {
								hidMergeSingleJoyAsDualJoy((HidNpadIdType) id0, (HidNpadIdType) id1);
							} else if (id0 > id1) {
								hidMergeSingleJoyAsDualJoy((HidNpadIdType) id1, (HidNpadIdType) id0);
							}
							break;
						}
					}
				}
			}
		}
	} else {
		if (singleJoycons) {
			singleJoycons = 0;
			for (int id=0; id<8; id++) {
				hidSetNpadJoyHoldType(HidNpadJoyHoldType_Vertical);
				hidScanInput();
				hidSetNpadJoyAssignmentModeDual((HidNpadIdType) id);
			}
		}
	}
}
#endif

#if defined(__PSP2__) || defined(__SWITCH__)
void remap_custom_controls() // assign custom 1-3 to currently used custom set
{
	for (int i=0; i<MAX_NUM_CONTROLLERS; i++)
	{
		int j=mainMenu_custom_controlSet;
		mainMenu_custom_up[i] = mainMenu_customPreset_up[j][i];
		mainMenu_custom_down[i] = mainMenu_customPreset_down[j][i];
		mainMenu_custom_left[i] = mainMenu_customPreset_left[j][i];
		mainMenu_custom_right[i] = mainMenu_customPreset_right[j][i];
		mainMenu_custom_stickup[i] = mainMenu_customPreset_stickup[j][i];
		mainMenu_custom_stickdown[i] = mainMenu_customPreset_stickdown[j][i];
		mainMenu_custom_stickleft[i] = mainMenu_customPreset_stickleft[j][i];
		mainMenu_custom_stickright[i] = mainMenu_customPreset_stickright[j][i];
		mainMenu_custom_A[i] = mainMenu_customPreset_A[j][i];
		mainMenu_custom_B[i] = mainMenu_customPreset_B[j][i];
		mainMenu_custom_X[i] = mainMenu_customPreset_X[j][i];
		mainMenu_custom_Y[i] = mainMenu_customPreset_Y[j][i];
		mainMenu_custom_L[i] = mainMenu_customPreset_L[j][i];
		mainMenu_custom_R[i] = mainMenu_customPreset_R[j][i];
#ifdef __SWITCH__
		mainMenu_custom_L2[i] = mainMenu_customPreset_L2[j][i];
		mainMenu_custom_R2[i] = mainMenu_customPreset_R2[j][i];
		mainMenu_custom_L3[i] = mainMenu_customPreset_L3[j][i];
		mainMenu_custom_R3[i] = mainMenu_customPreset_R3[j][i];
#endif
	}
}		
#endif

static void getChanges(void)
{
	if (mainMenu_sound)
	{
		if (mainMenu_sound == 1)
			changed_produce_sound=2;
		else
			changed_produce_sound=3;
		sound_default_evtime();
	}
	else
		changed_produce_sound=0;
	changed_gfx_framerate=mainMenu_frameskip;
}
	
int gui_init (void)
{
	SDL_ShowCursor(SDL_DISABLE);
#if !(defined(ANDROIDSDL) || defined(AROS))
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_JoystickOpen(0);
#endif
	if (prSDLScreen!=NULL)
	{
		emulating=0;
		uae4all_init_sound();
		init_kickstart();

#if defined(__PSP2__) // NOT __SWITCH__
		//Lock PS Button to prevent file corruption
		sceShellUtilLock(SCE_SHELL_UTIL_LOCK_TYPE_PS_BTN);
#endif

#ifdef USE_UAE4ALL_VKBD
		vkbd_init();
#endif

#ifdef USE_GUICHAN
		if (!uae4all_image_file0[0])
			run_mainMenuGuichan();
#else
		init_text(1);
#if !defined(__SWITCH__) && !defined(__PSP2__)
		if (!uae4all_image_file0[0])
#endif
			run_mainMenu();
		quit_text();
#endif
		inputmode_init();
		uae4all_pause_music();
		emulating=1;
		getChanges();
		check_all_prefs();
		return 0;
	}
	return -1;
}

int gui_update (void)
{
	extern char *savestate_filename;
	extern char *screenshot_filename;
	strcpy(changed_df[0],uae4all_image_file0);
	strcpy(changed_df[1],uae4all_image_file1);
	strcpy(changed_df[2],uae4all_image_file2);
	strcpy(changed_df[3],uae4all_image_file3);
	make_savestate_filenames(savestate_filename, screenshot_filename);
	real_changed_df[0]=1;
	real_changed_df[1]=1;
	real_changed_df[2]=1;
	real_changed_df[3]=1;
	return 0;
}

static void goMenu(void)
{
	int exitmode=0;
	int autosave=mainMenu_autosave;
	if (quit_program != 0)
		return;
	emulating=1;
#if !defined(__PSP2__) && !defined(__SWITCH__) //no need to erase all the vkbd graphics from memory on Vita
#ifdef USE_UAE4ALL_VKBD
	vkbd_quit();
#endif	
#endif
	pause_sound();
#ifdef USE_GUICHAN
	running=true;
	exitmode=run_mainMenuGuichan();
#else
	init_text(0);
	menu_raise();
	
	exitmode=run_mainMenu();
#endif

	/* Clear menu garbage at the bottom of the screen */
	black_screen_now();
	notice_screen_contents_lost();
	resume_sound();
#ifndef USE_GUICHAN
	if ((!(strcmp(prefs_df[0],uae4all_image_file0))) || ((!(strcmp(prefs_df[1],uae4all_image_file1)))))
		menu_unraise();
	quit_text();
#endif
#ifdef USE_UAE4ALL_VKBD
#if !defined(__PSP2__) && !defined(__SWITCH__) //no need to reload all the vkbd graphics everytime on Vita
	vkbd_init();
#endif
#endif
	getChanges();
#ifdef USE_UAE4ALL_VKBD
	vkbd_init_button2();
#endif
	if (exitmode==1 || exitmode==2)
	{
		extern char *savestate_filename;
		extern char *screenshot_filename;
		extern int saveMenu_n_savestate;
		for(int i=0;i<mainMenu_drives;i++)
		{
			if (i==0 && strcmp(changed_df[0],uae4all_image_file0)) {
				strcpy(changed_df[0],uae4all_image_file0);
				real_changed_df[0]=1;
			}
			else if (i==1 && strcmp(changed_df[1],uae4all_image_file1)) {
				strcpy(changed_df[1],uae4all_image_file1);
				real_changed_df[1]=1;
			}
			else if (i==2 && strcmp(changed_df[2],uae4all_image_file2)) {
				strcpy(changed_df[2],uae4all_image_file2);
				real_changed_df[2]=1;
			}
			else if (i==3 && strcmp(changed_df[3],uae4all_image_file3)) {
				strcpy(changed_df[3],uae4all_image_file3);
				real_changed_df[3]=1;
			}
		}
		make_savestate_filenames(savestate_filename, screenshot_filename);
	}
	if (exitmode==3)
	{
		extern char *savestate_filename;
		extern char *screenshot_filename;
		for(int i=0;i<mainMenu_drives;i++)
		{
			changed_df[i][0]=0;
			if (i==0) {
				uae4all_image_file0[0]=0;
				if (strcmp(changed_df[0],uae4all_image_file0))
				{ 
				strcpy(changed_df[0],uae4all_image_file0);
				real_changed_df[0]=1;
				}
			}
			else if (i==1) {
				uae4all_image_file1[0]=0;
				if (strcmp(changed_df[1],uae4all_image_file1))
				{ 
				strcpy(changed_df[1],uae4all_image_file1);
				real_changed_df[1]=1;
				}
			}
			else if (i==2) {
				uae4all_image_file2[0]=0;
				if (strcmp(changed_df[2],uae4all_image_file2))
				{ 
				strcpy(changed_df[2],uae4all_image_file2);
				real_changed_df[2]=1;
				}
			}
			else if (i==3) {
				uae4all_image_file3[0]=0;
				if (strcmp(changed_df[3],uae4all_image_file3))
				{ 
				strcpy(changed_df[3],uae4all_image_file3);
				real_changed_df[3]=1;
				}
			}
			disk_eject(i);
		}
		make_savestate_filenames(savestate_filename, screenshot_filename);
	}
	if (exitmode==2)
	{
		if (autosave!=mainMenu_autosave)
		{
			prefs_df[0][0]=0;
		prefs_df[1][0]=0;
			prefs_df[2][0]=0;
		prefs_df[3][0]=0;
		}
		if(gp2xButtonRemappingOn)
			togglemouse();
			uae_reset ();
	}
	check_all_prefs();
	gui_purge_events();
	fpscounter_reset();
	notice_screen_contents_lost();
	
	//remove gfx garbage in pixel array
	lockscr();
	memset((char *) prSDLScreen->pixels, 0, prSDLScreen->h*prSDLScreen->pitch);
	unlockscr();
}

int customKey;
void getMapping(int customId)
{
	switch(customId)
	{
		case 1: customKey=AK_UP; break;
		case 2: customKey=AK_DN; break;
		case 3: customKey=AK_LF; break;
		case 4: customKey=AK_RT; break;
		case 5: customKey=AK_NP0; break;
		case 6: customKey=AK_NP1; break;
		case 7: customKey=AK_NP2; break;
		case 8: customKey=AK_NP3; break;
		case 9: customKey=AK_NP4; break;
		case 10: customKey=AK_NP5; break;
		case 11: customKey=AK_NP6; break;
		case 12: customKey=AK_NP7; break;
		case 13: customKey=AK_NP8; break;
		case 14: customKey=AK_NP9; break;
		case 15: customKey=AK_ENT; break;
		case 16: customKey=AK_NPDIV; break;
		case 17: customKey=AK_NPMUL; break;
		case 18: customKey=AK_NPSUB; break;
		case 19: customKey=AK_NPADD; break;
		case 20: customKey=AK_NPDEL; break;
		case 21: customKey=AK_NPLPAREN; break;
		case 22: customKey=AK_NPRPAREN; break;
		case 23: customKey=AK_SPC; break;
		case 24: customKey=AK_BS; break;
		case 25: customKey=AK_TAB; break;
		case 26: customKey=AK_RET; break;
		case 27: customKey=AK_ESC; break;
		case 28: customKey=AK_DEL; break;
		case 29: customKey=AK_LSH; break;
		case 30: customKey=AK_RSH; break;
		case 31: customKey=AK_CAPSLOCK; break;
		case 32: customKey=AK_CTRL; break;
		case 33: customKey=AK_LALT; break;
		case 34: customKey=AK_RALT; break;
		case 35: customKey=AK_LAMI; break;
		case 36: customKey=AK_RAMI; break;
		case 37: customKey=AK_HELP; break;
		case 38: customKey=AK_LBRACKET; break;
		case 39: customKey=AK_RBRACKET; break;
		case 40: customKey=AK_SEMICOLON; break;
		case 41: customKey=AK_COMMA; break;
		case 42: customKey=AK_PERIOD; break;
		case 43: customKey=AK_SLASH; break;
		case 44: customKey=AK_BACKSLASH; break;
		case 45: customKey=AK_QUOTE; break;
		case 46: customKey=AK_NUMBERSIGN; break;
		case 47: customKey=AK_LTGT; break;
		case 48: customKey=AK_BACKQUOTE; break;
		case 49: customKey=AK_MINUS; break;
		case 50: customKey=AK_EQUAL; break;
		case 51: customKey=AK_A; break;
		case 52: customKey=AK_B; break;
		case 53: customKey=AK_C; break;
		case 54: customKey=AK_D; break;
		case 55: customKey=AK_E; break;
		case 56: customKey=AK_F; break;
		case 57: customKey=AK_G; break;
		case 58: customKey=AK_H; break;
		case 59: customKey=AK_I; break;
		case 60: customKey=AK_J; break;
		case 61: customKey=AK_K; break;
		case 62: customKey=AK_L; break;
		case 63: customKey=AK_M; break;
		case 64: customKey=AK_N; break;
		case 65: customKey=AK_O; break;
		case 66: customKey=AK_P; break;
		case 67: customKey=AK_Q; break;
		case 68: customKey=AK_R; break;
		case 69: customKey=AK_S; break;
		case 70: customKey=AK_T; break;
		case 71: customKey=AK_U; break;
		case 72: customKey=AK_V; break;
		case 73: customKey=AK_W; break;
		case 74: customKey=AK_X; break;
		case 75: customKey=AK_Y; break;
		case 76: customKey=AK_Z; break;
		case 77: customKey=AK_1; break;
		case 78: customKey=AK_2; break;
		case 79: customKey=AK_3; break;
		case 80: customKey=AK_4; break;
		case 81: customKey=AK_5; break;
		case 82: customKey=AK_6; break;
		case 83: customKey=AK_7; break;
		case 84: customKey=AK_8; break;
		case 85: customKey=AK_9; break;
		case 86: customKey=AK_0; break;
		case 87: customKey=AK_F1; break;
		case 88: customKey=AK_F2; break;
		case 89: customKey=AK_F3; break;
		case 90: customKey=AK_F4; break;
		case 91: customKey=AK_F5; break;
		case 92: customKey=AK_F6; break;
		case 93: customKey=AK_F7; break;
		case 94: customKey=AK_F8; break;
		case 95: customKey=AK_F9; break;
		case 96: customKey=AK_F10; break;
		default: customKey=0;
	}
}

void gui_handle_events (void)
{
#ifdef USE_SDL2
	//Uint8 *keystate = (Uint8 *)((hostptr) SDL_GetKeyboardState(NULL));
	Uint8 *keystate=const_cast<Uint8*>(SDL_GetKeyboardState(NULL));
#else
	Uint8 *keystate = SDL_GetKeyState(NULL);
#endif
#if defined(__PSP2__) || defined(__SWITCH__)
	SDL_JoystickUpdate();
	SDL_Joystick *currentJoy = uae4all_joy0;
	int lX, lY, rX, rY;
	float joyX = 0;
	float joyY = 0;
	float joyDeadZoneSquared = 10240.0*10240.0;
	float slope = 0.414214f; // tangent of 22.5 degrees for size of angular zones

	for (int i=0; i<nr_joysticks; i++)
	{
		switch (i)
		{	
			case 0:
				currentJoy = uae4all_joy0;
				break;
			case 1:
				currentJoy = uae4all_joy1;
				break;
			case 2:
				currentJoy = uae4all_joy2;
				break;
			case 3:
				currentJoy = uae4all_joy3;
				break;
			case 4:
				currentJoy = uae4all_joy4;
				break;
			case 5:
				currentJoy = uae4all_joy5;
				break;
			case 6:
				currentJoy = uae4all_joy6;
				break;
			case 7:
				currentJoy = uae4all_joy7;
				break;
		}
		//Only Joystick 0 analog axis are important for mouse control, the others
		//are used to have the dpad on the left stick but that is all
		lX = SDL_JoystickGetAxis(currentJoy, 0);
		lY = SDL_JoystickGetAxis(currentJoy, 1);
		rX = SDL_JoystickGetAxis(currentJoy, 2);
		rY = SDL_JoystickGetAxis(currentJoy, 3);
		
		//Is this the first time this routine is called when the program has just been launched? 
		//If yes, center the joysticks now
		//After that, center the joysticks everytime we open the menu with "select"
		if (!haveJoysticksBeenCentered) {	
			lAnalogXCenter[i]=lX;
			lAnalogYCenter[i]=lY;
			rAnalogXCenter[i]=rX;
			rAnalogYCenter[i]=rY;
			//From now on only center when entering menu
			haveJoysticksBeenCentered=1;
		}
				
		lX=lX-lAnalogXCenter[i];
		lY=lY-lAnalogYCenter[i];
		rX=rX-rAnalogXCenter[i];
		rY=rY-rAnalogYCenter[i];

		if (i==0)
		{
				//save the main controller analog inputs those are used in the vkeyboard etc.
				lAnalogX=lX;
				lAnalogY=lY;
				rAnalogX=rX;
				rAnalogY=rY;	
		}
		// Main Controller is special (it does mouse controls vkeyboard etc.)
		// On Main Controller, always use either the left of right analog for mouse pointer movement
		// the other stick replicates the dpad inputs
		dpadRight[i]  = SDL_JoystickGetButton(currentJoy, PAD_RIGHT);
		dpadLeft[i]  = SDL_JoystickGetButton(currentJoy, PAD_LEFT);
		dpadUp[i]  = SDL_JoystickGetButton(currentJoy, PAD_UP);
		dpadDown[i]  = SDL_JoystickGetButton(currentJoy, PAD_DOWN);

		stickUp[i] = 0;
		stickDown[i] = 0;
		stickLeft[i] = 0;
		stickRight[i] = 0;

		buttonA[i] = SDL_JoystickGetButton(currentJoy, PAD_SQUARE);
		buttonB[i] = SDL_JoystickGetButton(currentJoy, PAD_CIRCLE);
		buttonX[i] = SDL_JoystickGetButton(currentJoy, PAD_CROSS);
		buttonY[i] = SDL_JoystickGetButton(currentJoy, PAD_TRIANGLE);
		triggerL[i] = SDL_JoystickGetButton(currentJoy, PAD_L);
		triggerR[i] = SDL_JoystickGetButton(currentJoy, PAD_R);

		buttonSelect[i] = SDL_JoystickGetButton(currentJoy, PAD_SELECT);
		buttonStart[i] = SDL_JoystickGetButton(currentJoy, PAD_START);
#ifdef __SWITCH__
		triggerL2[i] = SDL_JoystickGetButton(currentJoy, PAD_L2);
		triggerR2[i] = SDL_JoystickGetButton(currentJoy, PAD_R2);
		triggerL3[i] = SDL_JoystickGetButton(currentJoy, PAD_L3);
		triggerR3[i] = SDL_JoystickGetButton(currentJoy, PAD_R3);

		if (singleJoycons) {
			joyX=lX;
			joyY=-lY;

			dpadRight[i] = 0;
			dpadLeft[i] = 0;
			dpadUp[i] = 0;
			dpadDown[i] = 0;
			stickUp[i] = 0;
			stickDown[i] = 0;
			stickLeft[i] = 0;
			stickRight[i] = 0;
			triggerL2[i] = 0;
			triggerR2[i] = 0;
			
			if (i == 0) {
				buttonSelect[0] |= buttonStart[0];
				buttonStart[0] = triggerL[0];

				// push player 1 joystick in for mouse movement or keyboard adjustment
				if (triggerL3[0]) {
					rAnalogX = joyX;
					rAnalogY = -joyY;
					joyX = 0;
					joyY = 0;
				} else {
					rAnalogX = 0;
					rAnalogY = 0;
				}
				triggerL[0] = 0;
				triggerL3[0] = 0;
				triggerR3[0] = 0;
				lAnalogX = 0;
				lAnalogY = 0;
			}
		}
#endif

#ifdef __SWITCH__
		if (!singleJoycons)
#endif
		{
			// analog joystick acts as digital controls with proper circular deadzone
#ifdef USE_UAE4ALL_VKBD
			if (i==0 && mainMenu_leftStickMouse && !(buttonStart[0] && triggerR[0]) && !vkbd_mode)
#else
			if (i==0 && mainMenu_leftStickMouse && !(buttonStart[0] && triggerR[0]))
#endif
			{
				joyX=rX;
				joyY=-rY;
			}
			else
			{
				joyX=lX;
				joyY=-lY;
			}
		}
		if ((joyX*joyX + joyY*joyY) > joyDeadZoneSquared)
		{
			int *up = 0;
			int *down = 0;
			int *left = 0;
			int *right = 0;
#ifdef __SWITCH__
			if (mainMenu_customControls && !vkbd_mode && !(buttonStart[0] && triggerR[0]) && !singleJoycons)
#else
			if (mainMenu_customControls && !vkbd_mode && !(buttonStart[0] && triggerR[0]))
#endif
			{
				up = &stickUp[i];
				down = &stickDown[i];
				left = &stickLeft[i];
				right = &stickRight[i];
			} else
			{
				up = &dpadUp[i];
				down = &dpadDown[i];
				left = &dpadLeft[i];
				right = &dpadRight[i];
			}
			// upper right quadrant
			if (joyY>0 && joyX>0)
			{
				if (joyY>slope*joyX)
					*up = 1;
				if (joyX>slope*joyY)
					*right = 1;
			}
			// upper left quadrant
			else if (joyY>0 && joyX<=0)
			{
				if (joyY>slope*(-joyX))
					*up = 1;
				if ((-joyX)>slope*joyY)
					*left = 1;
			}
			// lower right quadrant
			else if (joyY<=0 && joyX>0)
			{
				if ((-joyY)>slope*joyX)
					*down = 1;
				if (joyX>slope*(-joyY))
					*right = 1;
			}
			// lower left quadrant
			else if (joyY<=0 && joyX<=0)
			{
				if ((-joyY)>slope*(-joyX))
					*down = 1;
				if ((-joyX)>slope*(-joyY))
					*left = 1;
			}
		}
	}

#ifdef USE_UAE4ALL_VKBD
	//no autofire when keyboard is displayed
	if (mainMenu_customAutofireButton && !vkbd_mode)
#else
	if (mainMenu_customAutofireButton)
#endif
	{
		int *autoButton;
		for (int i=0; i<nr_joysticks; i++)
		{
			int *autoButton;
			switch (mainMenu_customAutofireButton)
			{
				case 1: 
					autoButton = &buttonA[i];
					break;
				case 2:
					autoButton = &buttonY[i];
					break;
				case 3:
					autoButton = &buttonB[i];
					break;
				case 4:
					autoButton = &buttonX[i];
					break;
				case 5:
					autoButton = &triggerL[i];
					break;
				case 6:
					autoButton = &triggerR[i];
					break;
#ifdef __SWITCH__
				case 7:
					autoButton = &triggerL2[i];
					break;
				case 8:
					autoButton = &triggerR2[i];
					break;
#endif
			}
			if (*autoButton)
			{
				if (customAutofireDelay[i]>mainMenu_autofireRate)
				{
					*autoButton=1; // press button for one frame only
					customAutofireDelay[i]=0;
				}
				else
					*autoButton=0;
					customAutofireDelay[i]++;
			}
			else
				customAutofireDelay[i]=0;
		}
	}

	if(buttonSelect[0])
	{
		//re-center the Joysticks when the user opens the menu
		for (int i=0; i<nr_joysticks; i++)
		{
			switch (i)
			{	
				case 0:
					currentJoy = uae4all_joy0;
					break;
				case 1:
					currentJoy = uae4all_joy1;
					break;
				case 2:
					currentJoy = uae4all_joy2;
					break;
				case 3:
					currentJoy = uae4all_joy3;
					break;
				case 4:
					currentJoy = uae4all_joy4;
					break;
				case 5:
					currentJoy = uae4all_joy5;
					break;
				case 6:
					currentJoy = uae4all_joy6;
					break;
				case 7:
					currentJoy = uae4all_joy7;
					break;
			}
			lAnalogXCenter[i]=SDL_JoystickGetAxis(currentJoy, 0);
			lAnalogYCenter[i]=SDL_JoystickGetAxis(currentJoy, 1);
			rAnalogXCenter[i]=SDL_JoystickGetAxis(currentJoy, 2);
			rAnalogYCenter[i]=SDL_JoystickGetAxis(currentJoy, 3);
		}
		goMenu();
	}

#else
	dpadUp[0] = keystate[SDLK_UP];
	dpadDown[0] = keystate[SDLK_DOWN];
	dpadLeft[0] = keystate[SDLK_LEFT];
	dpadRight[0] = keystate[SDLK_RIGHT];
	buttonA[0] = keystate[SDLK_HOME];
	buttonB[0] = keystate[SDLK_END];
	buttonX[0] = keystate[SDLK_PAGEDOWN];
	buttonY[0] = keystate[SDLK_PAGEUP];
#ifndef ANDROIDSDL
	triggerL[0] = keystate[SDLK_RSHIFT];
	triggerR[0] = keystate[SDLK_RCTRL];
	buttonSelect[0] = keystate[SDLK_LCTRL];
	buttonStart[0] = keystate[SDLK_LALT];

	if(keystate[SDLK_LCTRL])
		goMenu();

	if(keystate[SDLK_F12])
		SDL_WM_ToggleFullScreen(prSDLScreen);
#else
	triggerL[0] = keystate[SDLK_F13];
	triggerR[0] = keystate[SDLK_RCTRL];
	buttonSelect[0] = keystate[SDLK_F12];
	buttonStart[0] = keystate[SDLK_F11];

	if(keystate[SDLK_F12])
		goMenu();
#endif
#endif // __PSP2__

#ifdef ANDROIDSDL

#ifdef USE_UAE4ALL_VKBD
	//textUI virtual keyboard via F15 
	if(keystate[SDLK_F15])
	{
		if(!justLK)
		{
			sleep(1);
			vkbd_mode = !vkbd_mode;
			justLK=1;
		}
	}
	else if(justLK)
		justLK=0;
	//Quick Switch - textUI virtual keyboard via buttonB+buttonY
	if((mainMenu_quickSwitch!=0) && buttonB[0] && buttonY[0])
	{
		if(!justLK)
		{
			sleep(1);
			vkbd_mode = !vkbd_mode;
			justLK=1;
		}
	}
	else if(justLK)
		justLK=0;
#endif
	// Quick Switch - screen lowres/hires
	if (((mainMenu_quickSwitch==1) && buttonB[0] && dpadUp[0]) || ((mainMenu_quickSwitch==2) && buttonY[0] && dpadUp[0]))
	{
	  if (visibleAreaWidth==320) {
		visibleAreaWidth=640;
		mainMenu_displayHires=1;
	  }
	  else if (visibleAreaWidth==640) {
		visibleAreaWidth=320;
		mainMenu_displayHires=0;
		}
		getChanges();
		check_all_prefs();
		update_display();
	}
	// Quick Switch - screen height
	if (((mainMenu_quickSwitch==1) && buttonB[0] && dpadDown[0]) || ((mainMenu_quickSwitch==2) && buttonY[0] && dpadDown[0]))
	{
	  if (mainMenu_displayedLines==200)
		mainMenu_displayedLines=216;
	  else if (mainMenu_displayedLines==216)
		mainMenu_displayedLines=240;
	  else if (mainMenu_displayedLines==240)
		mainMenu_displayedLines=256;
	  else if (mainMenu_displayedLines==256)
		mainMenu_displayedLines=262;
	  else if (mainMenu_displayedLines==262)
		mainMenu_displayedLines=270;
	  else if (mainMenu_displayedLines==270)
		mainMenu_displayedLines=200;
		getChanges();
		check_all_prefs();
		update_display();
	}
	// Quick Switch - save state
	if (((mainMenu_quickSwitch==1) && buttonB[0] && dpadLeft[0]) || ((mainMenu_quickSwitch==2) && buttonY[0] && dpadLeft[0]))
	{	
	  keystate[SDLK_s]=0;
	  savestate_state = STATE_DOSAVE;
	}
	// Quick Switch - restore state
	if (((mainMenu_quickSwitch==1) && buttonB[0] && dpadRight[0]) || ((mainMenu_quickSwitch==2) && buttonY[0] && dpadRight[0]))
	{
		extern char *savestate_filename;
		FILE *f=fopen(savestate_filename, "rb");
		keystate[SDLK_l]=0;
		if(f)
		{
			fclose(f);
			savestate_state = STATE_DORESTORE;
		}
		else
			gui_set_message("Failed: Savestate not found", 100);
	}
#endif 		
	
#ifdef USE_UAE4ALL_VKBD
if(!vkbd_mode)
#endif
{
#if defined(__PSP2__) || defined(__SWITCH__)
	if(buttonStart[0] && triggerL[0]) //toggle custom control config 1-3
	{
		if (can_change_custom_controlSet)
		{
			if (mainMenu_customControls)
			{
				mainMenu_custom_controlSet++;
				if (mainMenu_custom_controlSet>=MAX_NUM_CUSTOM_PRESETS)
					mainMenu_custom_controlSet = 0;
				// zero triggerL before the control config switches
				if(mainMenu_custom_L[0] == -1) buttonstate[0]=0;
				else if(mainMenu_custom_L[0] == -2) buttonstate[2]=0;
				else if(mainMenu_custom_L[0] > 0)
				{		
					getMapping(mainMenu_custom_L[0]);
					uae4all_keystate[customKey] = 0;
					record_key((customKey << 1) | 1);
				}
				remap_custom_controls();
				can_change_custom_controlSet = 0;
			}
		}
	}
	else if (!can_change_custom_controlSet)
	{
		can_change_custom_controlSet = 1;
	}
	else if(buttonStart[0] && triggerR[0])
#else
	//L + R
	if(triggerL[0] && triggerR[0])
#endif
	{
		//up
		if(dpadUp[0])
		{
			moveVertical(1);
			moved_y += 2;
		}
		//down
		else if(dpadDown[0])
		{
			moveVertical(-1);
			moved_y -= 2;
		}
		//left
		else if(dpadLeft[0])
		{
#if defined(__PSP2__) || defined(__SWITCH__)
// Change zoom:
// quickSwitch resolution presets
			if (can_change_quickSwitchModeID)
			{			
				if (quickSwitchModeID==sizeof(quickSwitchModes)/sizeof(quickSwitchModes[0])-1)
				{
					quickSwitchModeID=0;
				}
				else
				{
					quickSwitchModeID++;
				}
				mainMenu_displayedLines = 
					quickSwitchModes[quickSwitchModeID].num_lines;	
				moveY = 
					quickSwitchModes[quickSwitchModeID].top_pos;
				getChanges();
				check_all_prefs();
				update_display();
				can_change_quickSwitchModeID=0;
			}
#else
			screenWidth -=10;
			if(screenWidth<200)
				screenWidth = 200;
			update_display();
#endif
		}
		//right
		else if(dpadRight[0])
		{
#if defined(__PSP2__) || defined(__SWITCH__)
			if (can_change_quickSwitchModeID)
			{
				if (quickSwitchModeID==0)
				{
					quickSwitchModeID=sizeof(quickSwitchModes)/sizeof(quickSwitchModes[0])-1;
				}
				else
				{
					quickSwitchModeID--;
				}
				mainMenu_displayedLines = 
					quickSwitchModes[quickSwitchModeID].num_lines;	
				moveY = 
					quickSwitchModes[quickSwitchModeID].top_pos;
				getChanges();
				check_all_prefs();
				update_display();
				can_change_quickSwitchModeID = 0;
			}
#else
			screenWidth +=10;
			if(screenWidth>800)
				screenWidth = 800;
			update_display();
#endif
		}
		else if (!can_change_quickSwitchModeID)
		{
			can_change_quickSwitchModeID = 1;
		}
#if !defined(__PSP2__) && !defined(__SWITCH__)
		//1
		else if(keystate[SDLK_1])
		{
			SetPresetMode((presetModeId / 10) * 10 + 0);
			update_display();
		}
		//2
		else if(keystate[SDLK_2])
		{
			SetPresetMode((presetModeId / 10) * 10 + 1);
			update_display();
		}
		//3
		else if(keystate[SDLK_3])
		{
			SetPresetMode((presetModeId / 10) * 10 + 2);
			update_display();
		}
		//4
		else if(keystate[SDLK_4])
		{
			SetPresetMode((presetModeId / 10) * 10 + 3);
			update_display();
		}
		//5
		else if(keystate[SDLK_5])
		{
			SetPresetMode((presetModeId / 10) * 10 + 4);
			update_display();
		}
		//6
		else if(keystate[SDLK_6])
		{
			SetPresetMode((presetModeId / 10) * 10 + 5);
			update_display();
		}
		//7
		else if(keystate[SDLK_7])
		{
			SetPresetMode((presetModeId / 10) * 10 + 6);
			update_display();
		}
		//8
		else if(keystate[SDLK_8])
		{
			SetPresetMode((presetModeId / 10) * 10 + 7);
			update_display();
		}
		//9
		else if(keystate[SDLK_9])
		{
			if(mainMenu_displayedLines > 100)
				mainMenu_displayedLines--;
			update_display();
		}
		//0
		else if(keystate[SDLK_0])
		{
			if(mainMenu_displayedLines < 286)
				mainMenu_displayedLines++;
			update_display();
		}
		else if(keystate[SDLK_w])
		{
			// Change width
			if(presetModeId < 50)
				SetPresetMode(presetModeId + 10);
			else
				SetPresetMode(presetModeId - 50);
			update_display();
		}
#ifdef WITH_TESTMODE
		else if(keystate[SDLK_t])
		{
			if(no_limiter)
				no_limiter = 0;
			else
				no_limiter = 1;
			char value[8];
			snprintf(value, 8, "%d", no_limiter ? 0 : 1);
#ifndef WIN32
			setenv("SDL_OMAP_VSYNC",value,1);
#endif
			update_display();
		}		
#endif
	}

	else if(triggerL[0])
	{
		//cutRight
		if(keystate[SDLK_COMMA] && mainMenu_cutLeft > 0)
		{
			mainMenu_cutLeft--;
			update_display();
		}
		else if(keystate[SDLK_PERIOD] && mainMenu_cutLeft < 100)
		{
			mainMenu_cutLeft++;
			update_display();
		}
		else if(keystate[SDLK_a])
		{
			keystate[SDLK_a]=0;
			mainMenu_CPU_speed == 3 ? mainMenu_CPU_speed = 0 : mainMenu_CPU_speed++;
		}
		else if(keystate[SDLK_c])
		{
			keystate[SDLK_c]=0;
			mainMenu_customControls = !mainMenu_customControls;
		}
		else if(keystate[SDLK_d])
		{
			keystate[SDLK_d]=0;
			mainMenu_showStatus = !mainMenu_showStatus;
		}
		else if(keystate[SDLK_f])
		{
			keystate[SDLK_f]=0;
			mainMenu_frameskip ? mainMenu_frameskip = 0 : mainMenu_frameskip = 1;
			getChanges();
			check_all_prefs();
		}

		//Q key
		if(keystate[SDLK_q])
		{
			if(!justPressedQ)
			{
				uae4all_keystate[AK_NPMUL] = 1;
				record_key(AK_NPMUL << 1);
				uae4all_keystate[AK_F10] = 1;
				record_key(AK_F10 << 1);				
				justPressedQ=1;
			}
		}
		else if(justPressedQ)
		{
			uae4all_keystate[AK_NPMUL] = 0;
			record_key((AK_NPMUL << 1) | 1);
			uae4all_keystate[AK_F10] = 0;
			record_key((AK_F10 << 1) | 1);
			justPressedQ=0;
		}
	}

	//autofire on/off
	else if(triggerR[0])
	{
		//(Y) button
		if(buttonY[0])
		{
			if(!justPressedY[0])
			{
				//autofire on/off
				switch_autofire = !switch_autofire;
				justPressedY[0]=1;
			}
		}
		else if(justPressedY[0])
			justPressedY[0]=0;

		//Q key
		if(keystate[SDLK_q])
		{
			if(!justPressedQ)
			{
				uae4all_keystate[AK_NPMUL] = 1;
				record_key(AK_NPMUL << 1);
				uae4all_keystate[AK_F10] = 1;
				record_key(AK_F10 << 1);				
				justPressedQ=1;
			}
		}
		else if(justPressedQ)
		{
			uae4all_keystate[AK_NPMUL] = 0;
			record_key((AK_NPMUL << 1) | 1);
			uae4all_keystate[AK_F10] = 0;
			record_key((AK_F10 << 1) | 1);
			justPressedQ=0;
		}

		//cutRight
		if(keystate[SDLK_COMMA] && mainMenu_cutRight > 0)
		{
			mainMenu_cutRight--;
			update_display();
		}
		else if(keystate[SDLK_PERIOD] && mainMenu_cutRight < 100)
		{
			mainMenu_cutRight++;
			update_display();
		}
#endif //!defined(__PSP2__) && !defined(__SWITCH__)
	}
	if (mainMenu_customControls && !gp2xMouseEmuOn && !gp2xButtonRemappingOn)
	{
		int quickSave = 0;
		int quickLoad = 0;
		int *button;
		int *justPressed;
		int *mainMenu_custom;
		for (int i = 0; i < nr_joysticks; i++)
		{		
			if(mainMenu_custom_dpad == 0) // always true on Vita
			{
#ifdef __SWITCH__
				for (int j = 0; j < 18; j++)
#else				
				for (int j = 0; j < 14; j++)
#endif
				{
					switch (j)
					{
						case 0:
							//UP
							button = &(dpadUp[i]);
							justPressed = &(justMovedUp[i]);
							mainMenu_custom = &(mainMenu_custom_up[i]);
							break;
						case 1:
							//DOWN
							button = &(dpadDown[i]);
							justPressed = &(justMovedDown[i]);
							mainMenu_custom = &(mainMenu_custom_down[i]);
							break;
						case 2:
							//LEFT
							button = &(dpadLeft[i]);
							justPressed = &(justMovedLeft[i]);
							mainMenu_custom = &(mainMenu_custom_left[i]);
							break;
						case 3:
							//RIGHT
							button = &(dpadRight[i]);
							justPressed = &(justMovedRight[i]);
							mainMenu_custom = &(mainMenu_custom_right[i]);
							break;
						case 4:
							//STICK UP
							button = &(stickUp[i]);
							justPressed = &(justMovedStickUp[i]);
							mainMenu_custom = &(mainMenu_custom_stickup[i]);
							break;
						case 5:
							//STICK DOWN
							button = &(stickDown[i]);
							justPressed = &(justMovedStickDown[i]);
							mainMenu_custom = &(mainMenu_custom_stickdown[i]);
							break;
						case 6:
							//STICK LEFT
							button = &(stickLeft[i]);
							justPressed = &(justMovedStickLeft[i]);
							mainMenu_custom = &(mainMenu_custom_stickleft[i]);
							break;
						case 7:
							//STICK RIGHT
							button = &(stickRight[i]);
							justPressed = &(justMovedStickRight[i]);
							mainMenu_custom = &(mainMenu_custom_stickright[i]);
							break;
						case 8:
							//(A)
							button = &(buttonA[i]);
							justPressed = &(justPressedA[i]);
							mainMenu_custom = &(mainMenu_custom_A[i]);
							break;
						case 9:
							//(B)
							button = &(buttonB[i]);
							justPressed = &(justPressedB[i]);
							mainMenu_custom = &(mainMenu_custom_B[i]);
							break;
						case 10:
							//(X)
							button = &(buttonX[i]);
							justPressed = &(justPressedX[i]);
							mainMenu_custom = &(mainMenu_custom_X[i]);
							break;
						case 11:
							//(Y)
							button = &(buttonY[i]);
							justPressed = &(justPressedY[i]);
							mainMenu_custom = &(mainMenu_custom_Y[i]);
							break;
						case 12:
							//(L)
							button = &(triggerL[i]);
							justPressed = &(justPressedL[i]);
							mainMenu_custom = &(mainMenu_custom_L[i]);
							break;
						case 13:
							//(R)
							button = &(triggerR[i]);
							justPressed = &(justPressedR[i]);
							mainMenu_custom = &(mainMenu_custom_R[i]);
							break;
#ifdef __SWITCH__
						case 14:
							//(L2)
							button = &(triggerL2[i]);
							justPressed = &(justPressedL2[i]);
							mainMenu_custom = &(mainMenu_custom_L2[i]);
							break;
						case 15:
							//(R2)
							button = &(triggerR2[i]);
							justPressed = &(justPressedR2[i]);
							mainMenu_custom = &(mainMenu_custom_R2[i]);
							break;
						case 16:
							//(L3)
							button = &(triggerL3[i]);
							justPressed = &(justPressedL3[i]);
							mainMenu_custom = &(mainMenu_custom_L3[i]);
							break;
						case 17:
							//(R3)
							button = &(triggerR3[i]);
							justPressed = &(justPressedR3[i]);
							mainMenu_custom = &(mainMenu_custom_R3[i]);
							break;
#endif
						default:
							break;
					}

					if (*button)
					{
						if (!(*justPressed))
						{
							
							if (*mainMenu_custom == -1) buttonstate[0]=1;
							else if (*mainMenu_custom == -2) buttonstate[2]=1;
							else if (*mainMenu_custom == -27) quickSave=1;
							else if (*mainMenu_custom == -28) quickLoad=1;
							else if (*mainMenu_custom > 0)
							{
								getMapping(*mainMenu_custom);
								uae4all_keystate[customKey] = 1;
								record_key(customKey << 1);
							}
							*justPressed=1;
						}
					}
					else if (*justPressed)
					{
						if (*mainMenu_custom == -1) buttonstate[0]=0;
						else if (*mainMenu_custom == -2) buttonstate[2]=0;
						else if (*mainMenu_custom > 0)
						{		
							getMapping(*mainMenu_custom);
							uae4all_keystate[customKey] = 0;
							record_key((customKey << 1) | 1);
						}
						*justPressed=0;
					}
				} // end of buttons loop
			}
		}//end of nr_joysticks loop
		if (quickSave)
		{
			make_savestate_filenames(savestate_filename,screenshot_filename);
			savestate_state = STATE_DOSAVE;
		} 
		else if (quickLoad) 
		{
			make_savestate_filenames(savestate_filename,screenshot_filename);
			FILE *f=fopen(savestate_filename, "rb");
			keystate[SDLK_l]=0;
			if(f)
			{
				fclose(f);
				savestate_state = STATE_DORESTORE;
			}
		}
	}
	// on Vita/Switch: gp2xMouseEmuOn = 0, and gp2xButtonRemappingOn = 0;
	else if(!gp2xMouseEmuOn)
	{
		//DPad = arrow keys in stylus-mode
		if(gp2xButtonRemappingOn)
		{
			//dpad up
			if (dpadUp[0])
			{
				if(!justMovedUp[0])
				{
					//left and right mouse-buttons down
					buttonstate[0] = 1;
					buttonstate[2] = 1;
					stylusClickOverride = 1;
					justMovedUp[0]=1;
				}
			}
			else if(justMovedUp[0])
			{
				//left and right mouse-buttons up
				buttonstate[0] = 0;
				buttonstate[2] = 0;
				stylusClickOverride = 0;
				justMovedUp[0]=0;
			}
			//dpad down
			if (dpadDown[0])
			{
				if(!justMovedDown[0])
				{
					//no clicks with stylus now
					stylusClickOverride=1;
					justMovedDown[0]=1;
				}
			}
			else if(justMovedDown[0])
			{
				//clicks active again
				stylusClickOverride=0;
				justMovedDown[0]=0;
			}
			//dpad left
			if (dpadLeft[0])
			{
				if(!justMovedLeft[0])
				{
					//left mouse-button down
					buttonstate[0] = 1;
					stylusClickOverride = 1;
					justMovedLeft[0]=1;
				}
			}
			else if(justMovedLeft[0])
			{
				//left mouse-button up
				buttonstate[0] = 0;
				stylusClickOverride = 0;
				justMovedLeft[0]=0;
			}
			//dpad right
			if (dpadRight[0])
			{
				if(!justMovedRight[0])
				{
					//right mouse-button down
					buttonstate[2] = 1;
					stylusClickOverride = 1;
					justMovedRight[0]=1;
				}
			}
			else if(justMovedRight[0])
			{
				//right mouse-button up
				buttonstate[2] = 0;
				stylusClickOverride = 0;
				justMovedRight[0]=0;
			}
			//L + up
			if(triggerL[0] && dpadUp[0])
				stylusAdjustY-=2;
			//L + down
			if(triggerL[0] && dpadDown[0])
				stylusAdjustY+=2;
			//L + left
			if(triggerL[0] && dpadLeft[0])
				stylusAdjustX-=2;
			//L + right
			if(triggerL[0] && dpadRight[0])
				stylusAdjustX+=2;
		}
		//R-trigger in joystick mode
		else if(triggerR[0])
		{
			//(A) button
			if(buttonA[0])
			{
				if(!justPressedA[0])
				{
					//CTRL
					uae4all_keystate[AK_CTRL] = 1;
					record_key(AK_CTRL << 1);
					justPressedA[0]=1;
				}
			}
			else if(justPressedA[0])
			{
				uae4all_keystate[AK_CTRL] = 0;
				record_key((AK_CTRL << 1) | 1);
				justPressedA[0]=0;
			}
			//(B) button
			if(buttonB[0])
			{
				if(!justPressedB[0])
				{
					//left ALT
					uae4all_keystate[AK_LALT] = 1;
					record_key(AK_LALT << 1);
					justPressedB[0]=1;
				}
			}
			else if(justPressedB[0])
			{
				uae4all_keystate[AK_LALT] = 0;
				record_key((AK_LALT << 1) | 1);
				justPressedB[0]=0;
			}
			//(X) button
			if(buttonX[0])
			{
				if(!justPressedX[0])
				{
					//HELP
					uae4all_keystate[AK_HELP] = 1;
					record_key(AK_HELP << 1);
					justPressedX[0]=1;
				}
			}
			else if(justPressedX[0])
			{
				//HELP
				uae4all_keystate[AK_HELP] = 0;
				record_key((AK_HELP << 1) | 1);
				justPressedX[0]=0;
			}
		}
		else if(triggerL[0])
		{
			//(A) button
			if(buttonA[0])
			{
				if(!justPressedA[0])
				{
					//left mouse-button down
					buttonstate[0] = 1;
					justPressedA[0]=1;
				}
			}
			else if(justPressedA[0])
			{
				//left mouse-button up
				buttonstate[0] = 0;
				justPressedA[0]=0;
			}
			//(B) button
			if(buttonB[0])
			{
				if(!justPressedB[0])
				{
					//right mouse-button down
					buttonstate[2] = 1;
					justPressedB[0]=1;
				}
			}
			else if(justPressedB[0])
			{
				//right mouse-button up
				buttonstate[2] = 0;
				justPressedB[0]=0;
			}
		}
		else if(mainMenu_joyConf<2)
		{
			if(buttonY[0])
			{
				if(!justPressedY[0])
				{
					//SPACE
					uae4all_keystate[AK_SPC] = 1;
					record_key(AK_SPC << 1);
					justPressedY[0]=1;
				}
			}
			else if(justPressedY[0])
			{
				//SPACE
				uae4all_keystate[AK_SPC] = 0;
				record_key((AK_SPC << 1) | 1);
				justPressedY[0]=0;
			}
		}
	}
	else
	{
		if(buttonA[0])
		{
			if(!justPressedA[0])
			{
				//left mouse-button down
				buttonstate[0] = 1;
				justPressedA[0]=1;
			}
		}
		else if(justPressedA[0])
		{
			//left mouse-button up
			buttonstate[0] = 0;
			justPressedA[0]=0;
		}
		//(B) button
		if(buttonB[0])
		{
			if(!justPressedB[0])
			{
				//left mouse-button down
				buttonstate[2] = 1;
				justPressedB[0]=1;
			}
		}
		else if(justPressedB[0])
		{
			//left mouse-button up
			buttonstate[2] = 0;
			justPressedB[0]=0;
		}
		if(buttonY[0])
		{
			if(!justPressedY[0])
			{
				//SPACE
				uae4all_keystate[AK_SPC] = 1;
				record_key(AK_SPC << 1);
				justPressedY[0]=1;
			}
		}
		else if(justPressedY[0])
		{
			//SPACE
			uae4all_keystate[AK_SPC] = 0;
			record_key((AK_SPC << 1) | 1);
			justPressedY[0]=0;
		}
		if(dpadLeft[0])
		{
			if(!justMovedLeft[0])
			{
				//left ALT
				uae4all_keystate[0x64] = 1;
				record_key(0x64 << 1);
				justMovedLeft[0]=1;
			}
		}
		else if(justMovedLeft[0])
		{
			//left ALT
			uae4all_keystate[0x64] = 0;
			record_key((0x64 << 1) | 1);
			justMovedLeft[0]=0;
		}
		if(dpadRight[0])
		{
			if(!justMovedRight[0])
			{
				//left ALT
				uae4all_keystate[0x64] = 1;
				record_key(0x64 << 1);
				justMovedRight[0]=1;
			}
		}
		else if(justMovedRight[0])
		{
			//left ALT
			uae4all_keystate[0x64] = 0;
			record_key((0x64 << 1) | 1);
			justMovedRight[0]=0;
		}
	}

	if(!mainMenu_customControls && triggerR[0] && !(buttonStart[0]))
	{
		//R+dpad = arrow keys in joystick mode
		//dpad up
		if(dpadUp[0])
		{
			if(!justMovedUp[0])
			{
				//arrow up
				uae4all_keystate[0x4C] = 1;
				record_key(0x4C << 1);
				justMovedUp[0]=1;
			}
		}
		else if(justMovedUp[0])
		{
			//arrow up
			uae4all_keystate[0x4C] = 0;
			record_key((0x4C << 1) | 1);
			justMovedUp[0]=0;
		}
		//dpad down
		if(dpadDown[0])
		{
			if(!justMovedDown[0])
			{
				//arrow down
				uae4all_keystate[0x4D] = 1;
				record_key(0x4D << 1);
				justMovedDown[0]=1;
			}
		}
		else if(justMovedDown[0])
		{
			//arrow down
			uae4all_keystate[0x4D] = 0;
			record_key((0x4D << 1) | 1);
			justMovedDown[0]=0;
		}
		//dpad left
		if(dpadLeft[0])
		{
			if(!justMovedLeft[0])
			{
				//arrow left
				uae4all_keystate[0x4F] = 1;
				record_key(0x4F << 1);
				justMovedLeft[0]=1;
			}
		}
		else if(justMovedLeft[0])
		{
			//arrow left
			uae4all_keystate[0x4F] = 0;
			record_key((0x4F << 1) | 1);
			justMovedLeft[0]=0;
		}
		//dpad right
		if (dpadRight[0])
		{
			if(!justMovedRight[0])
			{
				//arrow right
				uae4all_keystate[0x4E] = 1;
				record_key(0x4E << 1);
				justMovedRight[0]=1;
			}
		}
		else if(justMovedRight[0])
		{
			//arrow right
			uae4all_keystate[0x4E] = 0;
			record_key((0x4E << 1) | 1);
			justMovedRight[0]=0;
		}
	}
	
#if defined(__PSP2__) || defined(__SWITCH__)
	//VITA Controls: If not using custom controls, use L=right mouse, R=left mouse 
	//because analog stick = mouse movement is always on for Vita
	if(!mainMenu_customControls)
	{
		//(R) button
		if(triggerR[0])
		{
			if(!justPressedR[0])
			{
				//left mouse-button down
				buttonstate[0] = 1;
				justPressedR[0]=1;
			}
		}
		else if(justPressedR[0])
		{
			//left mouse-button up
			buttonstate[0] = 0;
			justPressedR[0]=0;
		}
		//(L) button
		if(triggerL[0])
		{
			if(!justPressedL[0])
			{
				//right mouse-button down
				buttonstate[2] = 1;
				justPressedL[0]=1;
			}
		}
		else if(justPressedL[0])
		{
			//right mouse-button up
			buttonstate[2] = 0;
			justPressedL[0]=0;
		}
	}
#endif // __PSP2__

} // if(!vkbd_mode)

#ifdef USE_UAE4ALL_VKBD
#if defined(__PSP2__) || defined(__SWITCH__)
	//on Vita, Start brings up the  virtual keyboard, but Trigger R + Start is used for
	//quickswitch resolution etc. and Trigger L + Start is used for switching between
	//custom control configs
	if(buttonStart[0] && !triggerR[0] && !triggerL[0])
#else
	//L+K: virtual keyboard
	if(triggerL[0] && keystate[SDLK_k])
#endif
	{
		if(!justLK)
		{
			vkbd_mode = !vkbd_mode;
			justLK=1;
		}
	}
	else if(justLK)
		justLK=0;
#endif

#if !defined(__PSP2__) && !defined(__SWITCH__)
	if(triggerL[0] && keystate[SDLK_s])
	{
		keystate[SDLK_s]=0;
		savestate_state = STATE_DOSAVE;
	}
	if(triggerL[0] && keystate[SDLK_l])
	{
		extern char *savestate_filename;
		FILE *f=fopen(savestate_filename, "rb");
		keystate[SDLK_l]=0;
		if(f)
		{
			fclose(f);
			savestate_state = STATE_DORESTORE;
		}
		else
			gui_set_message("Failed: Savestate not found", 100);
	}
#endif

#ifdef USE_UAE4ALL_VKBD
	if (vkbd_key!=KEYCODE_NOTHING) // This means key was selected by user. We cannot test for zero, because that is a valid Amiga keycode
	{
		if (vkbd_key >= 0)
		{
			// Handle all sticky keys (release and press) here up front
			bool sticky=false;
			for (int i=0; i<NUM_STICKY; i++) 
			{
				if (vkbd_key == vkbd_sticky_key[i].code)
				{
					if ((vkbd_sticky_key[i].stuck) && uae4all_keystate[vkbd_sticky_key[i].code] == 0)
					{
						uae4all_keystate[vkbd_sticky_key[i].code]=1;
						record_key(vkbd_sticky_key[i].code<<1);
					}
					if (!(vkbd_sticky_key[i].stuck) && uae4all_keystate[vkbd_sticky_key[i].code] == 1)
					{
						uae4all_keystate[vkbd_sticky_key[i].code]=0;
						record_key((vkbd_sticky_key[i].code<<1)|1);
					}
					sticky=true; // a sticky key was pressed and handled. We are done.
					break;
				}
			}
			if (!sticky && vkbd_keysave==KEYCODE_NOTHING) // a non-sticky key was pressed and previous key was released. Press the new key
			{
				vkbd_keysave=vkbd_key; // remember which key we are pressing so we can release it later
				if (!uae4all_keystate[vkbd_keysave])
				{
					uae4all_keystate[vkbd_keysave]=1;
					record_key(vkbd_keysave<<1);
				}
			}
		} else if (vkbd_key == KEYCODE_STICKY_RESET) // the special button to reset all sticky keys was pressed
		{
			for (int i=0; i<NUM_STICKY; i++) 
			{
				if (uae4all_keystate[vkbd_sticky_key[i].code] == 1)
				{
					uae4all_keystate[vkbd_sticky_key[i].code]=0;
					record_key((vkbd_sticky_key[i].code<<1)|1);
				}
			}
		}
	}
	else if (vkbd_keysave!=KEYCODE_NOTHING) // some non-sticky key was released
	{
		if (vkbd_keysave >= 0) //handle key release 
		{
			uae4all_keystate[vkbd_keysave]=0;
			record_key((vkbd_keysave << 1) | 1);
		}
		vkbd_keysave=KEYCODE_NOTHING;
	}
#endif
}

void gui_set_message(const char *msg, int t)
{
	return;

	show_message=t;
	strncpy(show_message_str, msg, 36);
}

void gui_show_window_bar(int per, int max, int case_title)
{
	return;

	char *title;
	if (case_title)
		title=(char*)"  Restore State";
	else
		title=(char*)"  Save State";
	_text_draw_window_bar(prSDLScreen,80,64,172,48,per,max,title);
	SDL_Flip(prSDLScreen);
}
