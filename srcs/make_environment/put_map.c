#include "main_header.h"


void put_pixel(t_game *game, int x, int y, int color) {
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT) {
		int pixel = (y * game->size_line) + (x * (game->bpp / 8));
		*(unsigned int *)(game->img_data + pixel) = color;
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
	// for (int y = 0; y < game->map_height; y++)
	// 	for (int x = 0; x < game->map_width; x++)
	// 		put_pixel(game, x, y, 0x000000);
	for (int y = 0; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			put_pixel(game, x, y, 0x000000);
}

// void	clear_screen_2(t_game *game)
// {
// 	for (int y = 0; y < WIN_HEIGHT; y++)
// 		for (int x = 0; x < WIN_WIDTH; x++)
// 			put_pixel(game, x, y, 0x000000);
// }

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

// void put_vertical_line(int wall_height, int column, t_game *game, double ray_angle)
// {
// 	int x_start = column * 16 - 1; // 1920 / 120 = 16
// 	int y_start = (WIN_HEIGHT / 2) + (wall_height / 2);
// 	int y_end = (WIN_HEIGHT / 2) - (wall_height / 2);
// 	int i = 0;
// 	while (i < WIN_HEIGHT)
// 	{
// 		int j = 0;
// 		while (x_start + j < x_start + 16)
// 		{
// 			if (i >= y_end && i <= y_start)
// 			{
// 				if (ray_angle >= 0 && ray_angle <= M_PI/2)
// 				{
// 					if (game->side == 0)
// 						put_pixel(game, x_start + j, i, 0x00FF0000); 
// 					else
// 						put_pixel(game, x_start + j, i, YELLOW);
// 				}
// 				else if (ray_angle > M_PI/2 && ray_angle <= M_PI)
// 				{
// 					if (game->side == 0)
// 						put_pixel(game, x_start + j, i, 0x000000FF); // Green color for wall
// 					else
// 						put_pixel(game, x_start + j, i, YELLOW); // Red color for wall
// 				}
// 				else if (ray_angle > M_PI && ray_angle <= 3 * M_PI / 2)
// 				{
// 					if (game->side == 0)
// 						put_pixel(game, x_start + j, i, 0x000000FF); // Blue color for wall
// 					else
// 						put_pixel(game, x_start + j, i, 0x008000FF); // Purple color for wall
// 				}
// 				else if (ray_angle > 3 * M_PI / 2 && ray_angle < 2 * M_PI)
// 				{
// 					if (game->side == 0)
// 						put_pixel(game, x_start + j, i, 0x008000FF); // Purple color for wall
// 					else
// 						put_pixel(game, x_start + j, i, 0x000000FF); // Blue color for wall
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	// 1920 / 60 = 32 (each line is 32 pixels wide)
// 	// height is 1920
// 	// divide the screen height by 2 1920 / 2 = 960
// 	// devide the given height of the wall_height by two and add it to the 960 above
// 	// ak bgi dega, start printing from the (960 + wall_height / 2) to (960 - wall_height / 2)
// }

// void put_vertical_line(int wall_height, int column, t_game *game, double ray_angle)
// {
//     int x_start = column * 16; // 1920 / 120 = 16 pixels per column
//     int y_start = (WIN_HEIGHT / 2) + (wall_height / 2);
//     int y_end = (WIN_HEIGHT / 2) - (wall_height / 2);

//     // Clamp y_start and y_end to window boundaries
//     y_start = y_start > WIN_HEIGHT ? WIN_HEIGHT : y_start;
//     y_end = y_end < 0 ? 0 : y_end;

//     // Determine wall face based on side and ray angle
//     uint32_t color;
//     if (game->side == 0) // Horizontal wall hit (north or south)
//     {
//         if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2) // Ray moving up
//             color = YELLOW; // West face
//         else
//             color = PURPLE; // East face
//     }
//     else // Vertical wall hit (east or west)
//     {
//         if (ray_angle > 0 && ray_angle < M_PI) // Ray moving right
//             color = GREEN; // South face
//         else
//             color = WHITE; // North face
//     }

//     // Draw the vertical strip
//     int i = y_end;
//     while (i < y_start)
//     {
//         int j = 0;
//         while (j < 16) // Draw 16 pixels wide
//         {
//             put_pixel(game, x_start + j, i, color);
//             j++;
//         }
//         i++;
//     }
// }

void put_vertical_line_2(int wall_height, int column, t_game *game, double ray_angle)
{
    int x_start = column * 16; // 1920 / 120 = 16 pixels per column
    int y_start = (WIN_HEIGHT / 2) + (wall_height / 2);
    int y_end = (WIN_HEIGHT / 2) - (wall_height / 2);

    // Clamp y_start and y_end to window boundaries
    y_start = y_start > WIN_HEIGHT ? WIN_HEIGHT : y_start;
    y_end = y_end < 0 ? 0 : y_end;

    // Determine wall face and select texture
    void *texture;
    if (game->side == 0) // Horizontal wall hit (north or south)
    {
        if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2) // Ray moving up
            texture = game->loaded_textures.w_wall; // West face
        else
            texture = game->loaded_textures.s_wall; // East face
    }
    else // Vertical wall hit (east or west)
    {
        if (ray_angle > 0 && ray_angle < M_PI) // Ray moving right
            texture = game->loaded_textures.n_wall; // South face
        else
            texture = game->loaded_textures.e_wall; // North face
    }

    // Get texture data
    char *texture_data = mlx_get_data_addr(texture, &game->texture_bpp, &game->texture_size_line, &game->texture_endian);
    int texture_width = game->textures_info.width; // e.g., 64
    int texture_height = game->textures_info.height; // e.g., 64

    // Calculate wall hit position (texture x-coordinate)
    double wall_x; // Where the ray hits the wall (0 to 1)
    if (game->side == 0)
        wall_x = game->pos_y + game->perp_wall_dist * sin(ray_angle);
    else
        wall_x = game->pos_x + game->perp_wall_dist * cos(ray_angle);
    wall_x -= floor(wall_x); // Get fractional part (0 to 1)
    int tex_x = (int)(wall_x * (double)texture_width); // Texture x-coordinate
    if ((game->side == 0 && cos(ray_angle) > 0) || (game->side == 1 && sin(ray_angle) < 0))
        tex_x = texture_width - tex_x - 1; // Flip texture for correct orientation

    // Draw the vertical strip
    int i = y_end;
    while (i < y_start)
    {
        // Calculate texture y-coordinate
        double tex_pos = (i - WIN_HEIGHT / 2 + wall_height / 2) * (double)texture_height / wall_height;
        int tex_y = (int)tex_pos % texture_height;
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= texture_height)
            tex_y = texture_height - 1;

        // Get pixel color from texture
        int tex_index = (tex_y * game->texture_size_line) + (tex_x * (game->texture_bpp / 8));
        uint32_t color = *(uint32_t *)(texture_data + tex_index);

        // Draw 16 pixels wide
        int j = 0;
        while (j < 16)
        {
            put_pixel(game, x_start + j, i, color);
            j++;
        }
        i++;
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
		// draw the wall (3D projection)
		// int height = (game->projected_slice_height / distance_to_wall);
		// put_vertical_line(height, i, game);
		i++;
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

void	cast_fov_rays_2(t_game *game)
{
	int i = 0;
	double angle_init = game->dir_angle - M_PI / 6; // 30 degrees in radians;
	double one_degree = M_PI / 360; // 2 * 180
	double distance_to_wall = 0;
	while (i < 120)
	{
		double ray_angle = angle_init + (i * one_degree);
		cast_rays(game, ray_angle, &distance_to_wall);
		distance_to_wall = distance_to_wall * cos(ray_angle - game->dir_angle);
		game->perp_wall_dist = distance_to_wall;
		draw_direction_line(game, distance_to_wall * GRID_SIZE, cos(ray_angle), sin(ray_angle));
		// draw the wall (3D projection)
		int height = (game->projected_slice_height / (distance_to_wall * TEXTURE_SIZE));
		put_vertical_line_2(height, i, game, ray_angle);
		i++;
	}
}



// // experimenting
// void	cast_fov_rays_2(t_game *game)
// {
// 	int i = 0;
// 	double angle_init = game->dir_angle - M_PI / 6; // 30 degrees in radians;
// 	double one_degree = M_PI / 180;
// 	double perp_distance = 0;
// 	cast_rays(game, game->dir_angle, &perp_distance);
// 	double distance_to_wall = 0;
// 	double height;
// 	while (i < 60)
// 	{
// 		double ray_angle = angle_init + (i * one_degree);
// 		cast_rays(game, ray_angle, &distance_to_wall);
// 		// // calculate the actual distance to the wall
// 		distance_to_wall = distance_to_wall * cos(ray_angle - game->dir_angle);
// 		// height = game->projected_slice_height / distance_to_wall;
// 		// since it you are looking at the middle of the wall, add 
// 		// half the height and start putting the pixels down the collumn
// 		height = (game->projected_slice_height / distance_to_wall);
// 		put_vertical_line(height, i, game);
// 		// draw_direction_line(game, distance_to_wall * GRID_SIZE, cos(ray_angle), sin(ray_angle));
// 		i++;
// 	}
// 	draw_direction_line_2(game, perp_distance * GRID_SIZE, game->dir_x, game->dir_y);
// }


void	put_2d_map(t_game *game)
{
	clear_screen(game); // 1920 x 1080
	// put_map_background(game);
	// add the printing screen
	print_ceiling_floor(game);
	cast_fov_rays_2(game);
	cast_fov_rays(game);
	put_map_background_2(game, game->x_start_minimap, game->y_start_minimap);
	put_player_position(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

// // experimental
// void	put_2d_map(t_game *game)
// {
// 	clear_screen_2(game); // if you send dimensions seperately, you could use it twice
// 	// put_map_background(game);

// 	cast_fov_rays_2(game);
// 	// put_player_position(game);
// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// }
