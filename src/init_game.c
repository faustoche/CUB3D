/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:47:39 by fcrocq            #+#    #+#             */
/*   Updated: 2025/04/29 19:53:39 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// initialiser la minilibx
// créer une fenêtre
// charger les textures murales
// créer une image pour dessiner chaque frame
// initialiser la position du joueur
// initialiser la direction (vecteur)
// initialiser le plan de caméra (vecteur)

void	init_datas(t_game *game)
{
	game.mlx_ptr = NULL;
	game.win_ptr = NULL;
}

// vérifie dans le fichier les datas du début 

void	init_lines(char *line, t_map *map)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		map->no_path = ft_strdup(line + 3);
	else if (ft_strcmp(line, "SO ", 3) == 0)
		map->so_path = ft_strdup(line + 3);
	else if (ft_strcmp(line, "WE ", 3) == 0)
		map->we_path = ft_strdup(line + 3);
	else if (ft_strcmp(line, "EA ", 3) == 0)
		map->ea_path = ft_strdup(line + 3);
	else if (ft_strcmp(line, "F ", 2) == 0)
		map->floor_clr = ft_strdup(line + 2);
	else if (ft_strcmp(line, "C ", 2) == 0)
		map->ceiling_clr = ft_strdup(line + 2);
}
