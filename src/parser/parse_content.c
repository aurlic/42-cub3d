/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:25:17 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/10 15:56:34 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check position of the map.
 *
 * This function checks that the map is correctly placed at the end of the file.
 *
 * @param game game structure.
 * @param content content of the file
 * @return SUCCESS if map placement is correct, or FAILURE if not.
 */
int	check_map_pos(t_game *game, char **content)
{
	int	i;
	int	j;
	int	pos;
	
	i = 0;
	pos = 0;
	while (content[i])
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
		else if (content[i][j] == '1' && ft_strictcmp(content[pos - 1], "\n")
			&& pos != game->input->map_start)
			return (print_error(ERR_INVALID_MAP), FAILURE);
		i++;
	}
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
	if (check_map_pos(game, game->input->content) == FAILURE)
		return (FAILURE);
	if (parse_textures(game, game->input->content) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
