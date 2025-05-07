/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:31:14 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/07 16:17:53 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int	i;

	i = bottom_pixel;
	while (i < HEIGHT)
		ft_mlx_pixel_put(mlx, ray, i++, 0xB99470FF);
	i = 0;
	while (i < top_pixel)
		ft_mlx_pixel_put(mlx, ray, i++, 0x89CFF3FF);
}

int get_color(t_mlx *mlx)
{
    double angle = mlx->ray->ray_angle;
    angle = angle_to_radians(angle);

    if (mlx->ray->flag == 1)
    {
        if (angle > 0 && angle < M_PI)
            return (0x330000);
        else
            return (0xCC6699); // rose balais
    }
    else
    {
        if (angle > M_PI / 2 && angle < 3 * M_PI / 2) // l'angle est toujours le meme
            return (0xFF0066); // framboise
        else
            return (0xFFFF00FF);
    }
}


void	draw_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel)
{
	int	color;

	color = get_color(mlx);
	while (top_pixel < bottom_pixel)
		ft_mlx_pixel_put(mlx, ray, top_pixel++, color);
}

void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_height;
	double	bottom_pixel;
	double	top_pixel;

	mlx->ray->distance *= cos(angle_to_radians(mlx->ray->ray_angle - mlx->player->angle)); // fix l'effet fish eye
	wall_height = (TILE_SIZE / mlx->ray->distance) * ((WIDTH / 2) / tan(mlx->player->fov_rd / 2));
	bottom_pixel = (HEIGHT / 2) + (wall_height / 2);
	top_pixel = (HEIGHT / 2) - (wall_height / 2);
	if (bottom_pixel > HEIGHT)
		bottom_pixel = HEIGHT;
	if (top_pixel < 0)
		top_pixel = 0;
	printf("ray = %d | angle = %.2f° | dist = %.2f | top = %.2f | bottom = %.2f | wall_height = %.2f\n",
		ray,
		mlx->ray->ray_angle,
		mlx->ray->distance,
		top_pixel,
		bottom_pixel,
		wall_height);	
	draw_floor_ceiling(mlx, ray, top_pixel, bottom_pixel);
	draw_wall(mlx, ray, top_pixel, bottom_pixel);
}
