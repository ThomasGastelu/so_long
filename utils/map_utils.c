/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgastelu <tgastelu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:17:45 by tgastelu          #+#    #+#             */
/*   Updated: 2025/01/08 13:43:29 by tgastelu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	num_line_map(t_game *game)
{
	char	*buffer;
	int		status;
	int		size;
	int		fd;

	fd = open(game->ber, O_RDONLY);
	size = 1;
	buffer = malloc(2);
	if (!buffer)
		return (0);
	buffer[1] = '\0';
	status = read(fd, buffer, 1);
	while (status != 0)
	{
		if (buffer[0] == '\n')
			size++;
		status = read(fd, buffer, 1);
	}
	free(buffer);
	close(fd);
	return (size);
}

int	size_x_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	size_full_map(t_game *game)
{
	int		fd;
	int		size;
	int		r;
	char	*buffer;

	buffer = malloc(2);
	if (!buffer)
		return (0);
	buffer[1] = '\0';
	fd = open(game->ber, O_RDONLY);
	r = read(fd, buffer, 1);
	size = -1;
	while (size++, r > 0)
		r = read(fd, buffer, 1);
	free(buffer);
	close(fd);
	return (size);
}

char	*fill_mapp_ber(t_game *game)
{
	int		fd;
	int		r;
	int		i;
	char	*str;
	char	*buffer;

	i = size_full_map(game);
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	buffer = malloc(2);
	if (!buffer)
		return (NULL);
	buffer[1] = '\0';
	fd = open(game->ber, O_RDONLY);
	r = read(fd, buffer, 1);
	i = -1;
	while (i++, r > 0)
	{
		str[i] = buffer[0];
		r = read(fd, buffer, 1);
	}
	free(buffer);
	return (close(fd), str);
}

char	**fill_map_ber(t_game *game)
{
	char	*str;
	char	**map;
	int		i;

	i = 0;
	str = fill_mapp_ber(game);
	if (!str)
		return (NULL);
	while (str[i + 1])
		i++;
	if (str[i] == '\n')
		return (free(str), NULL);
	map = ft_split(str, '\n');
	if (!map)
		return (ft_free(game, map), NULL);
	free(str);
	return (map);
}
