cmake_minimum_required(VERSION 3.0)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(VERSION_MAJOR 2)
set(VERSION_MINOR 00)

if(BUILD_PSP2)
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if (DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else ()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif ()
endif ()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_DEBUG true CACHE BOOL "Build with psp2shell support")
endif()
endif(BUILD_PSP2)

if(BUILD_NX)
    set(CMAKE_SYSTEM_NAME "Generic")
    set(DEVKITPRO $ENV{DEVKITPRO})
    set(CMAKE_SYSTEM_PROCESSOR "armv8-a")
    set(CMAKE_C_COMPILER "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-gcc")
    set(CMAKE_CXX_COMPILER "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-g++")
    set(CMAKE_ASM_COMPILER "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-as")
    set(CMAKE_AR "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-gcc-ar" CACHE STRING "")
    set(CMAKE_RANLIB "${DEVKITPRO}/devkitA64/bin/aarch64-none-elf-gcc-ranlib" CACHE STRING "")
    set(CMAKE_FIND_ROOT_PATH ${DEVKITPRO} ${DEVKITPRO}/devkitA64 ${DEVKITPRO}/libnx ${DEVKITPRO}/portlibs/switch)
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Shared libs not available")
    link_directories(${DEVKITPRO}/libnx/lib ${DEVKITPRO}/portlibs/switch/lib)
endif(BUILD_NX)

execute_process(COMMAND "date" "+%Y.%m.%d"
        OUTPUT_VARIABLE BUILD_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)

project(uae4all2)

if(BUILD_PSP2)
  enable_language(ASM)

  include("${VITASDK}/share/vita.cmake" REQUIRED)
endif(BUILD_PSP2)

set(TITLEID "UAE4ALL00")

set(SRC_FILES
        src/psp2/psp2_input.c
        src/vkbd/vkbd.cpp
        src/audio.cpp
        src/autoconf.cpp
        src/blitfunc.cpp
        src/blittable.cpp
        src/blitter.cpp
        src/cfgfile.cpp
        src/cia.cpp
        src/savedisk.cpp
        src/savestate.cpp
        src/custom.cpp
        src/disk.cpp
        src/drawing.cpp
        src/ersatz.cpp
        src/expansion.cpp
        src/filesys.cpp
        src/fsdb.cpp
        src/fsdb_unix.cpp
        src/fsusage.cpp
        src/gfxutil.cpp
        src/hardfile.cpp
        src/keybuf.cpp
        src/main.cpp
        src/memory.cpp
        src/missing.cpp
        src/native2amiga.cpp
        src/gui.cpp
        src/od-joy.cpp
        src/scsi-none.cpp
        src/sdlgfx.cpp
        src/writelog.cpp
        src/unzip.c
        src/ioapi.c
        src/zfile.cpp
        src/menu/fade.cpp
        src/gp2x/gp2x.cpp
        src/gp2x/inputmode.cpp
        src/gp2x/menu/menu_helper.cpp
        src/gp2x/menu/menu_config.cpp
        src/gp2x/menu/menu.cpp
        src/gp2x/menu/menu_fileinfo.cpp
        src/gp2x/menu/menu_load.cpp
        src/gp2x/menu/menu_main.cpp
        src/gp2x/menu/menu_savestates.cpp
        src/gp2x/menu/menu_misc.cpp
        src/gp2x/menu/menu_controls.cpp
        src/gp2x/menu/menu_display.cpp
        src/gp2x/menu/menu_memory_disk.cpp
        src/sound_sdl_new.cpp
        src/m68k/fame/famec.cpp
        src/m68k/fame/m68k_intrf.cpp
        src/m68k/m68k_cmn_intrf.cpp
)

include_directories(
        ../common/include
        include
        src
        src/psp2
        src/switch
        src/gp2x
        src/menu
        src/include
        src/gp2x/menu
        src/vkbd
)

