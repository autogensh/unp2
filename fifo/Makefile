TARGET = fifo
OBJ = fifo.o

CC = gcc
CFLAG = -w
INC = 
LIB =

all: clean $(TARGET)

$(TARGET): $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAG) $(INC)

clean:
	rm -fv *.o $(TARGET)


