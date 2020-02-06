#make file - sortedlist

CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= -DNDBUG -03
CC=gcc
TARGET=scheduler
PQ=priorityq
UID=uid
VECTOR=vector
TASK=task
INCLUDE_DIR = ../include/
RELEASE_OBJ_DIR = ../lib_release/
SHARED_OBJ_DIR = ../lib/
INNER_OBJ_DIR = ./obj/

$(TARGET).out: $(SHARED_OBJ_DIR)lib$(TARGET).so $(INNER_OBJ_DIR)$(TARGET)_test.o 
	$(CC) $(CFLAGS) -o $@ $(INNER_OBJ_DIR)$(TARGET)_test.o -L$(SHARED_OBJ_DIR) -l$(TARGET) -l$(PQ) -ltask -Wl,-rpath,'$$ORIGIN/../lib'

$(TARGET)_mapping:$(SHARED_OBJ_DIR)lib$(TARGET).so $(INNER_OBJ_DIR)$(TARGET)_test.o 
	$(CC) $(CFLAGS) $(MAPPING) -o $@ $(INNER_OBJ_DIR)$(TARGET)_test.o -L$(SHARED_OBJ_DIR) -l$(TARGET) -Wl,-rpath,'$$ORIGIN/../lib'
	
$(SHARED_OBJ_DIR)lib$(TARGET).so: $(INNER_OBJ_DIR)$(TARGET).o
	$(CC) $(CFLAGS) -L$(SHARED_OBJ_DIR) -shared $< -l$(PQ) -l$(UID) -l$(TASK) -l$(VECTOR) -Wl,-rpath=$(SHARED_OBJ_DIR) -o $@

$(INNER_OBJ_DIR)$(TARGET).o: $(INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) $(DEBUG) -fPIC $(TARGET).c -I$(INCLUDE_DIR) -o $@

$(INNER_OBJ_DIR)$(TARGET)_test.o: $(INCLUDE_DIR)$(TARGET).h $(TARGET)_test.c
	$(CC) -c $(CFLAGS) $(DEBUG) $(TARGET)_test.c -I$(INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	$(INNER_OBJ_DIR)$(TARGET).o $(TARGET).out $(INNER_OBJ_DIR)$(TARGET)_test.o $(SHARED_OBJ_DIR)lib$(TARGET).so
	
release:
	make -f $(TARGET).mk DEBUG=$(RELEASE) SHARED_OBJ_DIR=$(RELEASE_OBJ_DIR)


