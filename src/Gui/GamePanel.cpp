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
#include "Gui/ItemTextPanel.h"
#include "Gui/PausePanel.h"
#include "Gui/SleepPanel.h"
#include "Gui/GamePanel.h"


#include "GameStates/GameStateHandler.h"


#include "TextButton.h"

#include "GamePanel.h"

#include "../GameEventHandler.h"

#include "../Global.h"
 
#include "../Data.h"

#include "../Characters/CharacterHandler.h"

#include "../MousePointer.h"


/**
 *
 */
GamePanel::GamePanel() : Panel(Rect(0, 0, 320, 200), "ExamplePanel"),
                               m_SwitchToInventoryEvent(std::make_shared<UserEvent>()),
                               m_SwitchToExploreEvent(std::make_shared<UserEvent>()),
                               m_ExplorePanel(std::make_shared<ExplorePanel>()),
                               m_InfoPanel(std::make_shared<InfoPanel>()),
                               m_InventoryPanel(std::make_shared<InventoryPanel>()),
                               m_PausePanel(std::make_shared<PausePanel>()),
                               m_ItemTextPanel(),
                               m_SleepPanel(std::make_shared<SleepPanel>()),
                               m_MiniMap(std::make_shared<MiniMap>())
                               // m_LeaveGameEvent(std::make_shared<UserEvent>())
                               /*
                               m_QuitButton(std::make_shared<TextButton>(Rect(10, 10, 100, 20))),
                               m_ExampleButton(std::make_shared<TextButton>()),
                               userEvent(std::make_shared<UserEvent>()),
                               leaveGameEvent(std::make_shared<UserEvent>()),
                               switchToInventoryEvent(std::make_shared<UserEvent>())
                               */
{

      
   for (int co = 0; co < 4; co++) {
      std::stringstream st;
      st << "Player Panel:" << co;
      m_PlayerPanel[co] = std::make_shared<PlayerPanel>(Vector2d(co * 138, 0), st.str(), co);

      auto tempPlayerPanel =
         std::static_pointer_cast<GusGui::GuiEventHandler>(m_PlayerPanel[co]);

      EventSystem::addEventHandler(std::dynamic_pointer_cast<GusGui::GuiEventHandler>(m_PlayerPanel[co]));
      
      
      LOG("add playerpanel");
      addGuiObject(m_PlayerPanel[co]);
   }
   
   setPlayerPanelsActive();
   
   auto inventoryPanelEventHandler =
         std::static_pointer_cast<GusGui::GuiEventHandler>(m_InventoryPanel);
   
   EventSystem::addEventHandler(inventoryPanelEventHandler);
   addGuiObject(m_InventoryPanel);
 
   auto explorePanelEventHandler =
         std::static_pointer_cast<GusGui::GuiEventHandler>(m_ExplorePanel);
   
   EventSystem::addEventHandler(explorePanelEventHandler);
   addGuiObject(m_ExplorePanel);
   
   m_ItemTextPanel = std::make_shared<ItemTextPanel>();
   
   addGuiObject(m_ItemTextPanel);
   addGuiObject(m_PausePanel);
   addGuiObject(m_SleepPanel);
   
   m_MiniMap = std::make_shared<MiniMap>();
   
   addGuiObject(m_MiniMap);
   
   addGuiObject(m_InfoPanel);
   
   switchGameMode(GAME_MODE_DUNGEON);
}


/**
 *
 */
void GamePanel::draw(const Vector2d &pos, float opacity)
{
   // Draw a white outline on the panel
   Rect newRect = getRect() + pos;

   // Primitives::rect(newRect, colorWhite);

   // Make the Panel class which we inherit from draw the gui objects
   Panel::draw(pos, opacity);
}


/*
void ExplorePanel::setQuitButtonEvent(std::shared_ptr<UserEvent> inEvent)
{
   m_QuitButton->setPressEvent(inEvent);
}
*/

/*

 */
GamePanel::~GamePanel()
{
   // userEvent.reset();
   /*
    if (userEvent != nullptr) {
        delete userEvent;
        userEvent = nullptr;
    }
    */
    
   //leaveGameEvent.reset();
   /*
    if (leaveGameEvent != nullptr) {
       delete leaveGameEvent;
       leaveGameEvent = nullptr;
    }
   */
}


/**
 *
 */
