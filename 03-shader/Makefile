
all: clean buildlib

1:
	c++ -I../lib shader1.cpp -o shader1.out  -L ../lib -lglprak -lglfw
	sudo ./shader1.out

2:
	c++ -I../lib shader2.cpp -o shader2.out  -L ../lib -lglprak -lglfw
	sudo ./shader2.out

3:
	c++ -I../lib shader3.cpp -o shader3.out  -L ../lib -lglprak -lglfw
	sudo ./shader3.out

buildlib:
	make -C ../lib

clean:
	rm -f *.out