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


int main() {



	printf("Entering the loop\n");
	while(1) {};

}