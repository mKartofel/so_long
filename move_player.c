/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:35:01 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/02 11:27:37 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	redraw_begin_tile(t_vars *vars)
{
	if (vars->map[(vars->player_i * vars->map_width + vars->player_i)
			+ vars->player_j] == 'E')
	{
		vars->map[(vars->player_i * vars->map_width + vars->player_i)
			+ vars->player_j] = 'E';
		mlx_put_image_to_window(vars->mlx, vars->win, vars->exit_img,
			vars->player_j * 50, vars->player_i * 50);
	}
	else
	{
		vars->map[(vars->player_i * vars->map_width + vars->player_i)
			+ vars->player_j] = '0';
		mlx_put_image_to_window(vars->mlx, vars->win, vars->ground_img,
			vars->player_j * 50, vars->player_i * 50);
	}
}

void	redraw_end_tile(t_vars *vars, int new_i, int new_j)
{
	if (vars->map[(new_i * vars->map_width + new_i) + new_j] == 'E')
	{
		vars->map[(new_i * vars->map_width + new_i) + new_j] = 'E';
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player_on_exit_img,
			new_j * 50, new_i * 50);
	}
	else
	{
		vars->map[(new_i * vars->map_width + new_i) + new_j] = 'P';
		mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img,
			new_j * 50, new_i * 50);
	}
}

/*
		 (-1,0)
			^
			|
			|
(0,-1)<---P(i,j)--->(0,+1)
			|
			|
			ˇ
		  (+1,0)

*/
void	move_player(int d_i, int d_j, t_vars *vars)
{
	int	new_i;
	int	new_j;

	new_i = vars->player_i + d_i;
	new_j = vars->player_j + d_j;
	if (new_i < 0 || new_j < 0 || new_i > (vars->map_height - 1) || new_j
		> (vars->map_width - 1))
		return ;
	if (vars->map[(new_i * vars->map_width + new_i) + new_j] == '1')
		return ;
	if (vars->map[(new_i * vars->map_width + new_i) + new_j] == 'C')
		vars->nb_collectibles--;
	redraw_begin_tile(vars);
	vars->player_i = new_i;
	vars->player_j = new_j;
	redraw_end_tile(vars, new_i, new_j);
	vars->movements++;
	if (vars->map[(new_i * vars->map_width + new_i) + new_j] == 'E'
		&& vars->nb_collectibles == 0)
	{
		ft_printf("The end.\nFinal number of movements : %d\n", vars->movements);
		close_program(vars);
	}
	else
		ft_printf("Movements : %d\n", vars->movements);
}

/*Map key_codes to functions*/
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_program(vars);
	else if (keycode == 119)
		move_player(-1, 0, vars);
	else if (keycode == 115)
		move_player(1, 0, vars);
	else if (keycode == 97)
		move_player(0, -1, vars);
	else if (keycode == 100)
		move_player(0, 1, vars);
	return (0);
}
