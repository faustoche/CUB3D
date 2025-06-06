/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:22:50 by faustoche         #+#    #+#             */
/*   Updated: 2025/06/06 14:04:08 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_pix(t_texture *texture, int x, int y)
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
	if (mlx->game->north.img)
		mlx_destroy_image(mlx->game->mlx_ptr, mlx->game->north.img);
	if (mlx->game->south.img)
		mlx_destroy_image(mlx->game->mlx_ptr, mlx->game->south.img);
	if (mlx->game->east.img)
		mlx_destroy_image(mlx->game->mlx_ptr, mlx->game->east.img);
	if (mlx->game->west.img)
		mlx_destroy_image(mlx->game->mlx_ptr, mlx->game->west.img);
}
