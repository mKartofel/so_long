/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:16 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/05/30 11:51:16 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"


#include<stdio.h> //ENLEVER
#include <stdlib.h>

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }	t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

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

int	key_hook(int keycode, t_vars *vars)
{
	printf("keycode = %d\n", keycode);
	if (keycode == 65307)
		close_program(vars);
	return (0);
}


int	main(void)
{
	// void	*mlx;
	// void	*mlx_win;
	// t_data	img;
	t_vars vars;

	int		img_width;
	int		img_height;

	// vars = malloc(sizeof(t_vars));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 400, "Hello world!");

	// img.img = mlx_new_image(vars.mlx, img_width, img_height);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);

	void * img = mlx_xpm_file_to_image(vars.mlx, "fox.xpm", &img_width, &img_height); //proteger
	printf("%d %d\n",img_width, img_height);
	
	mlx_put_image_to_window(vars.mlx, vars.win, img, 50, 50);

	// mlx_hook(vars.win, 2, 1L<<0, close_program, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	
	mlx_loop(vars.mlx);

	printf("Cokkadoodle\n");
}
