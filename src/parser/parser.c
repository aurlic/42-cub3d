/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:40:02 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 12:08:23 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Parse the input.
 *
 * This function calls all the functions necessary to parse the input and
 * check the validity of the map sent
 *
 * @param game game structure.
 * @param av arguments matrix.
 * @return SUCCESS if input is correct, or FAILURE if not.
 */
int	parser(t_game *game, char **av)
{
	if (check_arg_name(av[1]) == FAILURE)
		return (FAILURE);
	if (open_store_input(game, av[1]) == FAILURE)
		return (FAILURE);
	if (parse_content(game) == FAILURE)
		return (FAILURE);
	if (check_map(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
