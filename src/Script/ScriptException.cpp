/**
 *
 *	This file is part of FreeDungeon.
 *	Copyright 2019-2026 Andreas Rönnquist
 *
 *	FreeDungeon is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	FreeDungeon is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with FreeDungeon.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <list>
#include <sstream>
#include <memory>

#include "GusGame/GusGame.h"

using namespace Gus;

// #include "ExceptionLib.h"
using namespace ExceptionLib;
using namespace EventLib;

#include "ScriptException.h"

/**
 *
 */
ScriptException::ScriptException(const char *aszMsg, const std::string &luaErrorString) : RuntimeError( aszMsg ), m_LuaErrorString(luaErrorString), m_LuaString(aszMsg)
{
}

/**
 *
 */
ScriptException::ScriptException(const char *aszMsg) : RuntimeError( aszMsg ), m_LuaErrorString(""), m_LuaString("")
{
}


/**
 *
 */
ScriptException::ScriptException(const ScriptException &source) : RuntimeError(""), m_LuaErrorString(""), m_LuaString("")
{
   if (this != &source) {
      m_LuaErrorString = source.m_LuaErrorString;
      m_LuaString = source.m_LuaString;
   }
}

/**
 *
 */
const std::string &ScriptException::getLuaErrorString()
{
   return m_LuaErrorString;
}


/**
 *
 */
const std::string &ScriptException::getLuaString()
{
   return m_LuaString;
}


/**
 *
 */
// cppcheck-suppress [unusedFunction]
void ScriptException::setLuaString(const std::string &inString)
{
   m_LuaString = inString;
}
