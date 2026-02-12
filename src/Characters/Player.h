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
#ifndef __HEADER_PLAYER_
#define __HEADER_PLAYER_

/**
 *
 */
class Player
{
public:
   Player();
   virtual ~Player();

   Player(Player &player);

   Player &operator=(const Player &inPlayer);

   void setPortrait(int inPortrait);
   int getPortrait();

   void setName(const std::string &inName);
   const std::string &getName();

   void setSurname(const std::string &inSurName);
   const std::string &getSurname();

   std::shared_ptr<ItemHolder> getItemHolder(int inNumber);

protected:

   int m_Portrait;
   std::string m_Name, m_Surname;

   std::shared_ptr<ItemHolder> m_ItemHolder[30];

   float m_CarriedWeight;

};

#endif /*__HEADER_PLAYER_*/
