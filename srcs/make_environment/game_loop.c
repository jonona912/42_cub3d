#include "main_header.h"

int is_valid_position(t_game *game, double new_x, double new_y)
{
	int tile_x = (int)new_x;
	int tile_y = (int)new_y;

	if (new_x < 0 || new_x >= game->map_cols || new_y < 0 || new_y >= game->map_rows)
		return (0);
	if (game->map[tile_y][tile_x] == '1')
		return (0);
	return (1);
}

int is_move_valid(t_game *game, double move_x, double move_y)
{
	double new_x = game->pos_x + move_x;
	double new_y = game->pos_y + move_y;

	if (move_x != 0 || move_y != 0) {
		if (is_valid_position(game, new_x, new_y)) {
			// Full movement is valid
			game->pos_x = new_x;
			game->pos_y = new_y;
			return 1;
		} else {
			// Try moving only in x
			new_x = game->pos_x + move_x;
			new_y = game->pos_y;
			if (is_valid_position(game, new_x, new_y)) {
				game->pos_x = new_x;
				return 1;
			}
			// Try moving only in y
			new_x = game->pos_x;
			new_y = game->pos_y + move_y;
			if (is_valid_position(game, new_x, new_y)) {
				game->pos_y = new_y;
				return 1;
			}
		}
	}
	return 0;
}

long long get_current_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000;
}

double get_delta_time(void)
{
	static long long last_time = 0;
	long long current_time = get_current_time_ms();
	if (last_time == 0)
		last_time = current_time;
	double delta_time = (current_time - last_time) / 1000.0;
	last_time = current_time;
	return delta_time;
}

void handle_wasd_movement(t_game *game, double *move_x, double *move_y, double delta_time)
{
	double move_speed = 0.5;

	if (game->key_w)
	{
		*move_x += game->dir_x * move_speed * delta_time;
		*move_y += game->dir_y * move_speed * delta_time;
	}
	if (game->key_s)
	{
		*move_x -= game->dir_x * move_speed * delta_time;
		*move_y -= game->dir_y * move_speed * delta_time;
	}
	if (game->key_a)
	{
		*move_x += game->dir_y * move_speed * delta_time;
		*move_y -= game->dir_x * move_speed * delta_time;
	}
	if (game->key_d)
	{
		*move_x -= game->dir_y * move_speed * delta_time;
		*move_y += game->dir_x * move_speed * delta_time;
	}
}

int handle_movement_and_rotation(t_game *game, double *move_x, double *move_y)
{
	double delta_time = get_delta_time();
	int rotated = 0;
	double length = 0;
	handle_wasd_movement(game, move_x, move_y, delta_time);
	double move_speed = 5.0;
	if (game->key_left)
	{
		rotated = 1;
		game->dir_angle -= 1.5 * delta_time;
		game->dir_y = sin(game->dir_angle);
		game->dir_x = cos(game->dir_angle);
	}
	if (game->key_right) {
		rotated = 1;
		game->dir_angle += 1.5 * delta_time;
		game->dir_y = sin(game->dir_angle);
		game->dir_x = cos(game->dir_angle);
	}
	if (game->dir_angle > 2 * M_PI)
		game->dir_angle -= 2 * M_PI;
	if (game->dir_angle < 0)
		game->dir_angle += 2 * M_PI;

	if ((*move_x != 0 || game->dir_y == 0) && (*move_y != 0 || game->dir_x == 1)) {
		length = sqrt((*move_x) * (*move_x) + (*move_y) * (*move_y));
		if (length > 0) {
			*move_x = *move_x / length * move_speed * delta_time;
			*move_y = *move_y / length * move_speed * delta_time;
		}
	}
	return (rotated);
}

int two_d_game_loop(t_game *game)
{
	static int frame_count = 0;
	double move_x = 0;
	double move_y = 0;
	int rotated;
	rotated = handle_movement_and_rotation(game, &move_x, &move_y);
	// cast_fov_rays(game);
	if (is_move_valid(game, move_x, move_y) || rotated || !frame_count) {
		put_2d_map(game);
	}
	frame_count++;
	return (0);
}
