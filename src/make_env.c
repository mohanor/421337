#include "../minishell.h"

t_env *make_env(char **env)
{
    t_env *envr;
    int i;
    char **s;
    i = 0;
    envr = NULL;
    while(env[i])
    {
        s = ft_split(env[i],'=');
        ft_lstadd_back_env(&envr,ft_lstnew_env(s[0],s[1]));
        i++;
        free(s);
    }
    return (envr);
}