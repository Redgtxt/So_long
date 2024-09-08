#include "so_long.h"

void find_player(t_map *vars, int *player_x, int *player_y)
{
    int i;
    int j;

    i = 0;
    while (i < vars->rows)
    {
        j = 0;
        while (j < vars->column)
        {
            if (vars->matrix[i][j] == 'P')
            {
                *player_x = j + 1;
                *player_y = i + 1;
                printf("Jogador encontrado na posição X: %d, Y: %d\n", *player_x, *player_y);
                return;
            }
            j++;
        }
        i++;
    }
    error_message();
}
void check_conditions(t_map *vars)
{
    int i;
    int j;
    int c_count;
    int p_count;
    int exit_count;

    exit_count = 0;
    p_count = 0;
    c_count = 0;
    i = 0;
    while (i < vars->rows)
    {
        j = 0;
        while (j < vars->column)
        {
            if (vars->matrix[i][j] == 'C')
                c_count++;
            if(vars->matrix[i][j] == 'P')
                p_count++;
            if(vars->matrix[i][j] == 'E')
                exit_count++;
            j++;
        }
        i++;
    }
    if(c_count <= 0 || p_count != 1 || exit_count != 1)
        error_message();
}

void flood_fill(t_map *vars, int x, int y, int *found_exit,char Symbol)
{

    if (x < 0 || x >= vars->column || y < 0 || y >= vars->rows || vars->matrix[y][x] == '1')
        return;

    if (vars->matrix[y][x] == Symbol)
    {
        *found_exit = 1;
        return;
    }

    if (vars->matrix[y][x] == 'V')
        return;

    vars->matrix[y][x] = 'V';

    // Recursivamente aplica o Flood Fill nas 4 direções
    flood_fill(vars, x - 1, y, found_exit,Symbol);  // Esquerda
    flood_fill(vars, x + 1, y, found_exit,Symbol);  // Direita
    flood_fill(vars, x, y - 1, found_exit,Symbol);  // Cima
    flood_fill(vars, x, y + 1, found_exit,Symbol);  // Baixo
}

void check_path_player_to(t_map *vars, t_player_info *info,char Symbol)
{
    int found_exit = 0;//Flag


    if (info->player_xstart == -1 || info->player_ystart == -1)
        error_message();

    // Executa o Flood Fill a partir da posição do jogador
    flood_fill(vars, info->player_xstart - 1, info->player_ystart - 1, &found_exit,Symbol);//-1 pq na funcao find player tive de adiconar 1 para encontrar  a posicao do player

    if (found_exit == 0)
     error_message();
}
void check_letters(t_map *vars)
{
    t_player_info info;
    info.player_xstart = -1;
    info.player_ystart = -1;
    find_player(vars, &info.player_xstart, &info.player_ystart);
    check_conditions(vars);
    check_path_player_to(vars, &info,'E'); 
    check_path_player_to(vars, &info,'C'); 
}