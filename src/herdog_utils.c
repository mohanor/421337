#include "../minishell.h"

char    *get_unigue_name(void)
{
    static int    nbr;

    nbr++;
    return (ft_itoa(nbr));
}

int    file_exists(char *filename)
{
    struct dirent    *entity;
    DIR                *dir;

    dir = opendir("/tmp/");
    if (dir == NULL)
        return (0);
    entity = readdir(dir);
    while (entity != NULL)
    {
        if (!ft_strcmp(entity->d_name, filename))
            return (1);
        entity = readdir(dir);
    }
    closedir(dir);
    return (0);
}

char    *while_file_existe(char *filename)
{
    if (file_exists(filename))
        return (while_file_existe(ft_strjoin(filename, "_her")));
    return (filename);
}

int find_first_herdog(char *line)
{
    int i;
    
    i = 0;
    while(line[i])
    {
        scape_s_d_quot(line, &i);
        if(line[i] == '<' && line[i +1 ] == '<')
            return (i);
        i++;
    }
    return(-1);
}