#
# Try to find GusGui library and include path.
# Once done this will define
#
# GUSGUI_FOUND
# GUSGUI_INCLUDE_PATH
# GUSGUI_LIBRARY
# 

IF (WIN32)
	FIND_PATH( GUSGUI_INCLUDE_DIR GusGui/GusGui.h
		$ENV{PROGRAMFILES}/GusGui/include
		$ENV{MINGDIR}/include/
		$ENV{MINGDIR}/include/GusGui
		$ENV{MINGDIR}
		/usr/local
		/usr/local/include
		/usr/local/GusGui
		/usr/local/include/GusGui
		/local
		/local/include
		/local/GusGui
		/local/include/GusGui
		/GusGui
		DOC "The directory where GusGui/GusGui.h resides")
	FIND_LIBRARY( GUSGUI_LIBRARY
		NAMES GUSGUI gusgui GusGui gusgui.a GusGui.a libgusgui.a libgusgui
		PATHS
		$ENV{PROGRAMFILES}/GusGui/lib
		$ENV{MINGDIR}/GusGui/lib/
		#$ENV{MINGDIR}/lib/GL
		$ENV{MINGDIR}/
		/local/lib
		/lib/
		/
		DOC "The GusGui library")
ELSE (WIN32)
	FIND_PATH( GUSGUI_INCLUDE_DIR GusGui/GusGui.h
		#GusGui/GusGui.h
		#$ENV{PROGRAMFILES}/GusGui/include
		#$ENV{PROGRAMFILES}
		/usr/include
		/usr/local/include
		/usr/local/include/gusgui
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where gusgui.h resides")
	FIND_LIBRARY( GUSGUI_LIBRARY
		NAMES GUSGUI gusgui GusGui libgusgui
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The GusGui library")
ENDIF (WIN32)

IF (GUSGUI_INCLUDE_DIR)
	SET( GUSGUI_FOUND 1 CACHE STRING "Set to 1 if GusGui is found, 0 otherwise")
ELSE (GUSGUI_INCLUDE_DIR)
	SET( GUSGUI_FOUND 0 CACHE STRING "Set to 1 if GusGui is found, 0 otherwise")
ENDIF (GUSGUI_INCLUDE_DIR)

IF (GUSGUI_FOUND)
   IF (NOT GUSGUI_FIND_QUIETLY)
      MESSAGE(STATUS "Found GUSGUI: ${GUSGUI_LIBRARY}")
   ENDIF (NOT GUSGUI_FIND_QUIETLY)
ENDIF (GUSGUI_FOUND)

MARK_AS_ADVANCED( GUSGUI_FOUND )
