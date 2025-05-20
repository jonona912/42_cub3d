#include "main_header.h"


// divide rays into 2 parts 
// // calculate the distance to the wall
// // draw the line


typedef struct s_ray_params {
	double dir_x;
	double dir_y;
	double delta_dist_x;
	double delta_dist_y;
	int step_x;
	int step_y;
	double next_x;
	double next_y;
	double dist_to_x_wall;
	double dist_to_y_wall;
	int map_x;
	int map_y;
} t_ray_params;

void init_ray_params(t_game *game, double dir_angle, t_ray_params *ray)
{
	ray->dir_x = cos(dir_angle);
	ray->dir_y = sin(dir_angle);

	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);

	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);

	if (ray->dir_x > 0)
		ray->step_x = 1;
	else
		ray->step_x = -1;

	if (ray->dir_y > 0)
		ray->step_y = 1;
	else
		ray->step_y = -1;

	if (ray->dir_x >= 0)
		ray->next_x = ceil(game->pos_x);
	else
		ray->next_x = floor(game->pos_x);

	if (ray->dir_y >= 0)
		ray->next_y = ceil(game->pos_y);
	else
		ray->next_y = floor(game->pos_y);
}


void init_ray_side_distances(t_game *game, t_ray_params *ray)
{
	ray->dist_to_x_wall = 0;
	ray->dist_to_y_wall = 0;
	if (ray->dir_x > 0) {
		ray->dist_to_x_wall = (ray->next_x - game->pos_x) * ray->delta_dist_x;
	} else if (ray->dir_x < 0) {
		ray->dist_to_x_wall = (game->pos_x - ray->next_x) * ray->delta_dist_x;
	} else {
		ray->dist_to_x_wall = 1e30; // Ray parallel to y-axis
	}
	if (ray->dir_y > 0) {
		ray->dist_to_y_wall = (ray->next_y - game->pos_y) * ray->delta_dist_y;
	} else if (ray->dir_y < 0) {
		ray->dist_to_y_wall = (game->pos_y - ray->next_y) * ray->delta_dist_y;
	} else {
		ray->dist_to_y_wall = 1e30; // Ray parallel to x-axis
	}
}

int perform_dda(t_game *game, t_ray_params *ray)
{
	int hit = 0;

	ray->map_x = (int)game->pos_x;
	ray->map_y = (int)game->pos_y;
	while (!hit) {
		// Choose the closer grid line (x or y)
		if (ray->dist_to_x_wall < ray->dist_to_y_wall) {
			ray->map_x += ray->step_x;
			game->side = 0; // 0 for vertical wall
			if (game->map[ray->map_y][ray->map_x] != '1')
				ray->dist_to_x_wall += ray->delta_dist_x;
		} else {
			ray->map_y += ray->step_y;
			game->side = 1; // 1 for horizontal wall
			if (game->map[ray->map_y][ray->map_x] != '1')
				ray->dist_to_y_wall += ray->delta_dist_y;
		}
		// Check if we hit a wall (assuming map[y][x] and '1' is a wall)
		if (ray->map_y >= 0 && ray->map_y < game->map_rows && ray->map_x >= 0 && ray->map_x < game->map_cols) { 
			if (game->map[ray->map_y][ray->map_x] == '1') {
				hit = 1;
			}
		} else {
			// Out of bounds, stop the loop
			printf("Ray out of map bounds at: (%d, %d)\n", ray->map_x, ray->map_y);
			return (-1);
		}
	}
	return 0;
}


int cast_rays(t_game *game, double dir_angle, double *distance_to_wall)
{
	t_ray_params ray;

	init_ray_params(game, dir_angle, &ray);
	init_ray_side_distances(game, &ray);
	if (perform_dda(game, &ray) < 0)
		return (-1);
	*distance_to_wall = fmin(ray.dist_to_x_wall, ray.dist_to_y_wall);
	return (0);
}
