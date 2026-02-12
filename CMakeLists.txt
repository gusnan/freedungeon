
# This file is licensed under the GPL version 3, see GPL3.txt

cmake_minimum_required(VERSION 3.13)

# set the project name
project(freedungeon)


set(GUSGUI_LIBRARY_NAME gusgui)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

option (DEBUG "Build Debug executable" off)

find_package(Allegro5 REQUIRED)

if (DEBUG)
	message(STATUS "Building Debug executable")
	set(CMAKE_BUILD_TYPE "Debug")
	add_definitions(-D_DEBUG)
	#add_definitions(-Wwrite-strings
			#-Wextra
			#-Wall
			#-Winit-self
			#-O
			#-Wno-uninitialized
			#-Wno-unused-parameter
			#-Wno-switch
			#-w
			#-Wreturn-type
			#-Weffc++
		#)
	# Cpp only flags: (Will not be applied to C files.)
	set(CMAKE_CXX_FLAGS -Weffc++)

else (DEBUG)
	message(STATUS "Building Release executable")
	#add_definitions(-fomit-frame-pointer)
	set(CMAKE_BUILD_TYPE "Release")

endif (DEBUG)

# set(DLL_FLAGS -DBUILDING_GUSGAME_DLL)

add_custom_target(cppcheck
   # cppcheck --inline-suppr --enable=all ../src/

   #

   cppcheck --suppress=missingIncludeSystem --suppress=missingInclude --inline-suppr --enable=all  ../src/
   # cppcheck --suppress=missingIncludeSystem --suppress=unmatchedSuppression:src/script.c -i src/icons/icons_resources.c --inline-suppr --enable=all ./src/
)

set(BUILD_SHARED_LIBS on)

SET(CMAKE_SHARED_LIBRARY_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CXX_FLAGS} -DBUILDING_GUSGAME_DLL")

if (MSYS)
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-enable-auto-import")
endif (MSYS)


message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}")

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")


# find_package(OpenGL REQUIRED)

find_package(Allegro5 REQUIRED)
find_package(GusGame REQUIRED)
find_package(GusGui REQUIRED)
find_package(Lua REQUIRED)
# find_package(Boost REQUIRED COMPONENTS system filesystem thread)

message(STATUS "GusGame Library: ${GUSGAME_LIBRARY}")
message(STATUS "GusGui Library: ${GUSGUI_LIBRARY}")

include_directories(include ${GUSGAME_INCLUDE_DIR})
include_directories(include ${GUSGUI_INCLUDE_DIR})

# include_directories(include ${CMAKE_SOURCE_DIR}/include)
# include_directories(include ${CMAKE_SOURCE_DIR}/include/GusGui)
include_directories(include ${ALLEGRO_INCLUDE_DIR})
include_directories(include ${LUA_INCLUDE_DIR})


if (WIN32)
	if (MSYS)
		Set (WINGL_LIBS glu32)
	else (MSYS)
		Set (WINGL_LIBS glu32)
	endif (MSYS)

endif(WIN32)

find_package(OpenGL REQUIRED)
find_package(GusGame REQUIRED)
find_package(GusGui REQUIRED)

# find_package(Boost REQUIRED )

message(STATUS "GusGame Library: ${GUSGAME_LIBRARY}")
message(STATUS "GusGui Library: ${GUSGUI_LIBRARY}")


include_directories(include ${CMAKE_SOURCE_DIR}/src)
include_directories(include ${CMAKE_SOURCE_DIR}/src/Objects)

include_directories(include ${GUSGAME_INCLUDE_DIR})
include_directories(include ${GUSGUI_INCLUDE_DIR})
include_directories(include ${Boost_INCLUDE_DIR})

if (MSYS)
	message(STATUS "MingDir: $ENV{MINGDIR}")
endif (MSYS)

message(STATUS "Boost INCLUDE_DIR: ${Boost_INCLUDE_DIR}")
message(STATUS "GUSGAME_INCLUDE_DIR: ${GUSGAME_INCLUDE_DIR}")
message(STATUS "GUSGUI_INCLUDE_DIR: ${GUSGUI_INCLUDE_DIR}")

