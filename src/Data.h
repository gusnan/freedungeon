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
#ifndef __HEADER_DATA_
#define __HEADER_DATA_


const int EVENT_RIGHT_CLICK_PLAYER_0 =    1000;
const int EVENT_RIGHT_CLICK_PLAYER_1 =    1001;
const int EVENT_RIGHT_CLICK_PLAYER_2 =    1002;
const int EVENT_RIGHT_CLICK_PLAYER_3 =    1003;

const int EVENT_PRESS_LEADER_SELECT =     1004;

const int EVENT_SWITCH_TO_EXPLORE_MODE =  1005;
const int EVENT_SET_ITEM_TEXT =           1006;

/**
 *
 */
class Data
{
public:
   
   static Data &instance();

   std::shared_ptr<Bitmap> characterSheet;
   std::shared_ptr<Bitmap> championPortraits;
   std::shared_ptr<Bitmap> mainMenuScreen;

   std::shared_ptr<Bitmap> mainMenuRightDoor;
   std::shared_ptr<Bitmap> mainMenuLeftDoor;

   std::shared_ptr<Bitmap> championInformation;

   std::shared_ptr<BitmapFont> font;

   std::shared_ptr<Bitmap> itemsBitmap[7];

   std::shared_ptr<Bitmap> greyBorderItemSlot;

   std::shared_ptr<Bitmap> smallMapBitmap;

   void doneDataHandler();
   
   std::string getDataFolder(const std::string &inString);
   
   EventLib::UserEvent setItemTextEvent;
   
   std::shared_ptr<Bitmap> makeDouble(std::string filename);
   
protected:
   
   Data();
   virtual ~Data();

private:

};

#endif /*__HEADER_DATA_*/

