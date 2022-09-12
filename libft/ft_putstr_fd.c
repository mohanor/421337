#include "../minishell.h"

void	ft_putstr_fd(char *c, int fd)
{
	int	i;

	i = 0;
	if (c)
	{
		while (c[i])
		{
			write(fd, &c[i], 1);
			i++;
		}
        write(fd, "\n", 1);
    }
}