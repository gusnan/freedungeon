--[[----------------------------------------------------------------------------

  This file is part of freedungeon
  Copyright (C) 2026 Andreas Rönnquist

  freedungeon is free software: you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published
  by the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  freedungeon is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with freedungeon.
  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------]]

ih = require("item_helper");


torch = {}

torch.name = "Torch"
torch.type = "consumable";
torch.weight = 3
torch.smallimage = 4 -- torch

mes, res = ih:test_item(torch)
if (not res) then error(mes) end

create_item(torch)

---


skeleton_key = {}

skeleton_key.name="Skeleton Key"
skeleton_key.type="Key"
skeleton_key.smallimage = 179
skeleton_key.weight = 0.5

mes, res = ih:test_item(skeleton_key)
if (not res) then error(mes) end

create_item(skeleton_key)
