/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:03:39 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:20:46 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Convert an rbg string to int.
 *
 * This function converts an rgb string to an int. If also checks that each
 * char is a digit, and that the value doesn't exceed 255.
 *
 * @param str string containing the rgb values.
 * @return res if convertion successful, or -1 if not.
 */
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

/**
 * @brief Fill the structure with the values.
 *
 * This function fills the structure with the color values.
 *
 * @param game game structure.
 * @param content content of the file.
 * @param c color identifier.
 * @return SUCCESS if values are correctly formatted, or FAILURE if not.
 */
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

/**
 * @brief Check that the values are properly formatted.
 *
 * This function checks that the color are correctly formatted and then calls
 * the function to fill the structure with the corresponding values.
 *
 * @param game game structure.
 * @param content content of the file.
 * @param i position of the color values.
 * @param c color identifier.
 * @return SUCCESS if structure filled properly, or FAILURE if not.
 */
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
	if (!rgb[2] || rgb[3])
		return (free_matrix_safe(rgb), print_error(ERR_INVALID_COLOR), FAILURE);
	if (fill_color_values(game, rgb, c) == FAILURE)
		return (free_matrix_safe(rgb), FAILURE);
	free_matrix_safe(rgb);
	return (SUCCESS);
}

/**
 * @brief Call the function to fill the colors in the structure.
 *
 * This function checks string sent contains a correct color identifier
 * ('C' or 'F'), and calls a function to fill the structure with the
 * appropriate informations.
 *
 * @param game game structure.
 * @param content content of the file.
 * @return SUCCESS if color exists and is filled properly, or FAILURE if not.
 */
int	color_identifier(t_game *game, char *content)
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

/**
 * @brief Convert RGB to hex.
 *
 * This function transforms the 3 RGB values for floor and ceiling, to hex.
 *
 * @param game game structure.
 */
void	colors_to_hex(t_game *game)
{
	game->input->hex_f = (((game->input->color_f[0] & 0xff) << 16)
			+ ((game->input->color_f[1] & 0xff) << 8)
			+ (game->input->color_f[2] & 0xff));
	game->input->hex_c = (((game->input->color_c[0] & 0xff) << 16)
			+ ((game->input->color_c[1] & 0xff) << 8)
			+ (game->input->color_c[2] & 0xff));
}
