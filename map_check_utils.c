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







