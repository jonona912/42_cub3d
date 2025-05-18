#include "main_header.h"


int main(int argc, char **argv)
{
	t_game game;

	ft_memset(&game, 0, sizeof(t_game));
	// game.textures_info.n_wall_path = "textures/purplestone.xpm";
	// game.textures_info.w_wall_path = "textures/colorstone.xpm";
	// game.textures_info.s_wall_path = "textures/greystone.xpm";
	// game.textures_info.e_wall_path = "textures/mossy.xpm";
	// game.textures_info.width = 0;
	// game.textures_info.height = 0;
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3d map_file\n", STDERR_FILENO);
		return (1);
	}
	// game.map = validate_map(argv[1]);
	if (extract_map_info(argv[1], &game) == -1)
	{
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
		return (1);
	}
	if (!game.map)
	{
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
		return (1);
	}
	print_map(game.map);
	initialize_mlx(&game);
	free_map(game.map);
	return (0);
}


// make a 2D window with walls and player looking at a direction
// define the size of each square in the map and change color of the square based on type
