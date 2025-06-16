/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcrocq <fcrocq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:35:09 by fcrocq            #+#    #+#             */
/*   Updated: 2025/06/16 10:39:10 by fcrocq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# define FOV 60
# define ROTATION_SPEED 0.045
# define MOUSE_ROTATION_SPEED 0.004
# define PLAYER_SPEED 4
# define M_PI   3.14159265358979323846
# define MAX_DISTANCE 1000.0

# define EVENT_MOUSE_CODE 6
# define MINIMAP_SIZE 200
# define MINIMAP_TILE 10
# define MINIMAP_RADIUS 15
# define MINIMAP_RADIUS_X 15
# define MINIMAP_RADIUS_Y 9
# define WALL_COLOR     0x004400 // Vert foncé
# define FLOOR_COLOR    0x228B22 // Vert jungle
# define PLAYER_COLOR   0xFFD700 // Jaune
# define RAY_COLOR      0xFF4500 // Orange
# define EMPTY_COLOR    0x222222 // Gris
# define BORDER_COLOR   0x8B0000 // Rouge

# define NORTH 'NO'
# define SOUTH 'SO'
# define WEST 'WE'
# define EAST 'EA'
# define FLOOR 'F'
# define CEILING 'C'
# define WALL '1'

/*------------- STRUCTURES --------------*/

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}	t_texture;

typedef struct s_tex_data
{
	int			tex_x;
	double		step;
	double		tex_pos;
	t_texture	*texture;
}	t_tex_data;

typedef struct s_meta
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			f_r;
	int			f_g;
	int			f_b;
	int			c_r;
	int			c_g;
	int			c_b;
	int			f_color;
	int			c_color;
	int			f_set;
	int			c_set;
}	t_meta;

typedef struct s_game
{
	char		**map;
	int			player_x;
	int			player_y;
	int			width_map;
	int			height_map;
	void		*mlx_ptr;
	void		*win_ptr;
	char		player_dir;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_meta		meta;
}	t_game;

typedef struct s_player
{
	int			player_x;
	int			player_y;
	double		angle;
	float		fov_rd;
	int			rot;
	int			left_right;
	int			up_down;
	int			mouse_rot;
}	t_player;

typedef struct s_ray
{
	double		ray_angle;
	double		ray_dir_x;
	double		ray_dir_y;
	int			side;
	double		distance;
	int			flag;
	char		hit_cell;
	int			hit_x;
	int			hit_y;
	float		ray_x;
	float		ray_y;
	float		sin_a;
	float		cos_a;
	float		next_x;
	float		next_y;
	float		dx;
	float		dy;
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
	t_meta		*meta;
}	t_mlx;

typedef struct s_minimap
{
	t_mlx		*mlx;
	int			py;
	int			px;
	int			origin_x;
	int			origin_y;
	int			player_tile_x;
	int			player_tile_y;
	int			center_x;
	int			center_y;
	int			color;
	double		ray_x;
	double		ray_y;
	double		dx;
	double		dy;
}	t_minimap;

typedef struct s_wall
{
	t_texture	*texture;
	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;
	int			top;
	int			bottom;
}	t_wall;

/*-------------- FUNCTIONS --------------*/

/// BONUS ///
// doors.c
void		open_door_near_player(t_mlx *mlx);

// minimap_draw1-2.c
void		draw_minimap(t_mlx *mlx);
void		draw_minimap_player(t_minimap *mini);
int			choose_color(char tile);

// minimap_rays.c
void		draw_direction_ray(t_minimap *mini, double angle);

// mouse_event.c
int			mouse_handler(int x, int y, void *param);
int			mouse_leave(int keycode, void *param);

/// GAME BASE ///
// init_game.c
void		init_datas(t_game *game);
void		find_player(t_game *game);
void		init_player(t_player *player, t_game *game);
void		exit_game(t_mlx *mlx);

// keys_hook.c
void		hook(t_mlx *mlx, double move_x, double move_y);
int			key_input(int key, void *param);

// movements.c 
void		rotate_player(t_mlx *mlx, int i);
void		move_player(t_mlx *mlx, double move_x, double move_y);

/// PARSING ///
// enclosure_check.c
int			find_closure_error(t_game *g, int *ex, int *ey);
int			check_edge_row(char *row, int y);

// map_colors.c
int			parse_rgb(char *str, char ***rgb_out);
void		assign_colors(t_meta *m, char type, int vals[3]);
int			validate_count(char **rgb, char *header);
int			validate_components(char **rgb, char *header, int vals[3]);
int			set_color(char **parts, t_meta *m);

// map_textures.c
int			set_texture(char **p, t_meta *m);
int			all_header_fields_set(t_meta *m);
int			parse_header_line(char *line, t_meta *m);
int			read_header(int fd, t_meta *m);
int			open_and_read_header(const char *path, t_game *g, int *fd);

// map_validation.c
int			process_map_row(t_game *g, char *line, int rows, int width);
int			validate_map(t_game *g);
int			valid_map_chars(char *line);

// map.c
void		init_meta(t_meta *m);
int			open_map(const char *path, t_game *g);
int			combine_colors(int r, int g, int b);

// parser_utils.c
void		free_split(char **arr);
int			is_blank_line(char *line);
int			read_first_map_line(int fd, char **line);
void		chomp_newline(char *line);
int			skip_blank_preface(int fd, char **line);

// parsing.c
void		init_map_state(t_game *g, int *rows, int *width);
int			process_map_lines(int fd, t_game *g, int rows, int width);

/// RAYCASTING ///
// init_rays.c
int			check_angle_direction(float angle, char c);
int			is_wall(float x, float y, t_mlx *mlx);

// ray_utils.c
float		angle_to_radians(float angle);
float		cal_dist(float x1, float y1, float x2, float y2);
void		init_rays(t_ray *h_ray, t_ray *v_ray, t_mlx *mlx, float angle);

// raycasting.c
void		cast_rays(t_mlx *mlx);

/// RENDERING ///

// draw_wall.c
void		draw_wall_portion(t_mlx *mlx, int ray_num, int top, int bottom);

// load_textures.c
void		load_all_textures(t_mlx *mlx);

// put_textures.c
int			get_tex_pix(t_texture *texture, int x, int y);
void		free_textures(t_mlx *mlx);

// render_walls.c
t_texture	*select_wall_texture(t_ray *ray, t_game *game);
int			calculate_wall_height(t_ray *ray, t_player *player);
void		draw_textured_wall(t_mlx *mlx, int ray, int top_pixel, int bottom);
void		ft_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void		render_wall(t_mlx *mlx, int ray);

#endif