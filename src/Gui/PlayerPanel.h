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
#ifndef __HEADER_PLAYER_PANEL_
#define __HEADER_PLAYER_PANEL_

/**
 *
 */
class PlayerPanel : public Panel
{
public:
   explicit PlayerPanel(const Vector2d &pos, const std::string &name, int inPlayerNumber);
   virtual ~PlayerPanel();

   PlayerPanel(const PlayerPanel &inPlayerPanel);

   void draw(const Vector2d &pos, float opacity = 1.0f);

   virtual bool onRightMouseButtonPressed(const Vector2d &pos) override;
   // virtual bool onLeftMouseButtonPressed(const Vector2d &pos) override;
   
   virtual bool handleUserEvent(UserEvent &inUserEvent) override;

   void setShowPortrait(bool inShowPortrait);

   void setActive(bool active);

protected:
   
   std::shared_ptr<UserEvent> m_RightClickEvent;
   std::shared_ptr<UserEvent> m_LeaderClickedEvent;

   int m_PlayerNumber;

   bool m_ShowPortrait;

   std::shared_ptr<Button> m_LeaderButton;

   std::shared_ptr<ItemSlot> m_RightHandSlot, m_LeftHandSlot;
};


#endif /*__HEADER_PLAYER_PANEL_*/
