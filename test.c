#include "so_long.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void exit_program(void)
{
    ft_printf("Mensagem de erro customizada\n");
    exit(EXIT_FAILURE);
}

// Verifica se uma linha contém apenas o caractere '1'
void parse_line(char *line, size_t length)
{
    size_t i = 0;
    while (i < length - 1)  // -1 para ignorar o '\n'
    {
        if (line[i] != '1')
            exit_program();
        i++;
    }
}

// Verifica se todas as colunas começam e terminam com '1'
void validate_columns(char *line, size_t length)
{
    if (line[0] != '1' || line[length - 2] != '1')  // -2 para ignorar o '\n'
        exit_program();
}

int count_lines(int fd)
{
    int lines = 0;
    char *line;

    line = get_next_line(fd);
    while (line)
    {
        lines++;
        free(line);
        line = get_next_line(fd);
    }

    // Voltar para o início do arquivo
    lseek(fd, 0, SEEK_SET);

    return lines;
}

void check_for_E(char **map, int map_size, size_t length_first_line)
{
    int e_count = 0;
    int p_count = 0; 
    int c_count = 0; 
    int i = 0;

    while (i < map_size)
    {
        size_t j = 0;
        while (j < length_first_line - 1)  // -1 para ignorar o '\n'
        {
            if (map[i][j] == 'E')
                e_count++;
            if (map[i][j] == 'P')
                p_count++;
            if (map[i][j] == 'C')
                c_count++;
            j++;
        }
        i++;
    }

    // Verifica se há exatamente um 'E'
    if (e_count != 1 || p_count != 1 || c_count < 1)
        exit_program();
}


int main(void)
{
    int fd;
    size_t length_first_line;
    char *line;
    int map_size;
    char **map;

    // Abre o arquivo .ber
    fd = open("map.ber", O_RDONLY);
    if (fd < 0)
        exit_program();

    // Conta o número de linhas no arquivo
    map_size = count_lines(fd);

    // Aloca memória para armazenar todas as linhas do mapa
    map = (char **)malloc(sizeof(char *) * map_size);
    if (!map)
        exit_program();

    // Lê a primeira linha do mapa
    line = get_next_line(fd);
    if (line == NULL)
        exit_program();

    length_first_line = ft_strlen(line);
    parse_line(line, length_first_line);  // Verifica a primeira linha
    map[0] = line;

    int i = 1;
    while (i < map_size)
    {
        line = get_next_line(fd);
        if (line == NULL)
            exit_program();

        // Verifica se todas as linhas têm o mesmo comprimento
        if (ft_strlen(line) != length_first_line)
            exit_program();

        // Verifica se a primeira e a última coluna contêm '1'
        validate_columns(line, length_first_line);

        map[i] = line;
        i++;
    }

    // Verifica a última linha
    parse_line(map[map_size - 1], length_first_line);

    // Verifica a presença do caractere 'E'
    check_for_E(map, map_size, length_first_line);

    // Libera a memória e fecha o arquivo
    i = 0;
    while (i < map_size)
    {
        free(map[i]);
        i++;
    }
    free(map);
    close(fd);  // Fecha o arquivo após terminar
    return 0;
}
