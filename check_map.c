/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:51:39 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/02 10:21:03 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_count_PEC(int *count_PEC)
{
	count_PEC[0] = 0;
	count_PEC[1] = 0;
	count_PEC[2] = 0;
}

void count_PEC_chars(int *count_PEC, char c)
{
	if (c == 'P')
		count_PEC[0]++;
	else if (c == 'E')
		count_PEC[1]++;
	else if (c == 'C')
		count_PEC[2]++;
}

/*Check if the map is completely surrounded by walls (char 1)
Access elements of 2D map contained in str : map[(i * map_width + k) + j]
i : height coordinate
j : width coordinate
k : offset to jump "\n" characters (==i)*/
void check_walls(t_vars *vars)
{
	int i;
	int j;

	j = 0;
	while (j < vars->map_width)
	{
		if (vars->map[j] != '1' || vars->map[((vars->map_height - 1) * vars->map_width + (vars->map_height - 1)) + j] != '1')
			map_error("Error\nMap is not surrounded by walls", vars->map, NULL);
		j++;
	}
	i = 0;
	while(i < vars->map_height)
	{
		if (vars->map[(i * vars->map_width + i)] != '1' || vars->map[(i * vars->map_width + i) + (vars->map_width - 1)] != '1')
			map_error("Error\nMap is not surrounded by walls", vars->map, NULL);
		i++;
	}
}

/*Check if the map is valid.
Calculate the height and width of the map*/
void check_map(t_vars *vars)
{
	int i;
	int j;
	int height;
	int count_PEC[3];

	init_count_PEC(count_PEC);
	i = 0;
	while (vars->map[i] && vars->map[i] != '\n')
	{
		count_PEC_chars(count_PEC, vars->map[i]);
		i++;
	}
	vars->map_width = i;
	ft_printf("width = %d\n", vars->map_width);
	i++;
	height = 2;
	j = 0;
	while (vars->map[i])
	{
		if (vars->map[i] == '\n')
		{
			height++;
			// printf("j=%d width=%d\n", j, vars->map_width);
			if (j != vars->map_width)
				map_error("Error\nMap is not rectangular", vars->map, NULL);
			j = -1;
		}
		count_PEC_chars(count_PEC, vars->map[i]);
		i++;
		j++;
	}
	ft_printf("j=%d width=%d\n", j, vars->map_width);
	if (j != vars->map_width)
		map_error("Error\nMap is not rectangular", vars->map, NULL);
	vars->map_height = height;
	ft_printf("height = %d\n", vars->map_height);

	if (count_PEC[0] != 1 || count_PEC[1] == 0 || count_PEC[2] == 0)
		map_error("Error\nMap does not have the right number of PEC chars", vars->map, NULL);

	check_walls(vars);
}