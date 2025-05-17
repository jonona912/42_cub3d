#include "main_header.h"

int handle_keypress(int keysym, t_game *game)
{
    if (keysym == XK_w)
        game->key_w = 1;
    else if (keysym == XK_a)
        game->key_a = 1;
    else if (keysym == XK_s)
        game->key_s = 1; 
    else if (keysym == XK_d)
        game->key_d = 1;
    else if (keysym == XK_Left)
        game->key_left = 1;
    else if (keysym == XK_Right)
        game->key_right = 1;
    else if (keysym == XK_Escape)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    return (0);
}

int handle_keyrelease(int keysym, t_game *game)
{
    if (keysym == XK_w)
        game->key_w = 0;
    else if (keysym == XK_a)
        game->key_a = 0;
    else if (keysym == XK_s)
        game->key_s = 0;
    else if (keysym == XK_d)
        game->key_d = 0;
    else if (keysym == XK_Left)
        game->key_left = 0;
    else if (keysym == XK_Right)
        game->key_right = 0;
    return (0);
}

int handle_close(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
