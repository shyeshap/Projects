#make file - dll-producer-consumer

CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= '-DNDBUG -O3'
THREADS= -pthread
TARGET=dll_prod_cons_sem
DEP= dll
DEP_PATH= ./../../ds/dll/

$(TARGET).out: $(TARGET).c $(DEP_PATH)$(DEP).c
	$(CC) $(CFLAGS) $(RELEASE) $(THREADS) $(DEP_PATH)$(DEP).c $(TARGET).c -o $(TARGET).out

.PHONY: clean
clean:
	rm	$(INNER_OBJ_DIR)$(TARGET).o $(TARGET).out
