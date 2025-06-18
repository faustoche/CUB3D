/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:59 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/18 10:32:16 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	is_blank_line(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	if (line[pos] == '\0')
		return (1);
	return (0);
}

int	read_first_map_line(int fd, char **line)
{
	if (skip_blank_preface(fd, line) == 0)
	{
		printf("Error\nNo map data\n");
		return (0);
	}
	return (1);
}

void	chomp_newline(char *line)
{
	char	*carriage_return;
	char	*newline;

	carriage_return = ft_strchr(line, '\r');
	if (carriage_return != NULL)
		*carriage_return = '\0';
	newline = ft_strchr(line, '\n');
	if (newline != NULL)
		*newline = '\0';
}

int	skip_blank_preface(int fd, char **line)
{
	*line = get_next_line(fd);
	while (*line != NULL)
	{
		chomp_newline(*line);
		if (is_blank_line(*line) == 0)
			return (1);
		free(*line);
		*line = get_next_line(fd);
	}
	return (0);
}
