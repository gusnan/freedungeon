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

/*

    6,  33 - neclace
    6,  53 - left_hand
    6,  73 - belt 1
    6,  90 - belt 2

   34,  26 - head
   34,  46 - torso
   34,  66 - legs
   34,  86 - feet
   
   62,  53 - right hand
   62,  73 - right belt 1
   79,  73 - right belt 2
   62,  90 - right belt 3
   79,  90 - right belt 4
   
   83,  16
   100, 16
   117, 16
   134, 16
   151, 16
   168, 16
   185, 16
   202, 16
   
   66,  33
   83,  33
   100, 33
   117, 33
   134, 33
   151, 33
   168, 33
   185, 33
   202, 33
   
*/

const int inventory_pos_x[30] = { 12,  12,  12, 12,   68,  68,  68,  68, 124,
                                 124, 158, 124, 158, 166, 200, 234, 268, 302, 
                                 336, 370, 404, 132, 166, 200, 234, 268, 302, 
                                 336, 370, 404};
                                 
const int inventory_pos_y[30] = {  66, 106, 146, 180,  52, 92, 132, 172, 106, 
                                  146, 146, 180, 180,  32, 32,  32,  32,  32, 
                                   32,  32,  32,  66,  66, 66,  66,  66,  66, 
                                    66, 66,  66};

                                  /*
const int inventory_pos_x[30] = {  6,  6,   6,   6,  34,  34,  34,  34,  62,
                                  62,  79,  62, 79,  83, 100, 117, 134, 151, 
                                 168, 185, 202, 66,  83, 100, 117, 134, 151, 
                                 168, 185, 202};
                                 
const int inventory_pos_y[30] = { 33, 53, 73, 90, 26, 46, 66, 86, 53, 73, 73, 
                                  90, 90, 16, 16, 16, 16, 16, 16, 16, 16, 33, 
                                  33, 33, 33, 33, 33, 33, 33, 33 };
*/
                                  
/**
 *
 */
InventoryPanel::InventoryPanel() : Panel(Rect(0, 64, 448, 272), "Inventory Panel"),
                                 m_QuitButton(std::make_shared<Button>(Rect(360, 6, 18, 18), "", nullptr, false)), 
                                 //m_ExampleButton(nullptr),
                                 m_CloseInventoryButton(std::make_shared<Button>(Rect(Vector2d(420, 6), Vector2d(18, 18)), "", nullptr, false)),
                                 userEvent(std::make_shared<UserEvent>()),
                                 m_SwitchToExploreEvent(std::make_shared<UserEvent>()),
                                 m_LeaveGameEvent(std::make_shared<UserEvent>()),
                                 m_PlayerNumber(0)
                                 
{
	// We add a button to the panel. This at position 10,10 in the panel,
		// which places it at 110,110 on the screen.
	//	m_ExampleButton = boost::shared_ptr<ExampleButton>(new ExampleButton(Rect(10, 10, 100, 20)));
   
   // m_QuitButton->setPressEvent(leaveGameEvent);

   // m_QuitButton->setCenter(Rect(0, 0, 400, 300), GUI_OBJECT_CENTER_HORISONTALLY);
   // addGuiObject(m_QuitButton);

   // m_ExampleButton = std::shared_ptr<TextButton>(new TextButton(Rect(80, 170, 100, 10)));
   // m_QuitButton->setEvent(EventLib::eventQuit);

   // m_QuitButton->setPressEvent(userEvent);
   // addGuiObject(m_ExampleButton);
   
   std::shared_ptr<Player> player = CharacterHandler::instance().getPlayer(0);
   
   for (int co = 0; co < 30; co++) {
      m_ItemSlot[co] = std::make_shared<ItemSlot>(Vector2d(inventory_pos_x[co], inventory_pos_y[co]));
      
      m_ItemSlot[co]->setItemHolder(player->getItemHolder(co));
      m_ItemSlot[co]->setInventoryPosition(co);
     
      addGuiObject(m_ItemSlot[co]);
   }
   
   m_SwitchToExploreEvent->setUserEventNumber(EVENT_SWITCH_TO_EXPLORE_MODE);
   
   // m_CloseInventoryButton = std::make_shared<Button>(Rect(Vector2d(210, 3), Vector2d(9, 9)), "", nullptr, false);
   m_CloseInventoryButton->setPressEvent(m_SwitchToExploreEvent);
   
   addGuiObject(m_CloseInventoryButton);
   
   m_QuitButton->setPressEvent(m_LeaveGameEvent);
   
   addGuiObject(m_QuitButton);
   
   // std::shared_ptr<ItemHolder> itemHolder = std::make_shared<ItemHolder>();
   
   // m_ItemSlot->setItemHolder(itemHolder);
   
   // std::shared_ptr<Item> item = ItemHandler::instance().makeItem("Torch");
   
   // m_ItemSlot->getItemHolder()->setItem(item);
   
   // addGuiObject(m_ItemSlot);
}


/**
 *
 */