if(BUILD_PSP2)
  set(PSP2_SRC_FILES
    src/psp2/psp2_shader.cpp
    src/psp2/psp2-dirent.c
    src/psp2/psp2_touch.c
    src/psp2/psp2_kbdvita.c
    src/neon_helper.s
    src/gp2x/memset.s
    src/gp2x/memcpy.s
  )  
  set(SRC_FILES ${PSP2_SRC_FILES} ${SRC_FILES})

  include_directories(
    ${VITASDK}/arm-vita-eabi/include/SDL
  )

  set(FLAGS
          -Wno-write-strings
          -DVERSION=\"${BUILD_DATE}\"
          -DGP2X -DPANDORA -D__PSP2__ -DUSE_AUTOCONFIG -DUSE_ZFILE -DUSE_FAME_CORE -DWITH_TESTMODE
          -DUSE_SDL -DGCCCONSTFUNC="__attribute__\(\(const\)\)" -DUSE_UNDERSCORE
          -DSHM_SUPPORT_LINKS=0 -DUNALIGNED_PROFITABLE -DOPTIMIZED_FLAGS -DOS_WITHOUT_MEMORY_MANAGEMENT
          -DROM_PATH_PREFIX=\"ux0:/data/uae4all/roms/\" -DDATA_PREFIX=\"app0:/data/\" -DSAVE_PREFIX=\"ux0:/data/uae4all/saves/\" -DTHUMB_PREFIX=\"ux0:/data/uae4all/thumbs/\" -DTMP_PREFIX=\"ux0:/data/uae4all/tmp/\"
          -DUSE_UAE4ALL_VKBD
          -DUSE_ARMV7
          -DUSE_ARMNEON
          -DVERSION_MAJOR=\"${VERSION_MAJOR}\"
          -DVERSION_MINOR=\"${VERSION_MINOR}\"
          -marm -mfpu=neon -mtune=cortex-a9 -mfloat-abi=hard -ffast-math
          -fno-asynchronous-unwind-tables -funroll-loops
          -mword-relocations -fno-unwind-tables -fno-optimize-sibling-calls
          -mvectorize-with-neon-quad -funsafe-math-optimizations
          -mlittle-endian -munaligned-access
  )

  set(LDFLAGS
          SDL SDL_image
          ${CMAKE_SOURCE_DIR}/src/psp2/vita2d_fbo/lib/libvita2d.a
          ${CMAKE_SOURCE_DIR}/src/psp2/vita-shader-collection/lib/libvitashaders.a
          SceSysmodule_stub SceDisplay_stub SceGxm_stub
          SceCtrl_stub ScePgf_stub ScePower_stub SceCommonDialog_stub
          SceAudio_stub SceShellSvc_stub SceHid_stub SceTouch_stub png jpeg z m c
          SceAppUtil_stub SceAppMgr_stub
  )

  if (BUILD_DEBUG)
      list(APPEND FLAGS -DDEBUG -DDEBUG_UAE4ALL -DUAE_CONSOLE)
      list(APPEND LDFLAGS psp2shell SceSysmodule_stub SceNetCtl_stub
              SceNet_stub SceAppUtil_stub SceAppMgr_stub
      )
      set(UNSAFE_FLAG UNSAFE)
  else ()
      list(APPEND FLAGS -O3)
  endif (BUILD_DEBUG)

  add_executable(${PROJECT_NAME} ${SRC_FILES})
  target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
  target_link_libraries(${PROJECT_NAME} ${LDFLAGS})

  vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME} ${UNSAFE_FLAG})
  add_custom_target(${PROJECT_NAME}.vpk
          DEPENDS ${PROJECT_NAME}.self-self
          COMMAND rm -rf vpk && mkdir -p vpk/sce_sys
          COMMAND ${VITASDK}/bin/vita-mksfoex -s TITLE_ID=${TITLEID} "${PROJECT_NAME}" vpk/sce_sys/param.sfo
          COMMAND cp ${PROJECT_NAME}.self vpk/eboot.bin
          COMMAND cp -r ${CMAKE_SOURCE_DIR}/psp2data/* vpk
          COMMAND cd vpk && zip -r ../uae4all_${VERSION_MAJOR}.${VERSION_MINOR}.vpk . && cd ..
          COMMAND zip -d ${CMAKE_BINARY_DIR}/uae4all_${VERSION_MAJOR}.${VERSION_MINOR}.vpk *.DS_Store || true
          COMMAND zip -d ${CMAKE_BINARY_DIR}/uae4all_${VERSION_MAJOR}.${VERSION_MINOR}.vpk *__MAC* || true
  )
endif(BUILD_PSP2)

if(BUILD_NX)
  set(NX_SRC_FILES
    src/switch/switch_touch.c
    src/switch/sdl2_to_sdl1.cpp
    src/switch/switch_kbd.c
  )
  set(SRC_FILES ${NX_SRC_FILES} ${SRC_FILES})

  include_directories(
    ${DEVKITPRO}/portlibs/switch/include/SDL2
    ${DEVKITPRO}/libnx/include
    ${DEVKITPRO}/portlibs/switch/include
  )
  
  add_definitions(
    -DVERSION=\"${BUILD_DATE}\"
    -DGP2X
    -DPANDORA
    -D__SWITCH__
    -D__64BIT__
    -DUSE_AUTOCONFIG
    -DUSE_ZFILE
    -DUSE_FAME_CORE
    -DWITH_TESTMODE
    -DUSE_SDL
    -DUSE_SDL2
    -DGCCCONSTFUNC=\"__attribute__\(\(const\)\)\"
    -DUSE_UNDERSCORE
    -DSHM_SUPPORT_LINKS=0
    -DUNALIGNED_PROFITABLE
    -DOPTIMIZED_FLAGS
    -DOS_WITHOUT_MEMORY_MANAGEMENT
    -DROM_PATH_PREFIX=\"./roms/\"
    -DDATA_PREFIX=\"./data/\"
    -DSAVE_PREFIX=\"./saves/\"
    -DTHUMB_PREFIX=\"./thumbs/\"
    -DTMP_PREFIX=\"./tmp/\"
    -DUSE_UAE4ALL_VKBD
    -DVERSION_MAJOR=\"${VERSION_MAJOR}\"
    -DVERSION_MINOR=\"${VERSION_MINOR}\"
  )

  set(FLAGS
    -Wno-write-strings
    -march=armv8-a
    -mtune=cortex-a57
    -mtp=soft
#-fPIE is neccessary to prevent crash on startup
    -fPIE
    -O3
    -ffast-math
    -fno-asynchronous-unwind-tables
    -funroll-loops
    -fno-unwind-tables
    -fno-optimize-sibling-calls
    -funsafe-math-optimizations
    -mlittle-endian
    -ffunction-sections
    -fno-rtti
    -fno-exceptions
#    -fomit-frame-pointer
#    -fno-strict-aliasing
#    -fexpensive-optimizations		
#    -fweb
#    -frename-registers
#    -fomit-frame-pointer		
#    -falign-functions=32
#    -finline
#    -finline-functions
#    -fno-builtin
  )
  
  set(LIBS
    SDL2 
    SDL2_image
    SDL2_gfx
    EGL
    GLESv2
    glapi
    drm_nouveau
    nx
    png
    jpeg
    webp
    z
    m
    c
    stdc++
  )

  foreach(flag ${FLAGS})
    set(FLAGS_GENERAL "${FLAGS_GENERAL} ${flag}")
  endforeach(flag ${FLAGS})

  #set(CMAKE_C_FLAGS "${FLAGS_GENERAL}" CACHE STRING "C Flags" FORCE)
  #set(CMAKE_CXX_FLAGS "${FLAGS_GENERAL}" CACHE STRING "C++ Flags" FORCE)

  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS_GENERAL} -specs=${DEVKITPRO}/libnx/switch.specs --verbose")
  
  add_executable(${PROJECT_NAME}.elf ${SRC_FILES})
  target_compile_options(${PROJECT_NAME}.elf PRIVATE ${FLAGS})
  target_link_libraries(${PROJECT_NAME}.elf PRIVATE ${LIBS})
  add_custom_target(${PROJECT_NAME}.nro
    DEPENDS ${PROJECT_NAME}.elf
    COMMAND ${DEVKITPRO}/tools/bin/nacptool --create "${PROJECT_NAME}" "rsn8887" "${VERSION_MAJOR}.${VERSION_MINOR}" ${PROJECT_NAME}.nacp
    COMMAND ${DEVKITPRO}/tools/bin/elf2nro ${PROJECT_NAME}.elf ${PROJECT_NAME}.nro --icon=${CMAKE_SOURCE_DIR}/switchdata/icon0.jpg --nacp=${PROJECT_NAME}.nacp
  )
  add_custom_target(${PROJECT_NAME}_switch.zip
    DEPENDS ${PROJECT_NAME}.nro
    COMMAND rm -rf ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}/data
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}/roms
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}/kickstarts
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}/saves
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}/conf
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}/thumbs
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}/tmp
    COMMAND cp -f ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.nro ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}/${PROJECT_NAME}.nro
    COMMAND cp -r ${CMAKE_SOURCE_DIR}/switchdata/data/* ${CMAKE_BINARY_DIR}/release/${PROJECT_NAME}/data/
    COMMAND cd ${CMAKE_BINARY_DIR}/release && zip -r ../${PROJECT_NAME}_${VERSION_MAJOR}.${VERSION_MINOR}_switch.zip ${PROJECT_NAME} && cd ${CMAKE_BINARY_DIR}
    COMMAND zip -d ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_${VERSION_MAJOR}.${VERSION_MINOR}_switch.zip *.DS_Store || true
    COMMAND zip -d ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_${VERSION_MAJOR}.${VERSION_MINOR}_switch.zip *__MAC* || true
  )
endif(BUILD_NX)