GamePanel &GamePanel::operator=(const GamePanel &inGamePanel)
{
   // m_LeaveGameEvent = inGamePanel.m_LeaveGameEvent;
   
   m_InventoryPanel = inGamePanel.m_InventoryPanel;
   m_ExplorePanel = inGamePanel.m_ExplorePanel;
   m_ItemTextPanel = inGamePanel.m_ItemTextPanel;
   m_SleepPanel = inGamePanel.m_SleepPanel;
   m_PausePanel = inGamePanel.m_PausePanel;
   m_ItemTextPanel = inGamePanel.m_ItemTextPanel;
   m_InfoPanel = inGamePanel.m_InfoPanel;
   
   return *this;
}


/**
 * Handle keyboard presses and releases
 */
bool GamePanel::handleKeyboard(KeyEvent &keyEvent) {

   // Is it the Escape Button that is pressed? - then quit
   if (keyEvent.getType() == KeyEventPressed) {
      /*
      if (keyEvent.getValue() == Key::A) {
         // Global::quit = true;
        
         userEvent->pushEvent();
         return true;
      }
      */

      if (keyEvent.getValue() == Key::Escape) {
         if (m_InventoryPanel->getVisible()) {
            m_PausePanel->setSavedGameMode(GAME_MODE_INVENTORY);
            switchGameMode(GAME_MODE_PAUSE);
            return true;
         } else if (m_ExplorePanel->getVisible()) {
            m_PausePanel->setSavedGameMode(GAME_MODE_DUNGEON);
            switchGameMode(GAME_MODE_PAUSE);
            return true;
         } else if (m_PausePanel->getVisible()) {
            switchGameMode(m_PausePanel->getSavedGameMode());
            return true;
         }
      }
      
      /*
      if (keyEvent.getValue() == Key::Space) {
         
         return true;
      }
      */
      
      if (keyEvent.getValue() == Key::M) {
         if ((keyEvent.getCtrlPressed()) && (keyEvent.getAltPressed())) {
            m_MiniMap->switchMiniMapVisible();
            return true;
         }
      }
      
      if (keyEvent.getValue() == Key::N) {
         if ((keyEvent.getCtrlPressed()) && (keyEvent.getAltPressed())) {
            // m_ExplorePanel->switchShowStepCounter();
            bool vis = m_InfoPanel->getVisible();
            
            m_InfoPanel->setVisibleAndActive(!vis);
            return true;
         }
      }
      
   }
   //return handleKeyboard(keyEvent);
   return false;
}


/**
 *
 */
void GamePanel::handleSystemQuitEvent()
{
    //eventQuit->pushEvent();
}


/**
 * handle the quit event (This is called when the window close button is
 * pressed.)
 */
void GamePanel::handleQuitEvent()
{
   Global::quit = true;
}


/**
 *
 */
bool GamePanel::handleUserEvent(UserEvent &inUserEvent)
{
   UserEvent tempUserEvent = &inUserEvent;
   
   int userEventNumber = tempUserEvent.getUserEventNumber();
   std::string eventString = tempUserEvent.getEventString();
      
   // Check for the case where we are in inventory mode, and rightclick on
   // the player who's inventory is showing. Then we need to go to explore
   // mode
   if (m_InventoryPanel->getVisible()) {
      if ((userEventNumber >= EVENT_RIGHT_CLICK_PLAYER_0) && (userEventNumber <= EVENT_RIGHT_CLICK_PLAYER_3)) {
         if (userEventNumber - EVENT_RIGHT_CLICK_PLAYER_0 == m_InventoryPanel->getPlayerNumber()) {
            
            m_InventoryPanel->setPlayerNumber(-1);
            setPlayerShowPortrait(-1);
            switchGameMode(GAME_MODE_DUNGEON);
            return true;
         }
      }
   }
   
   switch (userEventNumber) {
   case EVENT_RIGHT_CLICK_PLAYER_0:
      m_InventoryPanel->setPlayerNumber(0);
      switchGameMode(GAME_MODE_INVENTORY);
      setPlayerShowPortrait(0);
      return true;
      break;
   case EVENT_RIGHT_CLICK_PLAYER_1:
      m_InventoryPanel->setPlayerNumber(1);
      switchGameMode(GAME_MODE_INVENTORY);
      setPlayerShowPortrait(1);
      return true;
      break;
   case EVENT_RIGHT_CLICK_PLAYER_2:
      m_InventoryPanel->setPlayerNumber(2);
      switchGameMode(GAME_MODE_INVENTORY);
      setPlayerShowPortrait(2);
      return true;
      break;
   case EVENT_RIGHT_CLICK_PLAYER_3:
      m_InventoryPanel->setPlayerNumber(3);
      switchGameMode(GAME_MODE_INVENTORY);
      setPlayerShowPortrait(3);
      return true;
      break;
   case EVENT_SWITCH_TO_EXPLORE_MODE:
      m_InventoryPanel->setPlayerNumber(-1);
      switchGameMode(GAME_MODE_DUNGEON);
      setPlayerShowPortrait(-1);
      return true;
      break;
   case EVENT_SET_ITEM_TEXT:
      m_ItemTextPanel->setText(eventString);
      return true;
      break;
   default:
      break;
   };
   
   return GuiEventHandler::handleUserEvent(inUserEvent);
}



