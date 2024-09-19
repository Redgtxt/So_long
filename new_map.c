/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:21:25 by hguerrei          #+#    #+#             */
/*   Updated: 2024/09/18 13:42:08 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	build_matrix(char *file, t_data *vars)
{
	int		fd;
	int		i;
	char	*line;

	vars->map.matrix = (char **)malloc(vars->map.rows * sizeof(char *));
	if (!vars->map.matrix)
		return (0); // Ajustado para retornar em caso de erro, evitando liberar um ponteiro não inicializado.
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(vars->map.matrix);
		error_message();
	}
	i = 0;
	while ((line = get_next_line(fd)))
	{
		vars->map.matrix[i] = line;
		i++;
	}
	close(fd);
	check_walls(vars);
	check_rectangular(vars);
	check_letters(vars);
	vars->map.map_width = vars->map.column * SIZE_PIXEL;
	vars->map.map_height = vars->map.rows * SIZE_PIXEL;
	return (1);
}


int	read_map(char *file, t_data *vars)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		error_message();
	}
	vars->map.column = 0;
	while (line[vars->map.column] != '\0' && line[vars->map.column] != '\n')
		vars->map.column++;
	vars->map.rows = 0;
	while (line)
	{
		vars->map.rows++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
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

	if (!matrix)
		return;
	i = 0;
	while (i < rows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

