/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:14:42 by tgastelu          #+#    #+#             */
/*   Updated: 2025/01/07 12:30:19 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	p_image(t_game *game, void *texture, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, texture, x * 40, y * 40);
}

void	fill_screen(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (y++, game->map_ber[y])
	{
		x = -1;
		while (x++, game->map_ber[y][x])
		{
			if (game->map_ber[y][x] == '0')
				p_image(game, game->floor, x, y);
			if (game->map_ber[y][x] == 'C')
				p_image(game, game->banana, x, y);
			if (game->map_ber[y][x] == 'E')
				p_image(game, game->door, x, y);
			if (game->map_ber[y][x] == '1')
				p_image(game, game->wall, x, y);
			if (game->map_ber[y][x] == 'P')
				p_image(game, game->player, x, y);
		}
	}
}

void	*xpm(t_game *game, char *text)
{
	int	largeur;
	int	hauteur;

	return (mlx_xpm_file_to_image(game->mlx, text, &largeur, &hauteur));
}

void	file_to_image(t_game *game)
{
	game->wall = xpm(game, "textures/wall.xpm");
	if (!game->wall)
		demolisateur(game);
	game->floor = xpm(game, "textures/floor.xpm");
	if (!game->floor)
		demolisateur(game);
	game->player = xpm(game, "textures/king.xpm");
	if (!game->player)
		demolisateur(game);
	game->door = xpm(game, "textures/door.xpm");
	if (!game->door)
		demolisateur(game);
	game->banana = xpm(game, "textures/banana.xpm");
	if (!game->banana)
		demolisateur(game);
	game->open_door = xpm(game, "textures/open_door.xpm");
	if (!game->open_door)
		demolisateur(game);
	game->king_door = xpm(game, "textures/king_door.xpm");
	if (!game->king_door)
		demolisateur(game);
}
