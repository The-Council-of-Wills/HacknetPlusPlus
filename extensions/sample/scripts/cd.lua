local args = ...

if args[2] then
	local cwd = getcwd()
	local nextwd = cwd:getElement(args[2])
	
	if nextwd then setcwd(nextwd)
	else print(args[2] .. ' is not a folder.') end
else print('Missing arguments.') end