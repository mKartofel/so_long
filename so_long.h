/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:25:26 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/01 15:36:19 by vfiszbin         ###   ########.fr       */
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
	void	*wall_img;
	void	*collectible_img;
	void	*exit_img;
	void	*player_on_exit_img;
	char 	*map;
	int		map_width;
	int		map_height;
	int		player_i;
	int		player_j;
	int		movements;
	int		nb_collectibles;

}	t_vars;

void draw_map(t_vars *vars);
char *read_map(char *filename);
int	close_program(t_vars *vars);
void map_error(char *error_msg, char *line, char *new_line);
void move_player(int d_i, int d_j, t_vars *vars);
int	key_hook(int keycode, t_vars *vars);

#endif