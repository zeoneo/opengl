.SILENT:
all: clean buildlib
	c++ -I../lib triangle.cpp -L ../lib -lglprak -lglfw
	sudo ./a.out

buildlib:
	make -C ../lib

clean:
	rm -f *.out