/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:13:49 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/16 10:32:00 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_textures_north(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->game->north.img = mlx_xpm_file_to_image(mlx->game->mlx_ptr,
			mlx->game->meta.no, &width, &height);
	if (!mlx->game->north.img)
		return (printf("Error\nCan't load the north texture\n"), 0);
	mlx->game->north.addr = mlx_get_data_addr(mlx->game->north.img,
			&mlx->game->north.bpp,
			&mlx->game->north.size_line,
			&mlx->game->north.endian);
	mlx->game->north.width = width;
	mlx->game->north.height = height;
	return (1);
}

static int	load_textures_south(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->game->south.img = mlx_xpm_file_to_image(mlx->game->mlx_ptr,
			mlx->game->meta.so, &width, &height);
	if (!mlx->game->south.img)
		return (printf("Error\nCan't load the south texture\n"), 0);
	mlx->game->south.addr = mlx_get_data_addr(mlx->game->south.img,
			&mlx->game->south.bpp,
			&mlx->game->south.size_line,
			&mlx->game->south.endian);
	mlx->game->south.width = width;
	mlx->game->south.height = height;
	return (1);
}

static int	load_textures_east(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->game->east.img = mlx_xpm_file_to_image(mlx->game->mlx_ptr,
			mlx->game->meta.ea, &width, &height);
	if (!mlx->game->east.img)
		return (printf("Error\nCan't load the east texture\n"), 0);
	mlx->game->east.addr = mlx_get_data_addr(mlx->game->east.img,
			&mlx->game->east.bpp,
			&mlx->game->east.size_line,
			&mlx->game->east.endian);
	mlx->game->east.width = width;
	mlx->game->east.height = height;
	return (1);
}

static int	load_textures_west(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->game->west.img = mlx_xpm_file_to_image(mlx->game->mlx_ptr,
			mlx->game->meta.we, &width, &height);
	if (!mlx->game->west.img)
		return (printf("Error\nCan't load the west texture\n"), 0);
	mlx->game->west.addr = mlx_get_data_addr(mlx->game->west.img,
			&mlx->game->west.bpp,
			&mlx->game->west.size_line,
			&mlx->game->west.endian);
	mlx->game->west.width = width;
	mlx->game->west.height = height;
	return (1);
}

void	load_all_textures(t_mlx *mlx)
{
	load_textures_north(mlx);
	load_textures_south(mlx);
	load_textures_east(mlx);
	load_textures_west(mlx);
}
