TARGET = server
OBJ = server.o

CC = gcc
CFLAGS = -g -w
INC = 
LIB = -lrt

all: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIB) $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(INC) $(CFLAGS)

clean:
	rm -fv *.o $(TARGET)


