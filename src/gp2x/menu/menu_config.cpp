#define _MENU_CONFIG_CPP

#include "sysconfig.h"
#include "sysdeps.h"
#include "config.h"
#include "menu.h"
#include "menu_config.h"
#include "autoconf.h"
#include "options.h"
#include "gui.h"
#include "sound.h"
#include "custom.h"
#include "gp2x.h"
#include "cfgfile.h"

extern int kickstart;
extern int blitter_in_partial_mode;
extern int sound_rate;
extern int skipintro;
extern int screenWidth;
extern int moveX;
extern int moveY;


#ifdef __SWITCH__
#include "switch_kbd.h"
#endif

#ifdef __PSP2__
#include "psp2_kbdvita.h"
#endif

#if !( defined(PANDORA) || defined(ANDROIDSDL) )
extern int timeslice_mode;
#endif
extern char launchDir[300];
extern char currentDir[300];
extern int nr_drives;
#if defined(__PSP2__) || defined(__SWITCH__) 
static char config_filename[255] = "uae4all.cfg";
#else
extern char *config_filename;
#endif

extern void extractFileName(char * str,char *buffer);


char filename0[256] = "";
char filename1[256] = "";
char filename2[256] = "";
char filename3[256] = "";

char config_load_filename[300] = "";

int mainMenu_chipMemory = DEFAULT_CHIPMEM_SELECT;
int mainMenu_slowMemory = 0;	/* off */
int mainMenu_fastMemory = 0;	/* off */

int mainMenu_bootHD = DEFAULT_ENABLE_HD;
int mainMenu_filesysUnits = 0;

int mainMenu_drives = DEFAULT_DRIVES;
int mainMenu_floppyspeed = 100;
int mainMenu_CPU_model = DEFAULT_CPU_MODEL;
int mainMenu_chipset = DEFAULT_CHIPSET_SELECT;
int mainMenu_spriteCollisions = DEFAULT_SPRITECOLLISIONS;
int mainMenu_sound = DEFAULT_SOUND;
int mainMenu_soundStereo = 1; // Default is stereo
int mainMenu_soundStereoSep = 3; // Default is 100% stereo separation
int mainMenu_CPU_speed = 0;

int mainMenu_cpuSpeed = 600;

