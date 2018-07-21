TARGET = client
OBJ = client.o

CC = gcc
CFLAGS = -g -w
INC = 
LIB = -lrt -lmenu -lncurses

all: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIB) $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(INC) $(CFLAGS)

clean:
	rm -fv *.o $(TARGET)


