/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:40:02 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/09 18:19:33 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(int fd)
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

	return (SUCCESS);
}

/**
 * @brief Open and store map.
 *
 * This function checks that the file passed isn't a directory, and then calls
 * the functions to store the map properly.
 *
 * @param str file passed to program.
 * @return SUCCESS if map store properly, or FAILURE if not.
 */
static int	open_store_map(char *file)
{
	int	fd;

	if (open(file, O_RDONLY | __O_DIRECTORY) > 2)
	{
		print_error(DIR_ARG_ERR);
		return (FAILURE);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(FILE_OPEN_ERR);
		return (FAILURE);
	}
	if (count_lines(fd) == FAILURE || store_map(fd) == FAILURE)
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
static int	check_arg_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (!str[i] || ft_strncmp(str + i, ".cub", 4) != 0
		|| str[i + 4] != '\0' || i < 1)
		return (print_error(FILE_NAME_ERR), FAILURE);
	return (SUCCESS);
}

/**
 * @brief Parse the input.
 *
 * This function calls all the functions necessary to parse the input and
 * check the validity of the map sent
 *
 * @param av arguments matrix.
 * @return SUCCESS if input is correct, or FAILURE if not.
 */
int	parser(char **av)
{
	if (check_arg_name(av[1]) == FAILURE)
		return (FAILURE);
	if (open_store_map(av[1]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
