/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:16:03 by fcrocq            #+#    #+#             */
/*   Updated: 2025/04/30 14:59:18 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	up(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (new_y - 1 < 0)
		return ;
	if (game->map == NULL || game->map[new_y - 1] == NULL)
		return ;
	if (new_x < 0 || new_x >= (int)ft_strlen(game->map[new_y - 1])) // ft_strlen si ligne est un string
		return ;
	if (game->map[new_y - 1][new_x] != '1')
		game->player_y = new_y - 1;
	display_map(game);
}

static void	down(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (new_y + 1 < 0)
		return ;
	if (new_x < 0 || new_x >= (int)ft_strlen(game->map[new_y + 1]))
		return ;
	if (game->map[new_y + 1][new_x] != '1')
		game->player_y = new_y + 1;
	display_map(game);
}

static void	left(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (new_x - 1 < 0)
		return ;
	if (new_x - 1 >= (int)ft_strlen(game->map[new_y]))
		return ;
	if (game->map[new_y][new_x - 1] != '1')
		game->player_x = new_x - 1;
	display_map(game);
}

static void	right(t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (new_x + 1 < 0)
		return ;
	if (new_x + 1 >= (int)ft_strlen(game->map[new_y]))
		return ;
	if (game->map[new_y][new_x + 1] != '1')
		game->player_x = new_x + 1;
	display_map(game);
}

int	input(int key, t_game *game)
{
	if (key == XK_W || key == XK_w || key == XK_Up)
		up(game);
	else if (key == XK_A || key == XK_a || key == XK_Left)
		left(game);
	else if (key == XK_S || key == XK_s || key == XK_Down)
		down(game);
	else if (key == XK_D || key == XK_d || key == XK_Right)
		right(game);
	else
		return (0);
	return (0);
}