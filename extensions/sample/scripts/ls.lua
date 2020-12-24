local args = ...

local childrenTable = getcwd():getChildren()
local ans = ''

for key, value in pairs(childrenTable) do
    ans = ans .. value:getName() .. ' '
end

print(ans)