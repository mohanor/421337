#include "../minishell.h"

t_env	*ft_lstnew_env(char	*var,char *value )
{
	t_env	*p;

	p = (t_env *) malloc(sizeof(t_env));
	if (!p)
		return (0);
	p->Var = var;
	p->Value = value;
	p->next = NULL;
    p->prev = NULL;
	return (p);
}