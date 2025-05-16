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
#define WIN_WIDTH 384
#define WIN_HEIGHT 320
#define WIN_TITLE "Cub3D - Raycaster"

typedef struct s_textures_info {
	char	*n_wall_path;
	char	*floor_path;
	int     width;
	int     height;
} t_textures_info;

typedef struct s_loaded_textures {
	void	*n_wall;
	void	*floor;
} t_loaded_textures;


// Add to your existing t_game structure
typedef struct s_game
{
    void    *mlx;           /* MiniLibX instance pointer */
    void    *win;           /* Window pointer */
    char    **map;          /* Game map */
    double  pos_x;          /* Player X position */
    double  pos_y;          /* Player Y position */
	double  dir_angle;
    double  dir_x;          /* Direction vector X */
    double  dir_y;          /* Direction vector Y */
    double  plane_x;        /* Camera plane X */
	double  plane_y;        /* Camera plane Y */
    double temp_x_move;
    double temp_y_move;
	int key_w;
    int key_a;
    int key_s;
    int key_d;
    int key_left;
    int key_right;
	t_textures_info textures_info; /* Textures info */
	t_loaded_textures loaded_textures; /* Loaded textures */
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
int draw_map(t_game *game, t_loaded_textures *loaded_textures, t_textures_info *texture_info);
void print_pixel(t_game *game, int x, int y);
void draw_direction_line(t_game *game, int x, int y, int distance);

// handle_keys.c
int handle_keypress(int keysym, t_game *game);
int handle_keyrelease(int keysym, t_game *game);

// game_loop.c
int game_loop(t_game *game);
int is_valid_position(t_game *game, double new_x, double new_y);






// Add to main_header.h
void set_player_direction(t_game *game);
void cast_rays(t_game *game, int num_rays);
void draw_line(t_game *game, int x1, int y1, int x2, int y2, int color);
void cast_rays_2(t_game *game, double dir_angle);
#endif