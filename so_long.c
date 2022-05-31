/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:16 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/05/31 12:05:59 by vfiszbin         ###   ########.fr       */
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

void map_error(char *error_msg, char *line, char *new_line)
{
	ft_putendl_fd(error_msg, 2);
	if (line != NULL)
		free(line);
	if (new_line != NULL)
		free(new_line);
	exit(1);
}

int	close_program(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	mlx_destroy_window(vars->mlx, vars->win);
	// exit(1); //changer par un mlx_loop_end ?
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	ft_printf("keycode = %d\n", keycode);
	if (keycode == 65307)
		close_program(vars);
	
	return (0);
}

/*Read the map contained in filename. Return
a string representing the map*/
char *read_map(char *filename)
{
	char *line;
	char *new_line;
	char *tmp;
	int fd;
	int read;

	fd = open(filename, O_RDONLY);
	if (!fd)
		map_error("Error\nCould not open file", NULL, NULL);
	line = get_next_line(fd);
	if (!line)
		map_error("Error\nget_next_line failed1", NULL, NULL);
	read = 1;
	while(read != 0)
	{
		new_line = get_next_line(fd); //pas prot en cas d'erreur, probleme ?
		if (!new_line)
			read = 0;
		else
		{
			tmp = line;
			line = ft_strjoin(line, new_line);
			if (!line)
				map_error("Error\nft_strjoin failed", line, new_line);
			free(tmp);
			free(new_line);
		}
	}
	return line;
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
	ft_printf("%d %d\n",img_width, img_height);
}

/*Access elements of 2D map contained in str : *(map + i * N + j) */

/*Draw the images to the correct coordinates on the window,
according to their position in the map string*/
void draw_map(t_vars *vars)
{
	int i;
	int j;
	int k;
	
	i = 0;
	j = 0;
	k = 0;
	while (vars->map[(i * vars->map_width + k) + j])
	{
		ft_printf("%c", vars->map[(i * vars->map_width + k) + j]);
		// ft_printf("i=%d j=%d\n", i, j);
		// ft_printf("el=%d\n", ((i * vars->map_width + k) + j));
		j++;
		if (vars->map[(i * vars->map_width + k) + j] == '\n'){
			i++;
			k++;
			j = 0;
		}
	}
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img, 50, 50);
}


int	main(void)
{
	// t_data	img;
	t_vars vars;

	vars.map = read_map("map.ber");
	ft_printf("%s\n", vars.map );
	get_map_height_and_width(&vars);

	// vars = malloc(sizeof(t_vars));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 600, 400, "Hello world!");

	// img.img = mlx_new_image(vars.mlx, img_width, img_height);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);

	load_images(&vars);
	draw_map(&vars);

	// mlx_hook(vars.win, 2, 1L<<0, close_program, &vars);
	// mlx_key_hook(vars.win, key_hook, &vars);
	
	// mlx_loop(vars.mlx);

	// ft_printf("Cokkadoodle\n");
}
