/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:05:08 by tgastelu          #+#    #+#             */
/*   Updated: 2024/11/29 17:41:05 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	place_2(char **map, int x, int y)
{
	if (map[y][x + 1] != '1' && map[y][x + 1] != '2' && map[y][x + 1] != 'P')
		return ((map[y][x + 1] = '2'), 1);
	if (map[y][x - 1] != '1' && map[y][x - 1] != '2' && map[y][x - 1] != 'P')
		return ((map[y][x - 1] = '2'), 1);
	if (map[y + 1][x] != '1' && map[y + 1][x] != '2' && map[y + 1][x] != 'P')
		return ((map[y + 1][x] = '2'), 1);
	if (map[y - 1][x] != '1' && map[y - 1][x] != '2' && map[y - 1][x] != 'P')
		return ((map[y - 1][x] = '2'), 1);
	return (0);
}

int	p_good(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				if (map[y - 1][x] == '2' || map[y + 1][x] == '2'
					|| map[y][x - 1] == '2' || map[y][x + 1] == '2')
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_free(t_game *game, char **map)
{
	int	y;

	if (!game->map_ber)
		return ;
	y = num_line_map(game);
	while (y > 0)
	{
		y--;
		free(map[y]);
	}
	free(map);
}

int	find_p(t_game *game, int x, int y)
{
	char	**map;

	map = fill_map_ber(game);
	if (!map)
		return (0);
	place_2(map, x, y);
	y = -1;
	while (y++, map[y])
	{
		x = -1;
		while (x++, map[y][x])
		{
			if (map[y][x] == '2')
			{
				if (p_good(map) == 1)
					return (ft_free(game, map), 1);
				if (place_2(map, x, y) == 1)
				{
					y = -1;
					break ;
				}
			}
		}
	}
	return (ft_free(game, map), 0);
}

int	find(t_game *game, char **map)
{
	int	x;
	int	y;
	int	r_value;

	r_value = 1;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'E')
				r_value = find_p(game, x, y);
			else if (map[y][x] == 'C')
				r_value = find_p(game, x, y);
			if (r_value == 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
