filename = "test_io.data"

io.input("test_io.data")

for count = 1,math.huge do
    local line = io.read("*line")
    if line == "" then
        break
    end
    io.write(string.format("%6d  ",count),line,"\n")
end
--[[
    6.0  -3.23   1000
    ... ...
    下面的代码读取注释中的数字
--]]
-- seek the beginner
io.input("test_io.data")
while true do
    local n1,n2,n3 = io.read("*number","*number","*number")
    if not n1 then
        break
    end
    print(math.max(n1,n2,n3))
end

--io.input("test_io.data")
print("#### read all ####")
local all= io.read("*all")
io.write(all)

foo = function (x) return 2*x end
print(foo(22))

--for name in pairs(_G) do print(_G) end