int mainMenu_joyConf = 0;
int mainMenu_joyPort = 2; // Default to port 1 on Vita because mouse is always on.
int mainMenu_autofireRate = 8;
int mainMenu_customAutofireButton = 0;
int mainMenu_showStatus = DEFAULT_STATUSLN;
int mainMenu_background = 0;
int mainMenu_font = 0;
int mainMenu_mouseMultiplier = DEFAULT_MOUSEMULTIPLIER;
int mainMenu_mouseEmulation = 1;
int mainMenu_stylusOffset = 0;
int mainMenu_tapDelay = 10;
int mainMenu_customControls = 0;
int mainMenu_custom_currentlyEditingControllerNr = 0;
int mainMenu_custom_dpad = 0;
int mainMenu_custom_up[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_down[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_left[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_right[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_stickup[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_stickdown[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_stickleft[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_stickright[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_A[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_B[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_X[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_Y[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_L[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_R[MAX_NUM_CONTROLLERS] = { };
#ifdef __SWITCH__
int mainMenu_custom_L2[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_R2[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_L3[MAX_NUM_CONTROLLERS] = { };
int mainMenu_custom_R3[MAX_NUM_CONTROLLERS] = { };
#endif
#if defined(__PSP2__) || defined(__SWITCH__)
int mainMenu_custom_controlSet = 0; //This controls which custom config is used
int mainMenu_customPreset_up[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_down[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_left[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_right[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_stickup[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_stickdown[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_stickleft[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_stickright[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_A[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_B[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_X[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_Y[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_L[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_R[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
#ifdef __SWITCH__
int mainMenu_customPreset_L2[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_R2[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_L3[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
int mainMenu_customPreset_R3[MAX_NUM_CUSTOM_PRESETS][MAX_NUM_CONTROLLERS] = { };
#endif
#endif
int mainMenu_autofire = DEFAULT_AUTOFIRE;

int mainMenu_displayedLines = 240;
int mainMenu_displayHires = 0;
char presetMode[20] = "320x240 upscaled";
int presetModeId = 2;
int mainMenu_cutLeft = 0;
int mainMenu_cutRight = 0;
int mainMenu_ntsc = DEFAULT_NTSC;
int mainMenu_frameskip = 0;
int mainMenu_vkbdLanguage = 0; //Default is US Keyboard
int mainMenu_vkbdStyle = 0; //Default is original style
int visibleAreaWidth = 320;


int saveMenu_n_savestate = 0;

#if defined(__PSP2__) || defined(__SWITCH__)
#if defined(__SWITCH__)
int mainMenu_shader = 1;
#else
int mainMenu_shader = 5;
#endif
int mainMenu_leftStickMouse = 0;
int mainMenu_touchControls = 1;
int mainMenu_deadZone = 1000;
#endif
#ifdef __SWITCH__
int mainMenu_swapAB = DEFAULT_SWAPAB;
int mainMenu_singleJoycons = DEFAULT_SINGLEJOYCONS;
#endif

// The following params in use, but can't be changed with gui
int mainMenu_autosave = DEFAULT_AUTOSAVE;
int mainMenu_button1 = GP2X_BUTTON_X;
int mainMenu_button2 = GP2X_BUTTON_A;
int mainMenu_autofireButton1 = GP2X_BUTTON_B;
int mainMenu_jump = -1;

// The following params not in use, but stored to write them back to the config file
int gp2xClockSpeed = -1;
int mainMenu_scanlines = 0;
int mainMenu_enableScreenshots = DEFAULT_ENABLESCREENSHOTS;
int mainMenu_enableScripts = DEFAULT_ENABLESCRIPTS;

#ifdef ANDROIDSDL
int mainMenu_onScreen = 1;
int mainMenu_onScreen_textinput = 1;
int mainMenu_onScreen_dpad = 1;
int mainMenu_onScreen_button1 = 1;
int mainMenu_onScreen_button2 = 1;
int mainMenu_onScreen_button3 = 1;
int mainMenu_onScreen_button4 = 1;
int mainMenu_onScreen_button5 = 0;
int mainMenu_onScreen_button6 = 0;
int mainMenu_custom_position = 0;
int mainMenu_pos_x_textinput = 0;
int mainMenu_pos_y_textinput = 0;
int mainMenu_pos_x_dpad = 4;
int mainMenu_pos_y_dpad = 215;
int mainMenu_pos_x_button1 = 430;
int mainMenu_pos_y_button1 = 286;
int mainMenu_pos_x_button2 = 378;
int mainMenu_pos_y_button2 = 286;
int mainMenu_pos_x_button3 = 430;
int mainMenu_pos_y_button3 = 214;
int mainMenu_pos_x_button4 = 378;
int mainMenu_pos_y_button4 = 214;
int mainMenu_pos_x_button5 = 430;
int mainMenu_pos_y_button5 = 142;
int mainMenu_pos_x_button6 = 378;
int mainMenu_pos_y_button6 = 142;
float mainMenu_button_size = 1.0;
int menuLoad_extfilter=1;
int mainMenu_quickSwitch=0;
int mainMenu_FloatingJoystick=0;
#endif
#if defined(ANDROIDSDL) || defined(AROS)
int mainMenu_vsync=0;
#endif
char custom_kickrom[256] = "./kick.rom\0";
int mainMenu_useSavesFolder = DEFAULT_USESAVESFOLDER;

void SetDefaultMenuSettings(int general)
{
    mainMenu_chipMemory = DEFAULT_CHIPMEM_SELECT;
    mainMenu_slowMemory = 0;	/* off */
    mainMenu_fastMemory = 0;	/* off */
    UpdateMemorySettings();

	if(general < 2) 
	{
		mainMenu_bootHD=DEFAULT_ENABLE_HD;
		kill_hd_configs();
    }

    if(general > 0) {
		  //reset floppies
        uae4all_image_file0[0] = '\0';
        uae4all_image_file1[0] = '\0';
        uae4all_image_file2[0] = '\0';
        uae4all_image_file3[0] = '\0';

        mainMenu_drives = DEFAULT_DRIVES;
    }
    mainMenu_floppyspeed = 100;

    mainMenu_CPU_model = DEFAULT_CPU_MODEL;
    mainMenu_chipset = DEFAULT_CHIPSET_SELECT;
    UpdateChipsetSettings();
    mainMenu_spriteCollisions = DEFAULT_SPRITECOLLISIONS;
    kickstart = DEFAULT_KICKSTART;
    mainMenu_sound = DEFAULT_SOUND;
    sound_rate = DEFAULT_SOUND_FREQ;
    mainMenu_soundStereo = 1; // Default is stereo
    mainMenu_soundStereoSep = 3; // Default is 100% stereo separation
    mainMenu_CPU_speed = 0;

    mainMenu_cpuSpeed = 600;
    mainMenu_joyConf = 0;
    mainMenu_joyPort = 2; // Default to port 1 on Vita because mouse is always on.
    mainMenu_autofireRate = 8;
    mainMenu_customAutofireButton = 0;
    mainMenu_showStatus = DEFAULT_STATUSLN;
    mainMenu_background = 0;
    mainMenu_font = 0;
    mainMenu_mouseMultiplier = DEFAULT_MOUSEMULTIPLIER;
    mainMenu_mouseEmulation = 1;
    mainMenu_stylusOffset = 0;
    mainMenu_tapDelay = 10;
    mainMenu_customControls = 0;
	mainMenu_custom_currentlyEditingControllerNr = 0;
    mainMenu_custom_dpad = 0;
	 for (int i=0; i<MAX_NUM_CONTROLLERS; i++) 
	 {
		 mainMenu_custom_up[i] = 0;
		 mainMenu_custom_down[i] = 0;
		 mainMenu_custom_left[i] = 0;
		 mainMenu_custom_right[i] = 0;
		 mainMenu_custom_stickup[i] = 0;
		 mainMenu_custom_stickdown[i] = 0;
		 mainMenu_custom_stickleft[i] = 0;
		 mainMenu_custom_stickright[i] = 0;
		 mainMenu_custom_A[i] = 0;
		 mainMenu_custom_B[i] = 0;
		 mainMenu_custom_X[i] = 0;
		 mainMenu_custom_Y[i] = 0;
		 mainMenu_custom_L[i] = 0;
		 mainMenu_custom_R[i] = 0;
#ifdef __SWITCH__
		 mainMenu_custom_L2[i] = 0;
		 mainMenu_custom_R2[i] = 0;
		 mainMenu_custom_L3[i] = 0;
		 mainMenu_custom_R3[i] = 0;
#endif
	}
#if defined(__PSP2__) || defined(__SWITCH__)
	 mainMenu_custom_controlSet = 0;
	 for (int i=0; i<MAX_NUM_CONTROLLERS; i++) 
	 {
		 for (int j=0; j<MAX_NUM_CUSTOM_PRESETS; j++)
		 {
			mainMenu_customPreset_up[j][i] = 0;
			mainMenu_customPreset_down[j][i] = 0;
			mainMenu_customPreset_left[j][i] = 0;
			mainMenu_customPreset_right[j][i] = 0;
			mainMenu_customPreset_stickup[j][i] = 0;
			mainMenu_customPreset_stickdown[j][i] = 0;
			mainMenu_customPreset_stickleft[j][i] = 0;
			mainMenu_customPreset_stickright[j][i] = 0;
			mainMenu_customPreset_A[j][i] = 0;
			mainMenu_customPreset_B[j][i] = 0;
			mainMenu_customPreset_X[j][i] = 0;
			mainMenu_customPreset_Y[j][i] = 0;
			mainMenu_customPreset_L[j][i] = 0;
			mainMenu_customPreset_R[j][i] = 0;
#ifdef __SWITCH__
			mainMenu_customPreset_L2[j][i] = 0;
			mainMenu_customPreset_R2[j][i] = 0;
			mainMenu_customPreset_L3[j][i] = 0;
			mainMenu_customPreset_R3[j][i] = 0;
#endif
		}
	}
	// remember on Switch/Vita 
	// X is the bottom button
	// B is the right button
	// Y is the top button
	// A is the left button
	// custom control set 1 defaults
	// controller 1 defaults
	mainMenu_customPreset_up[0][0] = -5; // ply1 joy up
	mainMenu_customPreset_down[0][0] = -6; // ply1 joy down
	mainMenu_customPreset_left[0][0] = -7; // ply1 joy left
	mainMenu_customPreset_right[0][0] = -8; // ply1 joy right
	mainMenu_customPreset_stickup[0][0] = -5; // ply1 joy up
	mainMenu_customPreset_stickdown[0][0] = -6; // ply1 joy down
	mainMenu_customPreset_stickleft[0][0] = -7; // ply1 joy left
	mainMenu_customPreset_stickright[0][0] = -8; // ply1 joy right
	mainMenu_customPreset_X[0][0] = -5; // ply1 joy up (jump)
	mainMenu_customPreset_B[0][0] = 23; // space
	mainMenu_customPreset_A[0][0] = -3; // ply1 fire 1
	mainMenu_customPreset_Y[0][0] = -4; // ply1 fire 2
	mainMenu_customPreset_L[0][0] = -2; // right mouse
	mainMenu_customPreset_R[0][0] = -1; // left mouse
#ifdef __SWITCH__
	mainMenu_customPreset_L2[0][0] = -26; // fast mouse
	mainMenu_customPreset_R2[0][0] = -25; // slow mouse
	mainMenu_customPreset_L3[0][0] = 0;
	mainMenu_customPreset_R3[0][0] = 0;
#endif
	// controller 2 defaults
	mainMenu_customPreset_up[0][1] = -9; // ply2 joy up
	mainMenu_customPreset_down[0][1] = -10; // ply2 joy down
	mainMenu_customPreset_left[0][1] = -11; // ply2 joy left
	mainMenu_customPreset_right[0][1] = -12; // ply2 joy right
	mainMenu_customPreset_stickup[0][1] = -9; // ply2 joy up
	mainMenu_customPreset_stickdown[0][1] = -10; // ply2 joy down
	mainMenu_customPreset_stickleft[0][1] = -11; // ply2 joy left
	mainMenu_customPreset_stickright[0][1] = -12; // ply2 joy right
	mainMenu_customPreset_X[0][1] = -9; // ply2 joy up (jump)
	mainMenu_customPreset_B[0][1] = 0;
	mainMenu_customPreset_A[0][1] = -1; // left mouse (ply2 fire 1)
	mainMenu_customPreset_Y[0][1] = -2; // right mouse (ply2 fire 2)
	mainMenu_customPreset_L[0][1] = 0;
	mainMenu_customPreset_R[0][1] = 0;
#ifdef __SWITCH__
	mainMenu_customPreset_L2[0][1] = 0;
	mainMenu_customPreset_R2[0][1] = 0;
	mainMenu_customPreset_L3[0][1] = 0;
	mainMenu_customPreset_R3[0][1] = 0;
#endif
	//controller 3 defaults
	mainMenu_customPreset_up[0][2] = -15; // ply3 joy up
	mainMenu_customPreset_down[0][2] = -16; // ply3 joy down
	mainMenu_customPreset_left[0][2] = -17; // ply3 joy left
	mainMenu_customPreset_right[0][2] = -18; // ply3 joy right
	mainMenu_customPreset_stickup[0][2] = -15; // ply3 joy up
	mainMenu_customPreset_stickdown[0][2] = -16; // ply3 joy down
	mainMenu_customPreset_stickleft[0][2] = -17; // ply3 joy left
	mainMenu_customPreset_stickright[0][2] = -18; // ply3 joy right
	mainMenu_customPreset_X[0][2] = -15; // ply3 joy up (jump)
	mainMenu_customPreset_B[0][2] = 0;
	mainMenu_customPreset_A[0][2] = -13; // ply3 fire 1
	mainMenu_customPreset_Y[0][2] = -14; // ply3 fire 2
	mainMenu_customPreset_L[0][2] = 0;
	mainMenu_customPreset_R[0][2] = 0;
#ifdef __SWITCH__
	mainMenu_customPreset_L2[0][2] = 0;
	mainMenu_customPreset_R2[0][2] = 0;
	mainMenu_customPreset_L3[0][2] = 0;
	mainMenu_customPreset_R3[0][2] = 0;
#endif
	//controller 4 defaults
	mainMenu_customPreset_up[0][3] = -21; // ply4 joy up
	mainMenu_customPreset_down[0][3] = -22; // ply4 joy down
	mainMenu_customPreset_left[0][3] = -23; // ply4 joy left
	mainMenu_customPreset_right[0][3] = -24; // ply4 joy right
	mainMenu_customPreset_stickup[0][3] = -21; // ply4 joy up
	mainMenu_customPreset_stickdown[0][3] = -22; // ply4 joy down
	mainMenu_customPreset_stickleft[0][3] = -23; // ply4 joy left
	mainMenu_customPreset_stickright[0][3] = -24; // ply4 joy right
	mainMenu_customPreset_X[0][3] = -21; // ply4 joy up (jump)
	mainMenu_customPreset_B[0][3] = 0;
	mainMenu_customPreset_A[0][3] = -19; // ply4 fire 1
	mainMenu_customPreset_Y[0][3] = -20; // ply4 fire 2
	mainMenu_customPreset_L[0][3] = 0;
	mainMenu_customPreset_R[0][3] = 0;
#ifdef __SWITCH__
	mainMenu_customPreset_L2[0][3] = 0;
	mainMenu_customPreset_R2[0][3] = 0;
	mainMenu_customPreset_L3[0][3] = 0;
	mainMenu_customPreset_R3[0][3] = 0;
#endif

	// custom control set 2 defaults
	// controller 1 defaults (for Pinball Dreams & Slam Tilt)
	mainMenu_customPreset_up[1][0] = 0;
	mainMenu_customPreset_down[1][0] = 2; // arrow down (spring launch ball)
	mainMenu_customPreset_left[1][0] = 33; // left alt (left flipper)
	mainMenu_customPreset_right[1][0] = 30; // right shift (magna saver)
	mainMenu_customPreset_stickup[1][0] = 0;
	mainMenu_customPreset_stickdown[1][0] = 2; // arrow down (spring launch ball)
	mainMenu_customPreset_stickleft[1][0] = 33; // left alt (left flipper)
	mainMenu_customPreset_stickright[1][0] = 30; // right shift (magna saver)
	mainMenu_customPreset_X[1][0] = 23; // space (nudge center)
	mainMenu_customPreset_B[1][0] = 34; // right alt (right flipper)
	mainMenu_customPreset_A[1][0] = 26; // return (launch ball)
	mainMenu_customPreset_Y[1][0] = 87; // F1 (start 1 player game)
	mainMenu_customPreset_L[1][0] = 33; // left alt (left flipper)
	mainMenu_customPreset_R[1][0] = 34; // right alt (right flipper)
#ifdef __SWITCH__
	mainMenu_customPreset_L2[1][0] = 33; // left alt (left flipper)
	mainMenu_customPreset_R2[1][0] = 34; // right alt (right flipper)
	mainMenu_customPreset_L3[1][0] = 0;
	mainMenu_customPreset_R3[1][0] = 0;
#endif

	// controller 2 defaults (for Pinball Dreams & Slam Tilt)
	mainMenu_customPreset_up[1][1] = 0;
	mainMenu_customPreset_down[1][1] = 2; // arrow down (spring launch ball)
	mainMenu_customPreset_left[1][1] = 33; // left alt (left flipper)
	mainMenu_customPreset_right[1][1] = 30; // right shift (magna saver)
	mainMenu_customPreset_stickup[1][1] = 0;
	mainMenu_customPreset_stickdown[1][1] = 2; // arrow down (spring launch ball)
	mainMenu_customPreset_stickleft[1][1] = 33; // left alt (left flipper)
	mainMenu_customPreset_stickright[1][1] = 30; // right shift (magna saver)
	mainMenu_customPreset_X[1][1] = 23; // space (nudge center)
	mainMenu_customPreset_B[1][1] = 34; // right alt (right flipper)
	mainMenu_customPreset_A[1][1] = 26; // return (launch ball)
	mainMenu_customPreset_Y[1][1] = 88; // F2 (start 2 player game)
	mainMenu_customPreset_L[1][1] = 33; // left alt (left flipper)
	mainMenu_customPreset_R[1][1] = 34; // right alt (right flipper)
#ifdef __SWITCH__
	mainMenu_customPreset_L2[1][1] = 33; // left alt (left flipper)
	mainMenu_customPreset_R2[1][1] = 34; // right alt (right flipper)
	mainMenu_customPreset_L3[1][1] = 0;
	mainMenu_customPreset_R3[1][1] = 0;
#endif

	// controller 3 defaults (for Pinball Dreams & Slam Tilt)
	mainMenu_customPreset_up[1][2] = 0;
	mainMenu_customPreset_down[1][2] = 2; // arrow down (spring launch ball)
	mainMenu_customPreset_left[1][2] = 33; // left alt (left flipper)
	mainMenu_customPreset_right[1][2] = 30; // right shift (magna saver)
	mainMenu_customPreset_stickup[1][2] = 0;
	mainMenu_customPreset_stickdown[1][2] = 2; // arrow down (spring launch ball)
	mainMenu_customPreset_stickleft[1][2] = 33; // left alt (left flipper)
	mainMenu_customPreset_stickright[1][2] = 30; // right shift (magna saver)
	mainMenu_customPreset_X[1][2] = 23; // space (nudge center)
	mainMenu_customPreset_B[1][2] = 34; // right alt (right flipper)
	mainMenu_customPreset_A[1][2] = 26; // return (launch ball)
	mainMenu_customPreset_Y[1][2] = 89; // F3 (start 3 player game)
	mainMenu_customPreset_L[1][2] = 33; // left alt (left flipper)
	mainMenu_customPreset_R[1][2] = 34; // right alt (right flipper)
#ifdef __SWITCH__
	mainMenu_customPreset_L2[1][2] = 33; // left alt (left flipper)
	mainMenu_customPreset_R2[1][2] = 34; // right alt (right flipper)
	mainMenu_customPreset_L3[1][2] = 0;
	mainMenu_customPreset_R3[1][2] = 0;
#endif

	// controller 4 defaults (for Pinball Dreams & Slam Tilt)
	mainMenu_customPreset_up[1][3] = 0;
	mainMenu_customPreset_down[1][3] = 2; // arrow down (spring launch ball)
	mainMenu_customPreset_left[1][3] = 33; // left alt (left flipper)
	mainMenu_customPreset_right[1][3] = 30; // right shift (magna saver)
	mainMenu_customPreset_stickup[1][3] = 0;
	mainMenu_customPreset_stickdown[1][3] = 2; // arrow down (spring launch ball)
	mainMenu_customPreset_stickleft[1][3] = 33; // left alt (left flipper)
	mainMenu_customPreset_stickright[1][3] = 30; // right shift (magna saver)
	mainMenu_customPreset_X[1][3] = 23; // space (nudge center)
	mainMenu_customPreset_B[1][3] = 34; // right alt (right flipper)
	mainMenu_customPreset_A[1][3] = 26; // return (launch ball)
	mainMenu_customPreset_Y[1][3] = 90; // F4 (start 4 player game)
	mainMenu_customPreset_L[1][3] = 33; // left alt (left flipper)
	mainMenu_customPreset_R[1][3] = 34; // right alt (right flipper)
#ifdef __SWITCH__
	mainMenu_customPreset_L2[1][3] = 33; // left alt (left flipper)
	mainMenu_customPreset_R2[1][3] = 34; // right alt (right flipper)
	mainMenu_customPreset_L3[1][3] = 0;
	mainMenu_customPreset_R3[1][3] = 0;
#endif
	remap_custom_controls();
#endif //__PSP2__
    SetPresetMode(2);
    moveX = 0;
    moveY = 16;
    mainMenu_cutLeft = 0;
    mainMenu_cutRight = 0;
    mainMenu_ntsc = DEFAULT_NTSC;
    mainMenu_frameskip = 0;
    mainMenu_vkbdLanguage = 0; //Default is US Keyboard
    mainMenu_vkbdStyle = 0; //Default is original style
    mainMenu_autofire = DEFAULT_AUTOFIRE;

#if defined(__PSP2__) || defined(__SWITCH__)
#ifdef __SWITCH__
    mainMenu_shader = 1;
#else
    mainMenu_shader = 5;
#endif
    mainMenu_leftStickMouse = 0;
    mainMenu_touchControls = 1;
    mainMenu_deadZone = 1000;
#endif
#ifdef __SWITCH__
    mainMenu_swapAB = DEFAULT_SWAPAB;
    mainMenu_singleJoycons = DEFAULT_SINGLEJOYCONS;
#endif
    // The following params can't be changed in gui
    skipintro = DEFAULT_SKIPINTRO;
    mainMenu_autosave = DEFAULT_AUTOSAVE;
    mainMenu_button1 = GP2X_BUTTON_X;
    mainMenu_button2 = GP2X_BUTTON_A;
    mainMenu_autofireButton1 = GP2X_BUTTON_B;
    mainMenu_jump = -1;

    gp2xClockSpeed = -1;
    mainMenu_scanlines = 0;
    mainMenu_enableScreenshots = DEFAULT_ENABLESCREENSHOTS;
    mainMenu_enableScripts = DEFAULT_ENABLESCRIPTS;
    mainMenu_useSavesFolder = DEFAULT_USESAVESFOLDER;
}


void UpdateCPUModelSettings()
{
    switch (mainMenu_CPU_model) {
    case 1:
        changed_prefs.cpu_level = M68020;
        break;
    default:
        changed_prefs.cpu_level = M68000;
        break;
    }
}


void UpdateMemorySettings()
{
    prefs_chipmem_size = 0x000080000 << mainMenu_chipMemory;

    /* >2MB chip memory => 0 fast memory */
    if ((mainMenu_chipMemory > 2) && (mainMenu_fastMemory > 0)) {
        mainMenu_fastMemory = 0;
        changed_prefs.fastmem_size = 0;
    }

    switch (mainMenu_slowMemory) {
    case 1:
    case 2:
        prefs_bogomem_size = 0x00080000 << (mainMenu_slowMemory - 1);
        break;
    case 3:
        prefs_bogomem_size = 0x00180000;	/* 1.5M */
        break;
    case 4:
        prefs_bogomem_size = 0x001C0000;	/* 1.8M */
        break;
    default:
        prefs_bogomem_size = 0;
    }

    switch (mainMenu_fastMemory) {
    case 0:
        changed_prefs.fastmem_size = 0;
        break;
    default:
        changed_prefs.fastmem_size = 0x00080000 << mainMenu_fastMemory;
    }

}


void UpdateChipsetSettings()
{
    switch (mainMenu_chipset & 0xff) {
    case 1:
        changed_prefs.chipset_mask = CSMASK_ECS_AGNUS | CSMASK_ECS_DENISE;
        break;
    case 2:
        changed_prefs.chipset_mask = CSMASK_ECS_AGNUS | CSMASK_ECS_DENISE | CSMASK_AGA;
        break;
    default:
        changed_prefs.chipset_mask = CSMASK_ECS_AGNUS;
        break;
    }
    switch (mainMenu_chipset & 0xff00) {
    case 0x100:
    //Immediate Blitter
        changed_prefs.immediate_blits = true;
        blitter_in_partial_mode = 0;
        break;
    //Improved Blitter
    case 0x200:
        changed_prefs.immediate_blits = false;
        blitter_in_partial_mode = 1;
        break;
    //Normal Blitter
    default:
        changed_prefs.immediate_blits = false;
        blitter_in_partial_mode = 0;
        break;
    }
}


void SetPresetMode(int mode)
{
    presetModeId = mode;

    switch(mode) {
    case 0:
        mainMenu_displayedLines = 200;
        screenWidth = 768;
        strcpy(presetMode, "320x200 upscaled");
        break;

    case 1:
        mainMenu_displayedLines = 216;
        screenWidth = 716;
        strcpy(presetMode, "320x216 upscaled");
        break;

    case 2:
        mainMenu_displayedLines = 240;
        screenWidth = 640;
        strcpy(presetMode, "320x240 upscaled");
        break;

    case 3:
        mainMenu_displayedLines = 256;
        screenWidth = 600;
        strcpy(presetMode, "320x256 upscaled");
        break;

    case 4:
        mainMenu_displayedLines = 262;
        screenWidth = 588;
        strcpy(presetMode, "320x262 upscaled");
        break;

    case 5:
        mainMenu_displayedLines = 270;
        screenWidth = 570;
        strcpy(presetMode, "320x270 upscaled");
        break;

    case 6:
        mainMenu_displayedLines = 200;
        screenWidth = 640;
        strcpy(presetMode, "320x200 NTSC");
        break;

    case 7:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "320x200 fullscreen");
        break;

    case 10:
        mainMenu_displayedLines = 200;
        screenWidth = 768;
        strcpy(presetMode, "640x200 upscaled");
        break;

    case 11:
        mainMenu_displayedLines = 216;
        screenWidth = 716;
        strcpy(presetMode, "640x216 upscaled");
        break;

    case 12:
        mainMenu_displayedLines = 240;
        screenWidth = 640;
        strcpy(presetMode, "640x240 upscaled");
        break;

    case 13:
        mainMenu_displayedLines = 256;
        screenWidth = 600;
        strcpy(presetMode, "640x256 upscaled");
        break;

    case 14:
        mainMenu_displayedLines = 262;
        screenWidth = 588;
        strcpy(presetMode, "640x262 upscaled");
        break;

    case 15:
        mainMenu_displayedLines = 270;
        screenWidth = 570;
        strcpy(presetMode, "640x270 upscaled");
        break;

    case 16:
        mainMenu_displayedLines = 200;
        screenWidth = 640;
        strcpy(presetMode, "640x200 NTSC");
        break;

    case 17:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "640x200 fullscreen");
        break;

    case 20:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "352x200 upscaled");
        break;

    case 21:
        mainMenu_displayedLines = 216;
        screenWidth = 784;
        strcpy(presetMode, "352x216 upscaled");
        break;

    case 22:
        mainMenu_displayedLines = 240;
        screenWidth = 704;
        strcpy(presetMode, "352x240 upscaled");
        break;

    case 23:
        mainMenu_displayedLines = 256;
        screenWidth = 660;
        strcpy(presetMode, "352x256 upscaled");
        break;

    case 24:
        mainMenu_displayedLines = 262;
        screenWidth = 640;
        strcpy(presetMode, "352x262 upscaled");
        break;

    case 25:
        mainMenu_displayedLines = 270;
        screenWidth = 624;
        strcpy(presetMode, "352x270 upscaled");
        break;

    case 26:
        mainMenu_displayedLines = 200;
        screenWidth = 704;
        strcpy(presetMode, "352x200 NTSC");
        break;

    case 27:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "352x200 fullscreen");
        break;

    case 30:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "704x200 upscaled");
        break;

    case 31:
        mainMenu_displayedLines = 216;
        screenWidth = 784;
        strcpy(presetMode, "704x216 upscaled");
        break;

    case 32:
        mainMenu_displayedLines = 240;
        screenWidth = 704;
        strcpy(presetMode, "704x240 upscaled");
        break;

    case 33:
        mainMenu_displayedLines = 256;
        screenWidth = 660;
        strcpy(presetMode, "704x256 upscaled");
        break;

    case 34:
        mainMenu_displayedLines = 262;
        screenWidth = 640;
        strcpy(presetMode, "704x262 upscaled");
        break;

    case 35:
        mainMenu_displayedLines = 270;
        screenWidth = 624;
        strcpy(presetMode, "704x270 upscaled");
        break;

    case 36:
        mainMenu_displayedLines = 200;
        screenWidth = 704;
        strcpy(presetMode, "704x200 NTSC");
        break;

    case 37:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "704x200 fullscreen");
        break;

    case 40:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "384x200 upscaled");
        break;

    case 41:
        mainMenu_displayedLines = 216;
        screenWidth = 800;
        strcpy(presetMode, "384x216 upscaled");
        break;

    case 42:
        mainMenu_displayedLines = 240;
        screenWidth = 768;
        strcpy(presetMode, "384x240 upscaled");
        break;

    case 43:
        mainMenu_displayedLines = 256;
        screenWidth = 720;
        strcpy(presetMode, "384x256 upscaled");
        break;

    case 44:
        mainMenu_displayedLines = 262;
        screenWidth = 704;
        strcpy(presetMode, "384x262 upscaled");
        break;

    case 45:
        mainMenu_displayedLines = 270;
        screenWidth = 684;
        strcpy(presetMode, "384x270 upscaled");
        break;

    case 46:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "384x200 NTSC");
        break;

    case 47:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "384x200 fullscreen");
        break;

    case 50:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "768x200 upscaled");
        break;

    case 51:
        mainMenu_displayedLines = 216;
        screenWidth = 800;
        strcpy(presetMode, "768x216 upscaled");
        break;

    case 52:
        mainMenu_displayedLines = 240;
        screenWidth = 768;
        strcpy(presetMode, "768x240 upscaled");
        break;

    case 53:
        mainMenu_displayedLines = 256;
        screenWidth = 720;
        strcpy(presetMode, "768x256 upscaled");
        break;

    case 54:
        mainMenu_displayedLines = 262;
        screenWidth = 704;
        strcpy(presetMode, "768x262 upscaled");
        break;

    case 55:
        mainMenu_displayedLines = 270;
        screenWidth = 684;
        strcpy(presetMode, "768x270 upscaled");
        break;

    case 56:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "768x200 NTSC");
        break;

    case 57:
        mainMenu_displayedLines = 200;
        screenWidth = 800;
        strcpy(presetMode, "768x200 fullscreen");
        break;

    default:
        mainMenu_displayedLines = 240;
        screenWidth = 640;
        strcpy(presetMode, "320x240 upscaled");
        presetModeId = 2;
        break;
    }

    switch(presetModeId / 10) {
    case 0:
        mainMenu_displayHires = 0;
        visibleAreaWidth = 320;
        break;

    case 1:
        mainMenu_displayHires = 1;
        visibleAreaWidth = 640;
        break;

    case 2:
        mainMenu_displayHires = 0;
        visibleAreaWidth = 352;
        break;

    case 3:
        mainMenu_displayHires = 1;
        visibleAreaWidth = 704;
        break;

    case 4:
        mainMenu_displayHires = 0;
        visibleAreaWidth = 384;
        break;

    case 5:
        mainMenu_displayHires = 1;
        visibleAreaWidth = 768;
        break;
    }
}


void set_joyConf()
{
    if(mainMenu_joyConf==0) {
        mainMenu_button1=GP2X_BUTTON_X;
        mainMenu_button2=GP2X_BUTTON_A;
        mainMenu_jump=-1;
        mainMenu_autofireButton1=GP2X_BUTTON_B;
    } else if(mainMenu_joyConf==1) {
        mainMenu_button1=GP2X_BUTTON_B;
        mainMenu_button2=GP2X_BUTTON_A;
        mainMenu_jump=-1;
        mainMenu_autofireButton1=GP2X_BUTTON_X;
    } else if(mainMenu_joyConf==2) {
        mainMenu_button1=GP2X_BUTTON_Y;
        mainMenu_button2=GP2X_BUTTON_A;
        mainMenu_jump=GP2X_BUTTON_X;
        mainMenu_autofireButton1=GP2X_BUTTON_B;
    } else if(mainMenu_joyConf==3) {
        mainMenu_button1=GP2X_BUTTON_B;
        mainMenu_button2=GP2X_BUTTON_A;
        mainMenu_jump=GP2X_BUTTON_X;
        mainMenu_autofireButton1=GP2X_BUTTON_Y;
    }
}

void kill_hd_configs()
{
	 //properly close all open hdf and hd dirs
	for (int i = 0; i < mainMenu_filesysUnits; i++) {
        kill_filesys_unit(currprefs.mountinfo, 0);
    }
    mainMenu_filesysUnits = 0;
}

void reset_hdConf()
{
	 kill_hd_configs();
    /* Reset HD config */

    switch (mainMenu_bootHD) {
    case 0:
        // nothing to do, already killed above
        break;
    case 1:
        if (uae4all_hard_dir[0] != '\0') {
            parse_filesys_spec(0, uae4all_hard_dir);
            mainMenu_filesysUnits++;
        }
        if (uae4all_hard_file0[0] != '\0') {
            parse_hardfile_spec(uae4all_hard_file0);
            mainMenu_filesysUnits++;
        }
        if (uae4all_hard_file1[0] != '\0') {
            parse_hardfile_spec(uae4all_hard_file1);
            mainMenu_filesysUnits++;
        }
        if (uae4all_hard_file2[0] != '\0') {
            parse_hardfile_spec(uae4all_hard_file2);
            mainMenu_filesysUnits++;
        }
        if (uae4all_hard_file3[0] != '\0') {
            parse_hardfile_spec(uae4all_hard_file3);
            mainMenu_filesysUnits++;
        }
        break;
    case 2:
        if (uae4all_hard_file0[0] != '\0') {
            parse_hardfile_spec(uae4all_hard_file0);
            mainMenu_filesysUnits++;
        }
        if (uae4all_hard_file1[0] != '\0') {
            parse_hardfile_spec(uae4all_hard_file1);
            mainMenu_filesysUnits++;
        }
        if (uae4all_hard_file2[0] != '\0') {
            parse_hardfile_spec(uae4all_hard_file2);
            mainMenu_filesysUnits++;
        }
        if (uae4all_hard_file3[0] != '\0') {
            parse_hardfile_spec(uae4all_hard_file3);
            mainMenu_filesysUnits++;
        }
        if (uae4all_hard_dir[0] != '\0') {
            parse_filesys_spec(0, uae4all_hard_dir);
            mainMenu_filesysUnits++;
        }
        break;
    }
}


static void replace(char * str,char replace, char toreplace)
{
    while(*str) {
        if (*str==toreplace) *str=replace;
        str++;
    }
}


int create_configfilename(char *dest, char *basename, int fromDir)
{
    char *p;
    p = basename + strlen(basename) - 1;
    while (*p != '/')
        p--;
    p++;
    if(fromDir == 0) {
        int len = strlen(p) + 1;
        char filename[len];
        strcpy(filename, p);
        char *pch = &filename[len];
        while (pch != filename && *pch != '.')
            pch--;
        if (pch) {
            *pch='\0';
            snprintf(dest, 300, "%s/conf/%s.conf", launchDir, filename);
            return 1;
        }
    } else {
        snprintf(dest, 300, "%s/conf/%s.conf", launchDir, p);
        return 1;
    }

    return 0;
}


int saveconfig(int general)
{
    char path[300];
    char *p;
    switch(general) {
    case 0:
        if (!uae4all_image_file0[0])
            return 0;
        if(!create_configfilename(path, uae4all_image_file0, 0))
            return 0;
        break;
    case 1:
        snprintf(path, 300, "%s/conf/uaeconfig.conf", launchDir);
        break;
    case 2:
        path[0] = '\0';
        if(mainMenu_bootHD == 1 && uae4all_hard_dir[0] != '\0')
            create_configfilename(path, uae4all_hard_dir, 1);
        if(mainMenu_bootHD == 2 && uae4all_hard_file0[0] != '\0')
            create_configfilename(path, uae4all_hard_file0, 0);
        if(path[0] == '\0')
            return 0;
        break;
    case 3:
        snprintf(path, 300, config_filename, launchDir);
        break;
    case 4:
#if defined(__SWITCH__) || defined(__PSP2__)
        char buf[100] = "";
#ifdef __SWITCH__
        kbdswitch_get("Enter config name:", "", 100, 0, buf);
#else
        strcpy(buf, kbdvita_get("Enter config name:", "", 100, 0));
#endif
        if (buf[0] == 0)
            return 0;
        snprintf(path, 300, "%s/conf/%s%s", launchDir, buf, ".conf");
#else
        return 0;
#endif
        break;
    }


    FILE *f=fopen(path,"w");
    if (!f) return 0;
    char buffer[255];

    snprintf((char*)buffer, 255, "kickstart=%d\n",kickstart);
    fputs(buffer,f);
#if defined(PANDORA) || defined(ANDROIDSDL)
    snprintf((char*)buffer, 255, "scaling=%d\n",0);
#else
    snprintf((char*)buffer, 255, "scaling=%d\n",mainMenu_enableHWscaling);
#endif
    fputs(buffer,f);
#if defined(__PSP2__) || defined(__SWITCH__)
    snprintf((char*)buffer, 255, "shader=%d\n",mainMenu_shader);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "leftstickmouse=%d\n",mainMenu_leftStickMouse);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "touchcontrols=%d\n",mainMenu_touchControls);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "deadzone=%d\n",mainMenu_deadZone);
    fputs(buffer,f);
#endif
    snprintf((char*)buffer, 255, "showstatus=%d\n",mainMenu_showStatus);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "background=%d\n",mainMenu_background);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "font=%d\n",mainMenu_font);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "mousemultiplier=%d\n",mainMenu_mouseMultiplier);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "mouseemulation=%d\n",mainMenu_mouseEmulation);
    fputs(buffer,f);
#if defined(PANDORA) || defined(ANDROIDSDL)
    snprintf((char*)buffer, 255, "systemclock=%d\n",5);   // mainMenu_throttle never changes -> removed
#else
    snprintf((char*)buffer, 255, "systemclock=%d\n",mainMenu_throttle);
#endif
    fputs(buffer,f);
#if defined(PANDORA) || defined(ANDROIDSDL)
    snprintf((char*)buffer, 255, "syncthreshold=%d\n",2); // timeslice_mode never changes -> removed
#else
    snprintf((char*)buffer, 255, "syncthreshold=%d\n",timeslice_mode);
#endif
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "frameskip=%d\n",mainMenu_frameskip);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "vkbdlanguage=%d\n",mainMenu_vkbdLanguage);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "vkbdstyle=%d\n",mainMenu_vkbdStyle);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "sound=%d\n",mainMenu_sound + mainMenu_soundStereo * 10);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "soundstereosep=%d\n",mainMenu_soundStereoSep);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "soundrate=%d\n",sound_rate);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "autosave=%d\n",mainMenu_autosave);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "gp2xclock=%d\n",gp2xClockSpeed);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "joyconf=%d\n",mainMenu_joyConf + (mainMenu_joyPort << 4));
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "autofireRate=%d\n",mainMenu_autofireRate);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "autofire=%d\n",mainMenu_autofire);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "customAutofireButton=%d\n",mainMenu_customAutofireButton);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "stylusOffset=%d\n",mainMenu_stylusOffset);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "tapDelay=%d\n",mainMenu_tapDelay);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "scanlines=%d\n",mainMenu_scanlines);
    fputs(buffer,f);
