/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:50:44 by fcrocq            #+#    #+#             */
/*   Updated: 2025/04/28 16:53:56 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// pour chaque colonne :
	// calculer la direction du rayon
	// utiliser DDA pour trouver le mur touché
	// calculer la distance au mur (pour évite l'effet fish eye)
	// déterminer quelle texture utiliser (NO, SO, WE, EA)
	// calculer la hauteur du mur à dessiner
	// dessiner la "bande" verticale correspondante avec la texture

	