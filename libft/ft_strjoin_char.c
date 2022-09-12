#include "../minishell.h"

char	*ft_strjoin_char(char const *s1, char s2)
{
	char	*p;
	size_t	i;
	int		j;

	j = 0;
	if (s1 != NULL && s2 )
		i = ft_strlen(s1) + 1;
	else
		return (0);
	p = (char *)malloc(i + 1);
	if (!p)
		return (0);
	while (s1[j])
		*p++ = s1[j++];
	*p++ = s2;
	*p = '\0';
	free((char *)s1);
	return (p - i);
}