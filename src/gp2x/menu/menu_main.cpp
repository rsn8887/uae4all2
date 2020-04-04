#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <SDL.h>

#if defined(ANDROID)
#include <SDL_screenkeyboard.h>
#endif

#include "sysconfig.h"
#include "sysdeps.h"
#include "config.h"
#include "gp2xutil.h"
#include "menu.h"
#include "menu_config.h"
#include "autoconf.h"
#ifdef USE_UAE4ALL_VKBD
#include "vkbd.h"
#endif
#include "options.h"
#include "sound.h"
#include "zfile.h"
#include "gui.h"
#include "gp2x.h"
#include "disk.h"
#include "cpuspeed/cpuctrl.h"
#include "custom.h"



/* PocketUAE config file. Used for parsing PocketUAE-like options. */
#include "savestate.h"

#if defined(__PSP2__) // NOT __SWITCH__
#include <psp2/shellutil.h>
#include <psp2/io/fcntl.h>
#endif
 
#ifdef __SWITCH__
#include <switch.h>
extern void update_joycon_mode();
#endif
 
#if defined(__PSP2__) || defined(__SWITCH__)
#define SDL_PollEvent PSP2_PollEvent
int inside_menu = 0;
#endif

extern int kickstart;
extern int oldkickstart;
extern int bReloadKickstart;
extern unsigned int sound_rate;
extern int skipintro;
extern int moveX;
extern int moveY;
extern int timeslice_mode;
extern int emulating;
extern int gp2xMouseEmuOn;
extern int gp2xButtonRemappingOn;

extern int init_sound(void);
extern void leave_program(void);
extern void extractFileName(char * str,char *buffer);
extern void update_display(void);
extern int saveAdfDir(void);
extern void setCpuSpeed(void);
extern void show_error(const char *);
extern void close_joystick();
extern void init_joystick();

extern char launchDir[300];
extern char currentDir[300];

extern char filename0[256];
extern char filename1[256];
extern char filename2[256];
extern char filename3[256];

extern char config_load_filename[300];

#ifdef __PSP2__
static const char *text_str_title=    "----- UAE4All Vita " VERSION_MAJOR "." VERSION_MINOR " -----";
#else
#ifdef __SWITCH__
static const char *text_str_title=    "----- UAE4All Switch " VERSION_MAJOR "." VERSION_MINOR " -----";
#else
#ifdef PANDORA
static const char *text_str_title=    "----- UAE4All Pandora -----";
#else
static const char *text_str_title=    "----- UAE4All Android -----";
#endif
#endif
#endif // __PSP2__
static const char *text_str_df0=		"DF0:";
static const char *text_str_df1=		"DF1:";
static const char *text_str_df2=		"DF2:";
static const char *text_str_df3=		"DF3:";
#if defined(__PSP2__) || defined(__SWITCH__)
static const char* text_str_hdnmem="Harddisk and Memory Options";
static const char *text_str_display="Display and Sound";
static const char *text_str_savestates="Savestates";
#else
static const char* text_str_hdnmem="Harddisk and Memory Options (H)";
static const char *text_str_display="Display and Sound (L-trigger)";
static const char *text_str_savestates="Savestates (S)";
#endif
static const char *text_str_eject="Eject All Drives";
const char *text_str_separator="---------------------------------";
#ifdef PANDORA
static const char *text_str_reset="Reset (R-trigger)";
#else
static const char *text_str_reset="Reset (Start Emulator)";
#endif
#if defined(__PSP2__) || defined(__SWITCH__)
static const char *text_str_exit= "Quit (L-trigger)";
#else
static const char *text_str_exit= "Quit (Q)";
#endif
#if defined(__PSP2__) || defined(__SWITCH__)
static const char *text_str_custom= "Custom Control Config";
#else
static const char *text_str_custom= "Custom Control Config (Y)";
#endif
#if defined(__PSP2__) || defined(__SWITCH__)
static const char *text_str_more= "More Options";
#else
static const char *text_str_more= "More Options (B)";
#endif
#if defined(__SWITCH__)
static const char *text_str_releasenotes= "Release Notes";
#endif

int mainMenu_case=-1;
int mainMenu_system=-1;
int quit_pressed_in_submenu=0;

int nr_drives=DEFAULT_DRIVES;
int current_drive=0;

