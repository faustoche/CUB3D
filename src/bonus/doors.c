/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:20:34 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/24 09:42:53 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// DIFFICULTÉ À OUVRIR LES PORTES
/// EST-CE QU'ON PASSERAIT PAS DE 1 À 2 ?
/// POURQUOI LA PORTE DISPARAIT QUAND JE LA TRAVERSE ?
/// la porte disparait pas, il n'y a juste pas de texture pour la porte ouverte
/// 2 TEXTURES DIFFERENTES POUR LA PORTE À TROUVER : OUVERTE/FERMÉE


void open_door_near_player(t_mlx *mlx)
{
	int px = (int)(mlx->player->player_x / TILE_SIZE);
	int py = (int)(mlx->player->player_y / TILE_SIZE);
	
	// On regarde autour du joueur (haut, bas, gauche, droite)
	// deux cases sinon c'est compliqué d'ouvrir les portes
	int dx[] = { 0, 2, 0, -2 };
	int dy[] = { -2, 0, 2, 0 };
	
	for (int i = 0; i < 4; i++) {
		int nx = px + dx[i];
		int ny = py + dy[i];
		
		if (nx >= 0 && ny >= 0 &&
			ny < mlx->game->height_map && nx < mlx->game->width_map &&
			mlx->game->map[ny][nx] == 'D') 
		{
				
			mlx->game->map[ny][nx] = 'D';
			break;
		}
	}
}