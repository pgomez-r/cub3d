/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:12:36 by codespace         #+#    #+#             */
/*   Updated: 2024/06/28 15:23:41 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_hook(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (d->exit_code == 0)
	{
		key_control(d);
		update_minimap(d);
	}
}

int	main(void)
{
	t_data	d;

	ft_init(&d);
	if (d.exit_code == 0)
	{
		d.game = mlx_init(WIDTH, HEIGTH, "CVB3D", false);
		ft_load_images(&d);
		//render_map(&st);
		//create_minipmap(&st);
		mlx_loop_hook(st.game, game_hook, &st);
		mlx_loop(st.game);
		mlx_terminate(st.game);
	}
	return (0);
}