int force_quit=0;

int lastCpuSpeed=600;
int ntsc=0;

#if defined(__PSP2__) || defined(__SWITCH__)
int ps_button_locked = 0;
#endif

static void adjustToWindow(char *str, char* buffer)
{
	if (strlen(str)<33) return;
	char *p=str+strlen(str)-13;
	for (int i=0;i<15;i++) {buffer[i]=*str;str++;}
	char tt[]={'.','.','.','\0',};
	strcat(buffer,tt);
	strcat(buffer,p);
}

static void showInfo()
{
	text_draw_background();
	char buffer[128];
	char buffertext[128];

	text_draw_window(2,2,35,20,"Info");
	SDL_Rect r;
	r.x=80-64; r.y=0; r.w=35*7; r.h=140;
	extern SDL_Surface *text_screen;
	SDL_SetClipRect(text_screen,&r);
	write_text(4,2,"DF0");

	extractFileName(uae4all_image_file0,buffer);
	adjustToWindow(buffer,buffertext);
	write_text(10,2,buffertext);

	write_text(4,4,"DF1");
	if (!uae4all_image_file1[0]) write_text(10,4,"Empty");
	else 
	{
		extractFileName(uae4all_image_file1,buffer);
		adjustToWindow(buffer,buffertext);
		write_text(10,4,buffer);
	}

	write_text(4,6,"DF2");
	if (!uae4all_image_file2[0]) write_text(10,4,"Empty");
	else 
	{
		extractFileName(uae4all_image_file2,buffer);
		adjustToWindow(buffer,buffertext);
		write_text(10,6,buffer);
	}
	
	write_text(4,8,"DF3");
	if (!uae4all_image_file3[0]) write_text(10,4,"Empty");
	else 
	{
		extractFileName(uae4all_image_file3,buffer);
		adjustToWindow(buffer,buffertext);
		write_text(10,8,buffer);
	}

		text_flip();
		SDL_Event ev;
		SDL_Delay(333);
		while(SDL_PollEvent(&ev))
		SDL_Delay(10);
		while(!SDL_PollEvent(&ev))
				SDL_Delay(10);
		while(SDL_PollEvent(&ev))
				if (ev.type==SDL_QUIT)
					exit(1);
		SDL_Delay(200);
		SDL_SetClipRect(text_screen,NULL);
}

