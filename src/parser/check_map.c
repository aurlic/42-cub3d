/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:29 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/11 19:04:46 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_chars(t_game *game, char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' && map[i][j] == 'S'
				&& map[i][j] == 'W' && map[i][j] == 'E')
				player++;
			if (map[i][j] != 1 && map[i][j] != 0 && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != ' ')
				return (print_error(ERR_INVALID_CHAR), FAILURE);
			j++;
		}
		i++;
	}
	if (player != 1)
		return (print_error(ERR_MULT_PLAYER), FAILURE);
	return (SUCCESS);
}

static int	get_max_width(char **map)
{
	int	i;
	int	max_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_width)
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
			j++;
		}
		i++;
	}
	return (cpy);
}

static int	map_to_rectangle(t_game *game, char **map)
{
	int		i;
	int		j;
	int		max_width;
	char	**rec;

	max_width = get_max_width(map);
	rec = copy_map(game, map, max_width);
	if (!rec)
		return (print_error(ERR_MALLOC), FAILURE);
	return (SUCCESS);
}

// static int	check_middle_lines(t_game *game, char **map)
// {
// 	int	i;
// 	int	j;
// 	int	last_char;

// 	i = 1;
// 	last_char = 0;
// 	while (i < game->input->map_height)
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (map[i][j] == '1')
// 				last_char = j;
			
// 			j++;
// 		}
// 	}
// 	return (SUCCESS);
// }

// static int	check_close(t_game *game, char **map)
// {
// 	int	j;

// 	j = -1;
// 	while (map[0][++j])
// 		if (map[0][j] != ' ' && map[0][j] != '1')
// 			return (print_error(ERR_INVALID_MAP), FAILURE);
// 	check_middle_lines(game, map);
// 	j = -1;
// 	while (map[game->input->map_height][++j])
// 		if (map[game->input->map_height][j] != ' '
// 			&& map[game->input->map_height][j] != '1')
// 			return (print_error(ERR_INVALID_MAP), FAILURE);

// }

int	check_map(t_game *game)
{
	if (check_chars(game, game->input->map) == FAILURE)
		return (FAILURE);
	if (map_to_rectangle(game, game->input->map) == FAILURE)
		return (FAILURE);
	// if (check_closed(game, game->input->map) == FAILURE)
	// 	return (FAILURE);
	/*
	TODO :	parcourir la map a chaque 0, chercher sur ses quatres cote adjacents
			si presence d'un \o -> return une erreur.
	*/
	return (SUCCESS);
}
