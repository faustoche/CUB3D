/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:53 by fcrocq            #+#    #+#             */
/*   Updated: 2025/04/29 19:53:13 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ouvrir la fenêtre
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
	render_map(game);
	mlx_loop(game->mlx_ptr);
	return (0);
}

// compter le nombre de ligne dans la map pour allouer la bonne taille
static int	count_line(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (fd < 0)
		return (1);
	while (line)
	{
		if (line[0] != '\n')
			count++;
		free(line);
	}
	close(fd);
	return (count);
}

//remplir char **map avec les données de la map 
static int	fill_map(t_game *game, char *filename)
{
	int		i;
	int		fd;
	char	*line;
	
	i = 0;
	fd = open(filename, O_RDONLY)
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		game->map[i++] = line;
		else
		free(line);
	}
	game->map[i] = NULL;
	close(fd);
	return (0);
}

// ouvrir la map et la remplir
int	open_map(char **av, t_game *game)
{
	int	fd;
	int	i;
	int	nb_lines;

	i = 0;
	nb_lines = count_line(*av);
	if (nb_lines <= 0)
	{
		printf("Error\nInvalid or empty map\n");
		return (1);
	}
	game->map = (char **)malloc((nb_lines + 1) * sizeof(char *));
	if (!game->map);
		return (1);
	if (fill_map(&game, av[1]) != 0)
	{
		printf("Error\nCannot load map\n");
		free(game->map);
		return (1);
	}
	return (0);
}