static void draw_mainMenu(int c)
{
	/* New Menu
	0 = DF0:
	1 = DF1:
	2 = DF2:
	3 = DF3:
	4 = eject all drives
	5 = number of drives
	6 = preset system setup
	7 = harddisk and memory options
	8 = display settings
	9 = savestates
	10 = custom controls
	11 = more options
	12 = reset
	13 = load config
	14 = save config as...
	15 = delete config
	16 = save general config
	17 = save config current game
	18 = quit
	19 = release notes (Switch only) 
	*/
	static int b=0;
	int bb=(b%6)/3;
	int menuLine = 3;
	int leftMargin = 7;
	int tabstop1 = 16+4;
	int tabstop2 = 18+4;
	int tabstop3 = 20+4;
	int tabstop4 = 22+4;
	int tabstop5 = 24+4;
	int tabstop6 = 26+4;
	int tabstop7 = 28+4;
	int tabstop8 = 30+4;
	int tabstop9 = 32+4;

	text_draw_background();
	text_draw_window(leftMargin-1,menuLine-1,35,40,text_str_title);

	// 0
	if ((c==0)&&(bb))
		write_text_inv(leftMargin,menuLine,text_str_df0);
	else
		write_text(leftMargin,menuLine,text_str_df0);
	if(strcmp(uae4all_image_file0, "")==0)
		write_text_inv(13,menuLine,"insert disk image");
	else
		write_text_inv(13,menuLine,filename0);

	// 1
	menuLine+=2;
	if(nr_drives > 1)
	{
		if((c==1)&&(bb))
			write_text_inv(leftMargin,menuLine,text_str_df1);
		else
			write_text(leftMargin,menuLine,text_str_df1);
		if(strcmp(uae4all_image_file1, "")==0)
			write_text_inv(13,menuLine,"insert disk image");
		else
			write_text_inv(13,menuLine,filename1);
	}

	// 2
	menuLine+=2;
	if(nr_drives > 2)
	{
		if ((c==2)&&(bb))
			write_text_inv(leftMargin,menuLine,text_str_df2);
		else
			write_text(leftMargin,menuLine,text_str_df2);
		if(strcmp(uae4all_image_file2, "")==0)
			write_text_inv(13,menuLine,"insert disk image");
		else
			write_text_inv(13,menuLine,filename2);
	}

	// 3
	menuLine+=2;
	if(nr_drives > 3)
	{
		if ((c==3)&&(bb))
			write_text_inv(leftMargin,menuLine,text_str_df3);
		else
			write_text(leftMargin,menuLine,text_str_df3);
		if(strcmp(uae4all_image_file3, "")==0)
			write_text_inv(13,menuLine,"insert disk image");
		else
			write_text_inv(13,menuLine,filename3);
	}

	menuLine++;
	write_text(leftMargin,menuLine,text_str_separator);
	menuLine++;

	// 4
	if ((c==4)&&(bb))
		write_text_inv(leftMargin,menuLine,text_str_eject);
	else
		write_text(leftMargin, menuLine,text_str_eject);

	// 5
	menuLine+=2;
	write_text(leftMargin,menuLine,"Number of Drives");
	
	if ((nr_drives==1)&&((c!=5)||(bb)))
		write_text_inv(tabstop3,menuLine,"1");
	else
		write_text(tabstop3,menuLine,"1");

	if ((nr_drives==2)&&((c!=5)||(bb)))
		write_text_inv(tabstop4,menuLine,"2");
	else
		write_text(tabstop4,menuLine,"2");

	if ((nr_drives==3)&&((c!=5)||(bb)))
		write_text_inv(tabstop5,menuLine,"3");
	else
		write_text(tabstop5,menuLine,"3");

	if ((nr_drives==4)&&((c!=5)||(bb)))
		write_text_inv(tabstop6,menuLine,"4");
	else
		write_text(tabstop6,menuLine,"4");

	menuLine++;
	write_text(leftMargin,menuLine,text_str_separator);
	menuLine++;

	// 6
	write_text(leftMargin,menuLine,"Preset System Setup:");

	if ((mainMenu_system!=1)&&((c!=6)||(bb)))
		write_text_inv(tabstop5+1,menuLine,"A500");
	else
		write_text(tabstop5+1,menuLine,"A500");

	if ((mainMenu_system!=0)&&((c!=6)||(bb)))
		write_text_inv(tabstop8,menuLine,"A1200");
	else
		write_text(tabstop8,menuLine,"A1200");

	// 7
	menuLine+=2;
	if ((c==7)&&(bb))
		write_text_inv(leftMargin,menuLine,text_str_hdnmem);
	else
		write_text(leftMargin,menuLine,text_str_hdnmem);

	// 8
	menuLine+=2;
	if ((c==8)&&(bb))
		write_text_inv(leftMargin,menuLine,text_str_display);
	else
		write_text(leftMargin,menuLine,text_str_display);

	// 9
	menuLine+=2;
	if ((c==9)&&(bb))
		write_text_inv(leftMargin,menuLine,text_str_savestates);
	else
		write_text(leftMargin,menuLine,text_str_savestates);

	// 10
	menuLine+=2;
	if ((c==10)&&(bb))
		write_text_inv(leftMargin,menuLine,text_str_custom);
	else
		write_text(leftMargin,menuLine,text_str_custom);

	// 11
	menuLine+=2;
	if ((c==11)&&(bb))
		write_text_inv(leftMargin,menuLine,text_str_more);
	else
		write_text(leftMargin,menuLine,text_str_more);

	menuLine++;
	write_text(leftMargin,menuLine,text_str_separator);

	// 12
	menuLine++;
	if ((c==12)&&(bb))
		write_text_inv(leftMargin,menuLine,text_str_reset);
	else
		write_text(leftMargin,menuLine,text_str_reset);

	menuLine++;
	write_text(leftMargin,menuLine,text_str_separator);

	// 13
	menuLine++;
	write_text(leftMargin,menuLine,"Config");

	if ((c==13)&&(bb))
		write_text_inv(leftMargin+7,menuLine,"Load");
	else
		write_text(leftMargin+7,menuLine,"Load");

	// 14
	if ((c==14)&&(bb))
		write_text_inv(leftMargin+13,menuLine,"Save As");
	else
		write_text(leftMargin+13,menuLine,"Save As");

	// 15
	if ((c==15)&&(bb))
		write_text_inv(leftMargin+22,menuLine,"Delete");
	else
		write_text(leftMargin+22,menuLine,"Delete");

	// 16
	menuLine+=2;
	if ((c==16)&&(bb))
		write_text_inv(leftMargin+7,menuLine,"Save General");
	else
		write_text(leftMargin+7,menuLine,"Save General");

	// 17
	if ((c==17)&&(bb))
		write_text_inv(leftMargin+20,menuLine,"Save Per-Game");
	else
		write_text(leftMargin+20,menuLine,"Save Per-Game");

	menuLine++;
	write_text(leftMargin,menuLine,text_str_separator);

	// 18
	menuLine++;
	if ((c==18)&&(bb))
		write_text_inv(leftMargin,menuLine,text_str_exit);
	else
		write_text(leftMargin,menuLine,text_str_exit);

#ifdef __SWITCH__
	// 19
	if ((c==19)&&(bb))
		write_text_inv(leftMargin+20,menuLine,text_str_releasenotes);
	else
		write_text(leftMargin+20,menuLine,text_str_releasenotes);
#endif

	menuLine++;
	write_text(leftMargin,menuLine,text_str_separator);

	text_flip();
	
	b++;
}

