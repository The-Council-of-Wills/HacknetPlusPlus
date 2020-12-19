local args = ...

local notes = getFileSystem():openFile('/home/notes/notes.txt')

if args[2] then
	notes:append(table.concat({table.unpack(args, 2)}, ' ') .. '\n')
end

print(notes:getContent())