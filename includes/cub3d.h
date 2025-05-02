#ifndef _CUB3D_H
# define _CUB3D_H

/*-------------- LIBRARIES --------------*/

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include "../minilibx-linux/mlx.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

/*--------------- DEFINES ---------------*/

# define WIDTH 1900
# define HEIGHT 1000
# define TILE_SIZE 30
# define FOV 60 // champs de vision
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4

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
	int		player_x;
	int		player_y;
	int		width_map;
	int		height_map;
}	t_game;

typedef struct s_map
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_clr;
	char	*ceiling_clr;
	char	*player;
}	t_map;

typedef struct s_player
{
	int		player_x;
	int		player_y;
	double	angle;
	float	fov_rd;
	int		rot;
	int		left_right;
	int		up_down;
}	t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	int		flag;
}	t_ray;

/*-------------- FUNCTIONS --------------*/

int		open_window(t_game *game, char **av);
int		open_map(char **av, t_game *game);
void	init_datas(t_game *game);
void	init_lines(char *line, t_map *map);
void	display_map(t_game *game);
int		input(int key, t_game *game);
void	find_player(t_game *game);

#endif