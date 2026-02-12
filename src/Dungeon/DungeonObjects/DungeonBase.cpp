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

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <memory>

#include "GusGame/GusGame.h"

#include "GusGame/EventLib.h"
#include "GusGame/EventSystem.h"

using namespace Gus;

using namespace LogLib;
using namespace ExceptionLib;
using namespace GraphicsLib;
using namespace EventLib;


#include "DungeonBase.h"



/**
 *
 */
DungeonBase::DungeonBase() : m_CanWalk(false), m_GuiPosition(Vector2d(0, 0))
{
}


/**
 *
 */
DungeonBase::~DungeonBase()
{
}


/**
 *
 */
bool DungeonBase::getCanWalk()
{
   return m_CanWalk;
}


/**
 *
 */
void DungeonBase::setGuiPosition(const Vector2d &inPosition)
{
   m_GuiPosition = inPosition;
}


/**
 *
 */
Vector2d DungeonBase::getGuiPosition()
{
   return m_GuiPosition;
}