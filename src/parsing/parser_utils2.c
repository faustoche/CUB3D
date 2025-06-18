/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:31:59 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/18 16:44:58 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	combine_colors(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	is_valid_number(char *str)
{
	int	i;

	if (!str)
		return (0);
	while (*str == ' ')
		str++;
	if (str[0] == '\0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
		{
			if (str[i] == ' ')
			{
				while (str[i] == ' ')
					i++;
				if (str[i] == '\0')
					return (1);
			}
			return (0);
		}
		i++;
	}
	return (1);
}

char	*normalize_map_line(char *line)
{
	char	*normalized;
	int		i;
	int		len;

	len = ft_strlen(line);
	normalized = malloc(sizeof(char) * (len + 1));
	if (!normalized)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (line[i] == ' ')
			normalized[i] = '0';
		else
			normalized[i] = line[i];
		i++;
	}
	normalized[len] = '\0';
	return (normalized);
}

void	clean_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	read_header_char(char *line, char *key)
{
	int		i;

	i = 0;
	if (line != NULL)
	{
		while (i < 2 && line[i] && line[i] != ' ' && line[i] != '\t')
		{
			key[i] = line[i];
			i++;
		}
		key[i] = '\0';
		return (1);
	}
	return (0);
}
