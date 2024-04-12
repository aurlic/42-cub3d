/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:29:04 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 14:25:58 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Get the biggest width in the map.
 *
 * @param map base map.
 * @return max_width.
 */
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

/**
 * @brief Check character validity.
 *
 * @param c char to check.
 * @return SUCCESS if char is valid, FAILURE if not.
 */
static int	is_map_char(char c)
{
	if (c == '0' || c == '1')
		return (SUCCESS);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief Copy old map.
 *
 * This function creates a copy of the base map, in a matrix ready to be filled
 * with '-', and with lines allocated with more memory.
 *
 * @param game game structure.
 * @param map base map.
 * @param max_width maximum width of a line.
 * @return SUCCESS if copy was successful, FAILURE if not.
 */
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

/**
 * @brief Fill voids in lines.
 *
 * This function replaces the '\0' trailing with '-', up to max_width.
 * 
 * @param rect_map new rectangle map.
 * @param max_width maximum width of a line.
 * @return SUCCESS if fill was successful, FAILURE if not.
 */
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

/**
 * @brief Convert base map to rectangle.
 *
 * This function calls the functions necessary to convert the base map to a
 * rectangle map, for easier parsing.
 * 
 * @param game game structure.
 * @param map map matrix.
 * @return SUCCESS if map is correctly changed to a rectangle, FAILURE if not.
 */
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
