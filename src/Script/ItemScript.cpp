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
#include <iostream>
#include <list>
#include <sstream>
#include <memory>

#include "GusGame/GusGame.h"

using namespace Gus;
using namespace Gus::ExceptionLib;
using namespace StringHelper;

using namespace LogLib;
using namespace GraphicsLib;

using namespace EventLib;

#include "ScriptBase.h"
// #include "Script.h"

#include "../Items/Item.h"
#include "../Items/ItemHandler.h"

#include "ItemScript.h"

// #include "ItemInclude.h"

#include "../Data.h"


/**
 *
 */
ItemScript::ItemScript() : ScriptBase()
{
	setup();
}


/**
 *
 */
ItemScript::~ItemScript()
{
}


/**
 *
 */
void ItemScript::registerCFunctions()
{
	lua_register(mlState, "create_item", luaCreateItem );
	lua_register(mlState, "log", luaLog);
}



/**
 *
 */
int ItemScript::luaCreateItem(lua_State *lua)
{
	std::string name = "", type = "";

	LOG("[C++] luaCreateItem.");

	if (!lua_istable(lua, -1)) {
		luaL_error(lua, "Table needed for item creation");
		return 0;
	}

	name = getStringValue(lua, "name");

	std::stringstream st;
	st << "Name: " << name;
	STLOG(st);

	type = StringHelper::lowercase(getStringValue(lua, "type"));

	st.str("");
	st << "Type: " << type;
	STLOG(st);

	double weight = getDoubleValue(lua, "weight");

	st.str("");
	st << "Weight: " << weight;
	STLOG(st);

	int smallimage = getNumberValue(lua, "smallimage");
	st.str("");
	st << "Smallimage: " << smallimage;
	STLOG(st);


   /*
	if (type == "consumable") {
   */
   
		std::shared_ptr<Item> item = std::make_shared<Item>();
      item->setName(name);
		item->setSmallImage(smallimage);
		// item->setWeight(weight);

		ItemHandler::instance().addMakeableItem(item);

   /*
	} else if (type == "container") {
		LOG("CONTAINER!");
	}
   */

	return 0;
}


/**
 *
 */
int ItemScript::luaLog(lua_State *lua)
{
	const char *message = luaL_checkstring(lua, 1);

	LOG(message);

	return 0;
}
