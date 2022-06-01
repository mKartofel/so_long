/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:16 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/01 11:16:15 by vfiszbin         ###   ########.fr       */
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
void move_player(int d_i, int d_j, t_vars *vars)
{
	int new_i;
	int new_j;

	new_i = vars->player_i + d_i;
	new_j = vars->player_j + d_j;

	if (new_i < 0 || new_j < 0 || new_i > (vars->map_height - 1) || new_j > (vars->map_width - 1))
	{
		ft_printf("You can't go out of map !\n");
		return ;
	}
	if (vars->map[(new_i * vars->map_width + new_i) + new_j] == '1')
	{
		ft_printf("An obstacle is in the way !\n");
		return ;
	}
	// ft_printf("initial case contains : %c\n", vars->map[(vars->player_i * vars->map_width + vars->player_i) + vars->player_j]);
	vars->map[(vars->player_i * vars->map_width + vars->player_i) + vars->player_j] = '0';
	mlx_put_image_to_window(vars->mlx, vars->win, vars->ground_img, vars->player_j * 50, vars->player_i * 50);	
	vars->player_i = new_i;
	vars->player_j = new_j;
	vars->map[(new_i * vars->map_width + new_i) + new_j] = 'P';
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img, new_j * 50, new_i * 50);
}

int	key_hook(int keycode, t_vars *vars)
{
	ft_printf("keycode = %d\n", keycode);
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
	vars->ground_img = mlx_xpm_file_to_image(vars->mlx, "grass.xpm", &img_width, &img_height); //proteger
	vars->wall_img = mlx_xpm_file_to_image(vars->mlx, "tree.xpm", &img_width, &img_height); //proteger

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
