
days = {"sunday", "monday", "tuesday", "wednesday","thursday", "friday", "saturday"}
for i ,v in ipairs (days)
    do print(v)
    end

    print("days ###########")
    print(days)

    print("exmple 2")
    mystable={}
    print("mytable type is  ", type(mytable))
    print("day type is  ", type(days))


    polyline = {color="blue", thickness=2, npoints=4,
    {x=1,   y=0},
    {x=-10, y=0},
    {x=-10, y=1},
    {x=4,   y=1}}

    print("dd" , polyline[1].x);
    print("ipairs  ###########")
    for i,v in ipairs(polyline)do
        print(i,v)
    end
    print("pairs  ###########")
    for i,v in pairs(polyline)do
        print(i,v)
    end


    list = nil
    for i = 1, 10 do
        list = { next = list, value = i}
    end
    print("list ###########")
    print(list)


    local l = list
    while l do
        print(l.value)
        l = l.next
    end
    squares = {1, 4, 9, 16, 25}
    print(type(squares))

    local s = table.concat(squares, "xxx \t")
    print(s)

    local t={}
    for line in io.lines() do
        if line == "" then
            break
        end

        t[#t +1] = line
    end
    print(#t)
    local s = table.concat(t, "\t**")
    print(s)
