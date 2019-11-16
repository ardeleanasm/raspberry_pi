CC = gcc
FLAGS = -Wall -c

OUT = obj

OBJ = cooling



SRC_FILES += main.c

all:create_dirs compile link

create_dirs:
	mkdir -p $(OUT)

compile:
	$(CC) $(FLAGS) $(SRC_FILES) -o $(OUT)/$(OBJ).o

link:
	$(CC) $(FLGAGS) $(LINK) $(OUT)/$(OBJ).o -o $(OUT)/$(OBJ)

clean:
	rm -rf obj/
