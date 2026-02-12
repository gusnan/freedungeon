#
# Try to find GusGame library and include path.
# Once done this will define
#
# GUSGAME_FOUND
# GUSGAME_INCLUDE_PATH
# GUSGAME_LIBRARY
# 

IF (WIN32)
	FIND_PATH( GUSGAME_INCLUDE_DIR GusGame/GusGame.h
		$ENV{PROGRAMFILES}/GusGame/include
		$ENV{MINGDIR}/include/
		$ENV{MINGDIR}/include/GusGame
		$ENV{MINGDIR}
		/usr/local
		/usr/local/include
		/usr/local/GusGame
		/usr/local/include/GusGame
		/local
		/local/include
		/local/GusGame
		/local/include/GusGame
		/GusGame
		DOC "The directory where GusGame/GusGame.h resides")
	FIND_LIBRARY( GUSGAME_LIBRARY
		NAMES GUSGAME gusgame GusGame gusgame.a GusGame.a libgusgame.a libgusgame
		PATHS
		$ENV{PROGRAMFILES}/GusGame/lib
		$ENV{MINGDIR}/GusGame/lib/
		#$ENV{MINGDIR}/lib/GL
		$ENV{MINGDIR}/
		/local/lib
		/lib/
		/
		DOC "The GusGame library")
ELSE (WIN32)
	FIND_PATH( GUSGAME_INCLUDE_DIR GusGame/GusGame.h
		#GusGame/GusGame.h
		#$ENV{PROGRAMFILES}/GusGame/include
		#$ENV{PROGRAMFILES}
		/usr/include
		/usr/local/include
		/usr/local/include/gusgame
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where gusgame.h resides")
	FIND_LIBRARY( GUSGAME_LIBRARY
		NAMES GUSGAME gusgame GusGame libgusgame
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The GusGame library")
ENDIF (WIN32)

IF (GUSGAME_INCLUDE_DIR)
	SET( GUSGAME_FOUND 1 CACHE STRING "Set to 1 if GusGame is found, 0 otherwise")
ELSE (GUSGAME_INCLUDE_DIR)
	SET( GUSGAME_FOUND 0 CACHE STRING "Set to 1 if GusGame is found, 0 otherwise")
ENDIF (GUSGAME_INCLUDE_DIR)

IF (GUSGAME_FOUND)
   IF (NOT GUSGAME_FIND_QUIETLY)
      MESSAGE(STATUS "Found GUSGAME: ${GUSGAME_LIBRARY}")
   ENDIF (NOT GUSGAME_FIND_QUIETLY)
ENDIF (GUSGAME_FOUND)

MARK_AS_ADVANCED( GUSGAME_FOUND )
