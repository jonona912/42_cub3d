#include "main_header.h"

int initialize_mlx(t_game *game)
{
	if (initialize_game_struct(game) == -1)
		return (1);
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_loop_hook(game->mlx, &two_d_game_loop, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &handle_close, game);
	mlx_loop(game->mlx);
	return (0);
}
