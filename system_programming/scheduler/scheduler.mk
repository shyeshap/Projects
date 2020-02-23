#make file - sortedlist

CFLAGS=-ansi -pedantic-errors -Wall -Wextra
DEBUG=	-g
RELEASE= -DNDBUG -03
CC=gcc
TARGET=scheduler
PRIORITYQ=priorityq
UID=uid
DS_INCLUDE_DIR = /home/codezila/git/ds/include/
SP_INCLUDE_DIR = /home/codezila/git/system_programming/include/
SP_LIB_DIR = /home/codezila/git/system_programming/lib/
DS_LIB_DIR = /home/codezila/git/ds/lib/
TASK=task
NOPIE= '-ansi -pedantic-errors -Wall -Wextra -no-pie'

$(TARGET).out: $(SP_LIB_DIR)lib$(TARGET).so $(TARGET)_test.o $(DS_LIB_DIR)lib$(PRIORITYQ).so $(SP_LIB_DIR)lib$(TASK).so $(SP_LIB_DIR)lib$(UID).so 
	$(CC) $(CFLAGS) -o $@ $(TARGET)_test.o -L$(SP_LIB_DIR) -l$(TARGET) -l$(TASK) -l$(UID) -L$(DS_LIB_DIR) -l$(PRIORITYQ) -Wl,-rpath=$(SP_LIB_DIR) -Wl,-rpath=$(DS_LIB_DIR)

$(SP_LIB_DIR)lib$(TARGET).so: $(TARGET).o 
	$(CC) $(CFLAGS) -shared $< -o $@

$(TARGET).o: $(SP_INCLUDE_DIR)$(TARGET).h $(TARGET).c
	$(CC) -c $(CFLAGS) -fPIC $(TARGET).c -I$(SP_INCLUDE_DIR) -I$(DS_INCLUDE_DIR) -o $@

$(TARGET)_test.o: $(SP_INCLUDE_DIR)$(TARGET).h $(TARGET)_test.c
	$(CC) -c $(CFLAGS) $(TARGET)_test.c -I$(SP_INCLUDE_DIR) -o $@

.PHONY: clean
clean:
	rm	*.o $(TARGET).out $(SP_LIB_DIR)lib$(TARGET).so

.PHONY: memmap
memmap:
	make -f scheduler.mk CFLAGS=$(NOPIE)