void showWarning(const char *msg)
{
	text_draw_window(4,9,37,4,"Message");
	write_text(5,11,msg);
	//write_text(11,16,"Press any button to continue");
	text_flip();
	SDL_Event ev;
	SDL_Delay(1000);
	while(SDL_PollEvent(&ev))
	{
		if (ev.type==SDL_QUIT)
			exit(1);
		SDL_Delay(10);
	}
}

void setSystem()
{
	if(mainMenu_system > 0)
	{
		mainMenu_chipMemory=2;
		mainMenu_slowMemory=0;
		mainMenu_fastMemory=4;
		kickstart=3;
		mainMenu_CPU_model=1;
		mainMenu_chipset=2;
		mainMenu_chipset|=0x100;//set blitter to "immediate"
		mainMenu_CPU_speed=1;
	}
	else
	{
		mainMenu_chipMemory=1;
		mainMenu_slowMemory=0;
		mainMenu_fastMemory=0;
		kickstart=1;
		mainMenu_CPU_model=0;
		mainMenu_chipset=0;
		mainMenu_chipset|=0x100;//set blitter to "immediate"
		mainMenu_CPU_speed=0;
	}
	UpdateMemorySettings();
	UpdateCPUModelSettings();
	UpdateChipsetSettings();
}

static int key_mainMenu(int *cp)
{
#ifdef ANDROIDSDL
SDL_ANDROID_SetScreenKeyboardShown(1);
#endif
	int back_c=-1;
	int c=(*cp);
	int end=0;
	int left=0, right=0, up=0, down=0, hit0=0, hit1=0, hit2=0, hit3=0, hit4=0, hit5=0, hit6=0, hitH=0, hitS=0, hitQ=0, hitN1=0, hitN2=0, hitN3=0, hitN4=0;
	SDL_Event event;
	int info=0;
	
	force_quit=0;

	static int holdingUp=0;
	static int holdingDown=0;
	static int holdingRight=0;
	static int holdingLeft=0;
	static Uint32 menu_last_press_time=0;
	static Uint32 menu_last_move_time=0;
	Uint32 now=SDL_GetTicks();
	if (holdingLeft || holdingRight || holdingUp || holdingDown)
	{
		if (now-menu_last_press_time>MENU_MIN_HOLDING_TIME && now-menu_last_move_time>MENU_MOVE_DELAY)
		{
			menu_last_move_time=now;
			SDL_Event ev;
			ev.type = SDL_KEYDOWN;
			if (holdingLeft)
				ev.key.keysym.sym = SDLK_LEFT;
			else if (holdingRight)
				ev.key.keysym.sym = SDLK_RIGHT;
			else if (holdingUp)
				ev.key.keysym.sym = SDLK_UP;
			else if (holdingDown)
				ev.key.keysym.sym = SDLK_DOWN;
			SDL_PushEvent(&ev);
		}
	}

	while (SDL_PollEvent(&event) > 0)
	{
		left=right=up=down=hit0=hit1=hit2=hit3=hit4=hit5=hit6=hitH=hitS=hitQ=hitN1=hitN2=hitN3=hitN4=0;
		if (event.type == SDL_QUIT)
		{
			mainMenu_case=MAIN_MENU_CASE_QUIT;
			end=-1;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			uae4all_play_click();
			switch(event.key.keysym.sym)
			{
				case SDLK_RIGHT: right=1; break;
				case SDLK_LEFT: left=1; break;
				case SDLK_UP: up=1; break;
				case SDLK_DOWN: down=1; break;
				case SDLK_PAGEDOWN: hit0=1; break;
				case SDLK_LALT: hit1=1; break;
				case SDLK_LCTRL: hit2=1; break;
#if defined(__PSP2__) || defined(__SWITCH__) //RSHIFT is PAD_L on Vita
				case SDLK_RSHIFT: hitQ=1; break;
#else
				case SDLK_RSHIFT: hit3=1; break;
				case SDLK_END: hit5=1; break;
				case SDLK_PAGEUP: hit6=1; break;
				case SDLK_HOME: hit0=1; break;
#endif
				case SDLK_RCTRL: hit4=1; break;
				case SDLK_i: info=1; break;
				case SDLK_h: hitH=1; break;
				case SDLK_s: hitS=1; break;
				case SDLK_q: hitQ=1; break;
				case SDLK_1: hitN1=1; break;
				case SDLK_2: hitN2=1; break;
				case SDLK_3: hitN3=1; break;
				case SDLK_4: hitN4=1;
			}
		} else if (event.type == SDL_KEYUP)
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_RIGHT:
					holdingRight=0;
					break;
				case SDLK_LEFT:
					holdingLeft=0;
					break;
				case SDLK_UP:
					holdingUp=0;
					break;
				case SDLK_DOWN:
					holdingDown=0;
					break;
				default:
					break;
			}
		}
		
		if (left && !holdingLeft)
		{
			holdingLeft=1;
			menu_last_press_time=now;
		}
		if (right && !holdingRight) 
		{
			holdingRight=1;
			menu_last_press_time=now;
		}
		if (up && !holdingUp) 
		{
			holdingUp=1;
			menu_last_press_time=now;
		}
		if (down && !holdingDown) 
		{
			holdingDown=1;
			menu_last_press_time=now;
		}

		if (info)
			showInfo();
		else if (hit1)
		{
			mainMenu_case=MAIN_MENU_CASE_RUN;
			end=1;
		}
		else if (hit2)
		{
			mainMenu_case=MAIN_MENU_CASE_CANCEL;
			end=1;
		}
		else if (hit3)
		{
			mainMenu_case=MAIN_MENU_CASE_DISPLAY;
			end=1;
		}
		else if (hit4)
		{
			// reset
			back_c = c;
			hit0 = 1;
			c = 12;
		}
		else if (hit5)
		{
			// more options
			back_c = c;
			hit0 = 1;
			c = 11;
		}
		else if (hit6)
		{
			// custom controls
			back_c = c;
			hit0 = 1;
			c = 10;
		}
		else if (hitH)
		{
			mainMenu_case=MAIN_MENU_CASE_MEMDISK;
			end=1;
		}
		else if (hitS)
		{
			mainMenu_case=MAIN_MENU_CASE_SAVESTATES;
			end=1;
		}
		else if (hitQ && right)
		{
			force_quit=1;
			mainMenu_case=MAIN_MENU_CASE_QUIT;
			end=1;
		}
		else if (hitQ)
		{
			mainMenu_case=MAIN_MENU_CASE_QUIT;
			end=1;
		}
		else if(hitN1)
		{
			current_drive=0;
			mainMenu_case=MAIN_MENU_CASE_LOAD;
			end=1;
		}
		else if(hitN2)
		{
			current_drive=1;
			mainMenu_case=MAIN_MENU_CASE_LOAD;
			end=1;
		}
		else if(hitN3)
		{
			current_drive=2;
			mainMenu_case=MAIN_MENU_CASE_LOAD;
			end=1;
		}
		else if(hitN4)
		{
			current_drive=3;
			mainMenu_case=MAIN_MENU_CASE_LOAD;
			end=1;
		}
		else if (up)
		{
			if(nr_drives<2 && c==4)
				c=0;
			else if(nr_drives<3 && c==4)
				c=1;
			else if(nr_drives<4 && c==4)
				c=2;
			else
				c--;
#ifdef __SWITCH__
			if (c < 0) c = 19;
#else
			if (c < 0) c = 18;
#endif
		}
		else if (down)
		{
			if(nr_drives<4 && c==2)
				c=4;
			else if(nr_drives<3 && c==1)
				c=4;
			else if(nr_drives<2 && c==0)
				c=4;
			else
#ifdef __SWITCH__
				c=(c+1)%20;
#else
				c=(c+1)%19;
#endif
		}

	/* New Menu
	0 = DF0:
	1 = DF1:
	2 = DF2:
	3 = DF3:
	4 = eject all drives
	5 = number of drives
	6 = preset system setup
	7 = display settings
	8 = sound
	9 = savestates
	10 = custom controls
	11 = more options
	12 = reset
	13 = load config
	14 = save config as...
	15 = delete config
	16 = save general config
	17 = save config current game
	18 = exit
	19 = release notes (Switch only)
	*/
		switch(c)
		{
			case 0:
				if (hit0)
				{
					current_drive=0;
					mainMenu_case=MAIN_MENU_CASE_LOAD;
					end=1;
				}
				break;
			case 1:
				if (hit0)
				{
					current_drive=1;
					mainMenu_case=MAIN_MENU_CASE_LOAD;
					end=1;
				}
				break;
			case 2:
				if (hit0)
				{
					current_drive=2;
					mainMenu_case=MAIN_MENU_CASE_LOAD;
					end=1;
				}
				break;
			case 3:
				if (hit0)
				{
					current_drive=3;
					mainMenu_case=MAIN_MENU_CASE_LOAD;
					end=1;
				}
				break;
			case 4:
				if (hit0)
				{
					strcpy(uae4all_image_file0, "");
					strcpy(uae4all_image_file1, "");
					strcpy(uae4all_image_file2, "");
					strcpy(uae4all_image_file3, "");
				}
				break;
			case 5:
				if (left)
				{
					if (nr_drives>1)
						nr_drives--;
					else
						nr_drives=4;
				}
				else if (right)
				{
					if (nr_drives<4)
						nr_drives++;
					else
						nr_drives=1;
				}	
				break;
			case 6:
				if (left)
				{
					if (mainMenu_system==0)
						mainMenu_system=1;
					else
						mainMenu_system=0;
					setSystem();
				}
				else if (right)
				{
					if (mainMenu_system<1)
						mainMenu_system=1;
					else
						mainMenu_system=0;
					setSystem();
				}
				break;
			case 7:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_MEMDISK;
					end=1;
				}
				break;
			case 8:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_DISPLAY;
					end=1;
				}
				break;
			case 9:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_SAVESTATES;
					end=1;
				}
				break;
			case 10:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_CONTROLS;
					end=1;
				}
				break;
			case 11:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_MISC;
					printf("Launch main menu MISC\n");
					end=1;
				}
				break;
			case 12:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_RESET;
					end=1;
				}
				break;
			case 13:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_LOAD_CONFIG;
					end=1;
				}
				break;
			case 14:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_SAVE;
					if (saveconfig(4))
						showWarning("Config saved.");
				}
				break;
			case 15:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_DELETE_CONFIG;
					end=1;
				}
				break;
			case 16:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_SAVE;
					saveconfig(1);
					showWarning("General config file saved.");
				}
				break;
			case 17:
				if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_SAVE;
					if (saveconfig())
						showWarning("Config saved for this game.");
				}
				break;
			case 18:
				if (hit0 && right)
				{
					force_quit=1;
					mainMenu_case=MAIN_MENU_CASE_QUIT;
					end=1;
				}
				else if (hit0)
				{
					mainMenu_case=MAIN_MENU_CASE_QUIT;
					end=1;
				}
				break;
