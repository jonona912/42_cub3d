#include "main_header.h"


void set_player_direction(t_game *game)
{
    int i = 0;
    int j;
    char direction;

    /* Find player position and direction in map */
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
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
                }
                else if (direction == 'S')
                {
                    game->dir_x = 0;
                    game->dir_y = 1;
                    game->plane_x = -0.66;
                    game->plane_y = 0;
                }
                else if (direction == 'E')
                {
                    game->dir_x = 1;
                    game->dir_y = 0;
                    game->plane_x = 0;
                    game->plane_y = 0.66;
                }
                else if (direction == 'W')
                {
                    game->dir_x = -1;
                    game->dir_y = 0;
                    game->plane_x = 0;
                    game->plane_y = -0.66;
                }
                return;
            }
            j++;
        }
        i++;
    }
}




// // // 
void	textures_info_init(t_textures_info *textures_info)
{
	textures_info->n_wall_path = "textures/north_wall.xpm";
	textures_info->floor_path = "textures/floor.xpm";
	textures_info->width = 64;
	textures_info->height = 64;

}

int	load_textures(t_game *game, t_loaded_textures *loaded_textures, t_textures_info *texture_info)
{
	loaded_textures->n_wall = mlx_xpm_file_to_image(game->mlx,
		texture_info->n_wall_path, &texture_info->width, &texture_info->height);
	if (!loaded_textures->n_wall)
	{
		return (-1);
	}
	loaded_textures->floor = mlx_xpm_file_to_image(game->mlx,
		texture_info->floor_path, &texture_info->width, &texture_info->height);
	if (!loaded_textures->floor)
	{
		return (-1);
	}
	return (0);
}

void draw_direction_line(t_game *game, int x, int y, int distance)
{
    int i = 0;
    int ex = 0;
    int yi = 0;
    y += 5;
    x += 5;
    while (i < distance)
    {
        ex = game->dir_x * i;
        yi = game->dir_y * i;
        mlx_pixel_put(game->mlx, game->win, x + ex, y + yi, 0x0000FF00);
        i++;
    }
}


void print_pixel(t_game *game, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(game->mlx, game->win, x + j, y + i, 0x00FF0000);
			j++;
		}
		i++;
	}
    i = 0;
    int ex = 0;
    int yi = 0;
    y += 5;
    x += 5;
    while (i < 20)
    {
        ex = cos(game->dir_angle) * i;
        yi = sin(game->dir_angle) * i;
        // printf("ex: %d, yi: %d\n", ex, yi);
        mlx_pixel_put(game->mlx, game->win, x + ex, y + yi, 0x00000000);
        i++;
    }
}

// int draw_map(t_game *game, t_loaded_textures *loaded_textures, t_textures_info *texture_info)
// {
// 	int x;
// 	int y;
// 	int	i;
// 	int j;

// 	y = 0;
// 	i = 0;
// 	while (i < 5)
// 	{
// 		x = 0;
// 		j = 0;
// 		while (j < 6)
// 		{
// 			if (game->map[i][j] == '1')
// 				mlx_put_image_to_window(game->mlx, game->win,
// 					loaded_textures->n_wall, x, y);
// 			else if (game->map[i][j] == '0')
// 				mlx_put_image_to_window(game->mlx, game->win,
// 					loaded_textures->floor, x, y);
// 			else if (game->map[i][j] == 'N')
// 					print_pixel(game, x + 27, y + 27);
// 			x += texture_info->width;
// 			j++;
// 		}
// 		y += texture_info->height;
// 		i++;
// 	}
// 	return (0);
// }


int draw_map(t_game *game, t_loaded_textures *loaded_textures, t_textures_info *texture_info)
{
    int x;
    int y;
    int i;
    int j;

    y = 0;
    i = 0;
    while (i < 5)
    {
        x = 0;
        j = 0;
        while (j < 6)
        {
            if (game->map[i][j] == '1')
                mlx_put_image_to_window(game->mlx, game->win,
                    loaded_textures->n_wall, x, y);
            else if (game->map[i][j] == '0' || game->map[i][j] == 'N' || 
                     game->map[i][j] == 'S' || game->map[i][j] == 'E' || 
                     game->map[i][j] == 'W')
                mlx_put_image_to_window(game->mlx, game->win,
                    loaded_textures->floor, x, y);
            x += texture_info->width;
            j++;
        }
        y += texture_info->height;
        i++;
    }
    /* Find player position and place marker */
    // set_player_direction(game);
    // int player_x = game->pos_x * texture_info->width;
    // int player_y = game->pos_y * texture_info->height;
    // print_pixel(game, player_x - 5, player_y - 5);
    
    /* Cast rays from player position */
    // cast_rays(game, 60); /* Cast 60 rays */
    
    return (0);
}

int initialize_mlx(t_game *game)
{
	// t_textures_info		textures_info;
	// t_loaded_textures	loaded_textures;
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
	game->dir_angle = 0;
	textures_info_init(&game->textures_info);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MiniLibX\n", STDERR_FILENO);
		// free_map(game->map);
		return (1);
	}
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->win)
	{
		ft_putstr_fd("Error: Failed to create window\n", STDERR_FILENO);
		// free_map(game->map);
		return (1);
	}
	// load textures here
	if (load_textures(game, &game->loaded_textures, &game->textures_info) == -1)
	{
		ft_putstr_fd("Error: Failed to load textures\n", STDERR_FILENO);
		// free_map(game->map);
		return (1);
	}
	draw_map(game, &game->loaded_textures, &game->textures_info);
	set_player_direction(game);
    int player_x = game->pos_x * game->textures_info.width;
    int player_y = game->pos_y * game->textures_info.height;
    print_pixel(game, player_x - 5, player_y - 5);

	// mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	// mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &handle_close, game);
	mlx_loop(game->mlx);
	return (0);
}

