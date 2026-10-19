/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:29 by hguerrei          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen_no_newline(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i] && string[i] != '\n')
		i++;
	return (i);
}

void	check_walls(t_data *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.column)
	{
		if (vars->map.matrix[0][i] != '1'
			|| vars->map.matrix[vars->map.rows - 1][i] != '1')
			error_message(vars, "the map must be surrounded by walls");
		i++;
	}
	i = 0;
	while (i < vars->map.rows)
	{
		if (vars->map.matrix[i][0] != '1'
			|| vars->map.matrix[i][vars->map.column - 1] != '1')
			error_message(vars, "the map must be surrounded by walls");
		i++;
	}
}

/* The subject asks for "Error\n" followed by an explicit message. Both go
   to stderr, and everything allocated so far is released before exiting. */
void	error_message(t_data *vars, char *reason)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putendl_fd(reason, STDERR_FILENO);
	cleanup(vars);
	exit(EXIT_FAILURE);
}

void	check_rectangular(t_data *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.rows)
	{
		if (ft_strlen_no_newline(vars->map.matrix[i]) != vars->map.column)
			error_message(vars, "the map must be rectangular");
		i++;
	}
}

/* The name must end in .ber, with something before the extension:
   maps/level.ber and ./level.ber are accepted, level.ber.txt and maps/.ber
   are not. */
void	check_name(char *path, t_data *vars)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".ber", 5) != 0
		|| path[len - 5] == '/')
		error_message(vars, "the map file must have a .ber extension");
}
