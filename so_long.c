/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:51:58 by tgastelu          #+#    #+#             */
/*   Updated: 2025/01/07 12:05:17 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroi_image(t_game *game)
{
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->door)
		mlx_destroy_image(game->mlx, game->door);
	if (game->banana)
		mlx_destroy_image(game->mlx, game->banana);
	if (game->open_door)
		mlx_destroy_image(game->mlx, game->open_door);
	if (game->king_door)
		mlx_destroy_image(game->mlx, game->king_door);
}

int	demolisateur(void *param)
{
	t_game	*game;

	game = (void *)param;
	destroi_image(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	ft_free(game, game->map_ber);
	free(game);
	exit (0);
}

void	parsing_exit(t_game *game, int i)
{
	if (i == 1)
		write(1, "PARSING:\nwrong input", 20);
	ft_free(game, game->map_ber);
	free(game);
	exit(0);
}

void	add_map(t_game *game, int *start)
{
	file_to_image(game);
	fill_screen(game);
	start++;
}

int	main(int ac, char **av)
{
	t_game	*game;
	int		start;

	start = 0;
	if (ac < 2 || ac > 2)
		return (ft_putstr_fd("./so_long mappe.ber", 0), 0);
	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
	game->ber = av[1];
	if (if_ber(game) == 0)
		return (free(game), 0);
	if (parsing(game) == 0)
		parsing_exit(game, 1);
	game->mlx = mlx_init();
	if (!game->mlx)
		parsing_exit(game, 0);
	game->win = mlx_new_window(game->mlx, size_x_map(game->map_ber[0]) * 40,
			num_line_map(game) * 40, "so_long");
	if (!game->win)
		demolisateur(game);
	if (!start)
		add_map(game, &start);
	player_settings(game);
	mlx_loop(game->mlx);
}
