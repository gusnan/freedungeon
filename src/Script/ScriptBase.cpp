/* ----------------------------------------------------------------------------
 *	Script
 *
 *	Copyright (C) 2006 Neil Lalonde
 *
 *	This program is free software; you can redistribute it and/or modify it under
 *	the terms of the GNU General Public License as published by the Free Software
 *	Foundation; either version 2 of the License, or (at your option) any later
 *	version.
 *
 *	This program is distributed in the hope that it will be useful, but WITHOUT
 *	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *	FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License along with
 *  this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 *  Place, Suite 330, Boston, MA 02111-1307 USA
 */
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

#include <string.h>
#include <list>

#include "GusGame/GusGame.h"

using namespace Gus;

using namespace GraphicsLib;
/*
using namespace LogLib;


using namespace ConfigLib;
*/

using namespace ExceptionLib;

#include "ScriptException.h"

// #include "ScriptHandler.h"

#include "ScriptBase.h"
#include <stdarg.h>

/*
#include "../Block.h"
#include "../Map.h"
*/

#include "../Data.h"

/**
 *
 */
namespace ScriptLib
{

std::stringstream ScriptBase::mssOut;

/**
 *
 */
std::string removeFolder(const std::string &st, const std::string &shortFileName)
{
   int res = -1;
   std::string resstring = "";

   for (int co = 0; co < (int)st.length(); co++) {

   }

   int q = 0;

   q = st.find(shortFileName);

   if (q > 0) {
      res = q;
   }

   if (res != -1) {
      resstring = st.substr(res, st.length() - res);
   }

   return resstring;

}


/**
 * loadScript
 * :--> Load a script, but do not run it yet.
 *		ie, The script virtual machine will not be aware
 *		of any functions, variables, etc in the script
 *		after this function call is made.  Call runScript
 *		to do that.
 */
void ScriptBase::loadScript(const std::string& aFilename)
{
   // If we have not got a Lua state
   if (!mbLuaState /*|| mbLoaded*/)
   {
      setup();
      sScriptName = aFilename;
   }

   //std::string fileName=ConfigHandler::config->GetScriptFolder()+sScriptName;

   std::string fileName = aFilename; //""; //ScriptHandler::Instance()->GetScriptFolder()+sScriptName;

   //std::string fileName=sScriptName;

   std::stringstream st;
   st << "Loading Script:" << fileName;
   STLOG(st);


   // Now load the script
   int s = luaL_loadfile(mlState, fileName.c_str());

   if (s == 0)
   {
      mbLoaded = true;
   } else {
      std::string errorMsg;

      errorMsg = lua_tostring(mlState, -1);

      std::string luaErrorString = getLuaErrorString(s);

      mssOut.str("");

      mssOut << luaErrorString << ": " << errorMsg;

      mssOut << "Failed to load script "
         << aFilename << "\nwith the following Lua error:[lightgray] "
         << luaErrorString << "[white].\n"
         << "" << removeFolder(errorMsg, aFilename);
      
      
      std::cout << mssOut.str();

      ScriptException ex(mssOut.str().c_str(), luaErrorString);

      throw(ex);
   }
}


/**
 * runScript
 * :--> Run a script that was loaded with loadScript.
 */
void ScriptBase::runScript(void)
{
   if (mbLoaded)
   {
      int s = lua_pcall(mlState, 0, LUA_MULTRET, 0);

      if (s > 0) {
         std::string errorMsg;

         errorMsg = lua_tostring(mlState, -1);

         std::string luaErrorString = getLuaErrorString(s);

         mssOut.str("");
         mssOut << "Script::runScript : Error caught running script "
            << sScriptName << "\n"
            << "    Error code is " << luaErrorString << ".\n"
            << "    Error msg is: " << errorMsg;
         throw(ScriptException(mssOut.str().c_str(), errorMsg));
      }
   } else {
      throw(ScriptException("Script::runScript : No script loaded yet!", ""));
   }
}


/**
 * setup
 * :--> Sets up the Lua stuff so that we can load and
 *		run scripts in this object
 */
void ScriptBase::setup(void)
{
   if (mbLuaState)
   {
      lua_close(mlState);
      mbLuaState = false;
      mbLoaded   = false;
   }

   /**
    * Create a Lua virtual machine.
    */
   //mlState = lua_open();
   mlState = luaL_newstate();

   /*
   luaopen_base(mlState);
   luaopen_table(mlState);
   //luaopen_io(mlState);
   luaopen_string(mlState);
   luaopen_math(mlState);
   */


   luaL_openlibs(mlState);

   mbLuaState = true;
   mbLoaded   = false;

   /**
    * Set our handling function for when Lua panics
    */
   lua_atpanic(mlState, &(ScriptBase::catchLuaError));

   // Fix the LUA path...

   std::string path = getStringGlobalFromTable("package", "path");
   m_OriginalPackagePath = path;

   //path+=";"+ScriptHandler::scriptFolder;
   // path += ";../script/;";

   std::string q = ""; // ScriptHandler::Instance()->GetScriptFolder();
   q = Data::instance().getDataFolder("script");

   std::stringstream st;

   st << "Script folder: " << q;
   STLOG(st);

   q = FileHelper::getAbsolutePath(q);

   q = FileHelper::fixEndSlash(q);

   q += "?.lua";

   path += ";" + q;

   st.str("");
   st << "Lua path: " << path;
   STLOG(st);

   //std::cout << "Path:" << path << std::endl;

   addStringGlobalToTable(mlState, "package", "path", path);


   // -------------------

   /**
   // Now register the C functions for the Lua scripts.
   // registerCFunctions is a virtual function which
   // derived classes should implement.  That derived
   // class's implementation of registerCFunctions
   // will get called now:
    */
   registerCFunctions();

   /**
   // Now clear the stack.  Various things are left on the stack
   // from the above operations, and we don't need them.  It
   // is perfectly acceptable (and correct?) to pop them off
   // so that the stack is empty.
    */
   int numPops = lua_gettop(mlState);
   lua_pop(mlState, numPops);
}


/*
 *
 */
// cppcheck-suppress [unusedFunction]
bool ScriptBase::functionExists(const char *func)
{
   bool result = false;
   if (!mbLoaded)
   {
      throw(ScriptException(
         "Script::callFunction : A script is not loaded!", ""));
   }

   lua_State *L = mlState;

//    int narg, nres;  /* number of arguments and results */

   // char *			pStringOutput = nullptr;
   // std::string *	pString = nullptr;
   int				numPopsNeeded = 0;

    lua_getglobal(L, func);  /* get function */

   if (lua_isfunction(L, -1))
   {
      result = true;
   }

   // Pop string results now.
   lua_pop(L, numPopsNeeded);

   return result;
}


/**
 * callFunction
 * :--> Code from "Programming in Lua"
 *		http://www.lua.org/pil/25.3.html
 *
 *		MIGHTY modification:
 *			String results need to be handled with std::string*
 *			arguments.  When Lua returns a string value to C, it leaves
 *			the string on the stack and it is C's responsibility to
 *			pop the strings off the stack.  So, this function will
 *			copy the string result into a given std::string and then
 *			pop the string off the stack.
 *			This is a change from the PiL book's source.
 */
// cppcheck-suppress [unusedFunction]
void ScriptBase::callFunction(const char *func, const char *sig, ...)
{
   if (!mbLoaded )
   {
      throw(ScriptException(
         "Script::callFunction : A script is not loaded!", ""));
   }

   lua_State *L = mlState;

    va_list vl;
    int narg, nres;  /* number of arguments and results */

   // char *			pStringOutput;
   // std::string *	pString;
   int				numPopsNeeded = 0;

    va_start(vl, sig);
    lua_getglobal(L, func);  /* get function */

   if (lua_isfunction(L, -1) )
   {
      /* push arguments */
      narg = 0;
      while (*sig) {  /* push arguments */
      switch (*sig++) {

         case 'd':  /* double argument */
         lua_pushnumber(L, va_arg(vl, double));
         break;

         case 'i':  /* int argument */
         lua_pushnumber(L, va_arg(vl, int));
         break;

         case 's':  /* string argument */
         lua_pushstring(L, va_arg(vl, char *));
         break;

         case '>':
         goto endwhile;

         default:
            mssOut.str("");
            mssOut << "Script::callFunction : invalid option ("
               << *(sig - 1) << ")";
            throw(ScriptException( mssOut.str().c_str(), ""));
      }
      narg++;
      luaL_checkstack(L, 1, "too many arguments");
      } endwhile:

      /* do the call */
      nres = strlen(sig);  /* number of expected results */
      if (lua_pcall(L, narg, nres, 0) != 0)  /* do the call */
      {
         mssOut.str("");
         mssOut << "Script::callFunction : error running function "
            << func << " : " << lua_tostring(L, -1);

         va_end(vl);
         throw(ScriptException( mssOut.str().c_str(), ""));
      }

      /* retrieve results */
      nres = -nres;  /* stack index of first result */
      while (*sig) {  /* get results */
      switch (*sig++) {

         case 'd':  /* double result */
            if (!lua_isnumber(L, nres))
            {
               throw(ScriptException( "Script::callFunction : wrong result type", ""));
            }
            *va_arg(vl, double *) = lua_tonumber(L, nres);
            break;

         case 'i':  /* int result */
            if (!lua_isnumber(L, nres))
            {
               throw(ScriptException( "Script::callFunction : wrong result type", ""));
            }

            *va_arg(vl, int *) = (int)lua_tonumber(L, nres);
            break;

         case 's':  /* string result */
            if (!lua_isstring(L, nres))
            {
               throw(ScriptException( "Script::callFunction : wrong result type", ""));
            }
            *va_arg(vl, std::string *) = lua_tostring(L, nres);
            numPopsNeeded++;
            break;

         default:
            mssOut.str("");
            mssOut << "Script::callFunction : invalid option ("
               << *(sig - 1) << ")";
            throw(ScriptException( mssOut.str().c_str(), ""));
      }
      nres++;
      }
   }

   // Pop string results now.
   lua_pop(L, numPopsNeeded);

    va_end(vl);
}

/**
 * addStringGlobal
 * :--> Add a global string variable to the script's
 *		environment.  You can only do this after a script
 *		has been loaded and run.
 */
void ScriptBase::addStringGlobal(const std::string& aName,
                             const std::string& aValue )
{
   addStringGlobal(mlState, aName, aValue );
}

void ScriptBase::addStringGlobal(lua_State *L, const std::string& aName,
                             const std::string& aValue)
{
   lua_pushstring(L, aValue.c_str());
   lua_setglobal(L, aName.c_str());
}

/**
 * addNumberGlobal
 * :--> Add a global number (float) variable to the script's
 *		environment.  You can only do this after a script
 *		has been loaded and run.
 */
void ScriptBase::addNumberGlobal(const std::string& aName,
                             double aValue)
{
   addNumberGlobal(mlState, aName, aValue );
}

void ScriptBase::addNumberGlobal(lua_State *L,const std::string& aName,
                             double aValue)
{
   lua_pushnumber(L, aValue );
   lua_setglobal(L, aName.c_str());
}


/**
 * getStringGlobal
 * :--> Get a string global from the script's environment.
 */
const std::string& ScriptBase::getStringGlobal(const std::string& aName)
{
   return(getStringGlobal(mlState, aName));
}


/**
 *
 */
const std::string& ScriptBase::getStringGlobal(lua_State *L, const std::string& aName)
{
   static std::string sOutput;

   lua_getglobal(L, aName.c_str());

   if (lua_isstring(L, -1) )
   {
      sOutput = (std::string)(lua_tostring(L, -1));
   }
   else
   {
      sOutput = "";
   }

   lua_pop(L, 1);

   return(sOutput);
}


/**
 * getNumberGlobal
 * :--> Get a number global from the script's environment.
 */
double ScriptBase::getNumberGlobal(const std::string& aName)
{
   return( getNumberGlobal(mlState, aName));
}


/**
 *
 */
double ScriptBase::getNumberGlobal(lua_State *L, const std::string& aName)
{
   static double fOutput;

   lua_getglobal(L, aName.c_str());

   if (lua_isnumber(L, -1) )
   {
      fOutput = (double)lua_tonumber(L, -1);
   }
   else
   {
      fOutput = 0;
   }

   lua_pop(L, 1);

   return(fOutput);
}


/**
 * getBoolGlobal
 * :--> Get a boolean global from the script's environment.
 */
bool ScriptBase::getBoolGlobal(const std::string& aName)
{
   return(getBoolGlobal(mlState, aName));
}


/**
 *
 */
bool ScriptBase::getBoolGlobal(lua_State *L, const std::string& aName)
{
   bool bOutput = false;
   //int lboint=0;

   lua_getglobal(L, aName.c_str());

   if (lua_isboolean(L, -1) )
   {
      //bOutput = (bool)lua_toboolean(L, -1);
      int temp=lua_toboolean(L, -1);

      /*
      std::stringstream st;
      st << "LUABOOL:" << temp;
      STLOG(st);
      */

      if (temp) bOutput = true;
   }

   //if (lboint!=0) bOutput=true;

   lua_pop(L, 1);

   return(bOutput);
}


/**
 * addStringGlobalToTable
 * :--> Add a global string variable to the script's
 *		environment in an existing table.
 *		You can only do this after a script has been loaded
 *		and run.
 */
void ScriptBase::addStringGlobalToTable(
                           const std::string& aTable,
                           const std::string& aName,
                           const std::string& aValue)
{
   addStringGlobalToTable(mlState, aTable, aName, aValue);
}


/**
 *
 */
void ScriptBase::addStringGlobalToTable(lua_State *L,
                           const std::string& aTable,
                           const std::string& aName,
                           const std::string& aValue)
{
   lua_getglobal(L, aTable.c_str());
   lua_pushstring(L, aName.c_str());
   lua_pushstring(L, aValue.c_str());
   lua_settable(L, -3 );

   lua_pop(L, 1);
}


/**
 * addNumberGlobalToTable
 * :--> Add a global number variable to the script's
 *		environment in an existing table.
 *		You can only do this after a script has been loaded
 *		and run.
 */
void ScriptBase::addNumberGlobalToTable(
                        const std::string& aTable,
                        const std::string& aName,
                        double aValue )
{
   addNumberGlobalToTable(mlState, aTable, aName, aValue);
}

void ScriptBase::addNumberGlobalToTable(lua_State *L,
                        const std::string& aTable,
                        const std::string& aName,
                        double aValue )
{
   lua_getglobal(L, aTable.c_str());
   lua_pushstring(L, aName.c_str());
   lua_pushnumber(L, aValue );
   lua_settable(L, -3 );

   lua_pop(L, 1);
}


/**
 * getStringGlobalFromTable
 * :--> Get a global string variable from the script's
 *		environment in an existing table.
 *		You can only do this after a script has been loaded
 *		and run.
 */
const std::string& ScriptBase::getStringGlobalFromTable(
                        const std::string& aTable,
                        const std::string& aName)
{
   try
   {
      return( getStringGlobalFromTable(mlState, aTable, aName));
   }
   catch(ScriptException &exception )
   {
      std::stringstream st;
      st << exception.getString();
      STLOG(st);

      mssOut << "    script name = " << sScriptName << "\n";

      throw(ScriptException( mssOut.str().c_str(), ""));
   }
}


const std::string& ScriptBase::getStringGlobalFromTable(lua_State *L,
                        const std::string& aTable,
                        const std::string& aName)
{
   lua_getglobal(L, aTable.c_str());
   lua_pushstring(L, aName.c_str());
   lua_gettable(L, -2);  // table "me" is at position -2 on stack

   if (lua_isstring(L, -1) )
   {
      static std::string returnString = lua_tostring(L, -1);
      lua_pop(L, 2);

      return( returnString );
   }
   else
   {
      lua_pop(L, 2);

      mssOut.str("");
      mssOut << "Script::getStringGlobalFromTable : Not a string!\n"
         << "    table name  = " << aTable << "\n"
         << "    key name    = " << aName << "\n";

      throw(ScriptException( mssOut.str().c_str() ));
   }
}


/**
 * getStringGlobalFromTable
 * :--> Get a global string variable from the script's
 *		environment in an existing table.
 *		You can only do this after a script has been loaded
 *		and run.
 */
const std::string& ScriptBase::getStringGlobalFromTable(
                        const std::string& aTable,
                        const int		   aIndex )
{
   try
   {
      return( getStringGlobalFromTable(mlState, aTable, aIndex ));
   }
   catch(ScriptException &exception )
   {
      std::stringstream st;
      st << exception.getString();
      STLOG(st);

      mssOut << "    script name = " << sScriptName << "\n";

      throw(ScriptException( mssOut.str().c_str() ));
   }
}


const std::string& ScriptBase::getStringGlobalFromTable(lua_State *L,
                        const std::string&  aTable,
                        const int			aIndex )
{
   lua_getglobal(L, aTable.c_str());
   lua_pushnumber(L, aIndex );
   lua_gettable(L, -2);

   if (lua_isstring(L, -1) )
   {
      static std::string returnString = lua_tostring(L, -1);
      lua_pop(L, 2);

      return( returnString );
   }
   else
   {
      lua_pop(L, 2);

      mssOut.str("");
      mssOut << "Script::getStringGlobalFromTable : Not a string!\n"
         << "    table name  = " << aTable << "\n"
         << "    key         = " << aIndex << "\n";

      throw(ScriptException( mssOut.str().c_str() ));
   }
}


/**
 * addNumberGlobalToTable
 * :--> Get a global number variable from the script's
 *		environment in an existing table.
 *		You can only do this after a script has been loaded
 *		and run.
 */
double ScriptBase::getNumberGlobalFromTable(
                        const std::string& aTable,
                        const std::string& aName)
{
   try
   {
      return( getNumberGlobalFromTable(mlState, aTable, aName));
   }
   catch(ScriptException &exception )
   {
      std::stringstream st;
      st << exception.getString();
      STLOG(st);

      mssOut << "    script name = " << sScriptName << "\n";

      throw(ScriptException( mssOut.str().c_str() ));
   }
}

double ScriptBase::getNumberGlobalFromTable(lua_State *L,
                        const std::string &aTable,
                        const std::string &aName)
{
   lua_getglobal(L, aTable.c_str());
   lua_pushstring(L, aName.c_str());
   lua_gettable(L, -2);  // table "me" is at position -2 on stack

   if (lua_isnumber(L, -1) )
   {
      static double dValue;
      dValue = lua_tonumber(L, -1);
      lua_pop(L, 2);

      return( dValue );
   }
   else
   {
      lua_pop(L, 2);

      mssOut.str("");
      mssOut << "Script::getStringGlobalFromTable : Not a number!\n"
         << "    table name  = " << aTable << "\n"
         << "    key name    = " << aName << "\n";

      throw(ScriptException( mssOut.str().c_str() ));
   }
}


/*
 * globalExists
 * :--> Return true if a global variable exists with the
 *		given name.
 */
bool ScriptBase::globalExists(const std::string &aName)
{
   try
   {
      return( globalExists(mlState, aName));
   }
   catch( RuntimeError &exception )
   {
      mssOut.str("");
      mssOut << "Script::globalExists : Failed for script " << sScriptName << ":\n"
         << exception.getString();

      throw(ScriptException( mssOut.str().c_str() ));
   }
}


bool ScriptBase::globalExists(lua_State *L, const std::string &aName)
{
   return( globalExistsInTable(L, "_G", aName));
}


/**
 * globalExistsInTable
 * :--> Return true if a global variable exists with the
 *		given name in a given table.
 */
bool ScriptBase::globalExistsInTable(const std::string& aTable,
                     const std::string& aName)
{
   try
   {
      return( globalExistsInTable(mlState, aTable, aName));
   }
   catch( RuntimeError &exception )
   {
      mssOut.str("");
      mssOut << "Script::globalExistsInTable : Failed for script " << sScriptName << ":\n"
         << exception.getString();

      throw(ScriptException( mssOut.str().c_str() ));
   }
}


bool ScriptBase::globalExistsInTable(lua_State *L, const std::string &aTable,
                     const std::string& aName)
{
   // 1. Put the table on the top of the stack:
   lua_getglobal(L, aTable.c_str());

   // 2. Put the index key in the table onto the stack:
   lua_pushstring(L, aName.c_str());

   // 3. Get aTable[ aName ] and put it on top of the stack.
   //    The value pushed onto the stack in step 2 is popped,
   //    but the table value pushed in step 1 remains.
   lua_gettable(L, -2);

   // We now have two items on the stack:
   // 1. The "aTable" table
   // 2. The value of aTable[ aName ], which is on the stack's top.

   if (lua_type(L, -1) != LUA_TNIL)
   {
      lua_pop(L, 2);
      return( true );
   }
   else
   {
      lua_pop(L, 2);
      return( false );
   }
}


bool ScriptBase::globalExistsInTable(const std::string &aTable,
                          const int aIndex )
{
   try
   {
      return( globalExistsInTable(mlState, aTable, aIndex ));
   }
   catch( RuntimeError &exception)
   {
      mssOut.str("");
      mssOut << "Script::globalExistsInTable : Failed for script " << sScriptName << ":\n"
         << exception.getString();

      throw(ScriptException( mssOut.str().c_str() ));
   }
}

bool ScriptBase::globalExistsInTable(lua_State *L,  const std::string& aTable,
                          const int aIndex )
{
   // 1. Put the table on the top of the stack:
   lua_getglobal(L, aTable.c_str());

   // 2. Put the index key in the table onto the stack:
   lua_pushnumber(L, aIndex );

   // 3. Get aTable[ aName ] and put it on top of the stack.
   //    The value pushed onto the stack in step 2 is popped,
   //    but the table value pushed in step 1 remains.
   lua_gettable(L, -2);

   // We now have two items on the stack:
   // 1. The "aTable" table
   // 2. The value of aTable[ aName ], which is on the stack's top.

   if (lua_type(L, -1) != LUA_TNIL)
   {
      lua_pop(L, 2);
      return(true);
   }
   else
   {
      lua_pop(L, 2);
      return(false);
   }
}

/**
 *	stackDump
 *	:-->	Print out the contents of the Lua stack into a
 *		string.
 */
const std::string& ScriptBase::stackDump(void)
{
   return( stackDump(mlState));
}

const std::string& ScriptBase::stackDump(lua_State *L)
{
   int i;
   int top = lua_gettop(L);
   static std::string	sOutput;

   mssOut.str("");

   for (i = 1; i <= top; i++)
   {
      /* repeat for each level */
      int t = lua_type(L, i);

      switch (t)
      {
         case LUA_TSTRING:  /* strings */
            mssOut << "'" << lua_tostring(L, i) << "'";
            break;

         case LUA_TBOOLEAN:  /* booleans */
            mssOut << (lua_toboolean(L, i) ? "true" : "false");
            break;

         case LUA_TNUMBER:  /* numbers */
            mssOut << lua_tonumber(L, i);
            break;

         default:  /* other values */
            mssOut << lua_typename(L, t);
            break;
      }

      mssOut << "  ";  /* put a separator */
   }

   mssOut << std::endl;  /* end the listing */

   sOutput = mssOut.str();

   return(sOutput);
}



/**
 *
 */
std::string ScriptBase::getStringValue(lua_State *lua, const std::string &tablename)
{
	// lua_pushstring(lua, (char*)(tablename.c_str()));
   // lua_pushstring(lua, (char*)(tablename.c_str()));
   lua_pushstring(lua, static_cast<const char*>(tablename.c_str()));
	lua_gettable(lua, -2);

	if (lua_isstring(lua, -1)) {

		const char *res = lua_tostring(lua, -1);

		lua_pop(lua, 1);
		//std::cout << "RES:" << res << std::endl;

		return res;
	} else {
		lua_pop(lua, 1);

		// LOG("Error!");
		std::stringstream st;

		st << tablename << " not found.";
		luaL_error(lua, st.str().c_str());
	}
	return "";
}


/**
 *
 */
double ScriptBase::getDoubleValue(lua_State *lua, const std::string &tablename)
{
	lua_pushstring(lua, static_cast<const char*>(tablename.c_str()));
	lua_gettable(lua, -2);

	if (lua_isstring(lua, -1)) {

		double res = lua_tonumber(lua, -1);

		lua_pop(lua, 1);

		return res;
	} else {
		lua_pop(lua, 1);

		//LOG("Error!");

		std::stringstream st;

		st << tablename << " not found.";
		luaL_error(lua, st.str().c_str());
	}

	return 0.0f;
}


/**
 *
 */
int ScriptBase::getNumberValue(lua_State *lua, const std::string &tablename)
{
	int value = (int)getDoubleValue(lua, tablename);

	return value;
}


// end of namespace
// ----------------
};

