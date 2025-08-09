/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 09:00:39 by mpazouki          #+#    #+#             */
/*   Updated: 2025/06/06 10:04:25 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

static int	is_valid_texture_path(t_game *game, const char *path)
{
	int	fd;
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		printf("Error: Invalid texture extension for '%s'. Must be .xpm\n",
			path);
		free_game(game);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("\033[31mError: Invalid texture path for '%s'\033[0m\n",
			path);
		free_game(game);
		return (0);
	}
	close(fd);
	return (1);
}

static int	set_texture_path(t_game *game, char **dest, int *flag,
		const char *path)
{
	if (++(*flag) > 1)
	{
		printf("\033[31mError: Duplicate directive\033[0m\n");
		return (0);
	}
	if (!is_valid_texture_path(game, path))
	{
		return (0);
	}
	if (!dest)
	{
		printf("\033[31mError: Null pointer for path\033[0m\n");
		return (0);
	}
	*dest = ft_strdup(path);
	if (!*dest)
	{
		printf("\033[31mError: Failed to allocate memory for path\033[0m\n");
		return (0);
	}
	return (1);
}

int	handle_texture_directive(t_game *game, const char *key, const char *path)
{
	if (!ft_strcmp(key, "NO"))
		return (set_texture_path(game, &game->textures_info.n_wall_path,
				&game->textures_info.has_no, path));
	else if (!ft_strcmp(key, "SO"))
		return (set_texture_path(game, &game->textures_info.s_wall_path,
				&game->textures_info.has_so, path));
	else if (!ft_strcmp(key, "WE"))
		return (set_texture_path(game, &game->textures_info.w_wall_path,
				&game->textures_info.has_we, path));
	else if (!ft_strcmp(key, "EA"))
		return (set_texture_path(game, &game->textures_info.e_wall_path,
				&game->textures_info.has_ea, path));
	printf("Error: Unknown texture key: %s\n", key);
	return (0);
}
