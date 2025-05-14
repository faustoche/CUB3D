/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:06:44 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/14 15:26:31 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void open_door_near_player(t_mlx *mlx)
{
    int px = (int)(mlx->player->player_x / TILE_SIZE);
    int py = (int)(mlx->player->player_y / TILE_SIZE);
    
    // On regarde autour du joueur (haut, bas, gauche, droite)
    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };
    
    for (int i = 0; i < 4; i++) {
        int nx = px + dx[i];
        int ny = py + dy[i];
        
        if (nx >= 0 && ny >= 0 &&
            ny < mlx->game->height_map && nx < mlx->game->width_map &&
            mlx->game->map[ny][nx] == 'D') 
        {
                
            mlx->game->map[ny][nx] = 'D'; // on "ouvre" la porte // VOIR pourquoi la porte disparait et devient mur
            break;
        }
    }
}