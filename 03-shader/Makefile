
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

4:
	c++ -I../lib shader4.cpp -o shader4.out  -L ../lib -lglprak -lglfw
	sudo ./shader4.out

5:
	c++ -I../lib shader5.cpp -o shader5.out  -L ../lib -lglprak -lglfw
	sudo ./shader5.out

6:
	c++ -I../lib shader6.cpp -o shader6.out  -L ../lib -lglprak -lglfw
	sudo ./shader6.out

buildlib:
	make -C ../lib

clean:
	rm -f *.out