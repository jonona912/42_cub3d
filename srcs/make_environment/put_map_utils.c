#include "main_header.h"

void	clear_screen(t_game *game)
{
	for (int y = 0; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			put_pixel(game, x, y, 0x000000);
}

void put_pixel(t_game *game, int x, int y, int color) {
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT) {
		int pixel = (y * game->size_line) + (x * (game->bpp / 8));
		*(unsigned int *)(game->img_data + pixel) = color;
	}
}


void print_ceiling_floor(t_game *game)
{
	int i = 0;
	int half_height = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		int j = 0;
		while (j < WIN_WIDTH)
		{
			if (i > half_height)
				put_pixel(game, j, i, 0x00000000); // Blue color for ceiling
			else
				put_pixel(game, j, i, 0x000000FF); // Black color for floor
			j++;
		}
		i++;
	}
}

