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
# define M_PI   3.14159265358979323846
# define MAX_DISTANCE 1000.0

# define NORTH 'NO'
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
	void	*mlx_ptr;
	void	*win_ptr;
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
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	t_ray		*ray;
	t_game		*game;
	t_player	*player;
}	t_mlx;


/*-------------- FUNCTIONS --------------*/

/// PARSING ///
int		open_map(char **av, t_game *game);
void	display_map(t_game *game);

/// RAYCASTING ///
int		check_angle_direction(float angle, char c);
int		init_ray_direction(float angle, float *inter, float *step, int horizon);
int		is_wall(float x, float y, t_mlx *mlx);
float	angle_to_radians(float angle);
void	cast_rays(t_mlx *mlx);

/// RENDERING ///
void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	draw_floor_ceiling(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel);
int		get_color(t_mlx *mlx);
void	draw_wall(t_mlx *mlx, int ray, int top_pixel, int bottom_pixel);
void	render_wall(t_mlx *mlx, int ray);

/// INIT GAME ///
void	init_datas(t_game *game);
void	init_lines(char *line, t_game *map);
void	find_player(t_game *game);
void	exit_game(t_mlx *mlx);

/// MOVEMENTS //

int		key_input(int key, void *param);
void	hook(t_mlx *mlx, double move_x, double move_y);
void	rotate_player(t_mlx *mlx, int i);

#endif
