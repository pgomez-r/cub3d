/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfredes- <gfredes-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:53:25 by gfredes-          #+#    #+#             */
/*   Updated: 2024/07/03 21:48:03 by gfredes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_invalid_map(int mode)
{
	if (mode == 1)
	{
		write (2, "Error: Invalid map\n", 19);
		exit (1);
	}
}
