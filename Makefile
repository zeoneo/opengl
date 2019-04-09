1:
	rm -f ./a.out
	c++ main.c glad.c -lglfw
	sudo ./a.out

2:
	rm -f ./a.out
	c++ color_window.c glad.c -lglfw
	sudo ./a.out

3:
	rm -f ./a.out
	c++ triangle.c glad.c -lglfw
	sudo ./a.out