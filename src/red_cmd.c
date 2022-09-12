#include "../minishell.h"

void    skipe_space(char *str, int *i, int *j)
{
    while (str[*i] && str[*i] == ' ')
        (*i)++;
    *j = *i;
}

t_lst_red	*new_node_r(char *str, char c)
{
	t_lst_red	*new;

	new = (t_lst_red *)malloc(sizeof(t_lst_red));
	if (!new)
		return (NULL);
	new->value = str;
	if (c == '>')
		new->token = "R_OUT";
	else if (c == '<')
		new->token = "R_IN";
	else
		new->token = "APPEND";
	new->next = NULL;
	return (new);
}

void	add_to_lst_r(t_lst_red **lst, char *str, char c)
{
	t_lst_red	*new;
	t_lst_red	*tmp;

	new = new_node_r(str, c);
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_list_args	*new_node(char *str)
{
	t_list_args	*new;

	new = (t_list_args *)malloc(sizeof(t_list_args));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

void	add_to_lst(t_list_args **lst, char *str)
{
	t_list_args	*new;
	t_list_args	*tmp;

	new = new_node(str);
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void print_redictions(char *str, t_lst_red **red, t_list_args **lst)
{
    int     i;
    int     j;
    char    c;

    i = 0;
    while (str[i])
    {
        if (str[i] == '>' || str[i] == '<')
        {
            c = str[i];
            if (str[i + 1] == '>')
            {
                c = 'A';
                i++;
            }
            i++;
            skipe_space(str, &i, &j);
            while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
                i++;
            add_to_lst_r(red, ft_substr(str, j , i - j), c);
            if (str[i] != '>' || str[i] != '<')
                i--;
        }
        else if (str[i] != ' ')
        {
            j = i;
            while (str[i] && str[i] != ' ' && str[i] != '>' && str[i] != '<')
            {
				if (str[i] == '\"' || str[i] == '\'')
				{
					c = str[i];
					while (str[++i] != c);
				}
                i++;
            }
            add_to_lst(lst, ft_substr(str, j, i - j));
        }
        i++;
    }
}

char	**make_tab(t_list_args *lst)
{
	int			i;
	char		**ptr;
	t_list_args	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	ptr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		ptr[i++] = tmp->str;
		tmp = tmp->next;
	}

	ptr[i] = NULL;
	return (ptr);
}

char    **get_path(t_env *env)
{
    t_env   *tmp;

    tmp = env;
    while (tmp)
    {
        if (!ft_strcmp(tmp->Var, "PATH"))
            return (ft_split(tmp->Value, ':'));
        tmp = tmp->next;
    }
    return NULL;
}

void	open_file_to_write_in(char *file_name)
{
	int	fd_file;

	fd_file = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd_file < 0)
	{
		perror("file not exisiste\n");
		return ;
	}
	dup2(fd_file, 1);
	close(fd_file);
}

void	open_file_to_read_from(char *file_name)
{
	int	fd_file;

	fd_file = open(file_name, O_RDONLY);
	if (fd_file < 0)
	{
		perror("file not exisiste\n");
		return ;
	}
	dup2(fd_file, 0);
	close(fd_file);
}

void	open_file_to_append(char *file_name)
{
	int	fd_file;

	fd_file = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd_file < 0)
	{
		perror("file not exisiste\n");
		return ;
	}
	dup2(fd_file, 1);
	close(fd_file);
}

void	ft_lst_r_redirection(t_lst_red *lst_r)
{
	t_lst_red	*tmp_r;

	tmp_r = lst_r;
	while (tmp_r)
	{
		if (!ft_strcmp(tmp_r->token, "R_OUT"))
			open_file_to_write_in(tmp_r->value);
		else if (!ft_strcmp(lst_r->token, "R_IN"))
			open_file_to_read_from(tmp_r->value);
		else if (!ft_strcmp(lst_r->token, "APPEND"))
			open_file_to_append(tmp_r->value);
		tmp_r = tmp_r->next;
	}
}

void    execve_with_path(char **ptr, t_env *env)
{
    char        **path;
    int         i;

    i = 0;
    path = get_path(env);
    while (path[i])
    {
        if (execve(ft_strjoin(ft_strdup(path[i]), ft_strjoin(ft_strdup("/"), ptr[0])), ptr, NULL) != -1)
            return ;
        i++;
    }
    printf("bash: %s: command not found\n", ptr[0]);
}

void red_cmd(char *line, t_env *env)
{

    t_lst_red   *red;
    t_list_args *lst;
    char        **ptr;
    
    red = NULL;
    lst = NULL;

    //ft_putstr_fd(line ,2);
    print_redictions(line, &red, &lst);
    ptr = make_tab(lst);
    if (red)
        ft_lst_r_redirection(red);
    if (!access(ptr[0], F_OK))
        execve(ptr[0], ptr, NULL);
    else
        execve_with_path(ptr, env);
        //exit (0);
}