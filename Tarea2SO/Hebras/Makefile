CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -O3
LIBS = `pkg-config --cflags --libs opencv4`
TARGET = programa

all: $(TARGET)

$(TARGET): codigo.cpp
	$(CC) $(CFLAGS) codigo.cpp -o $(TARGET) $(LIBS)

.PHONY: clean

clean:
	rm -f $(TARGET)
