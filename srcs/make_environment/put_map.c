#include "main_header.h"

void draw_direction_line(t_game *game, int distance, double dir_x, double dir_y)
{
	int i = 0;
	int ex = 0;
	int yi = 0;
	int x = (int)(game->pos_x * GRID_SIZE) - 5;
	int y = (int)(game->pos_y * GRID_SIZE) - 5; // -5 and +5???

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
void draw_direction_line_2(t_game *game, int distance, double dir_x, double dir_y)
{
	int i = 0;
	int ex = 0;
	int yi = 0;
	int x = (int)(game->pos_x * GRID_SIZE) - 5;
	int y = (int)(game->pos_y * GRID_SIZE) - 5; // -5 and +5???

	y += 5;
	x += 5;
	while (i < distance)
	{
		ex = dir_x * i;
		yi = dir_y * i;
		put_pixel(game, x + ex, y + yi, 0x000000FF);
		i++;
	}
}

// void draw_direction_line_2(t_game *game, int x, int y, int distance)
// {
// 	int i = 0;
// 	int ex = 0;
// 	int yi = 0;
// 	y += 5;
// 	x += 5;
// 	while (i < distance)
// 	{
// 		ex = game->dir_x * i;
// 		yi = game->dir_y * i;
// 		put_pixel(game, x + ex, y + yi, 0x000000FF);
// 		i++;
// 	}
// }

void put_pixel(t_game *game, int x, int y, int color) {
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height) {
		int pixel = (y * game->size_line) + (x * (game->bpp / 8));
		*(unsigned int *)(game->img_data + pixel) = color;
	}
}

void put_grid_boundary(t_game *game, int x, int y, int color)
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

void put_map_background(t_game *game)
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
				put_grid_boundary(game, x * GRID_SIZE, y * GRID_SIZE, 0x008000FF); // Wall (purple)
			x++;
		}
		y++;
	}
}

void	clear_screen(t_game *game)
{
	for (int y = 0; y < game->map_height; y++)
		for (int x = 0; x < game->map_width; x++)
			put_pixel(game, x, y, 0x000000);
}

void	clear_screen_2(t_game *game)
{
	for (int y = 0; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			put_pixel(game, x, y, 0x000000);
}

void	put_player_position(t_game *game) // printing is not centered
{
	int	square_size = GRID_SIZE >> 2; // 1/4 of the grid size
	int x = game->pos_x * GRID_SIZE - square_size / 2;
	int y = game->pos_y * GRID_SIZE - square_size / 2;

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

// void	cast_fov_rays(t_game *game)
// {
// 	int i = 0;
// 	double angle_init = game->dir_angle - M_PI / 6; // 30 degrees in radians;
// 	double one_degree = M_PI / 180;
// 	double distance_to_wall = 0;
// 	while (i < 60)
// 	{
// 		double ray_angle = angle_init + (i * one_degree);
// 		cast_rays(game, ray_angle, &distance_to_wall);
// 		draw_direction_line(game, distance_to_wall * GRID_SIZE, cos(ray_angle), sin(ray_angle));
// 		i++;
// 	}
// }

void put_vertical_line(int wall_height)
{
	// 1920 / 60 = 32 (each line is 32 pixels wide)
	// height is 1920
	// divide the screen height by 2 1920 / 2 = 960
	// devide the given height of the wall_height by two and add it to the 960 above
	// ak bgi dega, start printing from the (960 + wall_height / 2) to (960 - wall_height / 2)
}

// experimenting
void	cast_fov_rays_2(t_game *game)
{
	int i = 0;
	double angle_init = game->dir_angle - M_PI / 6; // 30 degrees in radians;
	double one_degree = M_PI / 180;
	double perp_distance = 0;
	cast_rays(game, game->dir_angle, &perp_distance);
	double distance_to_wall = 0;
	double height;
	while (i < 60)
	{
		double ray_angle = angle_init + (i * one_degree);
		cast_rays(game, ray_angle, &distance_to_wall);
		// // calculate the actual distance to the wall
		distance_to_wall = distance_to_wall * cos(ray_angle - game->dir_angle);
		// height = game->projected_slice_height / distance_to_wall;
		// since it you are looking at the middle of the wall, add 
		// half the height and start putting the pixels down the collumn
		height = (game->projected_slice_height / distance_to_wall);
		draw_direction_line(game, distance_to_wall * GRID_SIZE, cos(ray_angle), sin(ray_angle));
		i++;
	}
	draw_direction_line_2(game, perp_distance * GRID_SIZE, game->dir_x, game->dir_y);
}

// void	put_2d_map(t_game *game)
// {
// 	clear_screen(game);
// 	put_map_background(game);

// 	cast_fov_rays(game);
// 	put_player_position(game);
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// }


// experimental
void	put_2d_map(t_game *game)
{
	clear_screen_2(game); // if you send dimensions seperately, you could use it twice
	// put_map_background(game);

	cast_fov_rays_2(game);
	// put_player_position(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img_3d, 0, 0);
}
