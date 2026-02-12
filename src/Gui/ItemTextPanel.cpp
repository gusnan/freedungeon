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

#include "GusGui/GusGui.h"

using namespace GusGui;

#include "../Data.h"

#include "../Items/Item.h"
#include "../Items/ItemHolder.h"

#include "ItemTextPanel.h"


/**
 *
 */
// ItemTextPanel::ItemTextPanel() : Panel(Rect(233, 32, 100, 7), "ItemTextPanel"), m_Text("")
ItemTextPanel::ItemTextPanel() : Panel(Rect(466, 64, 200, 14), "ItemTextPanel"), m_Text("")
{
}


/**
 *
 */
ItemTextPanel::~ItemTextPanel()
{
}



/**
 *
 */
ItemTextPanel::ItemTextPanel(const ItemTextPanel &inItemTextPanel) : m_Text(inItemTextPanel.m_Text)
{
   // m_LeftHandSlot = inPlayerPanel.m_LeftHandSlot;
   // m_RightHandSlot = inPlayerPanel.m_RightHandSlot;
   
}


void ItemTextPanel::draw(const Vector2d &pos, float opacity) 
{ 
   Rect newRect = getRect() + pos;
   
   
   if (getVisible()) {

 
      //std::string name = StringHelper::upcase(player->getName());
      
      Data::instance().font->draw(newRect.position + Vector2d(0, 0), m_Text, colorCyan/*Color(1.0f, 1.0f, 1.0f)*/);
      
   // Make the Panel class which we inherit from draw the gui objects
      Panel::draw(pos, opacity);
   }
   
}



/**
 *
 */
void ItemTextPanel::setText(const std::string &inText)
{
   m_Text = StringHelper::upcase(inText);
}
