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
#ifndef __HEADER_DUNGEON_GLOBAL_EVENT_HANDLER_
#define __HEADER_DUNGEON_GLOBAL_EVENT_HANDLER_


class GameEventHandler : public GusGui::GuiEventHandler
{
public:
   // These should be protected if in singleton
   GameEventHandler();

   GameEventHandler(const GameEventHandler &source);

   GameEventHandler &operator=(const GameEventHandler &);

   virtual ~GameEventHandler();

   // singleton specific
   // static std::shared_ptr<GlobalEventHandler> instance();

   // void destroy();

   const Vector2d getMousePosition();

   virtual bool handleKeyboard(KeyEvent &keyEvent);
   virtual void handleSystemQuitEvent();

   virtual void handleQuitEvent();

   virtual bool handleUserEvent(UserEvent &inUserEvent) override;

   virtual void handleMouseMotion(MouseMotionEvent &event) override;
   virtual void handleActiveEvent(ActiveEvent &activeEvent) override;

protected:
   /*
   GlobalEventHandler();

   GlobalEventHandler(const GlobalEventHandler &source);

   GlobalEventHandler &operator=(const GlobalEventHandler &);
*/


private:
   
   // singleton specific
   // static std::shared_ptr<GlobalEventHandler> pinstance;
   std::shared_ptr<UserEvent> globalQuitEvent;

   Vector2d m_GlobalMousePosition;
};


#endif /*__HEADER_DUNGEON_GLOBAL_EVENT_HANDLER_*/