if (NOT ALLEGRO_FOUND)
	message(FATAL_ERROR "Allegro not found!")
endif (NOT ALLEGRO_FOUND)

# And some libs:

message(STATUS "Allegro5 LIBRARY: ${ALLEGRO_LIBRARIES}")

message(STATUS "OPENGL_LIBRARY: ${OPENGL_LIBRARY}")
message(STATUS "OPENGL_LIBRARIES: ${OPENGL_LIBRARIES}")
message(STATUS "GLUT_LIBRARY: ${GLUT_LIBRARY}")

message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

if (USE_GLEW)
	set (MY_GLEW_LIB ${GLEW_LIBRARY})
else (USE_GLEW)
	set (MY_GLEW_LIB )
endif (USE_GLEW)

if (MSYS)
	set (GL_LIBS ${OPENGL_LIBRARY} ${OPENGL_LIBRARIES})
else (MSYS)
	set (GL_LIBS ${OPENGL_LIBRARY})
endif (MSYS)

set(ALL_LIBS

	${LUA_LIBRARIES}
	${GL_LIBS}
	${GLUT_LIBRARY}
	${WINGL_LIBS}
	${MY_GLEW_LIB}
	${Boost_LIBRARIES}

	${ALLEGRO_LIBRARIES}
)


link_libraries( ${GUSGAME_LIBRARY} ${GUSGUI_LIBRARY} ${ALL_LIBS})

include_directories(include "/usr/local/include")
include_directories(include ${GUSGAME_INCLUDE})
include_directories(include ${GUSGUI_INCLUDE})

# LINK_DIRECTORIES( ${LINK_DIRECTORIES} ${LIBRARY_OUTPUT_PATH})

message (STATUS "Link directories: ${LINK_DIRECTORIES}")
message (STATUS "Library output path: ${LIBRARY_OUTPUT_PATH}")


# aux_source_directory(src SRC_FILES)

set(SRC_FILES
   
   src/GameStates/GameStateBase.cpp
   src/GameStates/GameStateMainMenu.cpp
   src/GameStates/GameStateExplore.cpp
   # src/GameModes/GameModeInventory.cpp
   
   src/GameStates/GameStateHandler.cpp
   
   src/Gui/TextButton.cpp
   src/Gui/MainMenuPanel.cpp
   src/Gui/ExplorePanel.cpp
   src/Gui/InfoPanel.cpp
   src/Gui/InventoryPanel.cpp
   src/Gui/GamePanel.cpp
   src/Gui/ItemSlot.cpp
   src/Gui/MessagePanel.cpp
   src/Gui/PausePanel.cpp
   src/Gui/SleepPanel.cpp
   src/Gui/MiniMap.cpp
   
   src/Gui/PlayerPanel.cpp
   src/Gui/ItemTextPanel.cpp
   
   src/Entry.cpp
   src/Global.cpp
   
   src/Data.cpp
   
   src/MousePointer.cpp
   
   src/GameEventHandler.cpp
   
   src/Items/Item.cpp
   src/Items/ItemHandler.cpp
   src/Items/ItemHolder.cpp
   
   src/Characters/CharacterHandler.cpp
   src/Characters/Player.cpp
   src/Characters/Enemy.cpp
   
   src/Dungeon/DungeonObjects/DungeonBase.cpp
   src/Dungeon/DungeonObjects/DungeonWall.cpp
   src/Dungeon/DungeonObjects/DungeonEmpty.cpp
#   src/Dungeon/DungeonObjects/WallDecorations/

   
   src/Dungeon/DrawDungeon.cpp
   src/Dungeon/Map.cpp
   src/Dungeon/DungeonHandler.cpp
   src/Dungeon/DungeonData.cpp
   
   src/Script/ScriptBase.cpp
   src/Script/ScriptException.cpp
   
   src/Script/ItemScript.cpp
   
)

# add the executable
add_executable(freedungeon ${SRC_FILES})
