/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:16:03 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/13 20:46:22 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
* Permets de mettre à jour la position du joueur et son angle
* Si le joueur tourne on ajoute ou enlève rot_speed à l'angle
	- rotation à gauche : -1
	- rotation à droite : 1
* Le joueur peut garder son orientation entre 0 et 2 pi radians
* Pourquoi 5 pour la vitesse de déplacement ?
	- Valeur arbitraire pour avoir une sensation de vitesse correcte
	- Avec 1 : lentement
	- Avec 10 : très rapide
* Pourquoi 0.05 pour la rotation ?
	- En radians, un tour complet = 2pi soit 6.28 degrés
	-  0.05 ≈ 3 degrés (0.05 * 180 / π ≈ 2.86°)
	- Ça donne une rotation fluide sans aller trop vite
*/

// void	update_player(t_mlx *mlx)
// {
// 	double	move_speed; // distance en pixels que le joueur parcourt a chaque frame
// 	double	rot_speed; // vitesse de rotation de l'angle en radian a chaque frame
// 	int		new_x;
// 	int		new_y;
// 	int		map_x;
// 	int		map_y;

// 	move_speed = 5.0; // 5 permet de donner une sensation de vitesse
// 	rot_speed = 0.05; // en radians, un tour complet = 2pi soit 6.28 degres. 
// 	if (mlx->player->rot) // si le joueur tourne (-1 ou 1)
// 		mlx->player->angle += mlx->player->rot * rot_speed; // pour adapter la rotation a gauche ou a droite
// 	new_x = mlx->player->player_x; // on copie la position actualisé
// 	new_y = mlx->player->player_y; // on copie la position actualisé
// 	if (mlx->player->up_down != 0) // cos si x, sin si y
// 	{
// 		new_x += cos(mlx->player->angle) * move_speed * mlx->player->up_down;
// 		new_y += sin(mlx->player->angle) * move_speed * mlx->player->up_down;
// 	}
// 	if (mlx->player->left_right != 0)
// 	{
// 		new_x += cos(mlx->player->angle + M_PI / 2) * move_speed * mlx->player->left_right;
// 		new_y += sin(mlx->player->angle + M_PI / 2) * move_speed * mlx->player->left_right;
// 	}
// 	map_x = new_x / TILE_SIZE; // savoir dans quelle case se trouve le joueur
// 	map_y = new_y / TILE_SIZE;
// 	if (mlx->game->map[map_y][map_x] != '1') // si ce n'est pas un 1 (un mur)
// 	{
// 		mlx->player->player_x = new_x; // on met la position a jour si y a pas de mur
// 		mlx->player->player_y = new_y;
// 	}
// }

int	key_input(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (key == XK_W || key == XK_w || key == XK_Up)
		mlx->player->up_down = 1;
	else if (key == XK_S || key == XK_s || key == XK_Down)
		mlx->player->up_down = -1;
	else if (key == XK_A || key == XK_a)
		mlx->player->left_right = -1;
	else if (key == XK_D || key == XK_d)
		mlx->player->left_right = 1;
	else if (key == XK_Left)
		mlx->player->rot = -1;
	else if (key == XK_Right)
		mlx->player->rot = 1;
	else if (key == XK_Escape)
		exit_game(mlx);
	else
		return (0);
	return (0);
}

void	rotate_player(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		mlx->player->angle += ROTATION_SPEED;
		if (mlx->player->angle > 2 * M_PI)
			mlx->player->angle -= 2 * M_PI;
	}
	else
	{
		mlx->player->angle -= ROTATION_SPEED;
		if (mlx->player->angle < 0)
			mlx->player->angle += 2 * M_PI;
	}
}

static void	move_player(t_mlx *mlx, double move_x, double move_y)
{
	int	map_y;
	int	map_x;
	int	new_x;
	int	new_y;

	new_x = roundf(mlx->player->player_x + move_x);
	new_y = roundf(mlx->player->player_y + move_y);
	map_x = (new_x / TILE_SIZE);
	map_y = (new_y / TILE_SIZE);
	if (mlx->game->map[map_y][map_x] != '1'
		&& (mlx->game->map[map_y][mlx->player->player_x / TILE_SIZE] != '1'
		&& mlx->game->map[mlx->player->player_y / TILE_SIZE][map_x] != '1'))
	{
		mlx->player->player_x = new_x;
		mlx->player->player_y = new_y;
	}
}

void hook(t_mlx *mlx, double move_x, double move_y)
{
    if (mlx->player->rot == 1)
        rotate_player(mlx, 1);
    if (mlx->player->rot == -1)
        rotate_player(mlx, 0);
    if (mlx->player->left_right == 1) // droit
    {
        move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
        move_y = cos(mlx->player->angle) * PLAYER_SPEED;
    }
    if (mlx->player->left_right == -1) // gauche
    {
        move_x = sin(mlx->player->angle) * PLAYER_SPEED;
        move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
    }
    if (mlx->player->up_down == 1) // en avant
    {
        move_x = cos(mlx->player->angle) * PLAYER_SPEED;
        move_y = sin(mlx->player->angle) * PLAYER_SPEED;
    }
    if (mlx->player->up_down == -1) // en arrière
    {
        move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
        move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
    }
    move_player(mlx, move_x, move_y);
}


// void	hook(t_mlx *mlx, double move_x, double move_y)
// {
// 	if (mlx->player->rot == 1)
// 		rotate_player(mlx, 1);
// 	if (mlx->player->rot == -1)
// 		rotate_player(mlx, 0);
// 	if (mlx->player->left_right == 1) // right
// 	{
// 		move_x = -sin(mlx->player->angle) * PLAYER_SPEED;
// 		move_y = cos(mlx->player->angle) * PLAYER_SPEED;
// 	}
// 	if (mlx->player->left_right == -1) // left
// 	{
// 		move_x = sin(mlx->player->angle) * PLAYER_SPEED;
// 		move_y = -cos(mlx->player->angle) * PLAYER_SPEED;
// 	}
// 	if (mlx->player->up_down == 1) // up
// 	{
// 		move_x = cos(mlx->player->angle) * PLAYER_SPEED;
// 		move_y = sin(mlx->player->angle) * PLAYER_SPEED;
// 	}
// 	if (mlx->player->up_down == -1) // dozn
// 	{
// 		move_x = -cos(mlx->player->angle) * PLAYER_SPEED;
// 		move_y = -sin(mlx->player->angle) * PLAYER_SPEED;
// 	}
// 	move_player(mlx, move_x, move_y);
// }