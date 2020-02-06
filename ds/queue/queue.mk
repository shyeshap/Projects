#make file - priority queue

CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= '-DNDBUG -O3'
CC=gcc
TARGET=queue
SINGLY_LL=linked_list
DLL= dll
INCLUDE_DIR = ../include/
RELEASE_OBJ_DIR = ../lib_release/
SHARED_OBJ_DIR = ../lib/
INNER_OBJ_DIR = ./obj/

$(TARGET).out: $(SHARED_OBJ_DIR)lib$(TARGET).so $(INNER_OBJ_DIR)$(TARGET)_test.o $(SHARED_OBJ_DIR)lib$(DLL).so
	$(CC) $(CFLAGS) $(INNER_OBJ_DIR)$(TARGET)_test.o -L$(SHARED_OBJ_DIR) -l$(TARGET) -Wl,-rpath,'$$ORIGIN/../lib' -o $@

$(SHARED_OBJ_DIR)lib$(TARGET).so: $(INNER_OBJ_DIR)$(TARGET).o
	$(CC) $(CFLAGS) -L$(SHARED_OBJ_DIR) -shared $<  -l$(SINGLY_LL) -Wl,-rpath=$(SHARED_OBJ_DIR) -o $@

$(INNER_OBJ_DIR)$(TARGET).o: $(INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) $(DEBUG) -fPIC $(TARGET).c -I$(INCLUDE_DIR) -o $@

$(INNER_OBJ_DIR)$(TARGET)_test.o: $(INCLUDE_DIR)$(TARGET).h $(TARGET)_test.c
	$(CC) -c $(CFLAGS) $(DEBUG) $(TARGET)_test.c -I$(INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	$(INNER_OBJ_DIR)$(TARGET).o $(TARGET).out $(INNER_OBJ_DIR)$(TARGET)_test.o $(SHARED_OBJ_DIR)lib$(TARGET).so

release:
	make -f $(TARGET).mk DEBUG=$(RELEASE) SHARED_OBJ_DIR=$(RELEASE_OBJ_DIR) 
