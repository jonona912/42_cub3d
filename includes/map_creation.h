#ifndef MAP_CREATION_H
#define MAP_CREATION_H

#include "libft.h"
#include "get_next_line.h"
#include "map_validation.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <sys/time.h>

/* MiniLibX Window Settings */
#define GRID_SIZE 16 // for 2D map grid size
#define TEXTURE_SIZE 64 // for texture size
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define WIN_TITLE "Cub3D - Raycaster"

#define BLUE 0x0000FF
#define GREEN 0x00FF00
#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define PURPLE 0x800080
#define YELLOW 0xFFFF00
#define CYAN 0x00FFFF
#define MAGENTA 0xFF00FF


typedef struct s_textures_info {
	char	*n_wall_path;
	char	*w_wall_path;
	char	*s_wall_path;
	char	*e_wall_path;
	double	floor_color;
	double	ceiling_color;
	int		width;
	int		height;
} t_textures_info;

typedef struct s_loaded_textures {
	void	*n_wall;
	void	*w_wall;
	void	*s_wall;
	void	*e_wall;
} t_loaded_textures;


// Add to your existing t_game structure
typedef struct s_game
{
	void			*mlx;           /* MiniLibX instance pointer */
	void			*win;           /* Window pointer */
	void			*img;
	char			*img_data;
	// void			*img_3d;
	// char			*img_data_3d;
	char			**map;
	int				bpp;
	int				size_line;
	int				endian;
	int				texture_bpp;
	int				texture_size_line;
	int				texture_endian;
	int				x_start_minimap;
	int				y_start_minimap;
	int				side;
	double			perp_wall_dist;
	double			true_ray_dist;
	// int				bpp_3d;
	// int				size_line_3d;
	// int				endian_3d;
	int				projected_slice_height;
	int				map_rows;
	int				map_cols;
	int				map_width;
	int				map_height;
	double			pos_x;          /* Player X position */
	double			pos_y;          /* Player Y position */
	double			dir_angle;
	double			dir_x;          /* Direction vector X */
	double			dir_y;          /* Direction vector Y */
	double			plane_x;        /* Camera plane X */
	double			plane_y;        /* Camera plane Y */
	double			temp_x_move;
	double			temp_y_move;
	int				key_w;
	int				key_a;
	int				key_s;
	int				key_d;
	int				key_left;
	int				key_right;
	t_textures_info		textures_info; /* Textures info */
	t_loaded_textures	loaded_textures; /* Loaded textures */
} t_game;

/* Ray casting specific structure */
typedef struct s_ray {
	double camera_x;    /* X-coordinate in camera space */
	double dir_x;       /* Ray direction X */
	double dir_y;       /* Ray direction Y */
	int map_x;          /* Map cell X */
	int map_y;          /* Map cell Y */
	double side_dist_x; /* Distance to next X side */
	double side_dist_y; /* Distance to next Y side */
	double delta_dist_x;/* X distance between sides */
	double delta_dist_y;/* Y distance between sides */
	int step_x;         /* X step direction (1 or -1) */
	int step_y;         /* Y step direction (1 or -1) */
	int hit;            /* Wall hit flag */
	int side;           /* Which side hit (NS or EW) */
	double perp_wall_dist; /* Distance to wall */
} t_ray;

/* MiniLibX related functions - add as needed */
int handle_close(t_game *game);


// initialize_mlx.c
int initialize_mlx(t_game *game);
void put_pixel(t_game *game, int x, int y, int color);

// handle_keys.c
int handle_keypress(int keysym, t_game *game);
int handle_keyrelease(int keysym, t_game *game);
int handle_close(t_game *game);

// initialize_game_struct.c
int initialize_game_struct(t_game *game);
void initialize_keys(t_game *game);
void set_player_direction(t_game *game);

// game_loop.c
int two_d_game_loop(t_game *game);
int is_valid_position(t_game *game, double new_x, double new_y);

// put_map_utils.c
void clear_screen(t_game *game);
void put_pixel(t_game *game, int x, int y, int color);
void print_ceiling_floor(t_game *game);

// put_map.c
void put_grid_boundary(t_game *game, int x, int y, int color);
void put_map_background(t_game *game);
void draw_map(t_game *game, t_loaded_textures *loaded_textures, t_textures_info *texture_info);
void print_pixel(t_game *game, int x, int y);
void draw_direction_line(t_game *game, int distance, double dir_x, double dir_y);
void put_2d_map(t_game *game);

// put_minimap.c
void put_map_background_2(t_game *game, int x_offset, int y_offset);
void put_player_position(t_game *game);
void cast_fov_rays(t_game *game);

// Add to main_header.h
int cast_rays(t_game *game, double dir_angle, double *first_cross_dist);

int extract_map_info(char *map_file, t_game *game);
#endif