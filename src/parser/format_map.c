/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:29:04 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 12:07:06 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_width(char **map)
{
	int	i;
	int	max_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)max_width)
			max_width = ft_strlen(map[i]);
		i++;
	}
	return (max_width);
}

static int	is_map_char(char c)
{
	if (c == '0' || c == '1')
		return (SUCCESS);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (SUCCESS);
	return (FAILURE);
}

static char	**copy_map(t_game *game, char **map, int max_width)
{
	int		i;
	int		j;
	char	**cpy;

	i = 0;
	cpy = ft_calloc(game->input->map_height + 1, sizeof(char *));
	if (!cpy)
		return (NULL);
	while (map[i])
	{
		j = 0;
		cpy[i] = ft_calloc(max_width + 1, sizeof(char));
		if (!cpy[i])
			return (free_matrix_safe(cpy), NULL);
		while (map[i][j])
		{
			if (is_map_char(map[i][j]) == SUCCESS)
				cpy[i][j] = map[i][j];
			else 
				cpy[i][j] = '-';
			j++;
		}
		i++;
	}
	return (cpy);
}

static char **fill_voids(char **rect_map, int max_width)
{
	int	i;
	int	j;

	i = 0;
	while (rect_map[i])
	{
		j = 0;
		while (rect_map[i][j])
			j++;
		while (j < max_width)
		{
			rect_map[i][j] = '-';
			j++;
		}
		i++;
	}
	return (rect_map);
}

int	map_to_rectangle(t_game *game, char **map)
{
	int		max_width;
	char	**rect_map;

	max_width = get_max_width(map);
	rect_map = copy_map(game, map, max_width);
	if (!rect_map)
		return (print_error(ERR_MALLOC), FAILURE);
	rect_map = fill_voids(rect_map, max_width);
	free_matrix_safe(map);
	game->input->map = rect_map;
	return (SUCCESS);
}
