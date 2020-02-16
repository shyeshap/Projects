#make file - dll-producer-consumer

CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= '-DNDBUG -O3'
CC=gcc
TARGET=dll_prod_cons
DLL= dll
DS_INCLUDE_DIR = ./../../ds/include/
SHARED_OBJ_DIR = ../lib/
RELEASE_OBJ_DIR = ../lib_release/
INNER_OBJ_DIR= ./obj/
DLL_MAKE_PATH= ../dll/makefile

$(TARGET).out: $(SHARED_OBJ_DIR)lib$(TARGET).so $(INNER_OBJ_DIR)$(TARGET)_test.o
	$(CC) $(CFLAGS) $(INNER_OBJ_DIR)$(TARGET)_test.o -L$(SHARED_OBJ_DIR) -l$(TARGET) -Wl,-rpath=$(SHARED_OBJ_DIR) -o $@

$(SHARED_OBJ_DIR)lib$(TARGET).so: $(INNER_OBJ_DIR)$(TARGET).o
	$(CC) $(CFLAGS) -L$(SHARED_OBJ_DIR) -shared $< -l$(DLL) -Wl,-rpath=$(SHARED_OBJ_DIR) -o $@

$(INNER_OBJ_DIR)$(TARGET).o: $(INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) $(DEBUG) -fPIC $(TARGET).c -I$(DS_INCLUDE_DIR) -o $@

$(INNER_OBJ_DIR)$(TARGET)_test.o: $(INCLUDE_DIR)$(TARGET).h $(TARGET)_test.c
	$(CC) -c $(CFLAGS) $(DEBUG) $(TARGET)_test.c -I$(INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	$(INNER_OBJ_DIR)$(TARGET).o $(INNER_OBJ_DIR)$(TARGET)_test.o $(TARGET).out $(SHARED_OBJ_DIR)lib$(TARGET).so
		
release:
	make -f $(TARGET).mk DEBUG=$(RELEASE) SHARED_OBJ_DIR=$(RELEASE_OBJ_DIR) 