#if defined(PANDORA) || defined(ANDROIDSDL)
    snprintf((char*)buffer, 255, "ham=%d\n",1);
#else
    snprintf((char*)buffer, 255, "ham=%d\n",mainMenu_ham);
#endif
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "enableScreenshots=%d\n",mainMenu_enableScreenshots);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "floppyspeed=%d\n",mainMenu_floppyspeed);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "drives=%d\n",nr_drives);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "videomode=%d\n",mainMenu_ntsc);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "mainMenu_cpuSpeed=%d\n",mainMenu_cpuSpeed);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "presetModeId=%d\n",presetModeId);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "moveX=%d\n",moveX);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "moveY=%d\n",moveY-16); // compatibility with versions <1.96
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "displayedLines=%d\n",mainMenu_displayedLines);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "screenWidth=%d\n",screenWidth);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "cutLeft=%d\n",mainMenu_cutLeft);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "cutRight=%d\n",mainMenu_cutRight);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "customControls=%d\n",mainMenu_customControls);
    fputs(buffer,f);
#if !defined(__PSP2__) && !defined(__SWITCH__)    
    snprintf((char*)buffer, 255, "custom_dpad=%d\n",mainMenu_custom_dpad[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_up=%d\n",mainMenu_custom_up[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_down=%d\n",mainMenu_custom_down[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_left=%d\n",mainMenu_custom_left[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_right=%d\n",mainMenu_custom_right[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_A=%d\n",mainMenu_custom_A[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_B=%d\n",mainMenu_custom_B[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_X=%d\n",mainMenu_custom_X[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_Y=%d\n",mainMenu_custom_Y[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_L=%d\n",mainMenu_custom_L[0]);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_R=%d\n",mainMenu_custom_R[0]);
    fputs(buffer,f);
#else
	snprintf((char*)buffer, 255, "custom_controlSet=%d\n",mainMenu_custom_controlSet);
	fputs(buffer,f);
	for (int i=0; i<MAX_NUM_CONTROLLERS; i++)
	{
		for (int j=0; j<MAX_NUM_CUSTOM_PRESETS; j++)
		{
			snprintf((char*)buffer, 255, "custom%d_up_Ply%d=%d\n",j+1,i,mainMenu_customPreset_up[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_down_Ply%d=%d\n",j+1,i,mainMenu_customPreset_down[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_left_Ply%d=%d\n",j+1,i,mainMenu_customPreset_left[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_right_Ply%d=%d\n",j+1,i,mainMenu_customPreset_right[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_stickup_Ply%d=%d\n",j+1,i,mainMenu_customPreset_stickup[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_stickdown_Ply%d=%d\n",j+1,i,mainMenu_customPreset_stickdown[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_stickleft_Ply%d=%d\n",j+1,i,mainMenu_customPreset_stickleft[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_stickright_Ply%d=%d\n",j+1,i,mainMenu_customPreset_stickright[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_A_Ply%d=%d\n",j+1,i,mainMenu_customPreset_A[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_B_Ply%d=%d\n",j+1,i,mainMenu_customPreset_B[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_X_Ply%d=%d\n",j+1,i,mainMenu_customPreset_X[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_Y_Ply%d=%d\n",j+1,i,mainMenu_customPreset_Y[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_L_Ply%d=%d\n",j+1,i,mainMenu_customPreset_L[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_R_Ply%d=%d\n",j+1,i,mainMenu_customPreset_R[j][i]);
			fputs(buffer,f);
#ifdef __SWITCH__
			snprintf((char*)buffer, 255, "custom%d_L2_Ply%d=%d\n",j+1,i,mainMenu_customPreset_L2[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_R2_Ply%d=%d\n",j+1,i,mainMenu_customPreset_R2[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_L3_Ply%d=%d\n",j+1,i,mainMenu_customPreset_L3[j][i]);
			fputs(buffer,f);
			snprintf((char*)buffer, 255, "custom%d_R3_Ply%d=%d\n",j+1,i,mainMenu_customPreset_R3[j][i]);
			fputs(buffer,f);
#endif
		}
	}
#endif
    snprintf((char*)buffer, 255, "cpu=%d\n",mainMenu_CPU_model);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "chipset=%d\n",mainMenu_chipset);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "spritecollisions=%d\n",mainMenu_spriteCollisions);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "cpu=%d\n",-mainMenu_CPU_speed);
    fputs(buffer,f);

    char namebuffer[256];
    if (uae4all_image_file0[0]) {
        strcpy(namebuffer,uae4all_image_file0);
        replace (namebuffer,'|',' ');
        snprintf((char*)buffer, 255, "df0=%s\n",namebuffer);
        fputs(buffer,f);
    } else {
        fputs("df0=\n",f);
    }
    if (uae4all_image_file1[0] && nr_drives > 1) {
        strcpy(namebuffer,uae4all_image_file1);
        replace (namebuffer,'|',' ');
        snprintf((char*)buffer, 255, "df1=%s\n",namebuffer);
        fputs(buffer,f);
    } else {
        fputs("df1=\n",f);
    }
    if (uae4all_image_file2[0] && nr_drives > 2) {
        strcpy(namebuffer,uae4all_image_file2);
        replace (namebuffer,'|',' ');
        snprintf((char*)buffer, 255, "df2=%s\n",namebuffer);
        fputs(buffer,f);
    } else {
            fputs("df2=\n",f);
    }
    if (uae4all_image_file3[0] && nr_drives > 3) {
        strcpy(namebuffer,uae4all_image_file3);
        replace (namebuffer,'|',' ');
        snprintf((char*)buffer, 255, "df3=%s\n",namebuffer);
        fputs(buffer,f);
    } else {
            fputs("df3=\n",f);
    }
    snprintf((char*)buffer, 255, "script=%d\n",mainMenu_enableScripts);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "screenshot=%d\n",mainMenu_enableScreenshots);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "skipintro=%d\n",skipintro);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "boot_hd=%d\n",mainMenu_bootHD);
    fputs(buffer,f);
    if (uae4all_hard_dir[0] == '\0')
        snprintf((char*)buffer, 255, "hard_disk_dir=%s\n","*");
    else
        snprintf((char*)buffer, 255, "hard_disk_dir=%s\n",uae4all_hard_dir);
    fputs(buffer,f);
    //HDF0
    if (uae4all_hard_file0[0] == '\0')
        snprintf((char*)buffer, 255, "hard_disk_file0=%s\n","*");
    else
        snprintf((char*)buffer, 255, "hard_disk_file0=%s\n",uae4all_hard_file0);
    fputs(buffer,f);
    //HDF1
    if (uae4all_hard_file1[0] == '\0')
        snprintf((char*)buffer, 255, "hard_disk_file1=%s\n","*");
    else
        snprintf((char*)buffer, 255, "hard_disk_file1=%s\n",uae4all_hard_file1);
    fputs(buffer,f);
    //HDF2
    if (uae4all_hard_file2[0] == '\0')
        snprintf((char*)buffer, 255, "hard_disk_file2=%s\n","*");
    else
        snprintf((char*)buffer, 255, "hard_disk_file2=%s\n",uae4all_hard_file2);
    fputs(buffer,f);
    //HDF3
    if (uae4all_hard_file3[0] == '\0')
        snprintf((char*)buffer, 255, "hard_disk_file3=%s\n","*");
    else
        snprintf((char*)buffer, 255, "hard_disk_file3=%s\n",uae4all_hard_file3);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "chipmemory=%d\n",mainMenu_chipMemory);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "slowmemory=%d\n",mainMenu_slowMemory);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "fastmemory=%d\n",mainMenu_fastMemory);
    fputs(buffer,f);
#ifdef ANDROIDSDL
    snprintf((char*)buffer, 255, "onscreen=%d\n",mainMenu_onScreen);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "onScreen_textinput=%d\n",mainMenu_onScreen_textinput);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "onScreen_dpad=%d\n",mainMenu_onScreen_dpad);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "onScreen_button1=%d\n",mainMenu_onScreen_button1);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "onScreen_button2=%d\n",mainMenu_onScreen_button2);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "onScreen_button3=%d\n",mainMenu_onScreen_button3);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "onScreen_button4=%d\n",mainMenu_onScreen_button4);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "onScreen_button5=%d\n",mainMenu_onScreen_button5);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "onScreen_button6=%d\n",mainMenu_onScreen_button6);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "custom_position=%d\n",mainMenu_custom_position);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_x_textinput=%d\n",mainMenu_pos_x_textinput);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_y_textinput=%d\n",mainMenu_pos_y_textinput);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_x_dpad=%d\n",mainMenu_pos_x_dpad);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_y_dpad=%d\n",mainMenu_pos_y_dpad);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_x_button1=%d\n",mainMenu_pos_x_button1);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_y_button1=%d\n",mainMenu_pos_y_button1);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_x_button2=%d\n",mainMenu_pos_x_button2);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_y_button2=%d\n",mainMenu_pos_y_button2);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_x_button3=%d\n",mainMenu_pos_x_button3);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_y_button3=%d\n",mainMenu_pos_y_button3);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_x_button4=%d\n",mainMenu_pos_x_button4);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_y_button4=%d\n",mainMenu_pos_y_button4);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_x_button5=%d\n",mainMenu_pos_x_button5);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_y_button5=%d\n",mainMenu_pos_y_button5);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_x_button6=%d\n",mainMenu_pos_x_button6);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "pos_y_button6=%d\n",mainMenu_pos_y_button6);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "quick_switch=%d\n",mainMenu_quickSwitch);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "FloatingJoystick=%d\n",mainMenu_FloatingJoystick);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "button_size=%f\n",mainMenu_button_size);
    fputs(buffer,f);
