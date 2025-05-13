/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:42:46 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/13 12:06:59 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Calcule la distance entre le joueur et un mur qu'il pourrait rencontrer en traçant une ligne
* horizontale à partir de sa position, en fonction d'un angle donné. 
*/
// static float	find_horizontal_hit_distance(t_mlx *mlx, float angle) // get h inter
// {
// 	float	horizontal_x; // stocke les coordonnees du point d;intersection
// 	float	horizontal_y;
// 	float	x_step; // defini increment des coordonnees  en fonction de l'angle
// 	float	y_step;
// 	int		pixel; // pixel d'intersection pour check si ;ur

// 	y_step = TILE_SIZE; // taille de chaque tuile
// 	x_step = TILE_SIZE / tan(angle); // taille de l'increment pour la proj du rayon a chaque pas. tan aide a determiner l'influence de l'angle sur le deplacement
// 	horizontal_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE; // trouve la coordonnee y la plus proche
// 	pixel = init_ray_direction(angle, &horizontal_y, &y_step, 1); //est-ce que le rayon rentre en contact avec qqchose
// 	horizontal_x = mlx->player->player_x + (horizontal_y - mlx->player->player_y) / tan(angle); // 
// 	if ((check_angle_direction(angle, 'y') && x_step > 0) || (!check_angle_direction(angle, 'y') && x_step < 0)) // check valeur de x step
// 		x_step *= -1;
// 	while (!is_wall(horizontal_x, horizontal_y - pixel, mlx)) // check si on heurte un mur avec la valeur du pixel
// 	{
// 		horizontal_x += x_step;
// 		horizontal_y += y_step;
// 	}
// 	return (sqrt(pow(horizontal_x - mlx->player->player_x, 2) + pow(horizontal_y - mlx->player->player_y, 2))); // pour recuperer la distance avec formule de la distance euclidienne
// }

// static float find_horizontal_hit_distance(t_mlx *mlx, float angle)
// {
//     float horizontal_x;
//     float horizontal_y;
//     float x_step;
//     float y_step;
//     int pixel;

//     y_step = TILE_SIZE;
//     x_step = TILE_SIZE / tan(angle);
    
//     // Trouver la première intersection horizontale
//     horizontal_y = floor(mlx->player->player_y / TILE_SIZE) * TILE_SIZE;
//     if (angle > 0 && angle < M_PI) // Si le rayon va vers le bas
//         horizontal_y += TILE_SIZE;
//     else
//         pixel = 1; // Pour ajuster la vérification de mur
    
//     // Calculer le x correspondant
//     horizontal_x = mlx->player->player_x + (horizontal_y - mlx->player->player_y) / tan(angle);
    
//     // Ajuster les pas en fonction de la direction
//     if (angle > M_PI) // Si le rayon va vers le haut
//         y_step = -TILE_SIZE;
    
//     if ((angle > M_PI/2 && angle < 3*M_PI/2) || (x_step < 0 && !(angle > M_PI/2 && angle < 3*M_PI/2)))
//         x_step *= -1;
    
//     // Avancer jusqu'à toucher un mur
//     while (horizontal_x >= 0 && horizontal_y >= 0 && 
//            horizontal_x < mlx->game->width_map * TILE_SIZE && 
//            horizontal_y < mlx->game->height_map * TILE_SIZE)
//     {
//         if (is_wall(horizontal_x, horizontal_y - (angle > M_PI ? 1 : 0), mlx))
//             break;
//         horizontal_x += x_step;
//         horizontal_y += y_step;
//     }
    
//     return (sqrt(pow(horizontal_x - mlx->player->player_x, 2) + 
//                 pow(horizontal_y - mlx->player->player_y, 2)));
// }


// // static float	find_vertical_hit_distance(t_mlx *mlx, float angle) // get h inter
// // {
// // 	float	vertical_x; // stocke les coordonnees du point d;intersection
// // 	float	vertical_y;
// // 	float	x_step; // defini increment des coordonnees  en fonction de l'angle
// // 	float	y_step;
// // 	int		pixel; // pixel d'intersection pour check si ;ur

