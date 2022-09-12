#include "../minishell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}