all: mandelbrot

mandelbrotFunction.o: mandelbrotFunction.cpp mandelbrot.h
	g++ -c -Wall -Werror mandelbrotFunction.cpp

main.o: main.cpp mandelbrot.h
	g++ -c -Wall -Werror main.cpp

mandelbrot: main.o mandelbrotFunction.o
	g++ -o mandelbrot main.o mandelbrotFunction.o
clean:
	rm -f *.o mandelbrot
