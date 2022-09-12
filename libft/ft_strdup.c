#include "../minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	p = (char *)malloc(sizeof(char) * (i + 1));
	if (!p)
		return (0);
	while (i)
	{
		p[j] = s1[j];
		i--;
		j++;
	}
	p[j] = '\0';
	return (p);
}