#endif
#if defined(ANDROIDSDL) || defined(AROS)
	snprintf((char*)buffer, 255, "VSync=%d\n",mainMenu_vsync);
 	fputs(buffer,f);
#endif

    strcpy(namebuffer,custom_kickrom);
    replace (namebuffer,'|',' ');
    snprintf((char*)buffer, 255, "custom_kickrom=%s\n",namebuffer);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "useSavesFolder=%d\n",mainMenu_useSavesFolder);
    fputs(buffer,f);
#ifdef __SWITCH__
    snprintf((char*)buffer, 255, "swapAB=%d\n",mainMenu_swapAB);
    fputs(buffer,f);
    snprintf((char*)buffer, 255, "singleJoycons=%d\n",mainMenu_singleJoycons);
    fputs(buffer,f);
#endif
    fclose(f);
    return 1;
}


void loadconfig(int general)
{
// general == 0 (default): loading disk specific config after inserting floppy #1 
// general == 1: first time, loading general config
// general == 2: loading hdf-file-specific config after inserting hdf file #1
// general == 3: loading config from guichan (unused)
// general == 4: loading hd-dir-specific config after selecting hd dir
// general == 5: loading general config via the load config... filerequester option on main menu 
#if defined(__PSP2__) || defined(__SWITCH__)
	if (general == 1)
	{
    //first time opening the screen on Vita
	 int visibleAreaWidth_old = visibleAreaWidth;
	 int mainMenu_displayedLines_old = mainMenu_displayedLines;
	 visibleAreaWidth = 320;
	 mainMenu_displayedLines = 200;
	 update_display();
	 visibleAreaWidth=visibleAreaWidth_old;
	 mainMenu_displayedLines = mainMenu_displayedLines_old;
	}
#endif

    char path[300];

    if(general == 1) {
        snprintf(path, 300, "%s/conf/adfdir.conf", launchDir);
        FILE *f1=fopen(path,"rt");
        if(!f1) {
            printf ("No config file %s!\n",path);
            strcpy(currentDir, launchDir);
#ifdef ANDROIDSDL
            char *dirname="../../com.cloanto.amigaforever.essentials/files/adf/";
            struct stat statbuf;
            stat (dirname, &statbuf);
            if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
                strcat(currentDir, "/../../com.cloanto.amigaforever.essentials/files/adf");
            else
#endif
                strcat(currentDir, "/roms/");
        } else {
            fscanf(f1,"path=%s\n",&currentDir);
            fclose(f1);
            printf("adfdir loaded. currentDir=%s\n", currentDir);
        }
    }

    if (general == 1)
        if (config_load_filename[0] != 0) {
            // custom config was specified as command line argument 
            snprintf(path, 300, "%s",config_load_filename);
        }
        else {
            snprintf(path, 300, "%s/conf/uaeconfig.conf", launchDir);
        }
    else if (general == 3)
        snprintf(path, 300, config_filename, launchDir);
    else if(general == 0)
        create_configfilename(path, uae4all_image_file0, 0);
    else if (general == 2) {
        path[0] = '\0';
        if(uae4all_hard_file0[0] != '\0')
            create_configfilename(path, uae4all_hard_file0, 0);
        if(path[0] == '\0')
            return;
    }
    else if (general == 4) {
        path[0] = '\0';
        if(uae4all_hard_dir[0] != '\0')
            create_configfilename(path, uae4all_hard_dir, 1);
        if(path[0] == '\0')
            return;
    }
    else if (general == 5) {
        snprintf(path, 300, config_load_filename);
    }

    FILE *f=fopen(path,"rt");
    if (!f) {
        printf ("No config file %s!\n",path);
    } else {
        // Set everthing to default and clear HD settings
        SetDefaultMenuSettings(general);

        char filebuffer[256];
#if defined(PANDORA) || defined(ANDROIDSDL)
        int dummy;
#endif
        fscanf(f,"kickstart=%d\n",&kickstart);
#if defined(PANDORA) || defined(ANDROIDSDL)
        fscanf(f,"scaling=%d\n",&dummy);
#else
        fscanf(f,"scaling=%d\n",&mainMenu_enableHWscaling);
#endif
#if defined(__PSP2__) || defined(__SWITCH__)
        fscanf(f,"shader=%d\n",&mainMenu_shader);
#if defined(__SWITCH__)
        if (mainMenu_shader > 3) mainMenu_shader = 1;
#endif
        fscanf(f,"leftstickmouse=%d\n",&mainMenu_leftStickMouse);
        fscanf(f,"touchcontrols=%d\n",&mainMenu_touchControls);
        fscanf(f,"deadzone=%d\n",&mainMenu_deadZone);        
#endif
        fscanf(f,"showstatus=%d\n",&mainMenu_showStatus);
        fscanf(f,"background=%d\n",&mainMenu_background);
        fscanf(f,"font=%d\n",&mainMenu_font);
        fscanf(f,"mousemultiplier=%d\n",&mainMenu_mouseMultiplier);
        //remain compatible with old configuration versions
        if (mainMenu_mouseMultiplier < 10) {
            if (mainMenu_mouseMultiplier == 1 || mainMenu_mouseMultiplier == 2 || mainMenu_mouseMultiplier == 4) {
                mainMenu_mouseMultiplier *= 100;
            }
            else {
                mainMenu_mouseMultiplier = DEFAULT_MOUSEMULTIPLIER;
            }
        }
        fscanf(f,"mouseemulation=%d\n",&mainMenu_mouseEmulation );
#if defined(PANDORA) || defined(ANDROIDSDL)
        fscanf(f,"systemclock=%d\n",&dummy);    // mainMenu_throttle never changes -> removed
        fscanf(f,"syncthreshold=%d\n", &dummy); // timeslice_mode never changes -> removed
#else
        fscanf(f,"systemclock=%d\n",&mainMenu_throttle);
        fscanf(f,"syncthreshold=%d\n", &timeslice_mode);
#endif
        fscanf(f,"frameskip=%d\n",&mainMenu_frameskip);
        fscanf(f,"vkbdlanguage=%d\n",&mainMenu_vkbdLanguage);
        fscanf(f,"vkbdstyle=%d\n",&mainMenu_vkbdStyle);
        fscanf(f,"sound=%d\n",&mainMenu_sound );
        if (mainMenu_sound >= 10) {
            mainMenu_soundStereo = 1;
            mainMenu_sound -= 10;
        } else
            mainMenu_soundStereo = 0;
        fscanf(f,"soundstereosep=%d\n",&mainMenu_soundStereoSep );
        fscanf(f,"soundrate=%d\n",&sound_rate);
#ifdef __SWITCH__
        // only 48 kHz supported on Switch
        sound_rate = DEFAULT_SOUND_FREQ;
#endif
        fscanf(f,"autosave=%d\n",&mainMenu_autosave);
        fscanf(f,"gp2xclock=%d\n", &gp2xClockSpeed);
        int joybuffer = 0;
        fscanf(f,"joyconf=%d\n",&joybuffer);
        mainMenu_joyConf = (joybuffer & 0x0f);
        mainMenu_joyPort = ((joybuffer >> 4) & 0x0f);
        if (mainMenu_joyPort == 0)
            mainMenu_joyPort = 2;
        fscanf(f,"autofireRate=%d\n",&mainMenu_autofireRate);
        fscanf(f,"autofire=%d\n",&mainMenu_autofire);
        fscanf(f,"customAutofireButton=%d\n",&mainMenu_customAutofireButton);
// Never actually load the custom Autofire button to reduce user confusion
        mainMenu_customAutofireButton = 0;
        fscanf(f,"stylusOffset=%d\n",&mainMenu_stylusOffset);
        fscanf(f,"tapDelay=%d\n",&mainMenu_tapDelay);
        fscanf(f,"scanlines=%d\n",&mainMenu_scanlines);
#if defined(PANDORA) || defined(ANDROIDSDL)
        fscanf(f,"ham=%d\n",&dummy);
#else
        fscanf(f,"ham=%d\n",&mainMenu_ham);
#endif
        fscanf(f,"enableScreenshots=%d\n",&mainMenu_enableScreenshots);
        fscanf(f,"floppyspeed=%d\n",&mainMenu_floppyspeed);
        fscanf(f,"drives=%d\n",&nr_drives);
        fscanf(f,"videomode=%d\n",&mainMenu_ntsc);
        fscanf(f,"mainMenu_cpuSpeed=%d\n",&mainMenu_cpuSpeed);
        fscanf(f,"presetModeId=%d\n",&presetModeId);
        fscanf(f,"moveX=%d\n",&moveX);
        fscanf(f,"moveY=%d\n",&moveY);
        moveY+=16; // compatibility with versions <1.96
        fscanf(f,"displayedLines=%d\n",&mainMenu_displayedLines);
        fscanf(f,"screenWidth=%d\n",&screenWidth);
        fscanf(f,"cutLeft=%d\n",&mainMenu_cutLeft);
        fscanf(f,"cutRight=%d\n",&mainMenu_cutRight);
        fscanf(f,"customControls=%d\n",&mainMenu_customControls);
#if !defined(__PSP2__) && !defined(__SWITCH__)
        fscanf(f,"custom_dpad=%d\n",&mainMenu_custom_dpad);
        fscanf(f,"custom_up=%d\n",&mainMenu_custom_up[0]);
        fscanf(f,"custom_down=%d\n",&mainMenu_custom_down[0]);
        fscanf(f,"custom_left=%d\n",&mainMenu_custom_left[0]);
        fscanf(f,"custom_right=%d\n",&mainMenu_custom_right[0]);
        fscanf(f,"custom_A=%d\n",&mainMenu_custom_A[0]);
        fscanf(f,"custom_B=%d\n",&mainMenu_custom_B[0]);
        fscanf(f,"custom_X=%d\n",&mainMenu_custom_X[0]);
        fscanf(f,"custom_Y=%d\n",&mainMenu_custom_Y[0]);
        fscanf(f,"custom_L=%d\n",&mainMenu_custom_L[0]);
        fscanf(f,"custom_R=%d\n",&mainMenu_custom_R[0]);
#else
		fscanf(f,"custom_controlSet=%d\n",&mainMenu_custom_controlSet);
		int config_1_73 = -1;
		int config_1_82 = -1;
		int config_1_83 = -1;
		int l=0;
		int m=0;
		for (int i=0; i<MAX_NUM_CONTROLLERS; i++)
		{
			if (config_1_82==1)
				break;
			for (int j=0; j<MAX_NUM_CUSTOM_PRESETS; j++) {
#ifdef __SWITCH__
				if (!(i==0 && j==1)) {
#endif
				if (config_1_83 == -1) {
					if (!fscanf(f,"custom%d\n",&l)) {
						config_1_82 = 1;
						break;
					}
					if (j==3 && l!=4) {
						config_1_83 = 1;
						break;
					}
				}
				else 
					config_1_83 = -1;
				fscanf(f,"_up_Ply%d=%d\n",&m,&mainMenu_customPreset_up[j][i]);
#ifdef __SWITCH__
				}
#endif
				fscanf(f,"custom%d_down_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_down[j][i]);
				fscanf(f,"custom%d_left_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_left[j][i]);
				fscanf(f,"custom%d_right_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_right[j][i]);
				if (fscanf(f,"custom%d_stickup_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_stickup[j][i]) > 1) {
					fscanf(f,"custom%d_stickdown_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_stickdown[j][i]);
					fscanf(f,"custom%d_stickleft_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_stickleft[j][i]);
					fscanf(f,"custom%d_stickright_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_stickright[j][i]);
					fscanf(f,"custom%d_A_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_A[j][i]);
				} else {
					mainMenu_customPreset_stickup[j][i] = mainMenu_customPreset_up[j][i];
					mainMenu_customPreset_stickdown[j][i] = mainMenu_customPreset_down[j][i];
					mainMenu_customPreset_stickleft[j][i] = mainMenu_customPreset_left[j][i];
					mainMenu_customPreset_stickright[j][i] = mainMenu_customPreset_right[j][i];
					fscanf(f,"A_Ply%d=%d\n",&m,&mainMenu_customPreset_A[j][i]);
				}
				fscanf(f,"custom%d_B_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_B[j][i]);
				fscanf(f,"custom%d_X_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_X[j][i]);
				fscanf(f,"custom%d_Y_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_Y[j][i]);
				fscanf(f,"custom%d_L_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_L[j][i]);
				fscanf(f,"custom%d_R_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_R[j][i]);
#ifdef __SWITCH__
				if (j == 0 && i == 0) {
					if (fscanf(f,"custom%d_L2_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_L2[j][i]) > 1) {
						fscanf(f,"custom%d_R2_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_R2[j][i]);
						fscanf(f,"custom%d_L3_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_L3[j][i]);
						fscanf(f,"custom%d_R3_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_R3[j][i]);
						fscanf(f,"custom%d_up_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_up[j+1][i]);
						config_1_73 = 0;
					} else {
						fscanf(f,"up_Ply%d=%d\n",&m,&mainMenu_customPreset_up[j+1][i]);
						config_1_73 = 1;
					}
				} else {
					if (config_1_73 == 0) {
						fscanf(f,"custom%d_L2_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_L2[j][i]);
						fscanf(f,"custom%d_R2_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_R2[j][i]);
						fscanf(f,"custom%d_L3_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_L3[j][i]);
						fscanf(f,"custom%d_R3_Ply%d=%d\n",&l,&m,&mainMenu_customPreset_R3[j][i]);
					}
				}
#endif
			}
		}
		remap_custom_controls(); // update the custom variables with the appropriate set.
		if (config_1_82 == 1) {
			fscanf(f,"pu=%d\n",&mainMenu_CPU_model);
		} else
#endif //__PSP2__
		fscanf(f,"cpu=%d\n",&mainMenu_CPU_model);
        fscanf(f,"chipset=%d\n",&mainMenu_chipset);
        fscanf(f,"spritecollisions=%d\n",&mainMenu_spriteCollisions);
        fscanf(f,"cpu=%d\n",&mainMenu_CPU_speed);
        if(mainMenu_CPU_speed < 0) {
            // New version of this option
            mainMenu_CPU_speed = -mainMenu_CPU_speed;
        } else {
            // Old version (500 5T 1200 12T 12T2)
            if(mainMenu_CPU_speed >= 2) {
                // 1200: set to 68020 with 14 MHz
                mainMenu_CPU_model = 1;
                mainMenu_CPU_speed--;
                if(mainMenu_CPU_speed > 2)
                    mainMenu_CPU_speed = 2;
            }
        }

        memset(filebuffer, 0, 256);
        //fscanf cannot be used to read zero length strings, so read the equal sign, too
        if (fscanf(f,"df0%s\n",filebuffer)) {
            replace(filebuffer,' ','|');
            strcpy(uae4all_image_file0,filebuffer+1);
            extractFileName(uae4all_image_file0,filename0);
        } else {
            memset(uae4all_image_file0, 0, 256);
            memset(filename0, 0, 256);
        }
        if (fscanf(f,"df1%s\n",filebuffer)) {
            replace(filebuffer,' ','|');
            strcpy(uae4all_image_file1,filebuffer+1);
            extractFileName(uae4all_image_file1,filename1);
        } else {
            memset(uae4all_image_file1, 0, 256);
            memset(filename1, 0, 256);
        }
        if (fscanf(f,"df2%s\n",filebuffer)) {
            replace(filebuffer,' ','|');
            strcpy(uae4all_image_file2,filebuffer+1);
            extractFileName(uae4all_image_file2,filename2);
        } else {
            memset(uae4all_image_file2, 0, 256);
            memset(filename2, 0, 256);
        }
        if (fscanf(f,"df3%s\n",filebuffer)) {
            replace(filebuffer,' ','|');
            strcpy(uae4all_image_file3,filebuffer+1);
            extractFileName(uae4all_image_file3,filename3);
        } else {
            memset(uae4all_image_file3, 0, 256);
            memset(filename3, 0, 256);
        }

        mainMenu_drives=nr_drives;
        // in versions <=1.70, some config files are missing the following
        // hd settings, so skip them if the `script=`` line is absent
        int oldconfig = fscanf(f,"script=%d\n",&mainMenu_enableScripts);
        if (oldconfig != 0) {
            fscanf(f,"screenshot=%d\n", &mainMenu_enableScreenshots);
            fscanf(f,"skipintro=%d\n", &skipintro);
            fscanf(f,"boot_hd=%d\n",&mainMenu_bootHD);

            fscanf(f,"hard_disk_dir=",uae4all_hard_dir);
            uae4all_hard_dir[0] = '\0';
            {
                char c[2] = {0, 0};
                *c = fgetc(f);
                while (*c && (*c != '\n')) {
                    strcat(uae4all_hard_dir, c);
                    *c = fgetc(f);
                }
            }
            if (uae4all_hard_dir[0] == '*')
                uae4all_hard_dir[0] = '\0';
    			//HDF0
            fscanf(f,"hard_disk_file0=",uae4all_hard_file0);
            uae4all_hard_file0[0] = '\0';
            {
                char c[2] = {0, 0};
                *c = fgetc(f);
                while (*c && (*c != '\n')) {
                    strcat(uae4all_hard_file0, c);
                    *c = fgetc(f);
                }
            }
            if (uae4all_hard_file0[0] == '*')
                uae4all_hard_file0[0] = '\0';
            //HDF1
            fscanf(f,"hard_disk_file1=",uae4all_hard_file1);
            uae4all_hard_file1[0] = '\0';
            {
                char c[2] = {0, 0};
                *c = fgetc(f);
                while (*c && (*c != '\n')) {
                    strcat(uae4all_hard_file1, c);
                    *c = fgetc(f);
                }
            }
            if (uae4all_hard_file1[0] == '*')
                uae4all_hard_file1[0] = '\0';
            //HDF2
            fscanf(f,"hard_disk_file2=",uae4all_hard_file2);
            uae4all_hard_file2[0] = '\0';
            {
                char c[2] = {0, 0};
                *c = fgetc(f);
                while (*c && (*c != '\n')) {
                    strcat(uae4all_hard_file2, c);
                    *c = fgetc(f);
                }
            }
            if (uae4all_hard_file2[0] == '*')
                uae4all_hard_file2[0] = '\0';
            //HDF3
            fscanf(f,"hard_disk_file3=",uae4all_hard_file3);
            uae4all_hard_file3[0] = '\0';
            {
                char c[2] = {0, 0};
                *c = fgetc(f);
                while (*c && (*c != '\n')) {
                    strcat(uae4all_hard_file3, c);
                    *c = fgetc(f);
                }
            }
            if (uae4all_hard_file3[0] == '*')
                uae4all_hard_file3[0] = '\0';
        }
        fscanf(f,"chipmemory=%d\n",&mainMenu_chipMemory);
        fscanf(f,"slowmemory=%d\n",&mainMenu_slowMemory);
        fscanf(f,"fastmemory=%d\n",&mainMenu_fastMemory);
#ifdef ANDROIDSDL
        fscanf(f,"onscreen=%d\n",&mainMenu_onScreen);
        fscanf(f,"onScreen_textinput=%d\n",&mainMenu_onScreen_textinput);
        fscanf(f,"onScreen_dpad=%d\n",&mainMenu_onScreen_dpad);
        fscanf(f,"onScreen_button1=%d\n",&mainMenu_onScreen_button1);
        fscanf(f,"onScreen_button2=%d\n",&mainMenu_onScreen_button2);
        fscanf(f,"onScreen_button3=%d\n",&mainMenu_onScreen_button3);
        fscanf(f,"onScreen_button4=%d\n",&mainMenu_onScreen_button4);
        fscanf(f,"onScreen_button5=%d\n",&mainMenu_onScreen_button5);
        fscanf(f,"onScreen_button6=%d\n",&mainMenu_onScreen_button6);
        fscanf(f,"custom_position=%d\n",&mainMenu_custom_position);
        fscanf(f,"pos_x_textinput=%d\n",&mainMenu_pos_x_textinput);
        fscanf(f,"pos_y_textinput=%d\n",&mainMenu_pos_y_textinput);
        fscanf(f,"pos_x_dpad=%d\n",&mainMenu_pos_x_dpad);
        fscanf(f,"pos_y_dpad=%d\n",&mainMenu_pos_y_dpad);
        fscanf(f,"pos_x_button1=%d\n",&mainMenu_pos_x_button1);
        fscanf(f,"pos_y_button1=%d\n",&mainMenu_pos_y_button1);
        fscanf(f,"pos_x_button2=%d\n",&mainMenu_pos_x_button2);
        fscanf(f,"pos_y_button2=%d\n",&mainMenu_pos_y_button2);
        fscanf(f,"pos_x_button3=%d\n",&mainMenu_pos_x_button3);
        fscanf(f,"pos_y_button3=%d\n",&mainMenu_pos_y_button3);
        fscanf(f,"pos_x_button4=%d\n",&mainMenu_pos_x_button4);
        fscanf(f,"pos_y_button4=%d\n",&mainMenu_pos_y_button4);
        fscanf(f,"pos_x_button5=%d\n",&mainMenu_pos_x_button5);
        fscanf(f,"pos_y_button5=%d\n",&mainMenu_pos_y_button5);
        fscanf(f,"pos_x_button6=%d\n",&mainMenu_pos_x_button6);
        fscanf(f,"pos_y_button6=%d\n",&mainMenu_pos_y_button6);
        fscanf(f,"quick_switch=%d\n",&mainMenu_quickSwitch);
        fscanf(f,"FloatingJoystick=%d\n",&mainMenu_FloatingJoystick);
        fscanf(f,"button_size=%f\n",&mainMenu_button_size);
#endif
#if defined(ANDROIDSDL) || defined(AROS)
		fscanf(f,"VSync=%d\n",&mainMenu_vsync);
#endif
        memset(filebuffer, 0, 256);
        fscanf(f,"custom_kickrom=%s\n",filebuffer);
        replace(filebuffer,' ','|');
        if (filebuffer[0]) {
            strcpy(custom_kickrom, filebuffer);
        }
        // ignore this option. All saves are always made into saves folder now
        fscanf(f,"useSavesFolder=%d\n",&mainMenu_useSavesFolder);
        mainMenu_useSavesFolder = DEFAULT_USESAVESFOLDER;
#ifdef __SWITCH__ 
        fscanf(f,"swapAB=%d\n",&mainMenu_swapAB);
        fscanf(f,"singleJoycons=%d\n",&mainMenu_singleJoycons);
#endif
        fclose(f);
    }
// make sure the just-loaded mainMenu_displayedLines is not changed by setPresetMode
    int old_displayedLines = mainMenu_displayedLines;
    SetPresetMode(presetModeId);
    mainMenu_displayedLines = old_displayedLines;
    UpdateCPUModelSettings();
    UpdateChipsetSettings();
#ifdef USE_GUICHAN
    if (running==false)
#endif
    {
#if !defined(__PSP2__) && !defined(__SWITCH__)
        update_display();
#endif
    }
    UpdateMemorySettings();
    set_joyConf();
}
