#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#ifndef WIDTH
# define WIDTH 40
#endif

#ifndef HEIGHT
# define HEIGHT 40
#endif

void	down(int n)
{
	printf("\x1b[%dB", n);
}

void	pos(int	n, int m)
{
	printf("\x1b[%d;%dH", n, m);
}

void	update(int layout[HEIGHT][WIDTH])
{
	int	new_arr[HEIGHT][WIDTH];
	int	i = 0;
	int	j = 0;
	int	cells = 0;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			cells = 0;
			if (i > 0 && j > 0 && layout[i-1][j-1] == 1)
				cells++;
			if (i > 0 && layout[i-1][j] == 1)
				cells++;
			if (i > 0 && j < WIDTH - 1 && layout[i-1][j+1] == 1)
				cells++;
			if (j > 0 && layout[i][j-1] == 1)
				cells++;
			if (j < WIDTH - 1 && layout[i][j+1] == 1)
				cells++;
			if (i < HEIGHT - 1 && j > 0 && layout[i+1][j-1] == 1)
				cells++;
			if (i < HEIGHT - 1 && layout[i+1][j] == 1)
				cells++;
			if (i < HEIGHT - 1 && j < WIDTH - 1 && layout[i+1][j+1] == 1)
				cells++;

			if (layout[i][j] == 1 && (cells == 2 || cells == 3))
				new_arr[i][j] = 1;
			else if (cells == 3 && layout[i][j] == 0)
				new_arr[i][j] = 1;
			else
				new_arr[i][j] = 0;
			j++;
		}
		i++;
	}
	memcpy(layout, new_arr, sizeof(new_arr));
}

void randomise_layout(int layout[HEIGHT][WIDTH], int seed)
{
	int i;
	int j;

	srand(seed);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			layout[i][j] = rand() % 2;
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	layout[HEIGHT][WIDTH];
	int	i = 0;
	int	j = 0;
	int	k = 0;

	if (argc != 2)
	{
		printf("Enter a seed\n");
		return (1);
	}

	randomise_layout(layout, atoi(argv[1]));

	while (1)
	{
		pos(2, 1);
		i = 0;
		while (i < HEIGHT)
		{
			j = 0;
			while (j < WIDTH)
			{
				if (layout[i][j] == 1)
					printf("██");
				else
					printf("  ");
				j++;
			}
			printf("\r");
			down(1);
			i++;
		}
		fflush(NULL);
		pos(HEIGHT + 2, 1);
		usleep(50 * 1000);
		update(layout);
		k++;
	}
}
