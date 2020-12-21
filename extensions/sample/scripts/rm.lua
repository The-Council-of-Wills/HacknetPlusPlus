local args = ...

if args[2] then
	local f = getcwd():getElement(args[2])
	
	if f then f:delete()
	else print('File' .. args[2] .. 'doesn\'t exist.') end
else print('Missing arguments.') end