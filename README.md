# Compile using -D to set width and heightx:

gcc -Wall -Wextra -D HEIGHT=80 -D WIDTH=155 GoL.c -o main -fsanitize=address -g

# Execute the program with a seed:

./main 234523
