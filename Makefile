%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

CC = gcc
PROG = cs392_shell

$(PROG) : cs392_shell.o cs392_exec.o cs392_log.o
	$(CC) -o cs392_shell cs392_shell.o cs392_exec.o cs392_log.o

clean:
	rm -rf *.o cs392_shell 