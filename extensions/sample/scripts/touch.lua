local args = ...

if args[2] then
	getcwd():openFile(args[2])
else print('Missing arguments.') end