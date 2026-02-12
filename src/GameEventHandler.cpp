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

#include "GameEventHandler.h"

#include "GameStates/GameStateHandler.h"

#include "Global.h"

#include "MousePointer.h"

 // std::shared_ptr<GlobalEventHandler> GlobalEventHandler::pinstance = nullptr;// initialize pointer

/**
 *	This should be a singleton, thus we need the Instance method
 */
 /*
std::shared_ptr<GlobalEventHandler> GlobalEventHandler::instance ()
{
   if (pinstance == nullptr) {
      pinstance = std::shared_ptr<GlobalEventHandler>(new GlobalEventHandler);
   }
   return pinstance;
}
*/

/*

 */

GameEventHandler::GameEventHandler() : GuiEventHandler(), 
                                           globalQuitEvent(std::make_shared<UserEvent>()),
                                           m_GlobalMousePosition()
{
}


/*

 */
GameEventHandler::~GameEventHandler()
{
   LOG("GlobalEventHandler destructor");
   globalQuitEvent.reset();
}


/**
 *
 */
GameEventHandler::GameEventHandler(const GameEventHandler &source) : globalQuitEvent(nullptr), m_GlobalMousePosition()
{
}


/**
 *
 */
GameEventHandler &GameEventHandler::operator=(const GameEventHandler &)
{
    return *this;
}


/**
 * Handle keyboard presses and releases
 */
bool GameEventHandler::handleKeyboard(KeyEvent &keyEvent) {

    // Is it the Escape Button that is pressed? - then quit
    if (keyEvent.getType() == KeyEventPressed) {
        if ((keyEvent.getValue() == Key::X) &&
            (keyEvent.getCtrlPressed()) && (keyEvent.getAltPressed())) {
            // Global::quit = true;
           
            EventSystem::pushEvent(globalQuitEvent);
            return true;
        }        

        if ((keyEvent.getValue() == Key::O) &&
            (keyEvent.getCtrlPressed()) && (keyEvent.getAltPressed())) {
            // Global::quit = true;

            std::stringstream st;
               
            st << "Mouse position: " << m_GlobalMousePosition;
               
            STLOG(st);
               
            return true;
        }
        
        if ((keyEvent.getValue() == Key::D) &&
            (keyEvent.getAltPressed())) 
        {
            LOG("Screenshot!");
            
            return true;
         }
    }
    return false;
}


/**
 *
 */
void GameEventHandler::handleSystemQuitEvent()
{
    //eventQuit->pushEvent();
}


/**
 * handle the quit event (This is called when the window close button is
 * pressed.)
 */
void GameEventHandler::handleQuitEvent()
{
    Global::quit = true;
}


/**
 *
 */
bool GameEventHandler::handleUserEvent(UserEvent &inUserEvent)
{
   if (inUserEvent == *globalQuitEvent) {
      Global::quit = true;

      return true;
   }
   return GuiEventHandler::handleUserEvent(inUserEvent);
}


/**
 * handle mouse movement
 */
void GameEventHandler::handleMouseMotion(MouseMotionEvent &event)
{
   m_GlobalMousePosition = event.getPosition();
}


/**
 *
 */
const Vector2d GameEventHandler::getMousePosition()
{
   return m_GlobalMousePosition;
}


/**
 *
 */
void GameEventHandler::handleActiveEvent(ActiveEvent &activeEvent)
{
   ActiveWindowState windowState = activeEvent.getWindowState();
   
   if (windowState == WindowStateMouseFocusLost) {
      MousePointer::instance().hide();
   }
   
   if (windowState == WindowStateMouseFocusGain) {
      MousePointer::instance().show();
   }
}
