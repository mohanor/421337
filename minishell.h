#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
# define SPECAT "|<>)("
# include <string.h> //strcmp
# include <fcntl.h>
#include <dirent.h>


//globalVaribel

int status;

//  env

typedef struct s_env {
	char *Var;
	char *Value;
	struct s_env *next;
	struct s_env *prev;
} t_env;

// token
typedef enum character_category
{
	EXPENSION,
	WORD,
	SQWORD, // '    '
	DQWORD, // "    "
	PIPE,//    |
    LPAREN, // )
    RPAREN, //(
    LESS, // <
    GREAT, // >
	GREATGREAT, // >>
	LESSLESS,// <<
    WHITESPACE, // \t\v\r\n
	REDIRECTION,
	OR,
	AND,
	NOTHING
}nodetype;

typedef struct s_list
{
	char	*token;
	nodetype	flag;
	struct s_list   *next;
}t_list;

typedef struct s_red
{
	char			*val;
	char			*type;
	struct s_red	*next;
} t_red;

typedef struct la
{
	char		*lexem;
	char		*token;
	struct la	*next;
	struct la	*back;
}	t_la;

typedef struct lst_red
{
	char			*value;
	char			*token;
	struct lst_red	*next;
}	t_lst_red;

typedef struct lst_pipe
{
	char			*str;
	struct lst_pipe	*next;
}	t_list_args;


//linked list env
void	ft_lstadd_back_env(t_env **alst, t_env *new);
t_env	*ft_lstnew_env(char	*var,char *value);
t_env	*ft_lstlast_env(t_env *lst);

//linked list list
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *content, int flag);


// libft
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_char(char const *s1, char s2);
int		ft_strchr(const char *s, int c);
int		ft_isdigit(int c);
void    ft_lstprint(t_list *lst);
void	ft_putstr_fd(char *c, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);



// minishell
int		syntaxe1_eror(char *line);
int		syntaxe2_eror(char *line);
void	disperse_cmd(char *line,t_env *envr);
void	pipe_cmd(char *list_cmd,t_env *envr);
t_env	*make_env(char **env);
void	Export(t_env *env, char *input);
void	token_and_expend(char *cmd, t_env *env);
char	*expend_herdog(char *line);
void	red_cmd(char *line, t_env *env);

// herdog utils
int find_first_herdog(char *line);
char    *while_file_existe(char *filename);
int    file_exists(char *filename);
char    *get_unigue_name(void);



// utls disperse
char last_parentes(char *line , int j,int i);
char first_parentes(char *line,int i ,int j);
int check_par(char *line);
char *after_last_operateur(char *line, int *opp);


// builtins
void env(t_env *env);

// utils
int b_e(char *line ,int index);
int a_e(char *line ,int index);
void scape_s_d_quot(char *line , int *k);
void scape_paren_quot_dec(char *line, int *k);
void scape_paren_quot_in(char *line, int *k);
void scape_t_d_s_qout(char *line);




#endif