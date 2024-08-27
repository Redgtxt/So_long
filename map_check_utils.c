#include "so_long.h"

void exit_program(void)
{
    ft_printf("Mensagem de erro customizada\n");
    exit(EXIT_FAILURE);
}

int check_name (char *path)
{
    int i;

    i = 0;
    while (path[i] && path[i] != '.')
        i++;
    if(path[i] == '\0' || ft_strncmp(path + i,".ber",4) != 0)
    {
        exit_program();
    }
    return 1;
}

void init_variables(t_data vars)
{
    vars.mlx = NULL;
    vars.win = NULL;
    vars.img = NULL;
    vars.addr = NULL;
    vars.bits_per_pixel = 0;
    vars.line_length = 0;
    vars.endian = 0;
    

}





