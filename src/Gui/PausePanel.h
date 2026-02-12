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
#ifndef __HEADER_PAUSE_PANEL_
#define __HEADER_PAUSE_PANEL_

class PausePanel : public Panel
{
public:
   PausePanel();
   virtual ~PausePanel();
   
   void draw(const Vector2d &pos, float opacity = 1.0f);

   void setPause(bool inPause = true);

   void setSavedGameMode(int inSavedGameMode);
   int getSavedGameMode();

protected:

   bool m_Paused;
   int m_SavedGameMode;
};

#endif /*__HEADER_PAUSE_PANEL_*/
