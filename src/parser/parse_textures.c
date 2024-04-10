/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:42:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/10 14:34:42 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fill_identifier(t_game *game, char **texture)
{
	if (ft_strictcmp(texture[0], "N") || ft_strictcmp(texture[0], "NO"))
	{
		if (game->input->wall_no)
			return (print_error(ERR_DUP_TEXTURES), FAILURE);
		game->input->wall_no = ft_strdup(texture[1]);
	}
	else if (ft_strictcmp(texture[0], "S") || ft_strictcmp(texture[0], "SO"))
	{
		if (game->input->wall_so)
			return (print_error(ERR_DUP_TEXTURES), FAILURE);
		game->input->wall_so = ft_strdup(texture[1]);
	}
	else if (ft_strictcmp(texture[0], "W") || ft_strictcmp(texture[0], "WE"))
	{
		if (game->input->wall_we)
			return (print_error(ERR_DUP_TEXTURES), FAILURE);
		game->input->wall_we = ft_strdup(texture[1]);
	}
	else if (ft_strictcmp(texture[0], "E") || ft_strictcmp(texture[0], "EA"))
	{
		if (game->input->wall_ea)
			return (print_error(ERR_DUP_TEXTURES), FAILURE);
		game->input->wall_ea = ft_strdup(texture[1]);
	}
	return (SUCCESS);
}

/**
 * @brief Parse the identifier.
 *
 * This function splits the line passed as parameter and call the function to
 * fill the structure.
 *
 * @param game game structure.
 * @param content content of the file
 * @return SUCCESS if textures are correct, or FAILURE if not.
 */
static int	parse_identifier(t_game *game, char *content)
{
	char	**texture;

	texture = ft_split(content, ' ');
	if (!texture[0])
		return (free_matrix_safe(texture), SUCCESS);
	// if (texture[2])
	// 	return (free_matrix_safe(texture), print_error(ERR_TEXTURES), FAILURE);
	if (fill_identifier(game, texture) == FAILURE)
		return (free_matrix_safe(texture), FAILURE);
	return (SUCCESS);
}

/**
 * @brief Parse the textures.
 *
 * This function calls the functions needed to parse the textures.
 *
 * @param game game structure.
 * @param content content of the file
 * @return SUCCESS if textures are correct, or FAILURE if not.
 */
int	parse_textures(t_game *game, char **content)
{
	int	i;
	int	j;

	i = 0;
	while (content[i] && i < game->input->map_start)
	{
		j = 0;
		printf("%s", content[i]);
		while (content[i][j] == ' ')
			j++;
		if (parse_identifier(game, content[i]) == FAILURE)
			return (FAILURE); // need to write error;
		i++;
	}
	return (SUCCESS);
}
