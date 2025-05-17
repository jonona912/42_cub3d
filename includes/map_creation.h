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
#define GRID_SIZE 32 // for 2D map grid size
#define TEXTURE_SIZE 64 // for texture size
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define WIN_TITLE "Cub3D - Raycaster"

typedef struct s_textures_info {
	char	*n_wall_path;
	char	*floor_path;
	int		width;
	int		height;
} t_textures_info;

typedef struct s_loaded_textures {
	void	*n_wall;
	void	*floor;
} t_loaded_textures;


// Add to your existing t_game structure
typedef struct s_game
{
	void			*mlx;           /* MiniLibX instance pointer */
	void			*win;           /* Window pointer */
	void			*img;
	char			*img_data;
	void			*img_3d;
	char			*img_data_3d;
	char			**map;
	int				bpp;
	int				size_line;
	int				endian;
	int				bpp_3d;
	int				size_line_3d;
	int				endian_3d;
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



// put_map.c
void put_grid_boundary(t_game *game, int x, int y, int color);
void put_map_background(t_game *game);
void draw_map(t_game *game, t_loaded_textures *loaded_textures, t_textures_info *texture_info);
void print_pixel(t_game *game, int x, int y);
void draw_direction_line(t_game *game, int distance, double dir_x, double dir_y);
void put_pixel(t_game *game, int x, int y, int color);
void put_2d_map(t_game *game);

// Add to main_header.h
int cast_rays(t_game *game, double dir_angle, double *first_cross_dist);
#endif