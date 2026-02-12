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
#include "Gui/PausePanel.h"
#include "Gui/SleepPanel.h"
#include "Gui/ExplorePanel.h"
#include "Gui/MainMenuPanel.h"
#include "Gui/InventoryPanel.h"
#include "Gui/ItemTextPanel.h"

#include "Gui/GamePanel.h"


#include "GameStates/GameStateBase.h"
#include "GameStates/GameStateMainMenu.h"
#include "GameStates/GameStateExplore.h"

#include "GameStates/GameStateHandler.h"


using namespace GusGui;

#include "TextButton.h"

#include "InfoPanel.h"

#include "../GameEventHandler.h"

#include "../Global.h"

#include "../Data.h"

#include "../Dungeon/DrawDungeon.h"
#include "../Dungeon/DungeonObjects/DungeonBase.h"
#include "../Dungeon/DungeonObjects/DungeonWall.h"

#include "../Dungeon/Map.h"
#include "../Dungeon/DungeonHandler.h"
#include "../Dungeon/DrawDungeon.h"


#include "InfoPanel.h"


/**
 *
 */
InfoPanel::InfoPanel() : Panel(Rect(5, 37 + 136 - 20, 214, 10), "Info Panel")
{
   setVisibleAndActive(false);
}


/**
 *
 */
InfoPanel::~InfoPanel()
{
}


/**
 *
 */
InfoPanel &InfoPanel::operator=(const InfoPanel &inInfoPanel)
{
   
   return *this;
}


/**
 *
 */
void InfoPanel::draw(const Vector2d &pos, float opacity) 
{
   if (getVisible()) {
   
      Primitives::rectFill(getRect(), Color(0.0f, 0.0f, 0.0f, 0.5f));
      
      Primitives::rect(getRect(), colorWhite);
      
   
      std::stringstream st;
      st << "TEST:" << DrawDungeon::instance().getStepCounter();
      
      Color col = Color(0.7f, 0.7f, 0.7f);
      
      if (DrawDungeon::instance().getStepCounter() % 2) {
         col = Color(1.0f, 1.0f, 1.0f);
      }
      
      Data::instance().font->draw(getPosition() + Vector2d(3, 3), (std::string)st.str(), col);

   }
}
