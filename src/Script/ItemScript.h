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
#ifndef __ITEM_SCRIPT_HEADER_
#define __ITEM_SCRIPT_HEADER_

/**
 *
 */
class ItemScript : public ScriptLib::ScriptBase
{
public:
	ItemScript();
	virtual ~ItemScript() override;

	virtual void registerCFunctions(void) override;

	static int luaLog(lua_State *lua);

	static int luaCreateItem(lua_State *lua);
protected:

};

#endif /*__ITEM_SCRIPT_HEADER_*/
