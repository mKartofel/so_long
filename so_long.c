/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:16 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/01 18:48:39 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }	t_data;


// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

int	close_program(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	mlx_destroy_window(vars->mlx, vars->win);
	// exit(1); //changer par un mlx_loop_end ?
	return (0);
}

int	main(void)
{
	t_vars vars;

	vars.movements = 0;
	vars.nb_collectibles = 0;

	vars.map = read_map("map2.ber");
	ft_printf("%s\n", vars.map );
	check_map(&vars);
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map_width * 50, vars.map_height * 50, "so_long");

	load_images(&vars);
	draw_map(&vars);

	mlx_key_hook(vars.win, key_hook, &vars);
	
	mlx_loop(vars.mlx);

	ft_printf("Cokkadoodle\n");
}
