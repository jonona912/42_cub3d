/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:25:35 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/05/20 13:27:26 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_header.h"

void	clear_screen(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	pixel;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		pixel = (y * game->size_line) + (x * (game->bpp / 8));
		*(unsigned int *)(game->img_data + pixel) = color;
	}
}

void	print_ceiling_floor(t_game *game)
{
	int	i;
	int	j;
	int	half_height;

	i = 0;
	half_height = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (i > half_height)
				put_pixel(game, j, i, game->textures_info.floor_color);
			else
				put_pixel(game, j, i, game->textures_info.ceiling_color);
			j++;
		}
		i++;
	}
}
