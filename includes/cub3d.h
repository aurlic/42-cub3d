/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:15:24 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/10 16:56:16 by traccurt         ###   ########.fr       */
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
# define ERR_WRONG_ARG_NB "Error 🤯\nWrong number of arguments.\n"
# define ERR_FILE_NAME "Error 🤯\nFile passed as argument doesn't meet format \
format requirements.\n\x1b[38;2;255;165;0m\x1b[1mCorrect format: ./cub3d file.cub\n\x1b[0m"
# define ERR_FILE_OPEN "Error 🤯\nCouldn't open file.\n"
# define ERR_DIR_ARG "Error 🤯\nDirectory passed as argument.\n\x1b[38;2;255;165;0m\x1b[1mCorrect format: ./cub3d file.cub\n\x1b[0m"
# define ERR_MALLOC "Error 🤯\nMalloc failed.\n"
# define ERR_INVALID_MAP "Error 🤯\nInvalid map (see subject for the map configuration details).\n"
# define ERR_TEXTURES "Error 🤯\nInvalid textures format.\n"

typedef struct s_input
{
	char	**content;
	char	**map;
	char	*wall_no;
	char	*wall_so;
	char	*wall_we;
	char	*wall_ea;
	int		color_f[3];
	int		color_c[3];
	int		map_h;
	int		map_w;
	int		map_start;
	int		file_lines;
}	t_input;

typedef struct s_game
{
	t_input	*input;
}	t_game;

/* PROTOTYPES */

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
/* ERROR */
/* error.c */
void	print_error(char *err_msg);

#endif