/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:22:50 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/21 22:26:33 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_pixel(t_texture *texture, int x, int y)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < texture->width && y < texture->height)
	{
		dst = texture->addr + (y * texture->size_line + x * (texture->bpp / 8));
		return (*(unsigned int *)dst);
	}
	return (0);
}

void	free_textures(t_mlx *mlx)
{
	if (mlx->game->north_texture.img)
		mlx_destroy_image(mlx->game->mlx_ptr, mlx->game->north_texture.img);
	if (mlx->game->south_texture.img)
		mlx_destroy_image(mlx->game->mlx_ptr, mlx->game->south_texture.img);
	if (mlx->game->east_texture.img)
		mlx_destroy_image(mlx->game->mlx_ptr, mlx->game->east_texture.img);
	if (mlx->game->west_texture.img)
		mlx_destroy_image(mlx->game->mlx_ptr, mlx->game->west_texture.img);
}