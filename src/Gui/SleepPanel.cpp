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

#include "../Items/Item.h"

#include "Gui/TextButton.h"

#include "Gui/MiniMap.h"
#include "Gui/ExplorePanel.h"
#include "Gui/MainMenuPanel.h"
#include "Gui/InventoryPanel.h"
#include "Gui/PausePanel.h"
#include "Gui/SleepPanel.h"
#include "Gui/ItemTextPanel.h"

#include "Gui/GamePanel.h"


#include "GameStates/GameStateBase.h"
#include "GameStates/GameStateMainMenu.h"
#include "GameStates/GameStateExplore.h"

#include "GameStates/GameStateHandler.h"

#include "TextButton.h"

#include "ExplorePanel.h"

#include "../GameEventHandler.h"

#include "../Global.h"

#include "../Data.h"

#include "../Characters/CharacterHandler.h"

#include "../Items/ItemHandler.h"

#include "../MousePointer.h"

#include "SleepPanel.h"



/**
 *
 */
SleepPanel::SleepPanel() : Panel(Rect(0, 32, 224, 136), "PausePanel")
{
}

/**
 *
 */
SleepPanel::~SleepPanel()
{
}



/**
 *
 */
void SleepPanel::draw(const Vector2d &pos, float opacity) 
{
   // Draw a white outline on the panel
   Rect newRect = getRect() + pos;
   
   if (getVisible()) {
      
      // Data::instance().characterSheet->blit(newRect + Vector2d(0, 0));
      
      /* Rect(0, 32, 224, 136) */
      
      
      // Make the Panel class which we inherit from draw the gui objects
      Panel::draw(pos, opacity);
   }
}