void InventoryPanel::draw(const Vector2d &pos, float opacity) 
{
   // Draw a white outline on the panel
   Rect newRect = getRect() + pos;
   
   if (getVisible()) {
      
      Data::instance().characterSheet->blit(newRect + Vector2d(0, 0));
      
      std::string name = StringHelper::upcase(CharacterHandler::instance().getPlayer(getPlayerNumber())->getName());
      std::string surname = StringHelper::upcase(CharacterHandler::instance().getPlayer(getPlayerNumber())->getSurname());
      
      std::stringstream st;
      
      st << name << " " << surname;
      
      Color nameColor = colorLightGray;
      
      if (m_PlayerNumber == CharacterHandler::instance().getPartyLeader())
         nameColor = colorYellow;
      
      Data::instance().font->draw(newRect.position + Vector2d(3, 3), st.str(), nameColor);

      // Make the Panel class which we inherit from draw the gui objects
      Panel::draw(pos, opacity);

      /*
      Rect r = m_CloseInventoryButton->getRect();
      Primitives::rect(r + newRect.position, Color(1.0f, 1.0f, 1.0f, 1.0f));
      
      r = m_QuitButton->getRect();
      Primitives::rect(r + newRect.position, Color(1.0f, 1.0f, 1.0f, 1.0f));
      */
   }
}


/*
void ExplorePanel::setQuitButtonEvent(std::shared_ptr<UserEvent> inEvent)
{
   m_QuitButton->setPressEvent(inEvent);
}
*/

/**
 *
 */
InventoryPanel::~InventoryPanel()
{
   userEvent.reset();
   /*
    if (userEvent != nullptr) {
        delete userEvent;
        userEvent = nullptr;
    }
    */
    
   m_LeaveGameEvent.reset();
   /*
    if (leaveGameEvent != nullptr) {
       delete leaveGameEvent;
       leaveGameEvent = nullptr;
    }
   */
   
      for (int co = 0; co < 30; co++) {
         m_ItemSlot[co].reset();
      }
}



/**
 *
 */
InventoryPanel &InventoryPanel::operator=(const InventoryPanel &)
{
    return *this;
}


/**
 * Handle keyboard presses and releases
 */
bool InventoryPanel::handleKeyboard(KeyEvent &keyEvent) {

   if (getActive()) {
      // Is it the Escape Button that is pressed? - then quit
      if (keyEvent.getType() == KeyEventPressed) {

         if (keyEvent.getValue() == Key::V) {
            LOG("Torch");
            std::shared_ptr<Item> item = ItemHandler::instance().makeItem("Torch");

            MousePointer::instance().setItem(item);

            return true;
         }

         if (keyEvent.getValue() == Key::B) {

            std::shared_ptr<Item> item = ItemHandler::instance().makeItem("Skeleton Key");

            MousePointer::instance().setItem(item);

            return true;
         }

         /*

         if (keyEvent.getValue() == Key::Escape) {
         leaveGameEvent->pushEvent();
         return true;
         }
         */
      }
   }
   return GuiEventHandler::handleKeyboard(keyEvent);
}


/**
 *
 */
void InventoryPanel::handleSystemQuitEvent()
{
    //eventQuit->pushEvent();
}


/**
 * handle the quit event (This is called when the window close button is
 * pressed.)
 */
void InventoryPanel::handleQuitEvent()
{
    Global::quit = true;
}


/**
 *
 */
bool InventoryPanel::handleUserEvent(UserEvent &inUserEvent)
{
   /*
   LOG("InventoryPanel::User event..");
   
      
   std::string qw = inUserEvent.getEventString();
   std::stringstream st2;
   st2 << "Test2: '" << qw << "'";
   STLOG(st2);
   */
   
   
   if (inUserEvent == *m_LeaveGameEvent) {
      LOG("Switch to Main Menu");
      GameModeHandler::instance().setGameMode(GAME_STATE_MAIN_MENU);
      return true;
   }

   /*
   if (*userEvent == inUserEvent) {
      Global::quit = true;

      return true;
   }
   */
   /*
   if (inUserEvent == *leaveGameEvent) {
      GameModeHandler::instance().setGameMode(GAME_MODE_MAIN_MENU);
      return true;
   }
   */


   return GuiEventHandler::handleUserEvent(inUserEvent);
}


/**
 *
 */
bool InventoryPanel::onRightMouseButtonPressed(const Vector2d &pos)
{
   /*
   LOG("Right mouse");
   switchToInventoryEvent->pushEvent();
   */
   
   return false;
}

/**
 *
 */
void InventoryPanel::setPlayerNumber(int inPlayerNumber)
{
   if (inPlayerNumber > -1) {
      m_PlayerNumber = inPlayerNumber;
      
      std::shared_ptr<Player> player = CharacterHandler::instance().getPlayer(inPlayerNumber);
      
      if (player != nullptr)
         for (int co = 0; co < 30; co++) {
            m_ItemSlot[co]->setItemHolder(player->getItemHolder(co));
         }
         
      // std::cout << "Holder: " << (long)(player->getItemHolder(8).get()) << std::endl;
   }
}


/**
 *
 */
int InventoryPanel::getPlayerNumber()
{
   return m_PlayerNumber;
}
