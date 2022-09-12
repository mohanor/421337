#include "../minishell.h"

void    Export(t_env *env, char *input)
{

    (void)env;
    if(ft_strchr(input,'=') == 1 )
    {
        if(ft_strchr(input,' ') == 1)
        {
            printf("Mnishell : bad esignemet\n");
            return;
        }
        if(ft_strchr(input,' ') == 1)
        {
            printf("Mnishell : bad esignemet\n");
            return;
        }
    }
    return;
}