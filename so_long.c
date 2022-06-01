/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:16 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/01 15:39:52 by vfiszbin         ###   ########.fr       */
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


/*Calculate the height and width of the map*/
void get_map_height_and_width(t_vars *vars)
{
	int i;
	int height;
	
	i = 0;
	while (vars->map[i] && vars->map[i] != '\n')
		i++;
	vars->map_width = i;
	ft_printf("width = %d\n", vars->map_width);
	height = 1;
	while (vars->map[i])
	{
		if (vars->map[i] == '\n')
			height++;
		i++;
	}
	vars->map_height = height;
	ft_printf("height = %d\n", vars->map_height);
}


int	main(void)
{
	// t_data	img;
	t_vars vars;

	vars.movements = 0;
	vars.nb_collectibles = 0;

	vars.map = read_map("map.ber");
	ft_printf("%s\n", vars.map );
	get_map_height_and_width(&vars);

	// vars = malloc(sizeof(t_vars));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map_width * 50, vars.map_height * 50, "so_long");

	// img.img = mlx_new_image(vars.mlx, img_width, img_height);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);

	load_images(&vars);
	draw_map(&vars);

	mlx_key_hook(vars.win, key_hook, &vars);
	
	mlx_loop(vars.mlx);

	ft_printf("Cokkadoodle\n");
}
