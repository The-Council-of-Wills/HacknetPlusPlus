local args = ...

if args[2] then
    getcwd():getElement(args[2]):delete()
end