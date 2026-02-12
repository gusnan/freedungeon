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

#ifndef __HEADER_MOUSE_POIINTER_
#define __HEADER_MOUSE_POIINTER_


/**
 *
 */
class MousePointer
{
public:

   static MousePointer &instance();

   void initMouse();
   void doneMouse();

   void setItem(std::shared_ptr<Item> inItem);
   std::shared_ptr<Item> getItem();

   void draw();

   void show();
   void hide();

   void setShowItem(bool inShowItem);

protected:
   
   MousePointer();
   virtual ~MousePointer();

private:

   std::shared_ptr<Bitmap> m_MouseBitmap;
   std::shared_ptr<Bitmap> m_CurrentMouseBitmap;

   std::shared_ptr<Item> m_Item;

   bool m_UseHardwareMouse;

   bool m_Visible;

   bool m_ShowItem;
};

#endif /*__HEADER_MOUSE_POIINTER_*/
