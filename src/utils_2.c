#include "../minishell.h"

void scape_t_d_s_qout(char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if((line[i] == '\"' && line[i+1] == '\"') ||  (line[i] == '\'' && line[i+1] == '\''))
        {
            line[i] = ' ';
            line[i+1] = ' ';
            i+=2;
        }
        scape_s_d_quot(line,&i);
        i++;
        
    }
    return;
}