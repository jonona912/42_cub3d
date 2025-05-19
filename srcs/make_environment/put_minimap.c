#include "main_header.h"

void draw_direction_line(t_game *game, int distance, double dir_x, double dir_y)
{
	int i = 0;
	int ex = 0;
	int yi = 0;
	int x = (int)(game->pos_x * GRID_SIZE) - 5 + game->x_start_minimap;
	int y = (int)(game->pos_y * GRID_SIZE) - 5 + game->y_start_minimap;

	y += 5;
	x += 5;
	while (i < distance)
	{
		ex = dir_x * i;
		yi = dir_y * i;
		put_pixel(game, x + ex, y + yi, 0x0000FF00);
		i++;
	}
}

void	cast_fov_rays(t_game *game)
{
	int i = 0;
	double angle_init = game->dir_angle - M_PI / 6; // 30 degrees in radians;
	double one_degree = M_PI / 180;
	double distance_to_wall = 0;
	while (i < 60)
	{
		double ray_angle = angle_init + (i * one_degree);
		cast_rays(game, ray_angle, &distance_to_wall);
		distance_to_wall = distance_to_wall * cos(ray_angle - game->dir_angle);
		draw_direction_line(game, distance_to_wall * GRID_SIZE, cos(ray_angle), sin(ray_angle));
		i++;
	}
}

void put_grid_boundary_2(t_game *game, int x, int y, int color)
{
	int i;
	int j;

	for (i = 0; i < GRID_SIZE; i++)
	{
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (i == 0 || i == GRID_SIZE - 1 || j == 0 || j == GRID_SIZE - 1)
				put_pixel(game, x + j, y + i, color);
		}
	}
}


void put_map_background_2(t_game *game, int x_offset, int y_offset)
{
	int x;
	int y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				put_grid_boundary_2(game, x * GRID_SIZE + x_offset, y * GRID_SIZE + y_offset, 0x008000FF); // Wall (purple)
			x++;
		}
		y++;
	}
}

void	put_player_position(t_game *game) // printing is not centered
{
	int	square_size = GRID_SIZE >> 2; // 1/4 of the grid size
	int x = game->pos_x * GRID_SIZE - square_size / 2 + game->x_start_minimap;
	int y = game->pos_y * GRID_SIZE - square_size / 2 + game->y_start_minimap;

	while (square_size > 0)
	{
		int i = 0;
		while (i < square_size)
		{
			int j = 0;
			while (j < square_size)
			{
				put_pixel(game, x + j, y + i, 0x00FF0000); // Red color for player
				j++;
			}
			i++;
		}
		square_size--;
	}
	// temp blue line
	// draw_direction_line_2(game, x, y, 20);
}
 