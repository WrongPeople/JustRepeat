project(JustRepeat)
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_COLOR_MAKEFILE ON)

if(MSVC)
    add_definitions(/D _CRT_SECURE_NO_WARNINGS)
endif()

############################
# API fix for Linux builds #
############################

if(UNIX AND NOT APPLE)
  add_definitions( -D__cdecl= )
endif()

#################
# Build plug-in #
#################

set(VSTSDK_PATH "${PROJECT_SOURCE_DIR}/../VST_SDK/VST2_SDK")
set(REASDK_PATH "${PROJECT_SOURCE_DIR}/../REA_SDK/jmde")

set(VSTSDK_INCLUDE_DIR ${VSTSDK_PATH})
set(REASDK_INCLUDE_DIR ${REASDK_PATH})

set(VSTSDK_PLUGIN_SOURCE
  ${VSTSDK_PATH}/public.sdk/source/vst2.x/audioeffectx.cpp
  ${VSTSDK_PATH}/public.sdk/source/vst2.x/audioeffect.cpp
  ${VSTSDK_PATH}/public.sdk/source/vst2.x/vstplugmain.cpp
  ${VSTSDK_PATH}/pluginterfaces/vst2.x/aeffectx.h
)

file(GLOB_RECURSE JUSTREPEAT_SOURCE "src/*.cpp")
set(JUSTREPEAT_SOURCE
    ${JUSTREPEAT_SOURCE}
    resources/vstplug.def
    ${VSTSDK_PLUGIN_SOURCE}
)

add_library(JustRepeat MODULE ${JUSTREPEAT_SOURCE})

include_directories(src)

include_directories(${VSTSDK_INCLUDE_DIR})
include_directories(${REASDK_INCLUDE_DIR})

target_link_libraries(JustRepeat ${VSTSDK_LIBRARIES})

######################################
# Set OSX-specific bundle properties #
######################################

set_target_properties(JustRepeat PROPERTIES
  BUNDLE true
  BUNDLE_EXTENSION "vst"
  XCODE_ATTRIBUTE_WRAPPER_EXTENSION "vst"
  MACOSX_BUNDLE_INFO_PLIST "resources/Info.plist.in"
  MACOSX_BUNDLE_BUNDLE_NAME "JustRepeat"
  MACOSX_BUNDLE_GUI_IDENTIFIER "com.WrongPeople.JustRepeat"
  MACOSX_BUNDLE_ICON_FILE ""
  MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0.0"
  MACOSX_BUNDLE_COPYRIGHT "WrongPeople © 2020"
)

####################
# Set Install Path #
####################

if(APPLE)
  install(TARGETS JustRepeat
    DESTINATION "$ENV{HOME}/Library/Audio/Plug-Ins/VST"
  )
elseif(WIN32)
  install(TARGETS JustRepeat
    DESTINATION "/Program Files/VstPlugins/"
  )
elseif(UNIX AND NOT APPLE) #Linux
  install(TARGETS JustRepeat
    DESTINATION "/usr/lib/lxvst"
  )
endif()
