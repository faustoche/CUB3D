/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:54:12 by fcrocq            #+#    #+#             */
/*   Updated: 2025/04/28 16:55:11 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// capturer les évènements clavier
// associer wasd + flèches + escape + croix
// appliquer les déplacements uniquement s'il n'y a pas de mur (collisions)