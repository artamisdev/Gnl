#include "get_next_line.h"


char    *read_function(int fd, char *storage)
{
    char *buffer;
    ssize_t chars_read;
    char *aux; 

    buffer = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
    if (!buffer)
        return (0);    
    while (!ft_strchr(storage, '\n'))
    {
        chars_read = read (fd, buffer, BUFFER_SIZE);
        if (chars_read == -1)
        {
            free(storage);
            free(buffer);
            return (NULL);
        }
        if (chars_read == 0)
            break;
        aux = storage;
        storage = ft_strjoin(storage, buffer);
        free(aux);
    }
    free(buffer);
    return (storage);
}

int  main (void)
{
    int fd;
    static char *storage;

    fd = open ("teste.txt", O_RDONLY);
    storage = read_function(fd, storage);
    printf("%s", storage);
}