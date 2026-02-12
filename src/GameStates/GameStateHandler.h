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
#ifndef __HEADER_GAME_MODE_HANDLER_
#define __HEADER_GAME_MODE_HANDLER_


#include "GameStateBase.h"
#include "GameStateMainMenu.h"
#include "GameStateExplore.h"


const int GAME_STATE_EXPLORE =      1;
// const int GAME_MODE_INVENTORY =    2;
const int GAME_STATE_MAIN_MENU =    3;

/**
 *
 */
class GameModeHandler
{
public:

   static GameModeHandler &instance();

   void initGameModeHandler();
   void doneGameModeHandler();

   void setGameMode(std::shared_ptr<GameModeBase> gameMode);
   void setGameMode(int gameMode);

protected:
   GameModeHandler();
   virtual ~GameModeHandler();

private:
   
   std::shared_ptr<GameModeBase> currentGameMode;

   std::shared_ptr<GameModeMainMenu> gameModeMainMenu;
   std::shared_ptr<GameModeExplore> gameModeExplore;
   // std::shared_ptr<GameModeInventory> gameModeInventory;
};


#endif /*__HEADER_GAME_MODE_HANDLER_*/
