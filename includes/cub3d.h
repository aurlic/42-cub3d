/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:15:24 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/22 17:38:33 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* LIBRAIRIES */

# include "../src/libft/includes/libft.h"
# include "../src/libft/includes/ft_printf.h"
# include "../src/libft/includes/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdbool.h>
# include <math.h>

/* STRUCTURES AND DATA */

# define SUCCESS 0
# define FAILURE 1
# define TMP 69
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define WIN_W 320
# define WIN_H 200
# define TEX_SIDE 64
# define PLAYER_SPEED 0.1
# define ROTATION_SPEED 0.05
# define MOUSE_CLOSE 17
# define TMP_ERR "YOUHOU CEST LA LE PROBLEME\n"
# define ERR_WRONG_ARG_NB "Error 🤯\nWrong number of arguments.\n"
# define ERR_FILE_NAME "Error 🤯\nFile passed as argument doesn't meet format \
format requirements.\n\x1b[38;2;255;165;0m\x1b[1mCorrect format: ./cub3d file.cub\n\x1b[0m"
# define ERR_FILE_OPEN "Error 🤯\nCouldn't open file.\n"
# define ERR_DIR_ARG "Error 🤯\nDirectory passed as argument.\n\x1b[38;2;255;165;0m\x1b[1mCorrect format: ./cub3d file.cub\n\x1b[0m"
# define ERR_MALLOC "Error 🤯\nMalloc failed.\n"
# define ERR_INVALID_MAP "Error 🤯\nInvalid map (see subject for the map configuration details).\n"
# define ERR_TEXTURES "Error 🤯\nInvalid textures format.\n"
# define ERR_MISSING_TEXTURES "Error 🤯\nMissing textures.\n"
# define ERR_INVALID_COLOR "Error 🤯\nInvalid color format.\n"
# define ERR_MISSING_COLOR "Error 🤯\nMissing color.\n"
# define ERR_INVALID_CHAR "Error 🤯\nInvalid char (see subject for the map configuration details).\n"
# define ERR_MULT_PLAYER "Error 🤯\nWrong player start configuration (see subject for the map configuration details).\n"
# define ERR_MLX_IMG "Error 🤯\nCouldn't create image.\n"

typedef struct s_input
{
	char	**content;
	char	**map;
	char	*wall_no;
	char	*wall_so;
	char	*wall_we;
	char	*wall_ea;
	int		tex_size;
	int		color_f[3];
	int		color_c[3];
	int		map_height;
	int		map_start;
	int		file_lines;
}	t_input;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

}	t_player;

typedef struct s_draw
{
	int		**textures;
	int		wall_height;
	int		start;
	int		end;
	double	wall_x;
	int		tex_dir;
	int		tex_x;
	int		tex_y;
	double	step;
	double	pos;
}	t_draw;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			**pixels;
	t_input		*input;
	t_img		*img;
	t_player	*player;
	t_ray		*ray;
	t_draw		*draw;
}	t_game;

/* PROTOTYPES */

/* CORE */
/* error.c */
void	print_error(char *err_msg);
void	free_game(t_game *game);
int		exit_game(t_game *game);
/* init.c */
int		init_game(t_game *game);
void	init_img(t_img *img);
int	init_pixels_tab(t_game *game);

/* DISPLAY */
/* textures.c */
int		load_textures(t_game *game);

/* PARSER */
/* parser.c */
int		parser(t_game *game, char **av);
/* parse_input.c */
int		check_arg_name(char *str);
int		open_store_input(t_game *game, char *file);
/* parse_content.c */
int		parse_content(t_game *game);
/* parse_textures.c */
int		parse_textures(t_game *game, char **content);
/* parse_colors.c */
int		color_identifier(t_game *game, char *content);
/* remove_newlines.c */
int		remove_newlines(t_game *game);
/* check_map.c */
int	check_map(t_game *game);
/* format_map.c */
int		map_to_rectangle(t_game *game, char **map);

/* RAYCASTING */
/* raycasting.c */
int	raycasting(t_game *game);

#endif