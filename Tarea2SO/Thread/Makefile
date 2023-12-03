CC = g++
CFLAGS = -std=c++11
LIBS = `pkg-config --cflags --libs opencv4`
TARGET = programa

all: $(TARGET)

$(TARGET): codigo.cpp
	$(CC) $(CFLAGS) -o $(TARGET) codigo.cpp $(LIBS)

clean:
	rm -f $(TARGET)
