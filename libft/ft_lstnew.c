#include "../minishell.h"

t_list	*ft_lstnew(char *content, int flag)
{
	t_list	*p;

	p = (t_list *) malloc(sizeof(t_env));
	if (!p)
		return (0);
	p->token = content;
	p->flag = flag;
	p->next = NULL;
	return (p);
}