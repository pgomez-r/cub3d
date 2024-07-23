/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 06:56:52 by pgruz11           #+#    #+#             */
/*   Updated: 2024/07/23 06:57:23 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_mov_validation(t_data *d, int mov_x, int mov_y)
{
	if (d->maps.map[(mov_y - OFFSET) / CELL][(mov_x - OFFSET) / CELL] == '1')
		return (1);
	if (d->maps.map[(mov_y - OFFSET) / CELL][(mov_x + OFFSET) / CELL] == '1')
		return (1);
	if (d->maps.map[(mov_y + OFFSET) / CELL][(mov_x - OFFSET) / CELL] == '1')
		return (1);
	if (d->maps.map[(mov_y + OFFSET) / CELL][(mov_x + OFFSET) / CELL] == '1')
		return (1);
	return (0);
}

float	ft_normalize_angle(float angle)
{
	if (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
