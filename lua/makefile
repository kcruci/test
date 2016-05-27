all: atest afunc

atest: average_main.cpp;
	g++ -o atest  average_main.cpp -llua -ldl

afunc: test_luafun.cpp;
	g++ -o $@  $< -llua -ldl
.PHONY:clean
clean:
	rm atest


