/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:15:24 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/09 17:42:10 by aurlic           ###   ########.fr       */
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
# define FAILURE -1
# define TMP 69
# define WRONG_ARG_NB "Error 🤯\nWrong number of arguments.\n"
# define FILE_NAME_ERR "Error 🤯\nFile passed as argument doesn't meet format \
format requirements.\n\x1b[38;2;255;165;0m\x1b[1mCorrect format: ./cub3d file.cub\n\x1b[0m"
# define DIR_ARG_ERR "Error 🤯\nDirectory passed as argument.\n\x1b[38;2;255;165;0m\x1b[1mCorrect format: ./cub3d file.cub\n\x1b[0m"

/* PROTOTYPES */

/* PARSER */
/* parser.c */
int		parser(char **av);

/* ERROR */
/* error.c */
void	print_error(char *err_msg);

#endif