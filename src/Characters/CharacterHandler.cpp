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

#include "CharacterHandler.h"


CharacterHandler &CharacterHandler::instance()
{
   static CharacterHandler instance;
   return instance;
}


/**
 *
 */
CharacterHandler::CharacterHandler() : m_PartyLeader(0)
{
}


/**
 *
 */
CharacterHandler::~CharacterHandler()
{
}


   
/**
 *
 */
void CharacterHandler::initCharacterHandler()
{
   LOG("CharacterHandler::initCharacterHandler()");
   
   m_Player[0] = std::make_shared<Player>();
   m_Player[0]->setName("Wuuf");
   m_Player[0]->setSurname("The Bika");
   m_Player[0]->setPortrait(22);
   
   m_Player[1] = std::make_shared<Player>();
   m_Player[1]->setName("Chani");
   m_Player[1]->setSurname("Sayyadina Sihaya");
   m_Player[1]->setPortrait(5);
   
   m_Player[2] = std::make_shared<Player>();
   m_Player[2]->setName("Alex");
   m_Player[2]->setSurname("Ander");
   m_Player[2]->setPortrait(11);
   
   m_Player[3] = std::make_shared<Player>();
   m_Player[3]->setName("Daroou");
   m_Player[3]->setSurname("XYZ Ampar");
   m_Player[3]->setPortrait(23);
}


/**
 *
 */
void CharacterHandler::doneCharacterHandler()
{
   LOG("CharacterHandler::doneCharacterHandler()");
   
   m_Player[0].reset();
   m_Player[1].reset();
   m_Player[2].reset();
   m_Player[3].reset();
}


/**
 *
 */
int CharacterHandler::getPartyLeader()
{
   return m_PartyLeader;
}


/**
 *
 */
void CharacterHandler::setPartyLeader(int inPartyLeader)
{
   m_PartyLeader = inPartyLeader;
}


/**
 *
 */
std::shared_ptr<Player> CharacterHandler::getPlayer(int nr)
{
   return m_Player[nr];
}
