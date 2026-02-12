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

using namespace LogLib;
using namespace ExceptionLib;
using namespace GraphicsLib;
using namespace EventLib;

#include "GusGui/GusGui.h"

using namespace GusGui;

#include "TextButton.h"

/**
 *
 */
TextButton::TextButton() : Button(Rect(), "ExampleButton", nullptr, true)
{
}


/**
 *
 */
TextButton::TextButton(const GraphicsLib::Rect &rect) : Button(rect, "ExampleButton", nullptr, true)
{
}


/**
 *
 */
TextButton::~TextButton()
{
}


/**
 *
 */
void TextButton::draw(const Vector2d& pos, float alpha)
{
   // Gray for standard button
   Primitives::rectFill(getRect() + pos, colorLightGray);
   if (getMouseOver()) {

      // red when hovered
      Primitives::rectFill(getRect() + pos, colorRed);
      if (getDown()) {
         // and white when pressed
         Primitives::rectFill(getRect() + pos, colorWhite);
      }
   }
}
