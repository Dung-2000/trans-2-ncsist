CC=gcc
LIBS= -lssl -lcrypto

SRC = src/$(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)
