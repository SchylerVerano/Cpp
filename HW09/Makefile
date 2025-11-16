CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
OBJ = main.o FileStreamBuf.o
TARGET = FileStreamBuf.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp FileStreamBuf.h
	$(CXX) $(CXXFLAGS) -c main.cpp

FileStreamBuf.o: FileStreamBuf.cpp FileStreamBuf.h
	$(CXX) $(CXXFLAGS) -c FileStreamBuf.cpp

clean:
	rm -f $(OBJ) $(TARGET) fsb_output.txt
