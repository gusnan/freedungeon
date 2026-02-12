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
#ifndef __HEADER_GAME_PANEL_
#define __HEADER_GAME_PANEL_


#include "PlayerPanel.h"


const int GAME_MODE_DUNGEON =    0;
const int GAME_MODE_INVENTORY =  1;
const int GAME_MODE_SLEEP =      2;
const int GAME_MODE_PAUSE =      3;


class GamePanel : public Panel
{
public:
   GamePanel();
   virtual ~GamePanel();

   GamePanel &operator=(const GamePanel &);
   
   void draw(const Vector2d &pos, float opacity = 1.0) override;

   virtual bool handleKeyboard(KeyEvent &keyEvent);
   virtual void handleSystemQuitEvent();

   virtual void handleQuitEvent();

   virtual bool handleUserEvent(UserEvent &inUserEvent) override;

   virtual bool onRightMouseButtonPressed(const Vector2d &pos) override;
   virtual bool onLeftMouseButtonPressed(const Vector2d &pos) override;

   void switchGameMode(int inGameMode);

   void setPlayerShowPortrait(int inNumber);


protected:
   
   std::shared_ptr<ExplorePanel> m_ExplorePanel;
   std::shared_ptr<InventoryPanel> m_InventoryPanel;
   std::shared_ptr<PausePanel> m_PausePanel;
   std::shared_ptr<SleepPanel> m_SleepPanel;

   std::shared_ptr<InfoPanel> m_InfoPanel;

   std::shared_ptr<UserEvent> m_SwitchToInventoryEvent;
   std::shared_ptr<UserEvent> m_SwitchToExploreEvent;

   std::shared_ptr<ItemTextPanel> m_ItemTextPanel;

   std::shared_ptr<PlayerPanel> m_PlayerPanel[4];

   std::shared_ptr<MiniMap> m_MiniMap;

   void setPlayerPanelsActive(bool inActive = true);

   // int getGameModeInteger();

};

#endif /*__HEADER_GAME_PANEL_*/
