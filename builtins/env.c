#include "../minishell.h"

void env(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while(tmp)
    {
        printf("%s=%s\n",tmp->Var,tmp->Value);
        tmp=tmp->next;
    }
}