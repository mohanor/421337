#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	int		i;
	int		j;

	j = 0;
	i = count * size;
	p = (char *)malloc (sizeof(char) * i);
	if (!p)
		return (0);
	while (i)
	{
		p[j] = '\0';
		i--;
		j++;
	}
	return (p);
}