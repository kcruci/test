all: aluacall aluafun

aluacall: lua_call.cpp;
	g++ -o $@ $< -llua -ldl

aluafun: lua_fun.cpp;
	g++ -o $@  $< -llua -ldl
.PHONY:clean
clean:
	rm alua*



