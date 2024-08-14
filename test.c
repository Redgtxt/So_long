#include "so_long.h"
//Começar por tratar do mapa
//Posso usar o GNL para ler o mapa e fazer a verificação do mesmo
/*
int check_map(fd)
{
   
}*/


void exit_program(void)
{
    ft_printf("Mensagem de erro customizada\n");
    exit(EXIT_FAILURE);
}

int main(void)
{
    int fd;
    size_t length;

    // Se acontecer algum erro ao abrir o mapa, fecho o programa
    fd = open("map.ber", O_RDONLY);
    if (fd < 0)
        exit_program();

    // Se a linha for nula (não tiver conteúdo), paro o programa
    char *line = get_next_line(fd);
    if (line == NULL)
        exit_program();

    length = ft_strlen(line);

    // Loop para verificar o conteúdo do mapa
    while (line)
    {
        // Saio do programa se as linhas não tiverem o mesmo tamanho
        if (ft_strlen(line) != length)
            exit_program();

        printf("%s", line);
        //printf("Comprimento da linha: [%zu]\n", length);

        free(line);
        line = get_next_line(fd);
    }

    close(fd);  // Fechar o arquivo após terminar
    return 0;
}