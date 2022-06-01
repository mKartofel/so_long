/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:16 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/01 15:36:15 by vfiszbin         ###   ########.fr       */
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


/*Load the images for the game assets from the .xpm files*/
void load_images(t_vars *vars)
{
	int		img_width;
	int		img_height;

	vars->player_img = mlx_xpm_file_to_image(vars->mlx, "fox.xpm", &img_width, &img_height); //proteger
	vars->ground_img = mlx_xpm_file_to_image(vars->mlx, "grass.xpm", &img_width, &img_height); //proteger
	vars->wall_img = mlx_xpm_file_to_image(vars->mlx, "tree.xpm", &img_width, &img_height); //proteger
	vars->collectible_img = mlx_xpm_file_to_image(vars->mlx, "chicken.xpm", &img_width, &img_height); //proteger
	vars->exit_img = mlx_xpm_file_to_image(vars->mlx, "hole.xpm", &img_width, &img_height); //proteger
	vars->player_on_exit_img = mlx_xpm_file_to_image(vars->mlx, "fox_on_hole.xpm", &img_width, &img_height); //proteger
}

/*Draw the images to the correct coordinates on the window,
according to their position in the map string
Access elements of 2D map contained in str : map[(i * map_width + k) + j]
i : height coordinate
j : width coordinate
k : offset to jump "\n" characters (==i)*/
void draw_map(t_vars *vars)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (vars->map[(i * vars->map_width + i) + j])
	{
		// ft_printf("%c", vars->map[(i * vars->map_width + i) + j]);
		// ft_printf("i=%d j=%d\n", i, j);
		// ft_printf("el=%d\n", ((i * vars->map_width + i) + j));
		if (vars->map[(i * vars->map_width + i) + j] == 'P')
		{
			vars->player_i = i; //recup coordonnees avant lors de la verification de map ?
			vars->player_j = j;
			mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img, j * 50, i * 50);			
		}
		else if (vars->map[(i * vars->map_width + i) + j] == '0')
			mlx_put_image_to_window(vars->mlx, vars->win, vars->ground_img, j * 50, i * 50);
		else if (vars->map[(i * vars->map_width + i) + j] == '1')
			mlx_put_image_to_window(vars->mlx, vars->win, vars->wall_img, j * 50, i * 50);
		else if (vars->map[(i * vars->map_width + i) + j] == 'C')
		{
			vars->nb_collectibles++; //compter lors de verification map ?
			mlx_put_image_to_window(vars->mlx, vars->win, vars->collectible_img, j * 50, i * 50);
		}
		else if (vars->map[(i * vars->map_width + i) + j] == 'E')
			mlx_put_image_to_window(vars->mlx, vars->win, vars->exit_img, j * 50, i * 50);
		j++;
		if (vars->map[(i * vars->map_width + i) + j] == '\n')
		{
			i++;
			j = 0;
		}
	}
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
