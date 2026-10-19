/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:37:16 by hguerrei          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Second pass over the file: one get_next_line string per row. The shape
   is checked before the walls, because check_walls reads every row at the
   first row's width and would read past the end of a shorter one. */
int	build_matrix(char *file, t_data *vars)
{
	int		fd;
	int		i;
	char	*line;

	vars->map.matrix = ft_calloc(vars->map.rows, sizeof(char *));
	if (!vars->map.matrix)
		error_message(vars, "out of memory");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_message(vars, "cannot open the map file");
	line = get_next_line(fd);
	i = 0;
	while (line && i < vars->map.rows)
	{
		vars->map.matrix[i++] = line;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	check_rectangular(vars);
	check_walls(vars);
	check_letters(vars);
	vars->map.map_width = vars->map.column * SIZE_PIXEL;
	vars->map.map_height = vars->map.rows * SIZE_PIXEL;
	return (1);
}

/* First pass: measure the first row and count the rows, so the second pass
   can allocate the row array exactly once. */
int	read_map(char *file, t_data *vars)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_message(vars, "cannot open the map file");
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		error_message(vars, "the map file is empty");
	}
	vars->map.column = ft_strlen_no_newline(line);
	vars->map.rows = 0;
	while (line)
	{
		vars->map.rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	build_matrix(file, vars);
	return (0);
}

char	**copy_matrix(t_data *vars)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (vars->map.rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < vars->map.rows)
	{
		copy[i] = ft_strdup(vars->map.matrix[i]);
		if (!copy[i])
		{
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_matrix(char **matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
