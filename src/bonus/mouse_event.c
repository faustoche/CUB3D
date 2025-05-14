/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:51:19 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/14 15:42:47 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Permet d'utiliser la souris pour la rotation du point de vue
* delta_x = variation
* Event mouse = 6 soit Motion notify -> to check
* Peut-être ajouter le leave notify pour éviter le débordement de l'écran qqpart ?
*/

int	mouse_handler(int x, int y, void *param)
{
	t_mlx		*mlx;
	static int	last_x;
	int			delta_x;

	mlx = (t_mlx *)param;
	(void)y;
	last_x = -1;
	if (last_x != -1)
	{
		delta_x = x - last_x;
		mlx->player->angle += delta_x * ROTATION_SPEED; // verifier si la rotatopn speed est correcte
		angle_to_radians(mlx->player->angle); // normaliser l'angle
	}
	last_x = x; // last x recuperer le dernier moment de la derniere frame
	return (0);
}
