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

#include "../Gui/TextButton.h"

#include "../Gui/MiniMap.h"
#include "../Gui/SleepPanel.h"
#include "../Gui/PausePanel.h"
#include "../Gui/ExplorePanel.h"
#include "../Gui/MainMenuPanel.h"
#include "../Gui/InventoryPanel.h"
#include "../Gui/ItemTextPanel.h"
#include "../Gui/GamePanel.h"

#include "GameStateBase.h"
#include "GameStateExplore.h"

#include "../Items/ItemHandler.h"

#include "../Characters/CharacterHandler.h"

#include "../MousePointer.h"

#include "../Dungeon/DrawDungeon.h"

#include "../Dungeon/DungeonObjects/DungeonWall.h"

#include "../Dungeon/Map.h"

#include "../Dungeon/DungeonHandler.h"

/**
 *
 */
GameModeExplore::GameModeExplore() : GameModeBase(), 
                                     m_GamePanel(std::make_shared<GamePanel>()) 
{
   LOG("GameModeExplore constructor");
   
   // exploreEventHandler = std::make_shared<ExploreEventHandler>();
   
   // m_ExplorePanel = std::make_shared<ExplorePanel>();
   // m_ExplorePanel->setQuitButtonEvent(exploreEventHandler->getLeaveGameEvent());
}


/**
 *
 */
GameModeExplore::~GameModeExplore()
{
   LOG("GameModeExplore destructor");
   
   m_GamePanel.reset();
}


/**
 *
 */
GameModeExplore::GameModeExplore(const GameModeExplore *inGameModeExplore) : m_GamePanel(nullptr)
{
}


/**
 *
 */
void GameModeExplore::enterGameMode()
{
   LOG("Enter Explore Game Mode");
   
   // ItemHandler::instance().initItemHandler();
   
   // CharacterHandler::instance().initCharacterHandler();
   
   std::shared_ptr<GusGui::GuiEventHandler> panelEventHandler = 
         std::static_pointer_cast<GusGui::GuiEventHandler>(m_GamePanel);
   
   EventSystem::addEventHandler(panelEventHandler);
      
   GuiHandler::instance()->addGuiObject(m_GamePanel);
   
   DrawDungeon::instance().initDrawDungeon();
   
   DungeonHandler::instance().initDungeonHandler();
   
}


/**
 *
 */
void GameModeExplore::leaveGameMode()
{
   LOG("Leave Explore Game Mode");
   
   std::shared_ptr<GusGui::GuiEventHandler> panelEventHandler = 
         std::static_pointer_cast<GusGui::GuiEventHandler>(m_GamePanel);
   
   EventSystem::removeEventHandler(panelEventHandler);
   
   GuiHandler::instance()->removeGuiObject(m_GamePanel);
   
   MousePointer::instance().setItem(nullptr);
   
   DrawDungeon::instance().doneDrawDungeon();
   
   DungeonHandler::instance().doneDungeonHandler();
}


/**
 *
 */
GameModeExplore &GameModeExplore::operator=(const GameModeExplore &inGameModeExplore)
{
   m_GamePanel = inGameModeExplore.m_GamePanel;
   return *this;
}

