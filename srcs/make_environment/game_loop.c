#include "main_header.h"

int is_valid_position(t_game *game, double new_x, double new_y)
{
	int tile_x = (int)new_x;
    int tile_y = (int)new_y;

    if (new_x < 0 || new_x >= WIN_WIDTH || new_y < 0 || new_y >= WIN_HEIGHT)
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
    double move_speed = 5.0;

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
    game->dir_y = sin(game->dir_angle);
    game->dir_x = cos(game->dir_angle);
    double length = 0;
    handle_wasd_movement(game, move_x, move_y, delta_time);
    double move_speed = 5.0;
    if (game->key_left) {
        rotated = 1;
        game->dir_angle -= 1.5 * delta_time;
    }
    if (game->key_right) {
        rotated = 1;
        game->dir_angle += 1.5 * delta_time;
    }
    if (game->dir_angle > 2 * M_PI)
        game->dir_angle -= 2 * M_PI;
    if (game->dir_angle < 0)
        game->dir_angle += 2 * M_PI;
    if (*move_x != 0 && *move_y != 0) {
        length = sqrt((*move_x) * (*move_x) + (*move_y) * (*move_y));
        if (length > 0) {
            *move_x = *move_x / length * move_speed * delta_time;
            *move_y = *move_y / length * move_speed * delta_time;
        }
    }
    return (rotated);
}


void cast_fov_rays(t_game *game)
{
    int i = 0;
    double sixty = M_PI / 6;
    double angle_init = game->dir_angle - sixty;
    while (i < 60)
    {
        double ray_angle = angle_init + (i * (M_PI / 180));
        cast_rays_2(game, ray_angle);
        i++;
    }
}

int game_loop(t_game *game)
{
    double move_x = 0;
    double move_y = 0;
    int rotated;
    rotated = handle_movement_and_rotation(game, &move_x, &move_y);
    cast_fov_rays(game);
    if (is_move_valid(game, move_x, move_y) || rotated) {
        draw_map(game, &game->loaded_textures, &game->textures_info);
        int pixel_x = (int)(game->pos_x * 64) - 5;
        int pixel_y = (int)(game->pos_y * 64) - 5;
        print_pixel(game, pixel_x, pixel_y);
    }
    return (0);
}
