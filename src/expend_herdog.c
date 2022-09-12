#include "../minishell.h"

char *delmeteur(char *line, int *k, char *s, char *del)
{
    char c;
    int i;

    i = *k;
    while(ft_strchr(s,line[i]) != 1 && line[i])
    {
        if(line[i] == '\"' || line[i] == '\'')
        {
            c = line[i];
            i++;
            while ( line[i] != c && line[i] != '\0')
            {   
                del = ft_strjoin_char(del,line[i]);
                i++; 
            }
            i++;
        }
        else 
        {
            del = ft_strjoin_char(del,line[i]);
            i++; 
        }
    }
    *k = i;
    return(del);
} 

char *find_del(char *line, int *k)
{
    int i;
    char *del;
    char *s;

    s = ft_strdup(" <>|&");
    del = ft_strdup("");
    i = *k;
    if(line[i] == '<' && line[i+1] == '<')
    {
        i++;
        i = a_e(line,i+1);
        del = delmeteur(line,&i,s,del);
        if(line[a_e(line,i)]== '<' && line[a_e(line,i)+1]== '<')
        {
            while(line[i] != '<' )
                i++;
        }
        *k = i;
        free(s);
        return(del);
    }
    free(s);
    return(NULL);
}

char *make_cmd(char * line, int k,int i, char *file_n)
{
    int j;
    char *s;

    j = 0;
    s= ft_strdup("");
    while(line[j])
    {
        if(j == k)
        {
            s = ft_strjoin(s,file_n);
            j = i;
        }
        if(line[j] != '\0')
        {
            s = ft_strjoin_char(s,line[j]);
            j++;
        }
    }
    free(line);
    return(s);
}

char *replac_herdog(char *line, int i)
{
    int fd;
    char *line_inp;
    char *del;
    int k = i;
    char *file_n;

    line_inp="";
    file_n= ft_strjoin(ft_strdup("/tmp/"),while_file_existe(get_unigue_name()));
    printf("%s\n",file_n);
    while(1)
    {
        del = find_del(line,&i);
        if(!del)
            break;            
        fd = open(file_n, O_RDONLY | O_WRONLY  |O_CREAT  , 0644 );
        while(1)
        {
            line_inp = readline(">");
            if(ft_strcmp(line_inp,del) == 0)
                break;
            ft_putstr_fd(line_inp, fd);
            free(line_inp);
        }
        free(del);
        close(fd);
    }
    return(make_cmd(line, k,i, file_n));
}

char *expend_herdog(char *line)
{
    int i;
    i = 0;
    while(i !=-1)
    {
        i = find_first_herdog(line);
        if(i != -1)
        {
            line = replac_herdog(line,i);
        }
    }
    return(line);    
}