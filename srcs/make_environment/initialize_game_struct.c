#include "main_header.h"

void	set_player_direction(t_game *game)
{
	int i = 0;
	int j;
	char direction;

	/* Find player position and direction in map */
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j]) // set angle 	game->dir_angle = 0;
		{
			direction = game->map[i][j];
			if (direction == 'N' || direction == 'S' || direction == 'E' || direction == 'W')
			{
				game->pos_x = j + 0.5; /* Center of the tile */
				game->pos_y = i + 0.5;
				
				/* Set direction based on player orientation */
				if (direction == 'N')
				{
					game->dir_x = 0;
					game->dir_y = -1;
					game->plane_x = 0.66;
					game->plane_y = 0;
					game->dir_angle = 3 * M_PI / 2;
				}
				else if (direction == 'S')
				{
					game->dir_x = 0;
					game->dir_y = 1;
					game->plane_x = -0.66;
					game->plane_y = 0;
					game->dir_angle = M_PI / 2;
				}
				else if (direction == 'E')
				{
					game->dir_x = 1;
					game->dir_y = 0;
					game->plane_x = 0;
					game->plane_y = 0.66;
					game->dir_angle = 0;
				}
				else if (direction == 'W')
				{
					game->dir_x = -1;
					game->dir_y = 0;
					game->plane_x = 0;
					game->plane_y = -0.66;
					game->dir_angle = M_PI;
				}
				return;
			}
			j++;
		}
		i++;
	}
}

void	initialize_keys(t_game *game)
{
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
}

// int	load_textures(t_game *game, t_loaded_textures *loaded_textures, t_textures_info *texture_info)
// {
// 	loaded_textures->n_wall = mlx_xpm_file_to_image(game->mlx,
// 		texture_info->n_wall_path, &texture_info->width, &texture_info->height);
// 	if (!loaded_textures->n_wall)
// 	{
// 		return (-1);
// 	}
// 	loaded_textures->floor = mlx_xpm_file_to_image(game->mlx,
// 		texture_info->floor_path, &texture_info->width, &texture_info->height);
// 	if (!loaded_textures->floor)
// 	{
// 		return (-1);
// 	}
// 	return (0);
// }

void	set_map_dimensions(t_game *game)
{
	int i = 0;
	int j = 0;

	while (game->map[i])
		i++;
	game->map_height = i * GRID_SIZE;
	game->map_rows = i;
	while (game->map[0][j])
		j++;
	game->map_width = j * GRID_SIZE;
	game->map_cols = j;
}

int	initialize_game_struct(t_game *game)
{
	set_map_dimensions(game);
	game->mlx = mlx_init();
	game->projected_slice_height = TEXTURE_SIZE * 255; // 255 arbitrary
	if (!game->mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MiniLibX\n", STDERR_FILENO);
		return (-1);
	}
	game->win = mlx_new_window(game->mlx, game->map_width, game->map_height, WIN_TITLE);
	if (!game->win)
	{
		ft_putstr_fd("Error: Failed to create window\n", STDERR_FILENO);
		return (-1);
	}
	game->img = mlx_new_image(game->mlx, game->map_width, game->map_height);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	game->img_3d = mlx_new_image(game->mlx, 1920, 1080);
	game->img_data_3d = mlx_get_data_addr(game->img_3d, &game->bpp_3d, &game->size_line_3d, &game->endian_3d);
	// if (load_textures(game, &game->loaded_textures, &game->textures_info) == -1)
	// {
	// 	ft_putstr_fd("Error: Failed to load textures\n", STDERR_FILENO);
	// 	return (-1);
	// }
	initialize_keys(game);
	set_player_direction(game);
	return (0);
}
