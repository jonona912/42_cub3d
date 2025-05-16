#include "main_header.h"

/* Handle key press events */
// int handle_keypress(int keysym, t_game *game)
// {
// 	printf("Key pressed: %d\n", keysym);
// 	if (keysym == XK_a) /* Left arrow key */ 
// 	{
// 		printf("Moving left: x: %f, y: %f\n", game->pos_x, game->pos_y);
// 		game->pos_x -= 0.1; /* Move left */
// 		draw_map(game, &game->loaded_textures, &game->textures_info);
// 		print_pixel(game, (game->pos_x * 64) - 5, (game->pos_y * 64) - 5);
// 	}
// 	else if (keysym == XK_d) /* Right arrow key */
// 	{
// 		game->pos_x += 0.1; /* Move right */
// 		draw_map(game, &game->loaded_textures, &game->textures_info);
// 		print_pixel(game, (game->pos_x * 64) - 5, (game->pos_y * 64) - 5);
// 	}
// 	else if (keysym == XK_w) /* Up arrow key */
// 	{
// 		game->pos_y -= 0.1; /* Move up */
// 		draw_map(game, &game->loaded_textures, &game->textures_info);
// 		print_pixel(game, (game->pos_x * 64) - 5, (game->pos_y * 64) - 5);
// 	}
// 	else if (keysym == XK_s) /* Down arrow key */
// 	{
// 		game->pos_y += 0.1; /* Move down */
// 		draw_map(game, &game->loaded_textures, &game->textures_info);
// 		print_pixel(game, (game->pos_x * 64) - 5, (game->pos_y * 64) - 5);
// 	}
// 	else
// 	{
// 		printf("Unknown key pressed: %d\n", keysym);
// 	}

// 	if (keysym == XK_Escape) /* ESC key */
// 	{
// 		mlx_destroy_window(game->mlx, game->win);
// 		exit(0);
// 	}
// 	/* Add other keypress handling as needed */
// 	return (0);
// }

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
	// game.mlx = mlx_init();
	// if (!game.mlx)
	// {
	// 	ft_putstr_fd("Error: Failed to initialize MiniLibX\n", STDERR_FILENO);
	// 	free_map(game.map);
	// 	return (1);
	// }
	// game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	// if (!game.win)
	// {
	// 	ft_putstr_fd("Error: Failed to create window\n", STDERR_FILENO);
	// 	free_map(game.map);
	// 	return (1);
	// }
	
	// mlx_hook(game.win, KeyPress, KeyPressMask, &handle_keypress, &game);
	// mlx_hook(game.win, DestroyNotify, StructureNotifyMask, &handle_close, &game);
	
	// mlx_loop(game.mlx);
	initialize_mlx(&game);
	free_map(game.map);
	return (0);
}


// make a 2D window with walls and player looking at a direction
// define the size of each square in the map and change color of the square based on type
