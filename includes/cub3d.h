/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaulnie <asaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:24:38 by faustoche         #+#    #+#             */
/*   Updated: 2025/05/21 14:14:14 by asaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "cub3d_bonus.h"

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

typedef struct s_meta
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f_r;
	int		f_g;
	int		f_b;
	int		c_r;
	int		c_g;
	int		c_b;
	int		f_set;
	int		c_set;
}	t_meta;

typedef struct s_game
{
	char	**map;
	int		player_x;
	int		player_y;
	int		width_map;
	int		height_map;
	void	*mlx_ptr;
	void	*win_ptr;
	t_meta	meta;
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
	char	hit_cell;
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

// enclosure_check.c
int	find_closure_error(t_game *g, int *ex, int *ey);

// map_colors.c
int parse_rgb(char *str, char ***rgb_out);
void assign_colors(t_meta *m, char type, int vals[3]);
int validate_count(char **rgb, char *header);
int validate_components(char **rgb, char *header, int vals[3]);
int set_color(char **parts, t_meta *m);

// map_textures.c
int set_texture(char **p, t_meta *m);
int all_header_fields_set(t_meta *m);
int parse_header_line(char *line, t_meta *m);
int read_header(int fd, t_meta *m);
int	open_and_read_header(const char *path, t_game *g, int *fd);

// map_validation.c
int	process_map_row(t_game *g, char *line, int rows, int width);
int validate_map(t_game *g);
int valid_map_chars(char *line);

// map.c
// static int	fill_map(t_game *game, char *filename);
// static int	count_line(char *filename);
void	init_meta(t_meta *m);
int	open_map(const char *path, t_game *g);
// int	open_map(char **av, t_game *game);

// parser_utils.c
void free_split(char **arr);
int	is_blank_line(char *line);
int	read_first_map_line(int fd, char **line);
void chomp_newline(char *line);
int	skip_blank_preface(int fd, char **line);

// parsing.c
void	init_map_state(t_game *g, int *rows, int *width);
int	process_map_lines(int fd, t_game *g, int rows, int width);

/// RAYCASTING ///
int		check_angle_direction(float angle, char c);
int		init_ray_direction(float angle, float *inter, float *step, int horizon);
int		is_wall(float x, float y, t_mlx *mlx);
float	angle_to_radians(float angle);
void	cast_rays(t_mlx *mlx);

/// RENDERING ///
void	ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	render_wall(t_mlx *mlx, int ray);

/// INIT GAME ///
void	init_datas(t_game *game);
void	init_player(t_player *player, t_game *game);
void	init_lines(char *line, t_game *map);
void	find_player(t_game *game);
void	exit_game(t_mlx *mlx);

/// MOVEMENTS //

int		key_input(int key, void *param);
void	hook(t_mlx *mlx, double move_x, double move_y);
void	rotate_player(t_mlx *mlx, int i);

#endif
