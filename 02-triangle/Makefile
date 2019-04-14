.SILENT:

all: clean buildlib

1:
	c++ -I../lib triangle.cpp -o triangle.out  -L ../lib -lglprak -lglfw
	sudo ./triangle.out

2:
	c++ -I../lib triangle2.cpp -o triangle2.out -L ../lib -lglprak -lglfw
	sudo ./triangle2.out

buildlib:
	make -C ../lib

clean:
	rm -f *.out