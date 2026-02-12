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

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <memory>

#include "GusGame/GusGame.h"

#include "GusGame/EventLib.h"
#include "GusGame/EventSystem.h"

using namespace Gus;

using namespace Gus::GraphicsLib;

using namespace LogLib;

#include "../Items/Item.h"
#include "../Items/ItemHolder.h"


#include "Player.h"

/**
 *
 */
Player::Player() : m_Portrait(0), 
                   m_Name(""),
                   m_Surname(""),
                   m_CarriedWeight(0.0f)
{
   for (int co = 0; co < 30; co++) {
      // m_ItemHolder[co] = std::make_shared<ItemHolder>();
      m_ItemHolder[co] = std::make_shared<ItemHolder>();
   }
}


/**
 *
 */
Player::~Player()
{
      for (int co = 0; co < 30; co++) {
      // m_ItemHolder[co] = std::make_shared<ItemHolder>();
      // m_ItemHolder[co] = new ItemHolder(); // std::make_shared<ItemHolder>();
         // delete m_ItemHolder[co];
         m_ItemHolder[co].reset();
   }
}


/**
 *
 */
Player::Player(Player &inPlayer) : m_Portrait(inPlayer.m_Portrait),
                                         m_Name(inPlayer.m_Name),
                                         m_Surname(inPlayer.m_Surname),
                                         m_CarriedWeight(inPlayer.m_CarriedWeight)
{
   for (int co = 0; co < 30; co++) {
      this->m_ItemHolder[co] = inPlayer.getItemHolder(co);
   }
}


/**
 *
 */
Player& Player::operator=(const Player &inPlayer)
{
   if (this == &inPlayer)
      return *this;

   m_Portrait = inPlayer.m_Portrait;   
   m_Name = inPlayer.m_Name;
   m_Surname = inPlayer.m_Surname;
   m_CarriedWeight = inPlayer.m_CarriedWeight;
   
   for (int co = 0; co < 30; co++) {
      m_ItemHolder[co] = inPlayer.m_ItemHolder[co];
   }   
   return *this;
}

/**
 *
 */
void Player::setPortrait(int inPortrait)
{
   m_Portrait = inPortrait;
}


/**
 *
 */
int Player::getPortrait()
{
   return m_Portrait;
}


/**
 *
 */
void Player::setName(const std::string &inName)
{
   m_Name = inName;
}


/**
 *
 */
const std::string &Player::getName()
{
   return m_Name;
}


/**
 *
 */
void Player::setSurname(const std::string &inSurname)
{
   m_Surname = inSurname;
}


/**
 *
 */
const std::string &Player::getSurname()
{
   return m_Surname;
}


/**
 *
 */
std::shared_ptr<ItemHolder> Player::getItemHolder(int inNumber)
{
   return m_ItemHolder[inNumber];
}


/**
 *
 */
