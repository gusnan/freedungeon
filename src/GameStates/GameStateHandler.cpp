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

// cppcheck-suppress [missingInclude]
#include "GusGame/GusGame.h"

// cppcheck-suppress [missingInclude]
#include "GusGame/EventLib.h"
// cppcheck-suppress [missingInclude]
#include "GusGame/EventSystem.h"

using namespace Gus;

using namespace LogLib;
using namespace ExceptionLib;
using namespace GraphicsLib;
using namespace EventLib;

// cppcheck-suppress [missingInclude]
#include "GusGui/GusGui.h"

using namespace GusGui;

#include "../Items/Item.h"

#include "../Gui/MiniMap.h"
#include "../Gui/TextButton.h"
#include "../Gui/MainMenuPanel.h"
#include "../Gui/ExplorePanel.h"
#include "../Gui/InventoryPanel.h"
#include "../Gui/PausePanel.h"
#include "../Gui/SleepPanel.h"
#include "../Gui/ItemTextPanel.h"

#include "../Gui/GamePanel.h"

#include "GameStateHandler.h"



/**
 *
 */
GameModeHandler &GameModeHandler::instance()
{
   static GameModeHandler instance;
   return instance;
}


/**
 *
 */
GameModeHandler::GameModeHandler() : currentGameMode(nullptr), 
                                     gameModeMainMenu(nullptr), 
                                     gameModeExplore(nullptr)
                                     // gameModeInventory(nullptr)
{
   LOG("GameModeHandler constructor");
}


/**
 *
 */
GameModeHandler::~GameModeHandler()
{
   doneGameModeHandler();
}


/**
 *
 */
void GameModeHandler::initGameModeHandler()
{
   LOG("initGameModeHandler");
   gameModeMainMenu = std::make_shared<GameModeMainMenu>();
   gameModeExplore = std::make_shared<GameModeExplore>();
   /// gameModeInventory = std::make_shared<GameModeInventory>();
   
   // setGameMode(gameModeMainMenu);
   setGameMode(gameModeExplore);
}


/**
 *
 */
void GameModeHandler::doneGameModeHandler()
{
   LOG("doneGameModeHandler");
   gameModeMainMenu.reset();
   gameModeExplore.reset();
   // gameModeInventory.reset();
}


/**
 *
 */
void GameModeHandler::setGameMode(std::shared_ptr<GameModeBase> inGameMode)
{
   if (currentGameMode != nullptr) {
      currentGameMode->leaveGameMode();
   }
   
   currentGameMode = inGameMode;
   
   if (currentGameMode != nullptr) {
      currentGameMode->enterGameMode();
   }
}


/**
 *
 */
void GameModeHandler::setGameMode(int gameMode)
{
   switch (gameMode)
   {
   case GAME_STATE_MAIN_MENU:
      setGameMode(gameModeMainMenu);
      break;
   case GAME_STATE_EXPLORE:
      setGameMode(gameModeExplore);
      break;
   /*
   case GAME_MODE_INVENTORY:
      setGameMode(gameModeInventory);
      break;
   */
   }
}
