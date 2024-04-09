/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:40:02 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/09 17:46:47 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (SUCCESS);
}