/**
 *
 */
bool GamePanel::onRightMouseButtonPressed(const Vector2d &pos)
{
   if (!Panel::onRightMouseButtonPressed(pos)) {

      LOG("GamePanel::Right mouse");

      if (m_InventoryPanel->getVisible()) {
         switchGameMode(GAME_MODE_DUNGEON);
         m_InventoryPanel->setPlayerNumber(-1);
         setPlayerShowPortrait(-1);
         return true;
      } else if (m_ExplorePanel->getVisible()) {
         m_InventoryPanel->setPlayerNumber(CharacterHandler::instance().getPartyLeader());
         switchGameMode(GAME_MODE_INVENTORY);
         setPlayerShowPortrait(CharacterHandler::instance().getPartyLeader());
         return true;
      } else if (m_PausePanel->getVisible()) {
         switchGameMode(GAME_MODE_DUNGEON);
         m_InventoryPanel->setPlayerNumber(-1);
         setPlayerShowPortrait(-1);
         return true;
      }
   } else {
      return true;
   }

   return false;
}

/**
 *
 */
bool GamePanel::onLeftMouseButtonPressed(const Vector2d &pos)
{
   if (m_PausePanel->getVisible()) {
      switchGameMode(GAME_MODE_DUNGEON);
      m_InventoryPanel->setPlayerNumber(-1);
      setPlayerShowPortrait(-1);
      return true;
   }
   
   return Panel::onLeftMouseButtonPressed(pos);
}


/**
 *
 */
void GamePanel::setPlayerShowPortrait(int inNumber)
{
   for (int co = 0; co < 4; co++) {
      m_PlayerPanel[co]->setShowPortrait(false);
   }
   
   if ((inNumber >= 0) && (inNumber < 4)) {
      m_PlayerPanel[inNumber]->setShowPortrait(true);
      m_PlayerPanel[inNumber]->setActive(false);
   }
}


/**
 * switches the Gamemode to Explore for true and inventory for false
 */
void GamePanel::switchGameMode(int inGameMode)
{
   switch (inGameMode)
   {
      case GAME_MODE_DUNGEON:
      {
         m_InventoryPanel->setVisibleAndActive(false);
         setPlayerPanelsActive(true);
         m_InventoryPanel->setPlayerNumber(CharacterHandler::instance().getPartyLeader());
         m_ExplorePanel->setVisibleAndActive(true);
         m_PausePanel->setVisibleAndActive(false);
         m_MiniMap->setVisibleAndActive(true);
         MousePointer::instance().setShowItem(true);
      }
      break;
      case GAME_MODE_INVENTORY:
      {
         m_InventoryPanel->setVisibleAndActive(true);
         m_ExplorePanel->setVisibleAndActive(false);
         m_PausePanel->setVisibleAndActive(false);
         MousePointer::instance().setShowItem(true);
         m_MiniMap->setVisibleAndActive(false);
         setPlayerPanelsActive(true);
      }
      break;
      case GAME_MODE_SLEEP:
      break;
      case GAME_MODE_PAUSE:
      {
         m_InventoryPanel->setVisibleAndActive(false);
         m_ExplorePanel->setVisibleAndActive(false);
         m_PausePanel->setVisibleAndActive(true);
         MousePointer::instance().setShowItem(false);
         m_MiniMap->setVisibleAndActive(false);
         setPlayerPanelsActive(false);
      }
      break;
   };
}


/**
 *
 */
void GamePanel::setPlayerPanelsActive(bool inActive)
{
   for (int co = 0; co < 4; co++) {
      m_PlayerPanel[co]->setActive(inActive);
   }
}


/**
 *
 */
/*
int GamePanel::getGameModeInteger()
{
   int result = -1;
   if (m_InventoryPanel->getVisible()) {
      result = GAME_MODE_INVENTORY;
   } else if (m_ExplorePanel->getVisible()) {
      result = GAME_MODE_DUNGEON;
   } else if (m_PausePanel->getVisible()) {
      result = GAME_MODE_PAUSE;
   } else if (m_SleepPanel->getVisible()) {
      result = GAME_MODE_SLEEP;
   }
   
   return result;
}
*/