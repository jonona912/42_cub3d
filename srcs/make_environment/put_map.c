#include "main_header.h"

double	calculate_wall_x(t_game *game, double ray_angle)
{
	double	wall_x;

	(void)(ray_angle);
	if (game->side == 0)
		wall_x = game->pos_y + game->true_ray_dist * sin(ray_angle);
	else
		wall_x = game->pos_x + game->true_ray_dist * cos(ray_angle);
	return (wall_x - floor(wall_x));
}

// bool needs_texture_flip(t_game *game, double ray_angle)
// {
//     return (game->side == 0 && cos(ray_angle) > 0) || (game->side == 1 && sin(ray_angle) < 0);
// }

char	*set_texture_type(t_game *game, double ray_angle)
{
	if (ray_angle > 2 * M_PI)
		ray_angle -= 2 * M_PI;
	else if (ray_angle < 0)
		ray_angle += 2 * M_PI;
	if (game->side == 0) // vertical wall
	{
		if (ray_angle > M_PI / 2 && ray_angle < (3 * M_PI) / 2)
			return game->loaded_textures.w_wall_data;
		else
			return game->loaded_textures.e_wall_data;
	}
	else
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			return game->loaded_textures.s_wall_data;
		else
			return game->loaded_textures.n_wall_data;
	}
}

void	put_vertical_line(int wall_height, int column, t_game *game, double ray_angle)
{
	// t_texture	texture_type;
	int y_start = (WIN_HEIGHT / 2) + (wall_height / 2);
	int y_end = (WIN_HEIGHT / 2) - (wall_height / 2);

	if (y_start > WIN_HEIGHT)
		y_start = WIN_HEIGHT;
	if (y_end < 0)
		y_end = 0;

	char *texture_data = set_texture_type(game, ray_angle);
	double wall_x = calculate_wall_x(game, ray_angle);
	int tex_x = (int)(wall_x * game->textures_info.width);
	// if (needs_texture_flip(game, ray_angle))
	//     tex_x = texture_width - tex_x - 1;

	int i = y_end;
	while (i < y_start)
	{
		double tex_pos = (i - WIN_HEIGHT / 2 + wall_height / 2) * (double)game->textures_info.height / wall_height;
		int tex_y = (int)tex_pos % game->textures_info.height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= game->textures_info.height)
			tex_y = game->textures_info.height - 1;

		int tex_index = (tex_y * game->texture_size_line) + (tex_x * (game->texture_bpp / 8));
		uint32_t color = *(uint32_t *)(texture_data + tex_index);
		put_pixel(game, column, i, color);
		i++;
	}
}

void	cast_and_creat_pseudo_3d_env(t_game *game)
{
	double	angle_init;
	// double	ray_step;
	double	distance_to_wall;
	int		height;
	double	ray_angle;

	angle_init = game->dir_angle - (M_PI / 6);
	// ray_step = (M_PI / 3) / WIN_WIDTH;
	distance_to_wall = 0;
	height = 0;
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		ray_angle = angle_init + (i * game->ray_step);
		if (cast_rays(game, ray_angle, &distance_to_wall) == -1)
		{
			ft_putstr_fd("Error: Ray out of map bounds\n", STDERR_FILENO);
			free_game_struct(game);
			exit (1);
		}
		game->true_ray_dist = distance_to_wall;
		distance_to_wall *= cos(ray_angle - game->dir_angle);
		game->perp_wall_dist = distance_to_wall;
		height = (game->projected_slice_height / (distance_to_wall * game->textures_info.width)) * 4;
		put_vertical_line(height, i, game, ray_angle);
	}
}

void	draw_screen(t_game *game)
{
	clear_screen(game);
	print_ceiling_floor(game);
	cast_and_creat_pseudo_3d_env(game); // <<<< ==========================================================

	// minimap
	cast_fov_rays(game);  // minimap
	put_map_background_2(game, game->x_start_minimap, game->y_start_minimap); // minimap
	put_player_position(game); // minimap
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
