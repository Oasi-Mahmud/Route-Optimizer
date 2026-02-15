CC = gcc
CFLAGS = -Wall -Wextra -O2 -lm

SOURCES = *.c
TARGET = main


all:
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS)
	@echo "Build complete!"

clean:
	rm -f $(TARGET) ../*.kml
	@echo "Clean complete"


run: all
	cd .. && ./main

test: all
	cd .. && ./main < test.txt