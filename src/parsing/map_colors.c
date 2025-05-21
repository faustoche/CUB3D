/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:53:15 by asaulnie          #+#    #+#             */
/*   Updated: 2025/05/21 13:46:40 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_rgb(char *str, char ***rgb_out)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (rgb == NULL)
	{
		printf("Error\nMemory allocation\n");
		return (0);
	}
	*rgb_out = rgb;
	return (1);
}

void	assign_colors(t_meta *m, char type, int vals[3])
{
	if (type == 'F')
	{
		m->f_r = vals[0];
		m->f_g = vals[1];
		m->f_b = vals[2];
		m->f_set = 1;
	}
	else
	{
		m->c_r = vals[0];
		m->c_g = vals[1];
		m->c_b = vals[2];
		m->c_set = 1;
	}
}

int	validate_count(char **rgb, char *header)
{
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		printf("Error\nMissing value for header '%s'\n", header);
		return (0);
	}
	return (1);
}

int	validate_components(char **rgb, char *header, int vals[3])
{
	int	i;
	int	v;

	i = 0;
	while (i < 3)
	{
		if (rgb[i][0] == '\0')
		{
			printf("Error\nMissing value for header '%s'\n", header);
			return (0);
		}
		v = ft_atoi(rgb[i]);
		if (v < 0 || v > 255)
		{
			printf("Error\nInvalid color out of range\n");
			return (0);
		}
		vals[i] = v;
		i++;
	}
	return (1);
}

int	set_color(char **parts, t_meta *m)
{
	char	**rgb;
	int		vals[3];

	if (!parse_rgb(parts[1], &rgb))
		return (0);
	if (!validate_count(rgb, parts[0]))
	{
		free_split(rgb);
		return (0);
	}
	if (!validate_components(rgb, parts[0], vals))
	{
		free_split(rgb);
		return (0);
	}
	assign_colors(m, parts[0][0], vals);
	free_split(rgb);
	return (1);
}
