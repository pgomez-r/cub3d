/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfredes- <gfredes-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:12:12 by gfredes-          #+#    #+#             */
/*   Updated: 2024/07/03 19:07:47 by gfredes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_width(char *line, t_info_map *info_map)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t')
			i++;
		else if (line[i] == '1' || line[i] == '0' || line[i] == 'W'
			|| line[i] == 'N' || line[i] == 'E' || line[i] == 'S')
		{
			if (line[i] == 'W' || line[i] == 'N' || line[i] == 'E'
				|| line[i] == 'S')
			{
				info_map->player += 1;
				info_map->player_view = line[i];
			}
			i++;
			width = i;
		}
	}
	if (width > info_map->map_width)
		info_map->map_width = width;
}

void	get_map_size(int fd, t_info_map *info_map)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_line_map(line, 0))
		{
			count++;
			get_width(line, info_map);
		}
		free (line);
	}
	info_map->map_height = count;
	info_map->map = (char **)malloc(sizeof(char *) * info_map->map_height);
	if (!info_map->map)
	{
		write(2, "Error: Memory allocation failled\n", 33);
		exit(1);
	}
	else if (info_map->player != 1)
		invalid_map(1);
}
