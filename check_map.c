/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:51:39 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/02 11:05:17 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_count_pec(int *count_pec)
{
	count_pec[0] = 0;
	count_pec[1] = 0;
	count_pec[2] = 0;
}

void	count_pec_chars(int *count_pec, char c)
{
	if (c == 'P')
		count_pec[0]++;
	else if (c == 'E')
		count_pec[1]++;
	else if (c == 'C')
		count_pec[2]++;
}

/*Check if the map is completely surrounded by walls (char 1)
Access elements of 2D map contained in str : map[(i * map_width + k) + j]
i : height coordinate
j : width coordinate
k : offset to jump "\n" characters (==i)*/
void	check_walls(t_vars *vars)
{
	int	i;
	int	j;

	j = 0;
	while (j < vars->map_width)
	{
		if (vars->map[j] != '1' || vars->map[((vars->map_height - 1)
					* vars->map_width + (vars->map_height - 1)) + j] != '1')
			map_error("Error\nMap is not surrounded by walls", vars->map, NULL);
		j++;
	}
	i = 0;
	while (i < vars->map_height)
	{
		if (vars->map[(i * vars->map_width + i)] != '1' || vars->map[
				(i * vars->map_width + i) + (vars->map_width - 1)] != '1')
			map_error("Error\nMap is not surrounded by walls", vars->map, NULL);
		i++;
	}
}

void	check_first_line(t_vars *vars, int *i, int *count_pec, int *height)
{
	init_count_pec(count_pec);
	*i = 0;
	while (vars->map[*i] && vars->map[*i] != '\n')
	{
		count_pec_chars(count_pec, vars->map[*i]);
		*i = *i +1;
	}
	vars->map_width = *i;
	*height = 2;
}

/*Check if the map is valid.
Calculate the height and width of the map*/
void	check_map(t_vars *vars)
{
	int	i;
	int	j;
	int	height;
	int	count_pec[3];

	check_first_line(vars, &i, count_pec, &height);
	j = 0;
	while (vars->map[++i])
	{
		if (vars->map[i] == '\n')
		{
			height++;
			if (j != vars->map_width)
				map_error("Error\nMap is not rectangular", vars->map, NULL);
			j = -1;
		}
		count_pec_chars(count_pec, vars->map[i]);
		j++;
	}
	if (j != vars->map_width)
		map_error("Error\nMap is not rectangular", vars->map, NULL);
	vars->map_height = height;
	if (count_pec[0] != 1 || count_pec[1] == 0 || count_pec[2] == 0)
		map_error("Error\nIncorrect number of PEC chars", vars->map, NULL);
	check_walls(vars);
}
