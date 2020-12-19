local args = ...

if args[2] and args[3] then
	local selected = getcwd():openFile(args[2])
	
	selected:append(table.concat({table.unpack(args, 3)}, ' ') .. '\n')
end