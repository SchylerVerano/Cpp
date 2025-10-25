all: ppm_to_jpeg

JPEGfunctions.o: JPEGfunctions.cpp JPEGfunctions.H
	g++ -c -Wall -Werror -std=c++17 JPEGfunctions.cpp

main.o: main.cpp JPEGfunctions.H
	g++ -c -Wall -Werror -std=c++17 main.cpp

ppm_to_jpeg: main.o JPEGfunctions.o
	g++ -o ppm_to_jpeg main.o JPEGfunctions.o -ljpeg

clean:
	rm -f *.o ppm_to_jpeg output.jpg
