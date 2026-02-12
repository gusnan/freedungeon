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

/*
#include "GameModes/MainMenuEventHandler.h"

#include "GameModes/GameModeBase.h"
#include "GameModes/GameModeMainMenu.h"
#include "GameModes/GameModeExplore.h"

#include "GameModes/GameModeHandler.h"
*/

using namespace GusGui;

#include "../Items/Item.h"

#include "TextButton.h"

#include "MainMenuPanel.h"


#include "Gui/MiniMap.h"
#include "Gui/TextButton.h"
#include "Gui/ExplorePanel.h"
#include "../Gui/InventoryPanel.h"
#include "Gui/PausePanel.h"
#include "Gui/SleepPanel.h"
#include "Gui/ItemTextPanel.h"

#include "../Gui/GamePanel.h"

#include "../GameEventHandler.h"



#include "GameStates/GameStateBase.h"
#include "GameStates/GameStateMainMenu.h"
#include "GameStates/GameStateExplore.h"

#include "GameStates/GameStateHandler.h"

#include "../Global.h"

#include "../Data.h"


/**
 *
 */
MainMenuPanel::MainMenuPanel() : Panel(GraphicsHandler::instance().getScreenRect(), "ExamplePanel"), 
                                 m_ExampleButton(std::make_shared<TextButton>(Rect(10, 10, 100, 20))), 
                                 m_QuitButton(std::make_shared<TextButton>()),
                                 enterGameEvent(nullptr)
{
	// We add a button to the panel. This at position 10,10 in the panel,
		// which places it at 110,110 on the screen.
	//	m_ExampleButton = boost::shared_ptr<ExampleButton>(new ExampleButton(Rect(10, 10, 100, 20)));

   m_ExampleButton->setCenter(Rect(0, 0, 400, 300), GUI_OBJECT_CENTER_HORISONTALLY);
   addGuiObject(m_ExampleButton);

   m_QuitButton = std::shared_ptr<TextButton>(new TextButton(Rect(10, 170, 100, 10)));
   // m_QuitButton->setEvent(EventLib::eventQuit);

   // m_QuitButton->setPressEvent(userEvent);
   addGuiObject(m_QuitButton);

   enterGameEvent = std::make_shared<UserEvent>(); // std::make_shared<UserEvent>();
   
   m_ExampleButton->setPressEvent(enterGameEvent);
   
   
}


/**
 *
 */
MainMenuPanel::~MainMenuPanel()
{
   enterGameEvent.reset();
}


/**
 *
 */
void MainMenuPanel::draw(const Vector2d &pos, float opacity) 
{
   Data::instance().mainMenuScreen->blit(pos + Vector2d(0,0));
   // Draw a white outline on the panel
   Rect newRect = getRect() + pos;
   
   Data::instance().mainMenuLeftDoor->blit(pos + Vector2d(0,32));
   Data::instance().mainMenuRightDoor->blit(pos + Vector2d(104,32));

   //Primitives::rect(newRect, colorWhite);

   // Make the Panel class which we inherit from draw the gui objects
   Panel::draw(pos, opacity);
}


/**
 *
 */
MainMenuPanel::MainMenuPanel(const MainMenuPanel &source) : m_ExampleButton(source.m_ExampleButton),
                                                            m_QuitButton(source.m_QuitButton),
                                                            enterGameEvent(source.enterGameEvent)
{
}


/**
 *
 */
MainMenuPanel &MainMenuPanel::operator=(const MainMenuPanel &)
{
    return *this;
}


/**
 * Handle keyboard presses and releases
 */
bool MainMenuPanel::handleKeyboard(KeyEvent &keyEvent) {

    // Is it the Escape Button that is pressed? - then quit
    if (keyEvent.getType() == KeyEventPressed) {
        if (keyEvent.getValue() == Key::A) {
            // Global::quit = true;
           
            EventSystem::pushEvent(enterGameEvent);
            return true;
        }
    }
    return false;
}


/**
 *
 */
void MainMenuPanel::handleSystemQuitEvent()
{
    //eventQuit->pushEvent();
}


/**
 * handle the quit event (This is called when the window close button is
 * pressed.)
 */
void MainMenuPanel::handleQuitEvent()
{
    Global::quit = true;
}


/**
 *
 */
bool MainMenuPanel::handleUserEvent(UserEvent &inUserEvent)
{
   LOG("MainMenuEventHandler::User event..");

   if (inUserEvent == *enterGameEvent) {
        // Global::quit = true;
        GameModeHandler::instance().setGameMode(GAME_STATE_EXPLORE);

        return true;
   }
   return GuiEventHandler::handleUserEvent(inUserEvent);
}

