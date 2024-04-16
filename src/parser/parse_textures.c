/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:42:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/16 09:34:57 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Fill the structure with textures.
 *
 * This function fills each wall texture in struct with the path sent.
 *
 * @param game game structure.
 * @param texture texture matrix containing direction and path.
 * @param dir cardinal direction
 * @return SUCCESS if fill successfull, or FAILURE if not.
 */
static int	fill_wall_textures(t_game *game, char **texture, int dir)
{
	if (dir == NO)
	{
		if (game->input->wall_no || (texture[2] && texture[2][0] != '\n'))
			return (print_error(ERR_TEXTURES), FAILURE);
		game->input->wall_no = ft_strdup(texture[1]);
	}
	if (dir == SO)
	{
		if (game->input->wall_so || (texture[2] && texture[2][0] != '\n'))
			return (print_error(ERR_TEXTURES), FAILURE);
		game->input->wall_so = ft_strdup(texture[1]);
	}
	if (dir == WE)
	{
		if (game->input->wall_we || (texture[2] && texture[2][0] != '\n'))
			return (print_error(ERR_TEXTURES), FAILURE);
		game->input->wall_we = ft_strdup(texture[1]);
	}
	if (dir == EA)
	{
		if (game->input->wall_ea || (texture[2] && texture[2][0] != '\n'))
			return (print_error(ERR_TEXTURES), FAILURE);
		game->input->wall_ea = ft_strdup(texture[1]);
	}
	return (SUCCESS);
}

/**
 * @brief Remove EA and WE textures newlines.
 *
 * This function fills the wall textures according to their cardinal direction.
 *
 * @param game game structure.
 * @param texture texture matrix containing direction and path.
 * @return SUCCESS if fill successful, or FAILURE if not or if unknown char.
 */
static int	wall_identifier(t_game *game, char **texture)
{
	if (ft_strictcmp(texture[0], "N") || ft_strictcmp(texture[0], "NO"))
	{
		if (fill_wall_textures(game, texture, NO) == FAILURE)
			return (FAILURE);
	}
	else if (ft_strictcmp(texture[0], "S") || ft_strictcmp(texture[0], "SO"))
	{
		if (fill_wall_textures(game, texture, SO) == FAILURE)
			return (FAILURE);
	}
	else if (ft_strictcmp(texture[0], "W") || ft_strictcmp(texture[0], "WE"))
	{
		if (fill_wall_textures(game, texture, WE) == FAILURE)
			return (FAILURE);
	}
	else if (ft_strictcmp(texture[0], "E") || ft_strictcmp(texture[0], "EA"))
	{
		if (fill_wall_textures(game, texture, EA) == FAILURE)
			return (FAILURE);
	}
	else if (!ft_strictcmp(texture[0], "F") && !ft_strictcmp(texture[0], "C"))
		return (print_error(ERR_TEXTURES), FAILURE);
	return (SUCCESS);
}

/**
 * @brief Parse the identifier.
 *
 * This function splits the line passed as parameter and calls the functions to
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
	if (!texture || !texture[0])
		return (free_matrix_safe(texture), SUCCESS);
	if (texture[0][0] == '\n')
		return (free_matrix_safe(texture), SUCCESS);
	if (wall_identifier(game, texture) == FAILURE)
		return (free_matrix_safe(texture), FAILURE);
	if (color_identifier(game, content) == FAILURE)
		return (free_matrix_safe(texture), FAILURE);
	return (free_matrix_safe(texture), SUCCESS);
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
		while (content[i][j] == ' ')
			j++;
		if (parse_identifier(game, content[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	if (!game->input->wall_no || !game->input->wall_so
		|| !game->input->wall_ea || !game->input->wall_we)
		return (print_error(ERR_MISSING_TEXTURES), FAILURE);
	i = 0;
	while (i <= 2)
	{
		if (game->input->color_c[i] == -1 || game->input->color_f[i] == -1)
			return (print_error(ERR_MISSING_COLOR), FAILURE);
		i++;
	}
	return (SUCCESS);
}
