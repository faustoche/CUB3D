/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:59 by fcrocq            #+#    #+#             */
/*   Updated: 2025/05/20 19:52:18 by asaulnie         ###   ########.fr       */
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

int is_blank_line(char *line)
{
    int pos = 0;

    // skip over spaces and tabs
    while (line[pos] == ' ' || line[pos] == '\t')
        pos++;

    // if we reached the end, the entire line is whitespace
    if (line[pos] == '\0')
        return 1;
    return 0;
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

void chomp_newline(char *line)
{
    char *p;

    // first strip '\r', then '\n'
    if ((p = ft_strchr(line, '\r')) != NULL)
        *p = '\0';
    if ((p = ft_strchr(line, '\n')) != NULL)
        *p = '\0';
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
