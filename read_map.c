/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:32:34 by vfiszbin          #+#    #+#             */
/*   Updated: 2022/06/02 09:56:28 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void map_error(char *error_msg, char *line, char *new_line)
{
	ft_putendl_fd(error_msg, 2);
	if (line != NULL)
		free(line);
	if (new_line != NULL)
		free(new_line);
	exit(1);
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
		map_error("Error\nget_next_line failed", NULL, NULL);
	read = 1;
	while(read != 0)
	{
		new_line = get_next_line(fd);
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
	close(fd);
	return line;
}
