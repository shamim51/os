#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int n = 3;
	int fd[2 * n];
	char write_msg[n][100];
	char read_msg[100];
	int pid;
	for (int i = 0; i < n; i++) {
		if (pipe(&fd[2 * i]) == -1) {
			printf("Error creating pipe\n");
			return -1;
		}
	}

	for (int i = 0; i < n; i++) {
		if (pid = fork() == 0) {
			printf("writing to %d child %d of parent %d\n", i, getpid(), getppid());
			close(fd[2 * i]);
			int j = 0;
			int counter = 0;
			while (1) {
				char in;
				scanf("%c", &in);
				if (in == '\n') {
					counter++;
					if (counter == 2) {
						break;
					}
				} else {
					write_msg[i][j] = in;
					j++;
				}
			}
			write_msg[i][j] = '\0';
			write(fd[2 * i + 1], &write_msg[i], sizeof(write_msg[i]));
			close(fd[2 * i + 1]);
			exit(0);
		}
		else {
			wait(&pid);
		}

	}
	for (int i = 0; i < n; i++) {
		read(fd[2 * i], read_msg, sizeof(read_msg));
		close(fd[2 * i]);
		printf("\nreading from child process %d of parent %d: %s", i, getpid(), read_msg);
	}
	printf("\n");
}
/*
gcc -o B B.c
./B
a b c

d e f

g h i
*/

