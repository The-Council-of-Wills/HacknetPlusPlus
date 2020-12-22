local args = ...

if args[2] then
	local file = getFileSystem():getElement('home'):openFile('junk-666.txt')
	for i=1, tonumber(args[2]) * 1024 do
		file:append('j666')
	end
end