/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:09:40 by tgastelu          #+#    #+#             */
/*   Updated: 2025/01/08 13:43:13 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../so_long.h"

int	whiling_check_char(char **map, char c)
{
	int	i;
	int	f;

	i = 0;
	while (map[i])
	{
		f = 0;
		while (map[i][f] && map[i][f] != '\n')
		{
			if (map[i][f] == c)
				return (1);
			f++;
		}
		i++;
	}
	return (0);
}

int	check_char(char **map)
{
	char	*chars;

	chars = "01CEP";
	while (*chars)
	{
		if (whiling_check_char(map, chars[0]) == 0)
			return (0);
		chars++;
	}
	return (1);
}

int	check_rect(char **map)
{
	int	i;
	int	f;
	int	size;

	size = 0;
	while (map[0][size] && map[0][size] != '\n')
		size++;
	i = 0;
	while (map[i])
	{
		f = 0;
		while (map[i][f] && map[i][f] != '\n')
			f++;
		if (f != size)
			return (0);
		i++;
	}
	return (size);
}

int	check_wall(char **map, int size)
{
	int	i;

	i = 0;
	while (map[0][i] && map[0][i] != '\n')
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	i = 1;
	while (map[i + 1])
	{
		if (map[i][0] != '1')
			return (0);
		else if (map[i][size] != '1')
			return (0);
		i++;
	}
	while (size >= 0)
	{
		if (map[i][size] != '1')
			return (0);
		size--;
	}
	return (1);
}

int	parsing(t_game *game)
{
	int	size;

	game->map_ber = fill_map_ber(game);
	if (!game->map_ber)
		return (0);
	if (check_char(game->map_ber) == 0)
		return (0);
	size = check_rect(game->map_ber);
	if (size == 0)
		return (0);
	if (check_wall(game->map_ber, size - 1) == 0)
		return (0);
	if (find(game, game->map_ber) == 0)
		return (0);
	return (1);
}
