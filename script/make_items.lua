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
