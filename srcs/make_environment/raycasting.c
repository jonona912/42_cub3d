#include "main_header.h"


// divide rays into 2 parts 
// // calculate the distance to the wall
// // draw the line
int cast_rays(t_game *game, double dir_angle, double *distance_to_wall)
{
    // Ray direction
    double dir_x = cos(dir_angle);
    double dir_y = sin(dir_angle);
    double delta_dist_x;
    double delta_dist_y;
    if (dir_x == 0) {
        delta_dist_x = 1e30; // Avoid division by zero
    } else {
        delta_dist_x = fabs(1.0 / dir_x);
    }
    if (dir_y == 0) {
        delta_dist_y = 1e30; // Avoid division by zero
    } else {
        delta_dist_y = fabs(1.0 / dir_y);
    }
    // Step direction
    int step_x;
    if (dir_x > 0) {
        step_x = 1;
    } else {
        step_x = -1;
    }
    int step_y;
    if (dir_y > 0) {
        step_y = 1;
    } else {
        step_y = -1;
    }

    // Determine next grid lines
    double next_x = (dir_x >= 0) ? ceil(game->pos_x) : floor(game->pos_x);
    double next_y = (dir_y >= 0) ? ceil(game->pos_y) : floor(game->pos_y);

    // Side distances (distance along ray to first x/y grid)
    double distance_to_x_wall = 0, distance_to_y_wall = 0;
    if (dir_x > 0) {
        distance_to_x_wall = (next_x - game->pos_x) * delta_dist_x;
    } else if (dir_x < 0) {
        distance_to_x_wall = (game->pos_x - next_x) * delta_dist_x;
    } else {
        distance_to_x_wall = 1e30; // Ray parallel to y-axis
    }
    if (dir_y > 0) {
        distance_to_y_wall = (next_y - game->pos_y) * delta_dist_y;
    } else if (dir_y < 0) {
        distance_to_y_wall = (game->pos_y - next_y) * delta_dist_y;
    } else {
        distance_to_y_wall = 1e30; // Ray parallel to x-axis
    }
    // DDA loop to find wall
    int map_x = (int)game->pos_x;
    int map_y = (int)game->pos_y;
    int hit = 0;
    while (!hit) {
        // Choose the closer grid line (x or y)
        if (distance_to_x_wall < distance_to_y_wall) {
            map_x += step_x;
            game->side = 0; // 0 for vertical wall
            if (game->map[map_y][map_x] != '1')
                distance_to_x_wall += delta_dist_x;
        } else {
            map_y += step_y;
            game->side = 1; // 1 for horizontal wall
                if (game->map[map_y][map_x] != '1')
            distance_to_y_wall += delta_dist_y;
        }
        // Check if we hit a wall (assuming map[y][x] and '1' is a wall)
        if (map_y >= 0 && map_y < game->map_rows && map_x >= 0 && map_x < game->map_cols) { 
            if (game->map[map_y][map_x] == '1') {
                hit = 1;
                // printf("Wall hit at: (%d, %d)\n", map_x, map_y);
            }
        } else {
            // Out of bounds, stop the loop
            printf("Ray out of map bounds at: (%d, %d)\n", map_x, map_y);
            return (-1);
        }
    }
    *distance_to_wall = fmin(distance_to_x_wall, distance_to_y_wall);
    // draw_direction_line(game, pixel_x, pixel_y, distance_to_wall * GRID_SIZE, dir_x, dir_y);
    return (0);
}
