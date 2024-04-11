/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:42:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/11 12:06:07 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rgb_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]))
		return (-1);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0' && str[i] != '\n')
		return (-1);
	if (res > 255)
		return (-1);
	return (res);
}

static int	fill_color_values(t_game *game, char **rgb, char c)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (rgb_atoi(rgb[i]) < 0)
			return (print_error(ERR_INVALID_COLOR), FAILURE);
		if (c == 'F')
			game->input->color_f[i] = rgb_atoi(rgb[i]);
		if (c == 'C')
			game->input->color_c[i] = rgb_atoi(rgb[i]);
		i++;
	}
	return (SUCCESS);
}

static int	check_color_values(t_game *game, char *content, int i, char c)
{
	char	**rgb;

	while (content[i] == ' ')
		i++;
	if (!ft_isdigit(content[i]))
		return (print_error(ERR_INVALID_COLOR), FAILURE);
	rgb = ft_split(content + i, ',');
	if (!rgb)
		return (print_error(ERR_MALLOC), FAILURE);
	if (rgb[3] || !rgb[2])
		return (print_error(ERR_INVALID_COLOR), FAILURE);
	if (fill_color_values(game, rgb, c) == FAILURE)
		return (FAILURE);
	//if (c == 'F')
	return (SUCCESS);
}

static int	f_c_identifier(t_game *game, char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		while (content[i] == ' ')
			i++;
		if ((content[i] == 'F' || content[i] == 'C') && content[i + 1]
			&& content[i + 1] == ' ')
		{
			if (check_color_values(game, content, i + 1, content[i]) == FAILURE)
				return (FAILURE);
			break ;
		}
		i++;
	}
	return (SUCCESS);
}

static int	fill_wall_textures(t_game *game, char **texture, int dir)
{
	if (dir == NO)
	{
		if (game->input->wall_no || (texture[2] && texture[2][0] != '\n'))
			return (print_error(ERR_TEXTURES), FAILURE); //err_dup_textures
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
		return (print_error(ERR_TEXTURES), FAILURE); //err unidentified texture
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
	if (texture[0][0] == '\n')
		return(free_matrix_safe(texture), SUCCESS);
	if (wall_identifier(game, texture) == FAILURE)
		return (free_matrix_safe(texture), FAILURE);
	if (f_c_identifier(game, content) == FAILURE)
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
			return (FAILURE); // need to write error;
		i++;
	}
	if (!game->input->wall_no || !game->input->wall_so ||
		!game->input->wall_ea || !game->input->wall_we)
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
