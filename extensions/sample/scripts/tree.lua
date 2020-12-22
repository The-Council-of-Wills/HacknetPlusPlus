local args = ...

function getSelectedTree()
	if args[2] then
		local dir = getcwd():getElement(args[2])
		
		if dir and dir:getTree() then
			return dir:getTree()
		end
	end
	
	return getFileSystem():getTree()
end

print(getSelectedTree())