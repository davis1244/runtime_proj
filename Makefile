CC=gcc
CFLAGs=-Wall -Wextra
TARGET=runtime

$(TARGET): runtime.c
	$(CC) $(CFLAGS) -o $(TARGET) runtime.c

clean:
	rm -f $(TARGET)