#ifdef __SWITCH__
			case 19:
				if (hit0)
				{
					// This works on all CFW
					WebWifiConfig conf;
					webWifiCreate(&conf, NULL, "https://github.com/rsn8887/uae4all2/releases/latest", (Uuid){0}, 0);
					webWifiShow(&conf, NULL);
					// The following would be better, but crashes on SX OS
					//WebCommonConfig config;
					//webPageCreate(&config,"https://github.com/rsn8887/uae4all2/releases/latest");
					//webConfigSetWhitelist(&config, "^http*");
					//webConfigShow(&config, NULL);
				}
				break;
#endif
		}
		if (back_c>=0)
		{
			c=back_c;
			back_c=-1;
		}			
	}

	(*cp)=c;
	return end;
}

static void raise_mainMenu()
{	
	text_draw_background();
	text_flip();
#if !defined(__PSP2__) && !defined(__SWITCH__)
	int i;
	for(i=0;i<10;i++)
	{
		text_draw_background();
		text_draw_window(40,(10-i)*24,260,200,text_str_title);
		text_flip();
	}
#endif
}

static void unraise_mainMenu()
{
#if !defined(__PSP2__) && !defined(__SWITCH__)
	int i;
	for(i=9;i>=0;i--)
	{
		text_draw_background();
		text_draw_window(40,(10-i)*24,260,200,text_str_title);
		text_flip();
	}
#endif
	text_draw_background();
	text_flip();
}

