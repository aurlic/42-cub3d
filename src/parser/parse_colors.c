/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:03:39 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 12:17:08 by aurlic           ###   ########.fr       */
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
	if (!rgb[2] || rgb[3])
		return (free_matrix_safe(rgb), print_error(ERR_INVALID_COLOR), FAILURE);
	if (fill_color_values(game, rgb, c) == FAILURE)
		return (free_matrix_safe(rgb), FAILURE);
	free_matrix_safe(rgb);
	return (SUCCESS);
}

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