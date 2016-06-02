filename = "test_io.data"


print("\n#### buffer read open read all ####")
f = io.open(filenam)
BUFFSIZE =5
local cc, lc, wc = 0, 0, 0  --分别计数字符、行和单词
while true do
    local lines,rest = f:read(BUFFSIZE,"*line")
    if not lines then
        break
    end

    if rest then
        lines = lines .. rest .. "\n"
    end
end
--[[

print("\n#### ####")
local str = "\n\n\ndddddf 123 fff f\nd"
print(str, #str)
print("\n#### ####")
--]]

print("\n#### ####")
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
print("\n#### read number ####")
io.input("test_io.data")
while true do
    local n1,n2,n3 = io.read("*number","*number","*number")
    if not n1 then
        break
    end
    print(math.max(n1,n2,n3))
end

io.input("test_io.data")

print("\n#### read all ####")
local all= io.read("*all")
io.write(all)

print("\n#### function ####")
foo = function (x) return 2*x end
print(foo(22))

--for name in pairs(_G) do print(_G) end

print("\n#### file open read all ####")
local f = io.open(filename, "r")
t = f:read("*all")
print(t)



