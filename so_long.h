/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:25:26 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/05/31 10:05:16 by vfiszbin         ###   ########.fr       */
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
	char 	*map;
	int		map_width;
	int		map_height;
}	t_vars;


#endif