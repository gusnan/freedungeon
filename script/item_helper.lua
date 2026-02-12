--[[----------------------------------------------------------------------------

  This file is part of freedungeon
  Copyright (C) 2017, 2026 Andreas Rönnquist

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


--[[

We don't do "error" here, it would make it appear as if the error is in this
file, while the actual error is where the tested item is created.

]]--


local item_helper = {}

--[[----------------------------------------------------------------------------
	test_name
------------------------------------------------------------------------------]]
function item_helper:test_name(item)

	-- print("Name: " .. name);

	if (item["name"] == nil) then return "Name is Nil!", false end

	-- local name = item["name"];

	if (type(item.name) ~= "string") then
		return "String required for name field", false
	end

	-- no message, return true as result
	return "", true
end


--[[----------------------------------------------------------------------------
	test_type
------------------------------------------------------------------------------]]
function item_helper:test_type(item)

	if (item.type == nil) then return "Type is Nil!", false end

	if (type(item.type) ~= "string") then return "Type string expected!", false end

	local typestr = string.upper(item.type);

	if (typestr == "CONSUMABLE") then
		allowed_type = true;
	elseif (typestr == "CONTAINER") then
		allowed_type = true;
	end

	if (allowed_type ~= true) then
		return "Type not recogninzed!", false
	end

	-- no message, return true as result
	return "", true
end


--[[----------------------------------------------------------------------------
	test_weight - test if the weight is correct of an item
------------------------------------------------------------------------------]]
function item_helper:test_weight(item)
	local weight = item.weight;

	if (weight == nil) then return "Weight is Nil!", false end;

	if (type(weight) ~= "number") then
		return "Weight of ".. item.name .. " isn't number!", false;
	end

	if (weight < 0) then
		return "Weight of ".. item.name .." is negative!", false;
	end

	-- no message, true as result
	return "", true;

end


--[[----------------------------------------------------------------------------
	test_item
------------------------------------------------------------------------------]]
function item_helper:test_item(item)

	local err, result;
	-- print("Name: " .. item.name)

	-- Check name
	err, result = item_helper:test_name(item);
	if (result ~= true) then return err, false; end

	-- Check type
	err, result = item_helper:test_type(item);
	if (result ~= true) then return err, false; end

	-- Check Weight
	err, result = item_helper:test_weight(item)
	if (result ~= true) then return err, false; end

	return "", true

	-- return "Faulty item table", false
end

return item_helper
