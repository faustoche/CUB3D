/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faustoche <faustoche@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:53 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/14 15:42:13 by faustoche        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fill_map(t_game *game, char *filename)
{
	int		i;
	int		fd;
	char	*line;
	
	i = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		game->map[i++] = line;
		else
		free(line);
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	close(fd);
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
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

//remplir char **map avec les données de la map 

// ouvrir la map et la remplir
int	open_map(char **av, t_game *game)
{
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
	if (!game->map)
		return (1);
	if (fill_map(game, av[1]) != 0)
	{
		printf("Error\nCannot load map\n");
		free(game->map);
		return (1);
	}
	game->height_map = 0;
	game->width_map = 0;
	while (game->map[game->height_map])
	{
		int len = ft_strlen(game->map[game->height_map]);
		if (len > game->width_map)
			game->width_map = len;
		game->height_map++;
	}
	return (0);
}


// vérifie dans le fichier les datas du début 

// void	init_lines(char *line, t_map *map)
// {
// 	if (ft_strncmp(line, "NO ", 3) == 0)
// 		map->no_path = ft_strdup(line + 3);
// 	else if (ft_strncmp(line, "SO ", 3) == 0)
// 		map->so_path = ft_strdup(line + 3);
// 	else if (ft_strncmp(line, "WE ", 3) == 0)
// 		map->we_path = ft_strdup(line + 3);
// 	else if (ft_strncmp(line, "EA ", 3) == 0)
// 		map->ea_path = ft_strdup(line + 3);
// 	else if (ft_strncmp(line, "F ", 2) == 0)
// 		map->floor_clr = ft_strdup(line + 2);
// 	else if (ft_strncmp(line, "C ", 2) == 0)
// 		map->ceiling_clr = ft_strdup(line + 2);
// 	else if (ft_strcmp(line, "Z") == 0)
// 		map->player = ft_strdup(line);
// }
