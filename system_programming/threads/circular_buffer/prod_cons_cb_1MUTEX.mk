#make file - dll-producer-consumer

CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=-g
INCLUDE= ./../../include
RELEASE= '-DNDBUG -O3'
THREADS= -pthread
TARGET= prod_cons_cb_1MUTEX
DEP= circular_buffer
DEP_PATH= ./../../ds/dll/

$(TARGET).out: $(TARGET).o 
	$(CC) $(CFLAGS) $(RELEASE) $(THREADS) $(TARGET).c $(DEP).c -I$(INCLUDE) -o $(TARGET).out

.PHONY: clean
clean:
	rm	$(INNER_OBJ_DIR)$(TARGET).o $(TARGET).out 
