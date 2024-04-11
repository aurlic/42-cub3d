/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:25:17 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/11 12:10:12 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check position of the map.
 *
 * This function checks that the map is correctly placed at the end of the file.
 * It also check that there is a map in the file.
 *
 * @param game game structure.
 * @param content content of the file
 * @param pos counter to track starting position of the map
 * @return SUCCESS if map placement is correct, or FAILURE if not.
 */
int	check_map_pos(t_game *game, char **content, int pos)
{
	int	i;
	int	j;
	
	i = -1;
	while (content[++i])
	{
		j = 0;
		while (content[i][j] == ' ')
			j++;
		if (content[i][j] == '1')
		{
			pos = i;
			if (game->input->map_start == 0)
				game->input->map_start = pos;
		}
		if (content[i][j] != '1' && content[i][j] != '\n' && pos != 0)
			return (print_error(ERR_INVALID_MAP), FAILURE);
		else if (content[i][j] == '1' && (pos != 0
			&& ft_strictcmp(content[pos - 1], "\n"))
			&& pos != game->input->map_start)
			return (print_error(ERR_INVALID_MAP), FAILURE);
	}
	if (game->input->map_start == 0)
		return (print_error(ERR_INVALID_MAP), FAILURE);
	return (SUCCESS);
}

/**
 * @brief Parse the content of the file.
 *
 * This function calls all the functions necessary to parse the file.
 *
 * @param game game structure.
 * @return SUCCESS if file is correct, or FAILURE if not.
 */
int	parse_content(t_game *game)
{
	if (check_map_pos(game, game->input->content, 0) == FAILURE)
		return (FAILURE);
	if (parse_textures(game, game->input->content) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
