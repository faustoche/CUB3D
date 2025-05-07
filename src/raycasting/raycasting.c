/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:42:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/07 16:25:04 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Calcule la distance entre le joueur et un mur qu'il pourrait rencontrer en traçant une ligne
* horizontale à partir de sa position, en fonction d'un angle donné. 
*/
static float	find_horizontal_hit_distance(t_mlx *mlx, float angle) // get h inter
{
	float	horizontal_x; // stocke les coordonnees du point d;intersection
	float	horizontal_y;
	float	x_step; // defini increment des coordonnees  en fonction de l'angle
	float	y_step;
	int		pixel; // pixel d'intersection pour check si ;ur

	y_step = TILE_SIZE; // taille de chaque tuile
	x_step = TILE_SIZE / tan(angle); // taille de l'increment pour la proj du rayon a chaque pas. tan aide a determiner l'influence de l'angle sur le deplacement
	horizontal_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE; // trouve la coordonnee y la plus proche
	pixel = init_ray_direction(angle, &horizontal_y, &y_step, 1); //est-ce que le rayon rentre en contact avec qqchose
	horizontal_x = mlx->player->player_x + (horizontal_y - mlx->player->player_y) / tan(angle); // 
	if ((check_angle_direction(angle, 'y') && x_step > 0) || (!check_angle_direction(angle, 'y') && x_step < 0)) // check valeur de x step
		x_step *= -1;
	while (is_wall(horizontal_x, horizontal_y - pixel, mlx)) // check si on heurte un mur avec la valeur du pixel
	{
		horizontal_x += x_step;
		horizontal_y += y_step;
	}
	return (sqrt(pow(horizontal_x - mlx->player->player_x, 2) + pow(horizontal_y - mlx->player->player_y, 2))); // pour recuperer la distance avec formule de la distance euclidienne
}

static float	find_vertical_hit_distance(t_mlx *mlx, float angle) // get h inter
{
	float	vertical_x; // stocke les coordonnees du point d;intersection
	float	vertical_y;
	float	x_step; // defini increment des coordonnees  en fonction de l'angle
	float	y_step;
	int		pixel; // pixel d'intersection pour check si ;ur

	x_step = TILE_SIZE; // taille de chaque tuile
	y_step = TILE_SIZE / tan(angle); // taille de l'increment pour la proj du rayon a chaque pas. tan aide a determiner l'influence de l'angle sur le deplacement
	vertical_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE; // trouve la coordonnee y la plus proche
	pixel = init_ray_direction(angle, &vertical_x, &x_step, 0); //est-ce que le rayon rentre en contact avec qqchose
	vertical_y = mlx->player->player_y + (vertical_x - mlx->player->player_x) * tan(angle); // 
	if ((check_angle_direction(angle, 'x') && y_step < 0) || (!check_angle_direction(angle, 'x') && y_step > 0)) // check valeur de x step
		y_step *= -1;
	while (is_wall(vertical_x - pixel, vertical_y, mlx)) // check si on heurte un mur avec la valeur du pixel
	{
		vertical_x += x_step;
		vertical_y += y_step;
	}
	return (sqrt(pow(vertical_x - mlx->player->player_x, 2) + pow(vertical_y - mlx->player->player_y, 2))); // pour recuperer la distance avec formule de la distance euclidienne
}

/* Cette fonction affiche les rayons en entonnoir */

// void	cast_rays(t_mlx *mlx)
// {
// 	double	horizontal_inter;
// 	double	vertical_inter;
// 	int		ray;

// 	ray = 0;
// 	mlx->ray->ray_angle = mlx->player->angle - (mlx->player->fov_rd / 2); // l'angle de debut
// 	while (ray < WIDTH) // loop
// 	{
// 		mlx->ray->flag = 0;
// 		horizontal_inter = find_horizontal_hit_distance(mlx, angle_to_radians(mlx->ray->ray_angle));
// 		vertical_inter = find_vertical_hit_distance(mlx, angle_to_radians(mlx->ray->ray_angle));
// 		if (vertical_inter <= horizontal_inter)
// 		{
// 			mlx->ray->distance = vertical_inter;
// 			mlx->ray->flag = 1;
// 		}
// 		else
// 		{
// 			mlx->ray->distance = horizontal_inter;
// 			mlx->ray->flag = 0;
// 		}
// 		render_wall(mlx, ray);
// 		ray++;
// 		mlx->ray->ray_angle += (mlx->player->fov_rd / WIDTH);
// 	}
// }


/* Cette fonction affiche les rayons en ligne droite donc pas de murs */

void	cast_rays(t_mlx *mlx)
{
	double	horizontal_inter;
	double	vertical_inter;
	//double	camera_x;
	double	angle;
	int		ray;
	
	angle = mlx->player->angle - (mlx->player->fov_rd / 2.0);
	ray = 0;
	// camera_x = (2 * ray / (double)WIDTH) - 1; // pourquoi ce calcul ?
	// mlx->ray->ray_angle = mlx->player->angle + atan(camera_x * tan(mlx->player->fov_rd / 2));
	while (ray < WIDTH) // loop
	{
		mlx->ray->flag = 0;
		horizontal_inter = find_horizontal_hit_distance(mlx, angle_to_radians(mlx->ray->ray_angle));
		vertical_inter = find_vertical_hit_distance(mlx, angle_to_radians(mlx->ray->ray_angle));	
		if (vertical_inter <= horizontal_inter)
		{
			mlx->ray->distance = vertical_inter;
			mlx->ray->flag = 1;
		}
		else
		{
			mlx->ray->distance = horizontal_inter;
			mlx->ray->flag = 0;
		}
		render_wall(mlx, ray);
		angle += mlx->player->fov_rd / (double)WIDTH; // chaque rayon a un angle legerement different pour correspondre a la position horizontale dans la fenetre
		ray++;
	}
}
