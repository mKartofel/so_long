/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:16 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/02 11:40:14 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_program(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	free_vars(vars);
	exit(1);
}

void	free_vars(t_vars *vars)
{
	free(vars->map);
	if (vars->player_img != NULL)
		mlx_destroy_image(vars->mlx, vars->player_img);
	if (vars->ground_img != NULL)
		mlx_destroy_image(vars->mlx, vars->ground_img);
	if (vars->wall_img != NULL)
		mlx_destroy_image(vars->mlx, vars->wall_img);
	if (vars->collectible_img != NULL)
		mlx_destroy_image(vars->mlx, vars->collectible_img);
	if (vars->exit_img != NULL)
		mlx_destroy_image(vars->mlx, vars->exit_img);
	if (vars->player_on_exit_img != NULL)
		mlx_destroy_image(vars->mlx, vars->player_on_exit_img);
	if (vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx != NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
}

void	init_vars_struct(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->player_img = NULL;
	vars->ground_img = NULL;
	vars->wall_img = NULL;
	vars->collectible_img = NULL;
	vars->exit_img = NULL;
	vars->player_on_exit_img = NULL;
	vars->map = NULL;
	vars->map_width = 0;
	vars->map_height = 0;
	vars->player_i = 0;
	vars->player_j = 0;
	vars->movements = 0;
	vars->nb_collectibles = 0;
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2 || ft_strrchr(argv[1], '.') == NULL || ft_strncmp(
			ft_strrchr(argv[1], '.'), ".ber", ft_strlen(argv[1])) != 0)
	{
		ft_putendl_fd("Error\nProgram usage : ./so_long <map_path>.ber", 2);
		exit(1);
	}
	init_vars_struct(&vars);
	vars.map = read_map(argv[1]);
	check_map(&vars);
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		close_program(&vars);
	vars.win = mlx_new_window(vars.mlx, vars.map_width * 50,
			vars.map_height * 50, "so_long");
	if (vars.win == NULL)
		close_program(&vars);
	load_images(&vars);
	draw_map(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 33, 1L << 5, close_program, &vars);
	mlx_loop(vars.mlx);
	free_vars(&vars);
}