int run_mainMenu()
{
	static int c=0;
	int end;
	int old_sound_rate = sound_rate;
	int old_stereo = mainMenu_soundStereo;
	int old_vkbdLanguage = mainMenu_vkbdLanguage;
    int old_vkbdStyle = mainMenu_vkbdStyle;
	mainMenu_case=-1;
	init_text(0);
	
#if defined(__PSP2__) || defined(__SWITCH__)
	inside_menu = 1;
	SDL_Event event;
	while (SDL_PollEvent(&event) > 0);
#endif
   
	while(mainMenu_case<0)
	{
		raise_mainMenu();
		end=0;
		draw_mainMenu(c);
		while(!end)
		{
			draw_mainMenu(c);
			end=key_mainMenu(&c);
		}
		unraise_mainMenu();
		switch(mainMenu_case)
		{
		case MAIN_MENU_CASE_LOAD:
		{
			int autostate_loaded = 0;
			if(run_menuLoad(currentDir, MENU_LOAD_FLOPPY) && current_drive==0)
			{
				// Check for disk-specific config
				char path[300];
				create_configfilename(path, uae4all_image_file0, 0);
				FILE *f=fopen(path,"rt");
				if(f)
				{
					// config file exists -> load
					fclose(f);
					loadconfig();
				}
				// Check for disk-specific Auto Savestate and load it automatically if possible
				if (emulating)
				{
					int old_saveMenu_n_savestate = saveMenu_n_savestate;
					saveMenu_n_savestate=11;
					make_savestate_filenames(savestate_filename,screenshot_filename);
					f=fopen(savestate_filename,"rb");
					if (f)
					{
						fclose(f);
						savestate_state=STATE_DORESTORE;
						autostate_loaded=1;
					} else 
					{
						saveMenu_n_savestate=old_saveMenu_n_savestate;
						make_savestate_filenames(savestate_filename,screenshot_filename);
					}
				}
			}
			if (autostate_loaded==1)
			{
				setCpuSpeed();
				mainMenu_case=1;
			} 
			else 
			{
				mainMenu_case=-1;
			}
			break;
		}
		case MAIN_MENU_CASE_MEMDISK:
			run_menuMemDisk();
			if (quit_pressed_in_submenu) //User quit menu while in sub-menu
			{
				if (emulating)
				{
					setCpuSpeed();
					mainMenu_case=1;
				}
				else
					mainMenu_case=-1;
				quit_pressed_in_submenu=0;
			}
			else
				mainMenu_case=-1;
			break;
		case MAIN_MENU_CASE_SAVESTATES:
			run_menuSavestates();
			if(savestate_state == STATE_DORESTORE || savestate_state == STATE_DOSAVE)
			{
				setCpuSpeed();
				mainMenu_case=1;
			}
			else if (quit_pressed_in_submenu) //User quit menu while in sub-menu
			{
				if (emulating)
				{
					setCpuSpeed();
					mainMenu_case=1;
				}
				else
					mainMenu_case=-1;
				quit_pressed_in_submenu=0;
			}
			else
				mainMenu_case=-1;
			break;
		case MAIN_MENU_CASE_EJECT:
			mainMenu_case=3;
			break;
		case MAIN_MENU_CASE_CANCEL:
			if (emulating)
			{
				setCpuSpeed();
				mainMenu_case=1;
			}
			else
				mainMenu_case=-1;
			break;
		case MAIN_MENU_CASE_RESET:
			setCpuSpeed();
			gp2xMouseEmuOn=0;
			gp2xButtonRemappingOn=0;
			mainMenu_drives=nr_drives;
			if (kickstart!=oldkickstart) 
			{
				oldkickstart=kickstart;
				snprintf(romfile, 256, "%s/kickstarts/%s",launchDir,kickstarts_rom_names[kickstart]);
				bReloadKickstart=1;
				uae4all_init_rom(romfile);
#ifdef ANDROIDSDL
				if (uae4all_init_rom(romfile)==-1)
				{
				    snprintf(romfile, 256, "%s/../../com.cloanto.amigaforever.essentials/files/rom/%s",launchDir,af_kickstarts_rom_names[kickstart]);			
				    uae4all_init_rom(romfile);
				} 				
#endif
			}
			if (emulating)
			{
				mainMenu_case=2;	
				break;
			}
		case MAIN_MENU_CASE_RUN:
			setCpuSpeed();
			mainMenu_case=1;
			break;
		case MAIN_MENU_CASE_CONTROLS:
			{
				run_menuControls();
				if (quit_pressed_in_submenu) //User quit menu while in sub-menu
				{
					if (emulating)
					{
						setCpuSpeed();
						mainMenu_case=1;
					}
					else
						mainMenu_case=-1;
					quit_pressed_in_submenu=0;
				}
				else
					mainMenu_case=-1;
			}
			break;
		case MAIN_MENU_CASE_DISPLAY:
			{
				run_menuDisplay();
				if (quit_pressed_in_submenu) //User quit menu while in sub-menu
				{
					if (emulating)
					{
						setCpuSpeed();
						mainMenu_case=1;
					}
					else
						mainMenu_case=-1;
					quit_pressed_in_submenu=0;
				}
				else
					mainMenu_case=-1;
			}
			break;
		case MAIN_MENU_CASE_MISC:
			{
				run_menuMisc();
				if (quit_pressed_in_submenu) //User quit menu while in sub-menu
				{
					if (emulating)
					{
						setCpuSpeed();
						mainMenu_case=1;
					}
					else
						mainMenu_case=-1;
					quit_pressed_in_submenu=0;
				}
				else
					mainMenu_case=-1;
			}
			break;
		case MAIN_MENU_CASE_LOAD_CONFIG:
		{
			char path[300];
			snprintf(path, 300, "%s/conf", launchDir);

			if(run_menuLoad(path, MENU_LOAD_CONFIG))
				loadconfig(5);
			mainMenu_case=-1;
			break;
		}
		case MAIN_MENU_CASE_DELETE_CONFIG:
		{
			char path[300];
			snprintf(path, 300, "%s/conf", launchDir);

			if(run_menuLoad(path, MENU_LOAD_DELETE_CONFIG)) {
				FILE *f=fopen(config_load_filename,"rb");
				if (f) {
					fclose(f);
					if (remove(config_load_filename) == 0) {
						showWarning("Config File deleted");
					} else {
						showWarning("Config File does not exist.");
					}
				}
			}
			mainMenu_case=-1;
			break;
		}
		case MAIN_MENU_CASE_QUIT:
			if (gui_data.hdled == HDLED_WRITE && force_quit == 0) 
			{
				showWarning("Amiga is writing to HDF. Press PAD_right+L to force quit.");
				break;
		   }
			exit_safely(0);
			break;
		default:
			mainMenu_case=-1;
		}
	}

	if (sound_rate != old_sound_rate || mainMenu_soundStereo != old_stereo)
		init_sound();
	
#if defined(USE_UAE4ALL_VKBD)
	if ((mainMenu_vkbdLanguage != old_vkbdLanguage) || (mainMenu_vkbdStyle != old_vkbdStyle))
	{
		vkbd_quit();
		vkbd_init();
	}
#endif

	//See if new joysticks have been paired
	close_joystick();
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);	
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	init_joystick();
	
	update_display();

#if defined(__PSP2__) || defined(__SWITCH__)
	inside_menu = 0;
#endif
	return mainMenu_case;
}
