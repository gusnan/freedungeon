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
#ifndef __HEADER_MAIN_MENU_PANEL_
#define __HEADER_MAIN_MENU_PANEL_


class MainMenuPanel : public Panel
{
public:
   MainMenuPanel();
   virtual ~MainMenuPanel();
   
   MainMenuPanel(const MainMenuPanel &source);

   MainMenuPanel &operator=(const MainMenuPanel &);
    
   void draw(const Vector2d &pos, float opacity = 1.0) override;
   
   virtual bool handleKeyboard(KeyEvent &keyEvent);
   virtual void handleSystemQuitEvent();

   virtual void handleQuitEvent();

   virtual bool handleUserEvent(UserEvent &inUserEvent) override;

protected:
   
   std::shared_ptr<TextButton> m_ExampleButton;
   std::shared_ptr<TextButton> m_QuitButton;

   // std::shared_ptr<UserEvent> enterGameEvent;
   std::shared_ptr<UserEvent> enterGameEvent;

};

#endif /*__HEADER_MAIN_MENU_PANEL_*/
