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

#include "../Data.h"

#include "../Items/Item.h"
#include "../Items/ItemHolder.h"

#include "../Characters/CharacterHandler.h"

#include "ItemSlot.h"

#include "PlayerPanel.h"


/**
 *
 */

PlayerPanel::PlayerPanel(const Vector2d &inPos, 
                         const std::string &name,
                         int inPlayerNumber) : 
                              //GusGui::GuiEventHandler(),
                              Panel(Rect(inPos, Vector2d(134, 58)), name),
                              m_RightClickEvent(std::make_shared<UserEvent>()),
                              m_PlayerNumber(inPlayerNumber),
                              m_LeaderButton(std::make_shared<Button>(Rect(0, 0, 134, 14), "LeaderButton", nullptr, false)),
                              m_LeaderClickedEvent(std::make_shared<UserEvent>()),
                              m_ShowPortrait(false),
                              m_RightHandSlot(nullptr), m_LeftHandSlot(nullptr)
{
   std::stringstream st;
   
   st << "PlayerPanel constructor - player number: " << inPlayerNumber;
   
   m_RightClickEvent->setUserEventNumber(EVENT_RIGHT_CLICK_PLAYER_0 + inPlayerNumber);
   
   STLOG(st);
   
   addGuiObject(m_LeaderButton);
   
   m_LeaderButton->setPressEvent(m_LeaderClickedEvent);
     
   std::shared_ptr<Player> player = CharacterHandler::instance().getPlayer(inPlayerNumber);
 
   m_LeftHandSlot = std::make_shared<ItemSlot>(Vector2d(8, 20));
   addGuiObject(m_LeftHandSlot);
   if (player != nullptr) {
      std::shared_ptr<ItemHolder> itemHolder = player->getItemHolder(1);
      
      m_LeftHandSlot->setItemHolder(itemHolder);
      m_LeftHandSlot->setInventoryPosition(1);
      m_LeftHandSlot->setDrawRect();
      
      // std::stringstream st;
      st.str("");
      st << "ItemSlot player: " << inPlayerNumber;
      
      m_LeftHandSlot->setName(st.str());
   }
   
   m_RightHandSlot = std::make_shared<ItemSlot>(Vector2d(48, 20));
   
   addGuiObject(m_RightHandSlot);
   if (player != nullptr) {
      m_RightHandSlot->setItemHolder(player->getItemHolder(8));
      m_RightHandSlot->setInventoryPosition(8);
      m_RightHandSlot->setDrawRect();
      
            
      // std::stringstream st;
      st.str("");
      st << "ItemSlot player: " << inPlayerNumber;
      
      m_RightHandSlot->setName(st.str());
   }
   
}


/**
 *
 */
PlayerPanel::~PlayerPanel()
{
   m_LeaderButton.reset();
}


/**
 *
 */
PlayerPanel::PlayerPanel(const PlayerPanel &inPlayerPanel) :
                                            Panel(Rect(inPlayerPanel.getPosition(), Vector2d(138, 58)), ""),
                                             m_PlayerNumber(inPlayerPanel.m_PlayerNumber),
                                             m_LeftHandSlot(inPlayerPanel.m_LeftHandSlot),
                                             m_RightHandSlot(inPlayerPanel.m_RightHandSlot),
                                             m_RightClickEvent(inPlayerPanel.m_RightClickEvent),
                                             m_LeaderClickedEvent(inPlayerPanel.m_LeaderClickedEvent),
                                             m_ShowPortrait(inPlayerPanel.m_ShowPortrait),
                                             m_LeaderButton(inPlayerPanel.m_LeaderButton)
{
   // m_LeftHandSlot = inPlayerPanel.m_LeftHandSlot;
   // m_RightHandSlot = inPlayerPanel.m_RightHandSlot;
   
}

/**
 *
 */
void PlayerPanel::draw(const Vector2d &pos, float opacity) 
{
   // Draw a white outline on the panel
   Rect newRect = getRect() + pos;
   
   if (getVisible()) {

   // Primitives::rect(newRect, colorWhite);
   
      Data::instance().championInformation->blit(getRect().position + Vector2d(0,0));
      
      Color nameColor = colorLightGray;
      
      if (m_PlayerNumber == CharacterHandler::instance().getPartyLeader())
         nameColor = colorYellow;
      
      std::shared_ptr<Player> player = CharacterHandler::instance().getPlayer(m_PlayerNumber);
      
      std::string name = StringHelper::upcase(player->getName());
      
      if (!m_ShowPortrait) {
         Data::instance().font->draw(newRect.position + Vector2d(1, 1), name, nameColor/*Color(1.0f, 1.0f, 1.0f)*/);
      } else {
         // draw the actual portrait
         Primitives::rectFill(Rect(Vector2d(0, 0) + newRect.position, Vector2d(88, 14)), Color(0.314f, 0.314f, 0.314f, 1.0f));
         
         
         
         int portraitNumber = player->getPortrait();
         
         int sourceX = portraitNumber % 8;
         int sourceY = portraitNumber / 8;
         
         Rect sourceRect = Rect(sourceX * 32, sourceY * 29, 32, 29); 
         
         Data::instance().championPortraits->blit(sourceRect, newRect.position + Vector2d(6, 0)); 
      }
      
   // Make the Panel class which we inherit from draw the gui objects
      Panel::draw(pos, opacity);
   }
}



/**
 *
 */
bool PlayerPanel::onRightMouseButtonPressed(const Vector2d &pos)
{

   if (!Panel::onRightMouseButtonPressed(pos)) {
      
      if (Panel::getMouseOver()) {
         // switchToInventoryEvent->pushEvent();
         
         EventSystem::pushEvent(m_RightClickEvent);
            
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
/*
bool PlayerPanel::onLeftMouseButtonPressed(const Vector2d &pos)
{
   if (getActive()) {
      return Panel::onLeftMouseButtonPressed(pos);
   }
   return false;
}
*/


/**
 *
 */
bool PlayerPanel::handleUserEvent(UserEvent &inUserEvent)
{
   // Panel::handleUserEvent(inUserEvent);
   
   if (inUserEvent == *m_LeaderClickedEvent) {
      CharacterHandler::instance().setPartyLeader(m_PlayerNumber);
      return true;
   }
   
   return Panel::handleUserEvent(inUserEvent);
}


/**
 *
 */
void PlayerPanel::setShowPortrait(bool inShowPortrait)
{
   m_ShowPortrait = inShowPortrait;
   
   if (m_ShowPortrait) {
      m_LeftHandSlot->setVisibleAndActive(false);
      m_RightHandSlot->setVisibleAndActive(false);
   } else {
      m_LeftHandSlot->setVisibleAndActive(true);
      m_RightHandSlot->setVisibleAndActive(true);
   }
   
}


/**
 *
 */
void PlayerPanel::setActive(bool active)
{
   for (std::vector<std::shared_ptr<GuiObject>>::iterator iter = m_GuiList->begin(); iter != m_GuiList->end();) {
      std::shared_ptr<GuiObject> obj = (*iter);
      obj->setActive(active);

      ++iter;
   }
   /// GuiObject::setActive(active);
}
