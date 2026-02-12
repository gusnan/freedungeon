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
#ifndef __HEADER_EXPLORE_PANEL_
#define __HEADER_EXPLORE_PANEL_

#include "InfoPanel.h"

class ExplorePanel : public Panel
{
public:
   ExplorePanel();
   virtual ~ExplorePanel();

   ExplorePanel &operator=(const ExplorePanel &);
   
   void draw(const Vector2d &pos, float opacity = 1.0) override;

   virtual bool handleKeyboard(KeyEvent &keyEvent);
   virtual void handleSystemQuitEvent();

   virtual void handleQuitEvent();

   virtual bool handleUserEvent(UserEvent &inUserEvent) override;

   virtual bool onRightMouseButtonPressed(const Vector2d &pos) override;

protected:
   
   // std::shared_ptr<TextButton> m_ExampleButton;
   // std::shared_ptr<TextButton> m_QuitButton;

   // std::shared_ptr<UserEvent> userEvent;
   //std::shared_ptr<UserEvent> leaveGameEvent;
   std::shared_ptr<UserEvent> switchToInventoryEvent;

};

#endif /*__HEADER_EXPLORE_PANEL_*/
