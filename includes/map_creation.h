#ifndef MAP_CREATION_H
#define MAP_CREATION_H

#include "libft.h"
#include "get_next_line.h"
#include "map_validation.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>

/* MiniLibX Window Settings */
#define WIN_WIDTH 1980
#define WIN_HEIGHT 1080
#define WIN_TITLE "Cub3D - Raycaster"

/* Game Structure */
typedef struct s_game
{
    void    *mlx;           /* MiniLibX instance pointer */
    void    *win;           /* Window pointer */
    char    **map;          /* Game map */
    /* Add more fields as needed for your game */
} t_game;

// print_debugging_fts.c
void print_map(char **map);

/* MiniLibX related functions - add as needed */
int handle_keypress(int keysym, t_game *game);
int handle_close(t_game *game);



#endif