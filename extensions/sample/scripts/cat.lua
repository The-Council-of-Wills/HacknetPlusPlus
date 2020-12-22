local args = ...

if args[2] then
	local f = getcwd:getElement(args[2])
	
	if f then
		local content = f:getContent()
		if content then
			print(content)
		else print(args[2] .. ' isn\'t a valid file or it\'s empty.') end
	else print('File ' .. args[2] .. ' doesn\'t exist.')
else print('Missing arguments.') end