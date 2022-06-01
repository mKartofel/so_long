/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:25:26 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/01 10:24:27 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"

// #include <stdio.h> //ENLEVER
#include <stdlib.h>
#include <fcntl.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	void	*player_img;
	void	*ground_img;
	char 	*map;
	int		map_width;
	int		map_height;
	int		player_i;
	int		player_j;
}	t_vars;

void draw_map(t_vars *vars);

#endif