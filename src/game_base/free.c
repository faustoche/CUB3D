/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:04:46 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/18 09:52:02 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_image_safe(void *mlx_ptr, void **img_ptr)
{
	if (*img_ptr)
	{
		mlx_destroy_image(mlx_ptr, *img_ptr);
		*img_ptr = NULL;
	}
}

void	destroy_images(t_game *data, t_mlx *mlx)
{
	destroy_image_safe(data->mlx_ptr, (void **)&data->north.img);
	destroy_image_safe(data->mlx_ptr, (void **)&data->south.img);
	destroy_image_safe(data->mlx_ptr, (void **)&data->east.img);
	destroy_image_safe(data->mlx_ptr, (void **)&data->west.img);
	if (mlx && mlx->img)
	{
		mlx_destroy_image(data->mlx_ptr, mlx->img);
		mlx->img = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	if (game->meta.no)
		free(game->meta.no);
	if (game->meta.so)
		free(game->meta.so);
	if (game->meta.we)
		free(game->meta.we);
	if (game->meta.ea)
		free(game->meta.ea);
	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}

void	cleanup_mlx(t_game *game)
{
	if (game->win_ptr)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		game->mlx_ptr = NULL;
	}
}

void	cleanup_all(t_game *game, t_player *player, t_ray *ray)
{
	if (game)
	{
		cleanup_mlx(game);
		cleanup_game(game);
		free(game);
	}
	if (player)
		free(player);
	if (ray)
		free(ray);
}
