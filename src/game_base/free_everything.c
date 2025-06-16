/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:04:46 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/16 14:21:24 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_meta(t_meta *meta)
{
	if (meta->no)
		free(meta->no);
	if (meta->so)
		free(meta->so);
	if (meta->ea)
		free(meta->ea);
	if (meta->we)
		free(meta->we);
	meta->no = NULL;
	meta->so = NULL;
	meta->ea = NULL;
	meta->we = NULL;
}

void	clean_game(t_game *game)
{
	int	i;

	i = 0;
	clean_meta(&game->meta);
	if (game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void	free_all(t_game *game, t_mlx *mlx)
{
	clean_game(game);
	if (mlx && mlx->game && mlx->game->win_ptr)
		mlx_destroy_window(mlx->game->mlx_ptr, mlx->game->win_ptr);
	if (mlx && mlx->game && mlx->game->mlx_ptr)
	{
		mlx_destroy_display(mlx->game->mlx_ptr);
		free(mlx->game->mlx_ptr);
	}
}


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
	if (mlx && mlx->img)
    {
        mlx_destroy_image(data->mlx_ptr, mlx->img);
        mlx->img = NULL;
    }
	destroy_image_safe(data->mlx_ptr, (void **)&data->north.img);
	destroy_image_safe(data->mlx_ptr, (void **)&data->south.img);
	destroy_image_safe(data->mlx_ptr, (void **)&data->east.img);
	destroy_image_safe(data->mlx_ptr, (void **)&data->west.img);
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

int close_window(void *param)
{
    t_mlx *mlx;
    
    mlx = (t_mlx *)param;
    if (!mlx || !mlx->game)
        return (0);
    destroy_images(mlx->game, mlx);
    if (mlx->game->mlx_ptr && mlx->game->win_ptr)
    {
        mlx_destroy_window(mlx->game->mlx_ptr, mlx->game->win_ptr);
        mlx->game->win_ptr = NULL;
    }
    if (mlx->game->mlx_ptr)
    {
        mlx_destroy_display(mlx->game->mlx_ptr);
        free(mlx->game->mlx_ptr);
        mlx->game->mlx_ptr = NULL;
    }
    cleanup_game(mlx->game);
    free(mlx->game);
    free(mlx->player);
    free(mlx->ray);
    exit(EXIT_SUCCESS);
    return (0);
}
