/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:39:36 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/19 12:01:07 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

/*-------------- LIBRARIES --------------*/

# include "cub3d.h"

/*--------------- DEFINES ---------------*/

# define EVENT_MOUSE_CODE 6
# define MINIMAP_SIZE 200
# define MINIMAP_TILE 10
# define MINIMAP_RADIUS 15
# define MINIMAP_RADIUS_X 15
# define MINIMAP_RADIUS_Y 9
# define WALL_COLOR     0x004400 // Vert foncé
# define FLOOR_COLOR    0x228B22 // Vert jungle
# define PLAYER_COLOR   0xFFD700 // Jaune
# define RAY_COLOR      0xFF4500 // Orange
# define EMPTY_COLOR    0x222222 // Gris
# define BORDER_COLOR   0x8B0000 // Rouge

/*------------- STRUCTURES --------------*/

typedef struct s_minimap
{
	t_mlx		*mlx;
	int			py;
	int			px;
	int			origin_x;
	int			origin_y;
	int			player_tile_x;
	int			player_tile_y;
	int			center_x;
	int			center_y;
	int			color;
	double		ray_x;
	double		ray_y;
	double		dx;
	double		dy;
}	t_minimap;

/*-------------- FUNCTIONS --------------*/

/// BONUS ///
// doors.c
void		open_door_near_player(t_mlx *mlx);

// minimap_draw1-2.c
void		draw_minimap(t_mlx *mlx);
void		draw_minimap_player(t_minimap *mini);
int			choose_color(char tile);
int			get_tile_color(t_minimap *mini, int map_x, int map_y);

// minimap_rays.c
void		draw_direction_ray(t_minimap *mini, double angle);

// mouse_event.c
int			mouse_handler(int x, int y, void *param);
int			mouse_leave(int keycode, void *param);

#endif