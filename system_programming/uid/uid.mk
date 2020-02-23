#make file - uid

CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG =	-g
RELEASE = '-DNDBUG -O3'
CC=gcc
TARGET = uid
INCLUDE_DIR = ./../include/
SHARED_OBJ_DIR = ./../lib/
SHARED_RELEASE_OBJ_DIR = ./../lib_release/
INNER_OBJ_DIR = ./obj/

$(TARGET).out: $(INNER_OBJ_DIR)$(TARGET)_test.o $(SHARED_OBJ_DIR)lib$(TARGET).so
	$(CC) $(CFLAGS) -o $@ $< -L$(SHARED_OBJ_DIR) -l$(TARGET) -Wl,-rpath=$(SHARED_OBJ_DIR)

$(SHARED_OBJ_DIR)lib$(TARGET).so: $(INNER_OBJ_DIR)$(TARGET).o
	$(CC) $(CFLAGS) -shared $< -o $@

$(INNER_OBJ_DIR)$(TARGET).o: $(TARGET).c $(INCLUDE_DIR)$(TARGET).h
	$(CC) -c $(CFLAGS) $(DEBUG) -fPIC $< -I$(INCLUDE_DIR) -o $@

$(INNER_OBJ_DIR)$(TARGET)_test.o: $(TARGET)_test.c $(INCLUDE_DIR)$(TARGET).h
	$(CC) -c $(CFLAGS) $(DEBUG) $< -I$(INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	$(INNER_OBJ_DIR)$(TARGET).o $(INNER_OBJ_DIR)$(TARGET)_test.o $(TARGET).out $(SHARED_OBJ_DIR)lib$(TARGET).so

release:
	make -f $(TARGET).mk DEBUG=$(RELEASE) SHARED_OBJ_DIR=$(SHARED_RELEASE_OBJ_DIR)
