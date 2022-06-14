//
// Created by Abdoul Kader on 14/6/2022.
//

#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct termios saved;

void restore(void) {
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}


int main(int ac, char **av, char **env) {

	int i = fork();

	int j = 0;
	while (env[j])
	{
		printf("%s\n", env[j]);
		j++;
	}
	return 0;
	if (i == 0){
		printf("child\n");
		execve(av[1], av, env);
		exit(0);
	}
	wait(NULL);
	printf("parent");
}