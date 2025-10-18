CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0` -lm
TARGET = travel_planner_gui
SOURCES = main.c graph.c algorithms.c gui.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

install-deps:
	sudo apt-get update
	sudo apt-get install libgtk-3-dev pkg-config

.PHONY: clean run install-deps