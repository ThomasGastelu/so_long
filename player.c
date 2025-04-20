/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:30:49 by tgastelu          #+#    #+#             */
/*   Updated: 2025/01/07 12:31:21 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

int	*find_pos(char **map, char c)
{
	int	*tab;
	int	y;
	int	x;

	tab = malloc(sizeof(int) * 2);
	if (!tab)
		return (NULL);
	y = -1;
	while (y++, map[y])
	{
		x = -1;
		while (x++, map[y][x])
		{
			if (map[y][x] == c)
			{
				tab[0] = y;
				tab[1] = x;
				return (tab);
			}
		}
	}
	return (tab);
}

int	open_dor(t_game *game)
{
	int	x;
	int	y;
	int	*tab;

	y = -1;
	while (y++, game->map_ber[y])
	{
		x = -1;
		while (x++, game->map_ber[y][x])
		{
			if (game->map_ber[y][x] == 'C')
				return (0);
		}
	}
	tab = find_pos(game->map_ber, 'E');
	if (tab == NULL)
		return (-1);
	mlx_put_image_to_window(game->mlx, game->win,
		game->open_door, tab[1] * 40, tab[0] * 40);
	free(tab);
	return (1);
}

int	move(t_game *game, int temp_x, int temp_y)
{
	if (game->map_ber[temp_y][temp_x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->door, temp_x * 40, temp_y * 40);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->floor, temp_x * 40, temp_y * 40);
	if (game->map_ber[game->y][game->x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->king_door, game->x * 40, game->y * 40);
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->player, game->x * 40, game->y * 40);
	if (temp_x != game->x || temp_y != game->y)
	{
		game->move += 1;
		ft_putnbr_fd(game->move, 1);
		ft_putchar_fd('\n', 1);
	}
	return (1);
}

int	mooving_player(int keycode, void *stru)
{
	t_game	*game;
	int		temp_x;
	int		temp_y;

	game = (t_game *)stru;
	temp_y = game->y;
	temp_x = game->x;
	if (keycode == 97 && if_wall(game->map_ber, game->x - 1, game->y))
		game->x -= 1;
	else if (keycode == 119 && if_wall(game->map_ber, game->x, game->y - 1))
		game->y -= 1;
	else if (keycode == 100 && if_wall(game->map_ber, game->x + 1, game->y))
		game->x += 1;
	else if (keycode == 115 && if_wall(game->map_ber, game->x, game->y + 1))
		game->y += 1;
	else if (keycode == 65307)
		demolisateur(game);
	if (open_dor(game) == 1 && game->map_ber[game->y][game->x] == 'E')
		demolisateur(game);
	if (game->map_ber[game->y][game->x] == 'C')
		game->map_ber[game->y][game->x] = '0';
	open_dor(game);
	return (move(game, temp_x, temp_y), 0);
}

void	player_settings(t_game *game)
{
	int	*tab;

	tab = find_pos(game->map_ber, 'P');
	game->y = tab[0];
	game->x = tab[1];
	free(tab);
	open_dor(game);
	mlx_key_hook(game->win, mooving_player, game);
	mlx_hook(game->win, 17, 0, demolisateur, game);
}
