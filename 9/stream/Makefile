 # Compiler
CC = icc

# Compiler flags
CFLAGS = -O3 -qopt-streaming-stores always

# Target executable
TARGET = stream

# Source file
SRC = stream.c

# Build target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean target
clean:
	rm -f $(TARGET)
