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
#ifndef __HEADER_TEXT_BUTTON_
#define __HEADER_TEXT_BUTTON_

/**
 *
 */
class TextButton : public Button
{
public:
   TextButton();

   explicit TextButton(const GraphicsLib::Rect &rect);

   virtual ~TextButton();

   virtual void draw(const Vector2d& pos, float alpha = 1.0) override;

protected:
};

#endif /*__HEADER_TEXT_BUTTON_*/
