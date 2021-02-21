Important note to Switch users
======
On the Switch, since v1.84, please use nsp injection to start uae4all2, otherwise the `config save as` and `savestate export` options will not work. On SX OS, you can do this by holding down R while launching any installed game to make hbmenu appear.

Recent Changes
======
2.00

- allow suspend/resume again. On Switch, it was fixed in SDK. On Vita, please install fdfix plugin to prevent corruption on resume.

Description
=====
Use4All2 Mod is an Amiga emulator for Vita and Switch. This is my mod of this great Amiga emulator that was originally ported to the Vita by Cpasjuste. Depending on when you read this, this mod might be ahead or behind his version.

![Screenshot of UAE4All2 running on Switch](https://i.postimg.cc/Tw0MsKkG/1.jpg)

![Photo of UAE4All2 running on Switch in tabletop mode](https://i.postimg.cc/3RD6Lr7j/Split-Joycon-b.jpg)

More Screenshots:

 <a href="https://postimg.cc/SJFvR4ZD" target="_blank"><img src="https://i.postimg.cc/SJFvR4ZD/3.jpg" alt="3"/></a> <a href="https://postimg.cc/jLHkJ1mK" target="_blank"><img src="https://i.postimg.cc/jLHkJ1mK/4.jpg" alt="4"/></a> <a href="https://postimg.cc/cvdk7mG3" target="_blank"><img src="https://i.postimg.cc/cvdk7mG3/5.jpg" alt="5"/></a> <a href="https://postimg.cc/9zqkc0BD" target="_blank"><img src="https://i.postimg.cc/9zqkc0BD/6.jpg" alt="6"/></a> <a href="https://postimg.cc/2Lv9G95Q" target="_blank"><img src="https://i.postimg.cc/2Lv9G95Q/7.jpg" alt="7"/></a> <a href="https://postimg.cc/G9YXZNcY" target="_blank"><img src="https://i.postimg.cc/G9YXZNcY/8.jpg" alt="8"/></a> <a href="https://postimg.cc/PPQ2qwv5" target="_blank"><img src="https://i.postimg.cc/PPQ2qwv5/9.png" alt="9"/></a> <a href="https://postimg.cc/w1Ffwm9G" target="_blank"><img src="https://i.postimg.cc/w1Ffwm9G/10.jpg" alt="10"/></a> <a href="https://postimg.cc/1gjWQ1n0" target="_blank"><img src="https://i.postimg.cc/1gjWQ1n0/11.jpg" alt="11"/></a> <a href="https://postimg.cc/MMf9Z3VC" target="_blank"><img src="https://i.postimg.cc/MMf9Z3VC/12.jpg" alt="12"/></a> <a href="https://postimg.cc/qtRmSvRM" target="_blank"><img src="https://i.postimg.cc/qtRmSvRM/13.jpg" alt="13"/></a> <a href="https://postimg.cc/vxR347vc" target="_blank"><img src="https://i.postimg.cc/vxR347vc/14.jpg" alt="14"/></a> <a href="https://postimg.cc/WqMSgD9S" target="_blank"><img src="https://i.postimg.cc/WqMSgD9S/15.jpg" alt="15"/></a> <a href="https://postimg.cc/7fkKDV6R" target="_blank"><img src="https://i.postimg.cc/7fkKDV6R/16.jpg" alt="16"/></a>

Thanks to Cpasjuste for the original port, for jumping in and adding shader support, for making the assembler optimizations work, and for fixing audio playback on suspend/resume in SDL2 for Switch.

Thanks to ScHlAuChi for extensive testing, ideas, and for contributing the new larger virtual keyboard images.

Thanks to wronghands for the new, better-looking menu font, all the new keyboard styles, and many ideas.

Thanks to CrashMidnick for the French virtual keyboard.

Thanks to the original authors Chui, john4p, TomB, notaz, Bernd Schneider, Toni Wilen, Pickle, smoku, AnotherGuest, Anonymous engineer, finkel, Lubomyr, pelya and many more.

Thanks to my supporters on Patreon: Andyways, Count Duckula, Jesse Harlin, Özgür Karter, Matthew Machnee, Mored4u, Ibrahim Fazel Poor, and RadicalR.

Installation
======
* Vita:
  * Install .vpk
  * Obtain and copy BIOS files `kick13.rom` (Amiga 500), and `kick31.rom` (Amiga 1200) to `ux0:/data/uae4all/kickstarts`.
  * Optional: copy over additional BIOS files `kick12.rom`, `kick20.rom`, `kickcustom.rom` (for e.g. version 3.1.4 or any other user-supplied BIOS) to the same folder.

* Switch:
  * Download and unzip `uae4all2_switch.zip`
  * Copy the resulting folder `uae4all2` to `/switch/` onto your SDCard, ensure none of the "archive" flags is set.
  * You should now have the executable `/switch/uae4all2/uae4all2.nro` and a folder `/switch/uae4all2/data/` with the keyboard icons and other data files on your SDCard. 
  * Obtain and copy BIOS files `kick13.rom` (Amiga 500), and `kick31.rom` (Amiga 1200) to your SDCard into `/switch/uae4all2/kickstarts/`.
  * Optional: copy over additional BIOS files `kick12.rom`, `kick20.rom`, `kickcustom.rom` (for e.g. version 3.1.4 or any other user-supplied BIOS) to the same folder.
  * Use nsp injection to start uae4all2, otherwise the `config save as` and `savestate export` options will not work. On SX OS, you can do this by holding down R while launching any installed game to make hbmenu appear.

* MD5 of verified working kickstart rom files, you can test yours at [onlinemd5](http://onlinemd5.com/):   
```
kick12.rom (256 kB): (MD5) 85AD74194E87C08904327DE1A9443B7A
kick13.rom (256 kB): (MD5) 82A21C1890CAE844B3DF741F2762D48D  
kick20.rom (512 kB): (MD5) FA4ACC75B49E880679FE02716AF24D71  
kick31.rom (512 kB): (MD5) 646773759326FBAC3B2311FD8C8793EE  
````
Other files might work, too.

* You can purchase legal bios roms from [Amiga Forever](https://www.amigaforever.com). They work. But since they are encrypted, you have to copy over your .key file along with the roms.

Vita/Switch-exclusive Features
======
- Full speed emulation of most Amiga games with zero frameskip
- Large, complete virtual keyboard with adjustable position and adjustable transparency
- Six fully mappable custom control sets: map Vita/Switch buttons to any Amiga joystick or key input
- Multiple hard-file support: up to 4 hdf files (size <2GB each on Vita, size <4GB each on Switch) can be mounted simultaneously
- Multiple controller support on Vita TV/Switch: up to four (eight on Switch) paired controllers can be fully mapped
- Analog mouse control: control the mouse using the analog stick with adjustable sensitivity
- Shader support: default "sharp_bilinear_simple" uses integer pre-scale for sharp, undistorted pixels with minimum blur, even if game is zoomed to fill the full screen
- Custom autofire: any mapped Vita/Switch button can have autofire with adjustable rate
- Savestate with hard-file support: state can be saved even when hard-files are used
- Additional emulator settings: sprite-sprite collisions can be enabled, blitter settings can be changed
- Adjustable stereo separation
- A button can be mapped to "slow mouse" in custom controls. When custom controls are on and that button is held down, the mouse pointer speed is greatly reduced. This is useful for precisely positioning the cursor.
- Sticky virtual keyboard modifiers: allows keyboard combos like CTRL-C to be entered easily
- Touchpad style pointer controls using the touchscreen
- Parallel port joystick adapter support for multiplayer games with up to 4 joysticks.
- Additional savestate slot called auto, for automatic savestate loading
- Physical keyboard and mouse support (Bluetooth on Vita, USB on Switch)
- Supports loading files from ux0: or uma0: partition (Vita only)
- Rear touch panel can be enabled for mouse pointer control (Vita only)
- Split Joy-Con support (Switch only)
- A "fast mouse" custom button can be mapped to speed up the mouse
- Automatic full 1080p support in docked mode (Switch only)
- Savestate import/export to backup savestates
- Config file management (load, save as, etc.)
- Thumbnail previews for savestates
- Four different on-screen keyboard styles: original, warm, cool, and dark
- On-screen keyboard keys can be pressed via touch input in addition to dpad navigation

Controls
=====

General
-----
(For Switch: Cross = B, Square = Y, Triangle = X, Circle = A, Select = Minus, Start = Plus)

Select = Toggle menu  
Start = Toggle virtual keyboard  
R+Start+Dpad up/down = Move screen up/down  
R+Start+Dpad left/right = Change screenmode (to zoom in on games with borders)  
Right analog stick = Analog mouse (can switch this to left stick in menu)  

When custom controls are off
-----
Up to four controllers are automatically mapped to players 1-4. Players 3 and 4 are on the emulated parallel port 4 player adapter.

Left analog stick = Amiga joystick directions  
Dpad = Amiga joystick directions  
L shoulder button = right mouse click (player 1 only)  
R shoulder button = left mouse click (player 1 only)
(Shown below are control presets 1 (default) / 2 / 3 / 4)  
Square = Autofire (default) / Fire / Autofire / Fire  
Cross = Fire (default) / Autofire / Up (Jump) / Up (Jump)  
Triangle = Space (default) / Space / Fire / Autofire  
Circle = Secondary Fire (used only in a few games)  
R+Square = Ctrl  
R+Circle = Left Alt  
R+Cross = Help  
L+Square = Left mouse  
L+Circle = Right mouse  
R+Dpad = Arrow keys  

When custom controls are on
-----
L+Start = Toggle between custom control set number 1, 2, 3, 4 and 5  

In this mode, Vita buttons can be mapped to any Amiga side keyboard key or joystick action. There's also a mapping option called "slow mouse." It will slow down the mouse pointer by a factor ten if that mapped button is held down. Up to four controllers can be mapped (for multiplayer on VitaTV and Switch). Four Amiga-side joysticks are supported. Joystick 3 and 4 are on the emulated parallel port joystick adapter.

Virtual keyboard controls
-----
Start = Toggle virtual keyboard  
Right analog stick up/down = Move virtual keyboard up and down  
Right analog stick left/right = Change virtual keyboard transparency  
Cross = Press selected key (on Switch, this can be changed from B to A)
Square = Backspace  
Triangle = Toggle shift  
Circle = Turn off all sticky keys (ctrl, alt, amiga, and shift) (on Switch, this can be changed from A to B)

Touch controls
-----
Note: for multi-touch gestures, the fingers have to be far enough apart from each other, so that the Vita will not erroneously recognize them as a single finger. Otherwise the pointer will jump around. 

Single short tap = left mouse click  
Single short tap while holding a second finger down = right mouse click  
Single finger drag = move the mouse pointer, how far the pointer moves in response to finger motion depends on the Mouse Speed setting  
Dual finger drag = drag'n'drop (left mouse button is held down)  
Three finger drag = drag'n'drop (right mouse button is held down)  

Switch controls
-----
The default OK button in menu and on-screen keyboard is B. This can be changed to A in "more options."

ZR button = slow-mouse (if custom controls are off)
ZL button = fast-mouse (if custom controls are off)

Split Joycon Mode: Split Joycon mode can be enabled/disabled in "more options." Upto four single Joycons are supported. Buttons can still be remapped. SL for player 1 is hardcoded to bring up the keyboard.  

Split Joycon Controls:  
Minus/Plus = Menu (player 1 only)  
SL = on-screen keyboard (player 1 only)  
Pressing stick while moving it = change keyboard transparency/position, control mouse pointer (player 1 only)  
SR + SL + Stick directions = hotkey to quick-zoom image and center image vertically (player 1 only)  

Physical Keyboard / Mouse controls
-----
On Vita (Bluetooth): Mouse + keyboard tested working with the "Jelly Comb Mini Bluetooth Keyboard With Mouse Touchpad, ASIN:B06Y56BBYP," and with the "Jelly Comb Bluetooth Wireless Mouse ASIN:B075HBDWCF." The Amiga keys are mapped to Windows (GUI) keys as well as Page Up/Down. The Vita doesn't pair with all Bluetooth keyboards and mice. As a rule, if the keyboard works to highlight bubbles with cursor keys, it should also work in UAE4All.

On Switch (USB): All keyboards seem to work. Not all mice seem to work. [Mouse compatibility sheet](https://docs.google.com/spreadsheets/d/1Drbo5-QuSX901MwtOytSMuqRGxeIkq2HELM806I9dj0/edit#gid=0) 

Notes
======
- *Bios:* Please put kickstart files in `ux0:/data/uae4all/kickstarts` on Vita and in `/switch/uae4all2/kickstarts` directory on Switch. Files must be named as `kick13.rom` (for Amiga 500), and `kick31.rom` (for Amiga 1200). Optionally, `kick12.rom`, `kick20.rom`, and `kickcustom.rom` (any user supplied file, e.g. version 3.1.4 or anything else), can also be supplied.
- *Speed:* Most games run full speed. Some slow Amiga 1200 and WHDLoad games actually run faster if the CPU speed is reduced from 14 MHz to 7 MHz, because they rely more on custom chips than CPU. Some graphics glitches in Lionheart WHDLoad inside the caves are fixed by this.
- *Config File:* If you have problems with settings not saving etc, please delete or rename your config file in the folder `ux0:/data/uae4all` (Vita) or `/switch/uae4all2/conf/` and restart the emu. I heard this can fix many problems when you are replacing an older version of this emulator with a newer version. Lots of things are changing in the config file between releases.
- *Display:* The sharp_bilinear_simple shader, on by default, creates a sharp pixel image with minimal blurring. It applies a maximum integer pre-scale first. Then it scales only the small remainder using the builtin bilinear filter, keeping the aspect ratio intact.
  Many Amiga games fit the Vita and Switch screens very nicely. For example, take Chaos Engine with a screen setting of 320*200 and sharp_bilinear_simple shader enabled. The picture can be zoomed using R+Start+Dpad left/right (R+Plus+Dpad left/right on Switch), and moved vertically using R+Start+Dpad up/down (R+Plus+Dpad up/down on Switch) to center it on the screen. Once this is done, the picture fills almost the whole screen and looks amazing with no artifacts or blurriness. The game runs smooth with zero frameskip.
  Selecting a 'Preset Width' of 320, 352 or 384 (max overscan) results in lo-res screen emulation, good for most games, while 640, 704, or 768 results in hi-res screen emulation, good for use with Workbench or some text-based games.
- *Blitter:* The blitter settings can help with graphics glitches in some games. Since it seems to work best, "immediate" is the default. But some games require setting blitter to "normal" and re-booting to remove graphics glitches, for example PP Hammer, Spindizzy Worlds, and Shufflepuck Cafe.
- *WHDLoad:* If you have problems with a WHDLoad .hdf game, maybe try an .adf version of the same game. Rock'n Roll is one of a few games that work on UAE4All2 only using .adf files. It has graphics glitches and runs too fast in WHDLoad with .hdf. To make it work correctly, I loaded the "Rock'n Roll.adf" from Gamebase Amiga, chose the preset A500 config, and changed the Blitter setting to Normal.
- *Sprite Collisions:* Some games require sprite-to-sprite collisions. Sprite collisions can be turned on in the "more options" menu. The only game I know of that requires this is SpaceTaxi 3.
- *Savestates:* Four regular savestates can be saved per game. There's also a slot for an automatic savestate, labeled "auto". If it exists, this will be loaded immediately when the .adf is inserted. To prevent this, delete the auto savestate by selecting it and choosing "delete savestate".
- *Multiplayer:* Up to four controllers on Vita TV and Switch are supported and can be fully mapped. The mouse can be switched off because it interferes with the other joystick that controls player 2 in most games. If you pair new controllers on Vita TV and they do not seem to work, scan for them in the "custom controls" menu by pressing L. At the bottom it will say how many controllers have been found. This scanning is not neccessary on Switch. By default, parallel port Amiga joysticks 3 and 4 are controlled by VitaTV/Switch gamepads 3 and 4. They can also be mapped to other inputs using the custom controls screen.
- *Sound:* For use with headphones, a stereo separation setting of 50 sounds better than the default setting of 100. The original Amiga had completely disjoint left/right channels. This can sound quite jarring on headphones. Concerning sound frequency, I think 48 kHz gives the best results. On the Switch, 48 kHz is the only supported frequency.

FAQ
=====
* Kickstart rom files not found on startup? 

  First, please ensure you are using the correct files. They should be `kick13.rom` (size: 262,144 bytes), and `kick31.rom` (size: 524,288). They should be placed in `ux0:/data/uae4all/kickstarts` on Vita and `/switch/uae4all2/kickstarts` on Switch. Second, on Vita, please make sure your ux0:/data folder does NOT have the FAT attributes "hidden" or "system" set. Additional supported files are `kick12.rom`, `kick20.rom`, and `kickcustom.rom` (for any user-supplied file, e.g. version 3.1.4).

* Black screen on Switch, or crash on startup?

  In my testing (only with exFAT), I found that exFAT corruption can cause all files in the uae4all2 folder to become corrupted (among others). This includes kick13.rom and other kickstart files, which causes a black screen when leaving the menu. Game .adf files can become corrupted, causing the game to stop booting. Even the executable uae4all2.nro and/or config files in the conf folder can become corrupted quite easily, causing black screen crash on startup. Either don't use exFAT, or make a good backup of the folder and restore it via FTP if there are problems. Once I switched to FAT32, all these problems with file corruption went away.

* HDF not working?

  The maximum hdf file size on Switch is 4 Gb, on Vita it is only 2 Gb. When creating a .hdf file in WinUAE for use with UAE4All2, set surfaces to 1 (size < 1 Gb), 2 (size > 1Gb), or 4 (size > 2 Gb) depending on the size of the file. Set blocksize to 512, sectors to 32 and reserved to 2. Don't use RDB mode. After creating the .hdf it has to be formatted using Workbench. A quick format to FFS filesystem is fine.

Games with known fixes
======

- Blastar  
  Issue: flickering scrolling  
  Fix: set “Blitter: Normal” and reboot  

- Golden Axe  
  Issue: runs too fast  
  Fix: set “Blitter: Normal” and reboot  

- Lionheart with A1200 config  
  Issue: some flickering graphics glitches in water and in cave, runs slow on Vita  
  Fix: run the floppy version using A500 config  
 
- Lure of the Temptress (adf only)  
  Issue: hangs at title  
  Fix: use hdf version  

- Mister and Misses (Amiga Power Coverdisk 14b)  
  Issue: flickering and missing floors  
  Fix: set “Blitter: Normal” and reboot  

- PP Hammer  
  Issue: flickering  
  Fix: set “Blitter: Normal” and reboot  

- Rainbow Islands (adf only)  
  Issue: hangs after title  
  Fix: use hdf version  

- Rock’n’Roll  
  Issue: gfx glitches / flickering  
  Fix: set “Blitter: Normal,” use .adf and A500 config, and reboot  

- Shufflepuck Cafe  
  Issue: flickering  
  Fix: set “Blitter: Normal” and reboot.  

- Spacetaxi 3  
  Issue: taxis move through each other  
  Fix: set “Sprite Collisions: On” then it works perfectly.  

- Spindizzy Worlds  
  Issue: flickering/screen tearing  
  Fix: set “Blitter: Normal” and reboot.  

- Xenon 2  
  Issue: hangs after title  
  Fix: use hdf version “Xenon21 disk” which works perfectly.  


Games with no fixes (or unknown fixes)
======

- Banshee AGA  
  Issue: score display on left is missing.  
  Fix: unknown  

- IK+  
  Issue: no sound fx  
  Fix: unknown, but can play PlayStation 1 version in Retroarch instead. The Retroarch PUAE core can play this game correctly on Vita.  

- Nebulus 2  
  Issue: doors are not showing  
  Fix: unknown. This requires cycle exact, which is not supported.  

- Prince of Persia  
  Issue: runs slow  
  Fix: unknown, but can play Usineur’s native Switch/Vita port [SDLPop](https://github.com/usineur/SDLPoP/releases)  

- Reshoot R  
  Issue: some of the blue background graphics are missing  
  Fix: unknown, but the game is still playable.  


Compiling
======
* Dependencies: SDL2, SDL2_image, libpng, libjpeg, zlib
* Clone repo into a folder somewhere
* Vita:
  * Install VitaSDK toolchain and all vdpm packages: http://vitasdk.org
  * Compile and package:
  ```
  mkdir build
  cd build
  cmake "your uae4all2 repo folder" -DBUILD_PSP2=ON -DCMAKE_BUILD_TYPE=Release
  make uae4all2.vpk
  ```
  * Note: The Vita source depends on FrangarCJ's Vita2d fbo branch with shader support here: https://github.com/Cpasjuste/vita2dlib/tree/fbo
  and FrangarCJ's vita-shader-collection gtu branch: https://github.com/frangarcj/vita-shader-collection/tree/gtu
  Those are both included as binaries and linked automatically.

* Switch:
  * Install DevkitPro: https://devkitpro.org/wiki/devkitPro_pacman#Using_Pacman
  * Install required libs (libnx >1.6.0 and recent sdl2 are required):
  ```
  sudo -E dkp-pacman -S switch-dev
  sudo -E dkp-pacman -S switch-sdl2
  sudo -E dkp-pacman -S switch-sdl2_image
  sudo -E dkp-pacman -S switch-glm
  sudo -E dkp-pacman -S switch-glad
  sudo -E dkp-pacman -S switch-mesa
  sudo -E dkp-pacman -S switch-libpng
  sudo -E dkp-pacman -S switch-zlib
  sudo -E dkp-pacman -S switch-libjpeg-turbo
  sudo -E dkp-pacman -S switch-libdrm-nouveau
  ```
  * Compile and package:
  ```
  mkdir build
  cd build
  cmake "your uae4all2 repo folder" -DBUILD_NX=ON -DCMAKE_BUILD_TYPE=Release
  make uae4all2_switch.zip
  ```
  * Unzip and copy all all files to Switch so you have `/switch/uae4all2/uae4all2.nro` and `/switch/uae4all2/data/` etc. on your SD card
  * Launch using your favorite homebrew launcher

CHANGELOG
=====
2.00

- allow suspend/resume again. On Switch, it was fixed in SDK. On Vita, please install fdfix plugin to prevent corruption on resume.

1.99

- allow touch input to control on-screen keyboard, in addition to dpad

1.98 (Switch only)

- recompile to add support for 9.0.0 firmware

1.97 (Switch only)

- add option to main menu that displays online instruction manual (opens web browser) 

1.96

- increase maximum displayed lines from 270 to 286, useful for overscan games like Babeanoid
- fix cia overlay in AGA mode, fixes Reshoot-R hang at title screen
- add instruction manual to Vita livearea screen

1.95

- add support for .zip floppy files (read-only)
- on Switch, also compile with optimization level 3

1.94

- fix hdf settings with non-zero hd dir causing wrong mounted drives
- implement .adz floppy disk format support (read only)
- widescreen file dialog to show longer filenames

1.93 (Switch only)

- fix mouse pointer getting stuck sometimes when using USB mouse (fixed in SDL)

1.92

- add frameskip option back in
- on Vita, also use 48 kHz as default sound frequency (seems to work a bit better)

1.91

- widescreen menu
- physical keyboard and mouse support also on Switch. All keyboards I tried seem to work. Not many mice work. The Logitech M187 mouse seems to work fine.
- on Switch, no more slow-down when returning from sleep (thanks @Cpasjuste)

1.90

- Add keyboard style option with many choices: original, warm, cool, dark (thanks @wronghands)
- On Switch, quit gracefully when using home button to exit
- Speed up rendering of savestate menu when thumbnails are displayed

1.89 (Switch only)

- On Switch, fix scaling artifacts when sharp_bilinear_simple was selected. Pixels are even sharper now! 

1.88

- add French on-screen keyboard (thanks @CrashMidnick)

1.87

- improve savestate thumbnail quality
- rename joystick port option to clarify what it means

1.86

- implement thumbnail previews for savestates
- savestates are now always stored in the saves folder, never in the rom folder

1.85

- make some notifications in menu more readable
- fix some visual inconsistencies in the menu

1.84

- implement config load with dialog, config save as, and config delete
- increase number of savestates per game to 12
- increase number of custom control sets to 6
- on Switch, fix some issues with vsync
- implement importing and exporting of savestates
- better menu font (thanks @wronghands)
- option to select menu font
- on Switch, automatically use 1080p resolution in docked mode

1.83

- stop hotkeys from affecting game controls in some cases
- always allow left stick to control on screen keyboard
- allow mapping of stick and dpad independently

1.82

- support up to eight controllers on Switch
- allow faster menu navigation by holding down directions

1.81

- allow higher CPU speed hack (for Alien Breed 3D)
- allow optional custom kickstart named kickcustom.rom (for 3.1.4 etc.)
- buttons can now be mapped to quickload/quicksave for fast savestates 
- a button can be mapped to "fast mouse", hold it down to speed up mouse
- "slow mouse" or "fast mouse" buttons now also affect touch and real mice
- populate custom controls with sensible defaults instead of all blank

1.80

- improve keyboard input (fixes Celtic Legends)
- on Switch, improve single/dual joycon mode switching

1.79

- fix interrupt 6 bitmask (fixes Marvin's Marv. Adv. AGA)

1.78

- fix 68020+ bitfield instructions (fixes crash in Virocop AGA)

1.77

- increase max files per dir from 3072 to 10240
- on Switch, in split JoyCon mode, make SL/SR act as L/R also in menu
- on Switch, in split JoyCon mode, disable L/R/ZL/ZR in menu

1.76

- fixed lag when navigating the savestate menu
- on Switch, added split Joycon option for tabletop multiplayer with up to four single Joycons
- on Switch, allow menu navigation with analog stick

1.75

- fixed crash when booting a floppy with floppy speed >1x 
- fixed inconsistencies in menu navigation
- enabled long filename display in file browser (hold Triangle or X to show it)
- fixed an issue where HD Dir could not be selected unless Boot HD was set to OFF
- removed legacy code and data files that were not needed

1.74 (Switch only)

- Allow remapping of ZR/ZL on Switch
- Map ZR/ZL to "slow-down mouse" on Switch if custom controls are off
- Add option to misc menu to choose either A or B as OK button on Switch
- Add sharp-bilinear-simple scaling routine, and make it the new default
- Add point filtering scaling routine

1.73 (Switch only)

- Fix savestates on Switch

1.72switch

- Added Switch release

1.72

- Savestate location can now be changed in the menu

- Savestates can now be deleted from the menu

- Implemented an automatic savestate. There's a new savestate slot called auto. If it exists, this savestate will be loaded immediately when inserting a floppy.

1.71

- Fix hd settings not saving, and displayline settings not loading in certain situations

1.70

- Improve pointer response to diagonal stick directions

1.69

- Improve pointer response to slow finger motion

1.68

- Parallel port joystick adapter support. By default, Amiga joysticks 3 and 4 are controlled by VitaTV gamepads 3 and 4. They can also be mapped to other inputs using the custom controls screen.

1.67

- Improve pointer controls with bluetooth mouse by re-compiling with latest SDL-Vita

1.66

- Prevent accidental clicks when moving pointer using touch

1.65

- eliminate transparent keyboard slowdown
- fix joystick port setting affecting custom controls unless set to 'port1'

1.64

- improved 'normal' blitter mode (fixes flicker in PP Hammer and Spindizzy Worlds)

1.63
- implemented three-finger drag as right-button drag (useful to hold-down the right mouse button). Fingers have to be somewhat apart from each other, otherwise they are recognized as single or dual touch by the Vita.

1.62
- re-compiled in safe-mode
- fix empty directory listing of uma0:

1.61
- re-compiled in unsafe-mode

1.60
- support for uma0: added
- prevent suspend mode because it can corrupt hdf files

1.59
- implemented touchpad-style pointer controls. Touch controls are configured under 'More Options/Touch.' Choices are 'Touch Off', 'Front only', or 'Front and Back.' The default is to use only the front panel. Both panels work the same, using relative touch mode. How far a certain finger motion moves the pointer depends on the Mouse Speed setting, which also affects how fast the analog stick moves the mouse.

1.58
- fix 'movec pcr,d0' not throwing exception on 68020 (fixes WHDload 18.3)
- recompiled with latest SDL library supporting full analog joystick range

1.57
- sticky virtual keyboard keys implemented. The alt, ctrl, amiga, and shift virtual keyboard keys are now sticky. Press them once to enable and another time to let go of the key. Key combos like "Amiga-Q" can now be entered using the virtual keyboard. The circle button quickly un-sticks all keys.

1.56
- fix keys being pressed when pressing Vita buttons (introduced in 1.55)

1.55
- support for Bluetooth keyboard and mouse added. The Vita doesn't pair with all Bluetooth keyboard/mouse combos. As a rule, if the keyboard works to highlight bubbles with cursor keys, it should also work in UAE4All. Mouse + keyboard tested working with the "Jelly Comb Mini Bluetooth Keyboard With Mouse Touchpad, ASIN:B06Y56BBYP." The Amiga keys are mapped to Windows (GUI) keys as well as Page Up/Down.

1.54
- more choices for setting mouse speeds in steps of 0.25 now
- a button can be mapped to "slow mouse" in custom controls. When custom controls are on and that button is held down, the mouse pointer speed is greatly reduced. This is useful for precisely positioning the cursor.

1.53
- fix analog stick angular zone sizes (22.5 degrees per half zone now e.g. eight 45 degree zones)

1.52
- improved joystick diagonals and deadzone when controlling the Amiga joystick with Vita analog stick. The joystick analog-to-digital conversion is now done using a proper radial deadzone with eight symmetric angular zones for the possible directions.

1.51
- fix autofire for ply 2 w/o custom controls

1.50
- fix improved analog deadzone (broken in last release)

1.49
- improved analog mouse deadzone (radial and scaled)

1.48
- cleaned up display menu
- added option to choose menu background

1.47
- new menu background
- fix swapped "Quote"<->"Backquote" overlay keyboard keys

1.46
- never save autofire button to reduce confusion 
- fixed menu navigation bug in HDF file selection

1.45
- added option to use autofire with custom configs, can choose one Vita button that will have autofire, or set it to 'none' (default) to turn it off

1.44
- improved contrast of virtual keyboard overlays (thanks to ScHlAuChi for new images)
- added option to choose between US, UK and German virtual keyboard overlay (thanks to ScHlAuChi for new images)

1.43
- full support for up to 4 controllers on Vita TV that can be fully mapped individually
- filelists (adf, hdf, etc) are now sorted alphabetically with directories at the top
- added option to turn off mouse emulation because it often interferes with second player (port 0 joystick) when playing multiplayer on the Vita TV
- added option to turn on sprite-sprite collisions, useful for Spacetaxi 3
- changed blitter default to "immediate" it seems to be more compatible

1.42
- added two player support on Vita TV, second paired Dualshock controller controls the 'other' joystick, only works if port is not set to 'both' 
- fixed a crash bug when changing audio parameters while sound was playing

1.41
- assembler optimizations enabled by Cpasjuste, emulator is faster now!

1.40
- disabled the menu entries 'screenwidth' and 'stylus offset' that did nothing on the Vita. To show the borders in overscan games like Settlers, simply use the menu option 'Preset Width' and set it to >320 for lores, (or >640 for hires). There are choices 352, 384, 704 and 768 that cover the full overscan range.

1.39
- fix sound setting changes not being applied until restart
- fix sound distortion for stereo separation settings 0 (mono) and 25%

1.38
- added stereo separation setting to select between 0 (mono) 25%, 50%, 75% and 100% (stereo, default, original Amiga sound)
- added the blitter options 'normal, immediate, and improved' default is 'normal.' Might help with some games

1.37
- some fixes to savestates. Now savestates work even with no disk inserted in df0. Savestate file name is now the first available name among df0, boot-hd, hdf2, hdf3, hdf4, df1, df2, df3.

1.36
- added measures to prevent file corruption: Disabled PS button because it caused corruption of hdf files; display a warning about file corruption if the Amiga is writing to hdf while the user tries to exit the program
- fix hdf size checking
- fixed up some menu text 
- adjusted quickswitch screenmodes by two pixels

1.35
- now upto four hdf files can be mounted. From my own testing, it looks like 2 Gb is the hdf size limit. Geometry for each file can be changed by manually editing the config file, default is sectors:surfaces:reserved:blocksize=32:1:2:512 for files <1 GB, 32:2:2:512 for files >1Gb and 32:4:2:512 for files >2Gb. Only files <=2 Gb seem to work.

1.34
- hires support (e.g. 640*256), switchable in display menu. (Select a screen mode with "640" as width in the first option of the display menu, and the Workbench will be rendered with every pixel. A width of "320" reverts back to old behavior.)

1.33
- implemented three fully mappable custom configs, configurable in controls menu. Quick switch between them using "L+Start"
- allow the "other joystick" to be mapped in custom controls to the Dpad or any buttons. This only works if ports is not set to "both". Works great for Llamatron in dual joystick mode!

1.32
- virtual keyboard transparency adjust now toggles between four values, two of which cause zero slow-down when keyboard is displayed. 
- resolution/zoom quick switch with R+Start+Dpad left/right is now more responsive

1.31
- Allow menu quit from within sub-menus using 'select'

1.30
- updated autocentering of analog sticks so that both sticks are always auto-centered, not just the one that controls the mouse

1.29
- Changed controls. The virtual keyboard is too useful to put it on an obscure combo. Start Button now toggles the virtual keyboard. When keyboard is active, right analog stick then controls the keyboard's vertical position and transparency. When keyboard is off, use R+Start+Dpad to move screen up and down and to quick switch between common resolutions. This used to be just Start+Dpad. Now it is R+Start+Dpad.

1.28
- bugfix: the virtual keyboard sometimes sent joystick button presses to the emulator when selecting keys. This has been fixed.

1.27
- virtual keyboard hotkeys added, square = backspace, triangle = toggle shift
- virtual keyboard controls are now more responsive

1.26
- virtual keyboard transparency is now adjustable (START+dpad left/right)
- fixed bug in virtual keyboard initialization where the keyboard send an endless string of ' symbols on boot up before it was first opened

1.25
- vastly improved virtual keyboard: The image is now bigger, supports more keys including the shift modifier, and is transparent (thanks to ScHlAuChi for the new keyboard image and many ideas)
- Fixed virtual keyboard not reacting when custom dpad mode was active
- The virtual keyboard can now be moved up and down using start+dpad up and start + dpad down.

1.24
- virtual keyboard (mapped to "hold start then press select") 
- labels in custom control menu now reflect Vita controller
- default analog mouse control deadzone increased from 100 to 1000 to fix mouse pointer drift (can be changed in menu)
- default joystick port set to 1, since the mouse is always on (can be changed in menu)

1.23
- added analog joystick deadzone setting
- implemented autocentering to fix mouse pointer drift on some Vitas. Centering happens on program start and whenever the menu is opened
- START+DPAD left/right for quick switching between different zoomed screenmodes, useful for games like Chaos Engine. Use START+DPAD up/down to center screen after quick switching.

1.22
- fixed broken analog mouse control dead zone and improved mouse analog sensitivity

1.21
- moved shader config to display menu

1.20:
- added analog mouse support with menu option to choose left or right stick for mouse control
- new menu items in misc menu:
  shader choice (default: sharp_bilinear_simple)
  choice which analog stick to use for mouse
- disabled broken gp2x stylus mode and mouse emu mode
- L/R are mouse buttons now
- screen movement switched from L+R+DPAD to START+DPAD
- START does not switch input modes anymore (mouse is always enabled)
- updated Readme.txt with new Vita control scheme
- fixed misc menu entries for shader and analog mouse
- custom controls menu is now more snappy

<1.20: 
- perfect 2x scaling support to reduce pixel wobble
- HD Dir fix (supports one HD Dir & one HDF simultaneously, but max hdf size is still 1 Gb)
- Shader support implemented by Cpasjuste
