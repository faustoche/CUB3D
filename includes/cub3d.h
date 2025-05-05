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

# define WIDTH 1900 // a tester
# define HEIGHT 1000 // a tester
# define TILE_SIZE 30 // a tester
# define FOV 60 // champs de vision // a tester
# define ROTATION_SPEED 0.045 // a tester
# define PLAYER_SPEED 4 // a tester

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
	char	**map;
	int		player_x;
	int		player_y;
	int		width_map;
	int		height_map;
	mlx_t	*mlx_ptr;
}	t_game;

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

typedef struct s_mlx
{
	mlx_image_t	*img;
	t_ray		*ray;
	t_game		*game;
	t_player	*player;
}	t_mlx;


/*-------------- FUNCTIONS --------------*/

int		open_window(t_game *game, char **av);
int		open_map(char **av, t_game *game);
void	init_datas(t_game *game);
void	init_lines(char *line, t_map *map);
void	display_map(t_game *game);
void	key_input(mlx_key_data_t key, void *param);
void	find_player(t_game *game);
void	update_player(t_mlx *mlx);

#endif