#include "main_header.h"

/* Handle key press events */
int handle_keypress(int keysym, t_game *game)
{
	printf("Key pressed: %d\n", keysym);
	if (keysym == XK_Escape) /* ESC key */
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	/* Add other keypress handling as needed */
	return (0);
}

/* Handle window close button */
int handle_close(t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int main(int argc, char **argv)
{
	t_game game;

	ft_memset(&game, 0, sizeof(t_game));

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d map_file\n", STDERR_FILENO);
		return (1);
	}
	
	game.map = validate_map(argv[1]);
	if (!game.map)
	{
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
		return (1);
	}
	print_map(game.map);
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_putstr_fd("Error: Failed to initialize MiniLibX\n", STDERR_FILENO);
		free_map(game.map);
		return (1);
	}
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game.win)
	{
		ft_putstr_fd("Error: Failed to create window\n", STDERR_FILENO);
		free_map(game.map);
		return (1);
	}
	
	mlx_hook(game.win, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask, &handle_close, &game);
	
	mlx_loop(game.mlx);

	free_map(game.map);
	return (0);
}


// make a 2D window with walls and player looking at a direction
// define the size of each square in the map and change color of the square based on type
