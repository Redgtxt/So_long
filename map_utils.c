/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:21:11 by hguerrei          #+#    #+#             */
/*   Updated: 2024/09/18 13:48:34 by hguerrei         ###   ########.fr       */
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

void check_walls(t_data *vars)
{
    int i;

	i = 0;
    while (i < vars->map.column )
    {
        if (vars->map.matrix[0][i] != '1' || vars->map.matrix[vars->map.rows - 1][i] != '1')
        {
            free_matrix(vars->map.matrix,vars->map.rows);
            error_message();
        }
		i++;
    }

	i = 0;
    while ( i < vars->map.rows)
    {
        if (vars->map.matrix[i][0] != '1' || vars->map.matrix[i][vars->map.column - 1] != '1')
        {
            free_matrix(vars->map.matrix,vars->map.rows);
            error_message();
        }
		i++;
    }
}


void error_message(void)
{
	ft_printf("ERROR\n");
	exit(1);
}

void check_rectangular(t_data *vars)
{
    int i;

	i = 0;
    while ( i < vars->map.rows)
    {
        if ((ft_strlen_no_newline(vars->map.matrix[i]) != vars->map.column))
        {
            free_matrix(vars->map.matrix,vars->map.rows);
            error_message();
        }
	i++;
    }
}
int check_name (char *path)
{
    int i;

    i = 0;
    while (path[i] && path[i] != '.')
        i++;
    if(path[i] == '\0' || ft_strncmp(path + i,".ber",4) != 0)
    {
        error_message();
    }
    return 1;
}





