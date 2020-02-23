
CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= -DNDBUG -03
CC=gcc
TARGET=task
SP_INCLUDE_DIR = ../include/
DS_INCLUDE_DIR = ../../ds/include/
SHARED_OBJ_DIR = ./../lib/
UID=uid

$(SHARED_OBJ_DIR)lib$(TARGET).so: $(TARGET).o $(SHARED_OBJ_DIR)lib$(UID).so
	$(CC) $(CFLAGS) -L$(SHARED_OBJ_DIR) -shared $< -l$(UID) -Wl,-rpath=$(SHARED_OBJ_DIR) -o $@

$(SHARED_OBJ_DIR)lib$(UID).so: ./../uid/obj/$(UID).o
	$(CC) $(CFLAGS) -shared $< -o $@

$(TARGET).o: $(SP_INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) -fPIC $(TARGET).c -I$(DS_INCLUDE_DIR) -I$(SP_INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	*.o $(SHARED_OBJ_DIR)lib$(TARGET).so
