/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfredes- <gfredes-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:32:47 by gfredes-          #+#    #+#             */
/*   Updated: 2024/06/30 16:33:42 by gfredes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file_name(char *argv)
{
	int	i;

	i = ft_strlen(argv) - 1;
	if (argv[i] == 'b' && argv[i - 1] == 'u' && argv[i - 2] == 'c'
		&& argv[i - 3] == '.')
		return (1);
	return (0);
}

void	check_args(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		write(2, "Error: Wrong number of arguments\n", 33);
		printf("Usage: ./cub3d <map_name>.cub\n");
		exit(1);
		return ;
	}
	fd = open(argv[1], O_RDONLY);
	close(fd);
	if (fd < 0 || !check_file_name(argv[1]))
	{
		write(2, "Error: Invalid file\n", 20);
		printf("Usage: ./cub3d <map_name>.cub\n");
		exit(1);
	}
	return ;
}