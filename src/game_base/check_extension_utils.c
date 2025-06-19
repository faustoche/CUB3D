/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:57:38 by asaulnie          #+#    #+#             */
/*   Updated: 2025/06/18 19:59:38 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_trailing_cub(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strcmp(filename + len - 4, ".cub") == 0);
}

int	has_extra_dot_cub(char *filename)
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
