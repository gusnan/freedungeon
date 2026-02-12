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
#ifndef __HEADER_INVENTORY_PANEL_
#define __HEADER_INVENTORY_PANEL_

#include "ItemSlot.h"

class InventoryPanel : public Panel
{
public:
   InventoryPanel();
   virtual ~InventoryPanel();

   // ExplorePanel(const ExplorePanel &source);

   InventoryPanel &operator=(const InventoryPanel &);
   
   void draw(const Vector2d &pos, float opacity = 1.0) override;

   virtual bool handleKeyboard(KeyEvent &keyEvent);
   virtual void handleSystemQuitEvent();

   virtual void handleQuitEvent();

   virtual bool handleUserEvent(UserEvent &inUserEvent) override;

   virtual bool onRightMouseButtonPressed(const Vector2d &pos) override;

   void setPlayerNumber(int inPlayerNumber);
   int getPlayerNumber();

protected:
   
   // std::shared_ptr<TextButton> m_ExampleButton;
   std::shared_ptr<Button> m_QuitButton;
   std::shared_ptr<Button> m_CloseInventoryButton;

   std::shared_ptr<UserEvent> userEvent;
   std::shared_ptr<UserEvent> m_SwitchToExploreEvent;
   std::shared_ptr<UserEvent> m_LeaveGameEvent;

   int m_PlayerNumber;

   std::shared_ptr<ItemSlot> m_ItemSlot[30];

};

#endif /*__HEADER_INVENTORY_PANEL_*/
