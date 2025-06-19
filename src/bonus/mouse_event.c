/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:51:19 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/19 10:44:23 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Absolute of int */

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/* 
** Handle mouse movement and sensitivity (with 500)
** pOURQUOI 500?
*/

int	mouse_handler(int x, int y, void *param)
{
	t_mlx		*mlx;
	static int	last_x = -1;
	static int	initialized = 0;
	int			delta_x;

	mlx = (t_mlx *)param;
	(void)y;
	if (!initialized)
	{
		last_x = x;
		initialized = 1;
		return (0);
	}
	delta_x = x - last_x;
	if (ft_abs(delta_x) < 500)
	{
		mlx->player->angle += delta_x * MOUSE_ROTATION_SPEED;
		angle_to_radians(mlx->player->angle);
	}
	last_x = x;
	return (0);
}

int	mouse_leave(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	return (0);
}
