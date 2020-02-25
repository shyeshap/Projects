CC = gcc -ansi -pedantic-errors -Wall -Wextra -g
TIME = 60

all: app.out wd.out
.PHONY: clean

app.out: wd.out wd.c wd_imp.c app_wd_test.c
	$(CC) wd.c wd_imp.c app_wd_test.c /home/codezila/git/system_programming/scheduler/scheduler.c /home/codezila/git/ds/dll/dll.c /home/codezila/git/ds/priorityq/priorityq.c /home/codezila/git/ds/sortedlist/sortedlist.c /home/codezila/git/system_programming/scheduler/task.c /home/codezila/git/system_programming/uid/uid.c -I/home/codezila/git/ds/include -I/home/codezila/git/system_programming/include/ -D_POSIX_C_SOURCE -pthread -o app.out

wd.out: wd.c wd_imp.c wd_main_process.c
	$(CC) wd.c wd_imp.c wd_main_process.c /home/codezila/git/system_programming/scheduler/scheduler.c /home/codezila/git/ds/dll/dll.c /home/codezila/git/ds/priorityq/priorityq.c /home/codezila/git/ds/sortedlist/sortedlist.c /home/codezila/git/system_programming/scheduler/task.c /home/codezila/git/system_programming/uid/uid.c -I/home/codezila/git/ds/include -I/home/codezila/git/system_programming/include/ -D_POSIX_C_SOURCE -pthread -o wd.out

clean:
	rm app.out wd.out

#./app.out wd.out 60
