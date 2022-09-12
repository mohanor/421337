#include "../minishell.h"

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*tmp;

	if (*alst)
	{
		tmp = ft_lstlast_env((*alst));
		tmp -> next = new;
        new->prev = tmp;
	}
	else
		*alst = new;
}