/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:59 by fcrocq            #+#    #+#             */
/*   Updated: 2025/04/29 19:45:09 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error\nOnly one argument needed\n");
		exit(EXIT_FAILURE);
	}
	// check de la map
	init_datas(&game);
	open_map(av, &game);
	open_window(&game);
	// raycasting
}