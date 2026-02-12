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

#include "Items/Item.h"

#include "Gui/MiniMap.h"
#include "Gui/TextButton.h"
#include "Gui/MainMenuPanel.h"
#include "Gui/ExplorePanel.h"
#include "Gui/InventoryPanel.h"
#include "Gui/PausePanel.h"
#include "Gui/SleepPanel.h"
#include "Gui/ItemTextPanel.h"

#include "Gui/GamePanel.h"

#include "GameStates/GameStateBase.h"
#include "GameStates/GameStateExplore.h"
#include "GameStates/GameStateMainMenu.h"

#include "GameEventHandler.h"

#include "Global.h"

using namespace GusGui;


bool Global::quit = false;

std::shared_ptr<GameEventHandler> Global::gameEventHandler;
