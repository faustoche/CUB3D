/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:53 by fcrocq            #+#    #+#             */
/*   Updated: 2025/04/29 11:44:09 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// vérifier que l'argument est bien un .cub
// lire le fichier ligne par ligne et sortir les lignes vides en dehors de la map
// identifier les éléments pour l'orientation de debut de map)
// vérifier que les éléments pour l'orientation sont avant la map
// calculer la largeur max et la hauteur max 
// vérifier s'il y a un seul joueur
// vérifier si la map est entourée de mur (1)

// stocker la map dans un tableau de char **

int	open_window(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		// libération des données;
		return (1);
	}
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1000, 1000, "cub3d");
	if (!game->win_ptr)
	{
		// libération des données;
		return (1);
	}
	mlx_loop(game->mlx_ptr);
	return (0);
}

int	open_map(char **av, t_game *game)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(*av, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open the file\n");
		return (1);
	}
	// a la place de 1000 : map height
	game->map = (char **)malloc(sizeof(1000 + 1) * sizeof(char *));
	if (!game->map)
	{
		close(fd);
		//libérer ce qui doit être libéré
		return (-1);
	}
	printf("%d\n", fd);
	return (fd);
}