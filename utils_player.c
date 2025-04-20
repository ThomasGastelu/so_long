/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:31:28 by tgastelu          #+#    #+#             */
/*   Updated: 2025/01/07 15:27:32 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

int	if_wall(char **map, int x, int y)
{
	if (map[y][x] == '1')
		return (0);
	return (1);
}

int	if_ber(t_game *game)
{
	int	i;
	int	fd;

	i = 0;
	game->move = 0;
	while (game->ber[i])
		i++;
	i = i - 4;
	if (ft_strncmp(".ber", &game->ber[i], 4) != 0)
		return (write(1, "File error: name", 16), 0);
	fd = open(game->ber, O_RDONLY);
	if (fd < 0)
		return (write(1, "File error: opening", 19), 0);
	close(fd);
	return (1);
}
