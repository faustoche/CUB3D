/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:57:38 by asaulnie          #+#    #+#             */
/*   Updated: 2025/06/19 10:19:54 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_trailing_cub(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strcmp(filename + len - 4, ".cub") == 0);
}

static int	has_extra_dot_cub(char *filename)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(filename);
	while (i < len - 4)
	{
		if (filename[i] == '.' && filename[i + 1] == 'c'
			&& filename[i + 2] == 'u' && filename[i + 3] == 'b')
			return (1);
		i++;
	}
	return (0);
}

int	check_extension(char *filename)
{
	if (!filename)
	{
		printf("Error\nFilename is null\n");
		return (-1);
	}
	if (!has_trailing_cub(filename) || has_extra_dot_cub(filename))
	{
		printf("Error\nFile extension must be exactly '.cub'\n");
		return (-1);
	}
	return (0);
}
