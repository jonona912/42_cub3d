#include "main_header.h"

void cast_rays_2(t_game *game, double dir_angle) {
    // Ray direction
    double dir_x = cos(dir_angle);
    double dir_y = sin(dir_angle);
    game->dir_x = dir_x; // Store for consistency
    game->dir_y = dir_y;

    // Delta distances (distance along ray to cross one grid unit)
    double delta_dist_x = (dir_x == 0) ? 1e30 : fabs(1.0 / dir_x);
    double delta_dist_y = (dir_y == 0) ? 1e30 : fabs(1.0 / dir_y);

    // Step direction
    int step_x = (dir_x > 0) ? 1 : -1;
    int step_y = (dir_y > 0) ? 1 : -1;

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
            if (game->map[map_y][map_x] != '1')
                distance_to_x_wall += delta_dist_x;
        } else {
            map_y += step_y;
                if (game->map[map_y][map_x] != '1')
            distance_to_y_wall += delta_dist_y;
        }

        // Check if we hit a wall (assuming map[y][x] and '1' is a wall)
        if (map_y >= 0 && map_y < 5 && map_x >= 0 && map_x < 6) { // Assuming 5x5 map
            if (game->map[map_y][map_x] == '1') {
                hit = 1;
                printf("Wall hit at: (%d, %d)\n", map_x, map_y);
            }
        } else {
            // Out of bounds, stop the loop
            printf("Ray out of map bounds at: (%d, %d)\n", map_x, map_y);
            break;
        }
    }

    // Draw direction line (using the shorter distance for visualization)
    int pixel_x = (int)(game->pos_x * 64) - 5;
    int pixel_y = (int)(game->pos_y * 64) - 5;
    double first_cross_dist = fmin(distance_to_x_wall, distance_to_y_wall);
    draw_direction_line(game, pixel_x, pixel_y, first_cross_dist * 64);
}
