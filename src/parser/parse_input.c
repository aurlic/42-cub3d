/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:23:06 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/10 11:23:50 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Store input in structure.
 *
 * This function store the full file in the structure.
 *
 * @param game game structure.
 * @param file file passed to program.
 * @return SUCCESS if content store properly, FAILURE if open fails.
 */
int	store_input(t_game *game, char *file)
{
	int		i;
	int		fd;
	char	*buf;

	i = 0;
	buf = "";
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_FILE_OPEN), FAILURE);
	while (buf)
	{
		buf = get_next_line(fd);
		if (buf)
			game->input->content[i++] = ft_strdup(buf);
		free(buf);
	}
	close (fd);
	return (SUCCESS);
}

/**
 * @brief Count input lines.
 *
 * This function counts the number of lines in the input file and mallocs the
 * content matrix.
 *
 * @param game game structure.
 * @param fd file descriptor of file passed to program.
 * @return SUCCESS if input lines counted properly, FAILURE if malloc fails.
 */
static int	count_lines(t_game *game, int fd)
{
	int		i;
	char	*buf;

	i = 0;
	buf = "";
	while (buf)
	{
		buf = get_next_line(fd);
		free(buf);
		i++;
	}
	game->input->file_lines = i - 1;
	game->input->content = ft_calloc(i, sizeof(char *));
	if (!game->input->content)
		return (print_error(ERR_MALLOC), FAILURE);
	return (SUCCESS);
}

/**
 * @brief Open and store input.
 *
 * This function checks that the file passed isn't a directory, and then calls
 * the functions to store the input properly.
 *
 * @param game game structure.
 * @param str file passed to program.
 * @return SUCCESS if input stored properly, or FAILURE if not.
 */
int	open_store_input(t_game *game, char *file)
{
	int	fd;

	if (open(file, O_RDONLY | __O_DIRECTORY) > 2)
		return (print_error(ERR_DIR_ARG), FAILURE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(ERR_FILE_OPEN), FAILURE);
	if (count_lines(game, fd) == FAILURE || store_input(game, file) == FAILURE)
		return (FAILURE);
	close(fd);
	return (SUCCESS);
}

/**
 * @brief Check validity of argument.
 *
 * This function check that the argument passed to the program is correctly
 * formated (format: *.cub).
 *
 * @param str file passed to program.
 * @return SUCCESS if input is correct, or FAILURE if not.
 */
int	check_arg_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (!str[i] || ft_strncmp(str + i, ".cub", 4) != 0
		|| str[i + 4] != '\0' || i < 1)
		return (print_error(ERR_FILE_NAME), FAILURE);
	return (SUCCESS);
}
