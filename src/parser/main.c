/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:14:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/09 16:57:56 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		(print_error(WRONG_ARG_NB), exit(EXIT_FAILURE));
	if (parser(av) == FAILURE)
		exit(TMP); 
	return (EXIT_SUCCESS);
}
