#ifndef _CUB3D_H
# define _CUB3D_H

/*-------------- LIBRARIES --------------*/

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

/*--------------- DEFINES ---------------*/

# define NORTH ' NO'
# define SOUTH 'SO'
# define WEST 'WE'
# define EAST 'EA'
# define FLOOR 'F'
# define CEILING 'C'
# define WALL '1'

/*------------- STRUCTURES --------------*/

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
}	t_game;


/*-------------- FUNCTIONS --------------*/

int	open_window(t_game *game);
int	open_map(char **av, t_game *game);

#endif