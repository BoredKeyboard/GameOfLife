Compile using -D to set the width and height of the sandbox:\n
	gcc -Wall -Wextra -D HEIGHT=80 -D WIDTH=155 GoL.c -o main -fsanitize=address -g

Execute the program with a seed:\n
	./main 234523
