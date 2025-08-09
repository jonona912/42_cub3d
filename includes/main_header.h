/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkhojazo <zkhojazo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:46:38 by zkhojazo          #+#    #+#             */
/*   Updated: 2025/06/06 11:31:04 by zkhojazo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HEADER_H
# define MAIN_HEADER_H
# include "libft.h"
# include "get_next_line.h"
# include "map_validation.h"
# include "map_creation.h"
# include <stdbool.h>

# include <mlx.h>

// print_debugging_fts.c
void	print_map(char **map);
int		cast_rays(t_game *game, double dir_angle, double *first_cross_dist);

#endif
