local args = ...

local notes = getFileSystem():getElement('home'):getElement('notes'):getElement('notes.txt')

if not args[2] then
	print(notes:getContents())
else
	table.remove(args, 1)
	notes:append(table.concat(args, ' '))
end