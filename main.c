

#include <stdio.h>

// #include "get_next_line.h"
// int    main(void)
// {
//     int fd;
//     char *result;

//     fd = open("teste.txt", O_RDONLY);
//     result = get_next_line(fd);
//     while (result != NULL)
//     {
//         printf("%s", result);
//         result = get_next_line(fd);
//     }
//     close(fd);
//     return(0);
// }

#include "get_next_line_bonus.h"
int main(void) //for bonus
{
    int fd1;
    int fd2;
    int fd3;
    char    *result1;
    char    *result2;
    char    *result3;

    fd1 = open("teste_bonus1.txt", O_RDONLY);
    fd2 = open("teste_bonus2.txt", O_RDONLY);
    fd3 = open("teste_bonus3.txt", O_RDONLY);

    printf("First Line:\n");
    result1 = get_next_line(fd1);
    printf("%s", result1);
    result2 = get_next_line(fd2);
    printf("%s", result2);
    result3 = get_next_line(fd3);
    printf("%s", result3);

    printf("Second Line:\n");
    result1 = get_next_line(fd1);
    printf("%s", result1);
    result2 = get_next_line(fd2);
    printf("%s", result2);
    result3 = get_next_line(fd3);
    printf("%s", result3);

    close(fd1);
    close(fd2);
    close(fd3);
}
