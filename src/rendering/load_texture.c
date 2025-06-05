/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:13:49 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/05 16:33:45 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures_north(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->game->north_texture.img = mlx_xpm_file_to_image(mlx->game->mlx_ptr,
			mlx->game->meta.no, &width, &height);
	if (!mlx->game->north_texture.img)
		return (printf("Error\nCan't load the north texture\n"), 0);
	mlx->game->north_texture.addr = mlx_get_data_addr(mlx->game->north_texture.img,
			&mlx->game->north_texture.bpp,
			&mlx->game->north_texture.size_line,
			&mlx->game->north_texture.endian);
	mlx->game->north_texture.width = width;
	mlx->game->north_texture.height = height;
	return (1);
}

int	load_textures_south(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->game->south_texture.img = mlx_xpm_file_to_image(mlx->game->mlx_ptr,
			mlx->game->meta.so, &width, &height);
	if (!mlx->game->south_texture.img)
		return (printf("Error\nCan't load the south texture\n"), 0);
	mlx->game->south_texture.addr = mlx_get_data_addr(mlx->game->south_texture.img,
			&mlx->game->south_texture.bpp,
			&mlx->game->south_texture.size_line,
			&mlx->game->south_texture.endian);
	mlx->game->south_texture.width = width;
	mlx->game->south_texture.height = height;
	return (1);
}

int	load_textures_east(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->game->east_texture.img = mlx_xpm_file_to_image(mlx->game->mlx_ptr,
			mlx->game->meta.ea, &width, &height);
	if (!mlx->game->east_texture.img)
		return (printf("Error\nCan't load the east texture\n"), 0);
	mlx->game->east_texture.addr = mlx_get_data_addr(mlx->game->east_texture.img,
			&mlx->game->east_texture.bpp,
			&mlx->game->east_texture.size_line,
			&mlx->game->east_texture.endian);
	mlx->game->east_texture.width = width;
	mlx->game->east_texture.height = height;
	return (1);
}

int	load_textures_west(t_mlx *mlx)
{
	int	width;
	int	height;

	mlx->game->west_texture.img = mlx_xpm_file_to_image(mlx->game->mlx_ptr,
			mlx->game->meta.we, &width, &height);
	if (!mlx->game->west_texture.img)
		return (printf("Error\nCan't load the west texture\n"), 0);
	mlx->game->west_texture.addr = mlx_get_data_addr(mlx->game->west_texture.img,
			&mlx->game->west_texture.bpp,
			&mlx->game->west_texture.size_line,
			&mlx->game->west_texture.endian);
	mlx->game->west_texture.width = width;
	mlx->game->west_texture.height = height;
	return (1);
}

void	load_all_textures(t_mlx *mlx)
{
	load_textures_north(mlx);
	load_textures_south(mlx);
	load_textures_east(mlx);
	load_textures_west(mlx);
}
