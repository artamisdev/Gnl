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
        storage = ft_strjoin(storage, buffer); // Proteção para o malloc do strjoin
        free(aux);
    }
    free(buffer);
    return (storage);
}

static  char *catch_line(char *str)
{
    int     i;
    char    *line;

    i = 0;
    if (!str || str[0] == '\0')
        return (NULL);
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    if (str[i] == '\n')
      i++;
    line = ft_calloc(sizeof(char), i + 1);
    if (!line)
        return (NULL);
    i = 0;
    while (str[i] != '\n' && str[i] != '\0')
    {
        line[i] = str[i];
        ++i;
    }
    if (str[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return (line);
}

char    *reload_storage(char *storage)
{
    int     len;
    char    *post_nl;

    post_nl = ft_strchr(storage, '\n');
    len = ft_strlen(post_nl + 1);
    if (len == 0)
    {
        free(storage);
        return (NULL);
    }
    ft_memmove(&storage[0], post_nl + 1, len);
    storage[len + 1] = '\0';
    return (storage);
}


char    *get_next_line(int fd)
{
    static char *storage;
    char    *line;

    storage = read_function(fd, storage);//Primeiro
    if (!storage)
        return(NULL);
    line = catch_line(storage);
    if (!line)
    {
        free(storage);
        storage = NULL;
        return (NULL);
    }
    storage = reload_storage(storage);
    return (line);
}
