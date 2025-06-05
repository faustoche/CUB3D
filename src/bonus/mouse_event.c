/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:51:19 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/05 15:20:41 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Permet d'utiliser la souris pour la rotation du point de vue
* delta_x = variation
* Event mouse = 6 soit Motion notify -> to check
* mlx->player->angle += delta_x * ROTATION_SPEED; 
verifier si la rotatopn speed est correcte
		angle_to_radians(mlx->player->angle); // normaliser l'angle
	}
	last_x = x; // last x recuperer le dernier moment de la derniere frame
*/

int	mouse_handler(int x, int y, void *param)
{
	t_mlx		*mlx;
	static int	last_x = -1;
	int			delta_x;

	mlx = (t_mlx *)param;
	(void)y;
	if (last_x != -1)
	{
		delta_x = x - last_x;
		mlx->player->angle += delta_x * ROTATION_SPEED;
		angle_to_radians(mlx->player->angle);
	}
	last_x = x;
	return (0);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/// COMMENT GÉRER LES SAUTS BRUSQUES AVEC LA SOURIS ?? ///
/// Au premier appel de la fonction (ouverture du jeu) on ne 
/// connait pas la position de la souris. Si on fait le calcul directement
/// on se retrouve avec une variable non adapté ce qui peut provoquer un saut
/// brusque avec la souris

int	mouse_handler_jump(int x, int y, void *param)
{
	t_mlx		*mlx;
	static int	last_x = -1;
	static int	initialized = 0; // est-ce que c'est le premier appel oui ou non
	int			delta_x;

	mlx = (t_mlx *)param;
	(void)y;
	if (!initialized) // si initialized est a 0 au premier appel
	{
		last_x = x; // on sauvegarde la position actuelle
		initialized = 1; // on marque comme etant deja appelé
		return (0); // on sort sans RIEN faire
	}
	delta_x = x - last_x; // calcul du deplacement sur l'horizon
	if (ft_abs(delta_x) < 100) // raisonnabilite du mouvement, 
	{
		mlx->player->angle += delta_x * ROTATION_SPEED;
		angle_to_radians(mlx->player->angle); // normalisation de l'angle
	}
	last_x = x; // position actuelle de la souris pour le prcohain appel
	return (0);
}