// // 	x_step = TILE_SIZE; // taille de chaque tuile
// // 	y_step = TILE_SIZE / tan(angle); // taille de l'increment pour la proj du rayon a chaque pas. tan aide a determiner l'influence de l'angle sur le deplacement
// // 	vertical_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE; // trouve la coordonnee y la plus proche
// // 	pixel = init_ray_direction(angle, &vertical_x, &x_step, 0); //est-ce que le rayon rentre en contact avec qqchose
// // 	vertical_y = mlx->player->player_y + (vertical_x - mlx->player->player_x) * tan(angle); // 
// // 	if ((check_angle_direction(angle, 'x') && y_step < 0) || (!check_angle_direction(angle, 'x') && y_step > 0)) // check valeur de x step
// // 		y_step *= -1;
// // 	while (!is_wall(vertical_x - pixel, vertical_y, mlx)) // check si on heurte un mur avec la valeur du pixel
// // 	{
// // 		vertical_x += x_step;
// // 		vertical_y += y_step;
// // 	}
// // 	return (sqrt(pow(vertical_x - mlx->player->player_x, 2) + pow(vertical_y - mlx->player->player_y, 2))); // pour recuperer la distance avec formule de la distance euclidienne
// // }

// static float find_vertical_hit_distance(t_mlx *mlx, float angle)
// {
//     float vertical_x;
//     float vertical_y;
//     float x_step;
//     float y_step;
//     int pixel;

//     x_step = TILE_SIZE;
//     y_step = TILE_SIZE * tan(angle);
    
//     // Trouver la première intersection verticale
//     vertical_x = floor(mlx->player->player_x / TILE_SIZE) * TILE_SIZE;
//     if (!(angle > M_PI/2 && angle < 3*M_PI/2)) // Si le rayon va vers la droite
//         vertical_x += TILE_SIZE;
//     else
//         pixel = 1; // Pour ajuster la vérification de mur
    
//     // Calculer le y correspondant
//     vertical_y = mlx->player->player_y + (vertical_x - mlx->player->player_x) * tan(angle);
    
//     // Ajuster les pas en fonction de la direction
//     if (angle > M_PI/2 && angle < 3*M_PI/2) // Si le rayon va vers la gauche
//         x_step = -TILE_SIZE;
    
//     if ((angle > M_PI) || (y_step < 0 && angle < M_PI))
//         y_step *= -1;
    
//     // Avancer jusqu'à toucher un mur
//     while (vertical_x >= 0 && vertical_y >= 0 && 
//            vertical_x < mlx->game->width_map * TILE_SIZE && 
//            vertical_y < mlx->game->height_map * TILE_SIZE)
//     {
//         if (is_wall(vertical_x - (angle > M_PI/2 && angle < 3*M_PI/2 ? 1 : 0), vertical_y, mlx))
//             break;
//         vertical_x += x_step;
//         vertical_y += y_step;
//     }
    
//     return (sqrt(pow(vertical_x - mlx->player->player_x, 2) + 
//                 pow(vertical_y - mlx->player->player_y, 2)));
// }

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


float cast_ray(t_mlx *mlx, float angle)
{
    float sinA = sin(angle);
    float cosA = cos(angle);
    float distance = 0;
    float ray_x = mlx->player->player_x;
    float ray_y = mlx->player->player_y;
    float step = 1.0;  // Pas plus petit pour une détection plus précise
    
    // Lancer le rayon jusqu'à toucher un mur
    while (distance < MAX_DISTANCE)
    {
        ray_x += cosA * step;
        ray_y += sinA * step;
        distance += step;
        
        // Si on touche un mur, on s'arrête
        if (is_wall(ray_x, ray_y, mlx))
        {
            // Déterminer si c'est un mur horizontal ou vertical
            float mod_x = fmod(ray_x, TILE_SIZE);
            float mod_y = fmod(ray_y, TILE_SIZE);
            
            if (mod_x < 1.0 || mod_x > TILE_SIZE - 1.0)
                mlx->ray->flag = 1;  // Mur vertical
            else if (mod_y < 1.0 || mod_y > TILE_SIZE - 1.0)
                mlx->ray->flag = 0;  // Mur horizontal
                
            return distance;
        }
    }
    
    return MAX_DISTANCE;  // Distance maximale si aucun mur trouvé
}


/* Cette fonction affiche les rayons en ligne droite donc pas de murs */


void cast_rays(t_mlx *mlx)
{
    float angle;
    int ray;
    
    angle = mlx->player->angle - (mlx->player->fov_rd / 2.0);
    ray = 0;
    while (ray < WIDTH)
    {
        float ray_angle = angle_to_radians(angle);
        mlx->ray->ray_angle = ray_angle;
        
        // Obtenir la distance avec le rayon
        mlx->ray->distance = cast_ray(mlx, ray_angle);
        
        // Corriger l'effet fisheye
        mlx->ray->distance *= cos(ray_angle - mlx->player->angle);
        
        printf("Ray %d: angle=%.2f, distance=%.2f, flag=%d\n", 
        ray, mlx->ray->ray_angle * 180 / M_PI, mlx->ray->distance, mlx->ray->flag);
        render_wall(mlx, ray);
        
        angle += mlx->player->fov_rd / (double)WIDTH;
        ray++;
    }
}