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
#ifndef __HEADER_ITEM_BASE_
#define __HEADER_ITEM_BASE_


/**
 *
 */
class Item
{
public:
   Item();
   virtual ~Item();

   Item(const Item &item);

   std::shared_ptr<Item> makeCopy() const;

   void setName(const std::string &inName);
   const std::string &getName();

   void draw(const Vector2d &pos);

   void setSmallImage(int inSmallimage);
   int getSmallImage();

protected:
   
   std::string m_Name;

   int m_SmallImage;

private:

   // https://stackoverflow.com/questions/43586090/clone-pattern-for-stdshared-ptr-in-c
   virtual Item* cloneImplementation() const {
      return new Item(*this);
   }
};


#endif /*__HEADER_ITEM_BASE_*/
