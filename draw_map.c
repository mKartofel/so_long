/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:39:11 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/02 10:12:26 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*Load the images for the game assets from the .xpm files*/
void load_images(t_vars *vars)
{
	int		img_width;
	int		img_height;


	vars->player_img = mlx_xpm_file_to_image(vars->mlx, "images/fox.xpm", &img_width, &img_height);
	if (vars->player_img == NULL)
		close_program(vars);
	vars->ground_img = mlx_xpm_file_to_image(vars->mlx, "images/grass.xpm", &img_width, &img_height);
	if (vars->ground_img == NULL)
		close_program(vars);
	vars->wall_img = mlx_xpm_file_to_image(vars->mlx, "images/tree.xpm", &img_width, &img_height);
	if (vars->wall_img == NULL)
		close_program(vars);
	vars->collectible_img = mlx_xpm_file_to_image(vars->mlx, "images/chicken.xpm", &img_width, &img_height);
	if (vars->collectible_img == NULL)
		close_program(vars);
	vars->exit_img = mlx_xpm_file_to_image(vars->mlx, "images/hole.xpm", &img_width, &img_height);
	if (vars->exit_img == NULL)
		close_program(vars);
	vars->player_on_exit_img = mlx_xpm_file_to_image(vars->mlx, "images/fox_on_hole.xpm", &img_width, &img_height);
	if (vars->player_on_exit_img == NULL)
		close_program(vars);
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