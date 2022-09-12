/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjalloul <mjalloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 22:33:42 by mjalloul          #+#    #+#             */
/*   Updated: 2022/09/11 19:52:32 by mjalloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *line;
    t_env *envr; 

    envr = make_env(env);
    while(1)
    {
        line = readline("Minishell> ");// free leaks
        if(line)
            add_history(line);
        scape_t_d_s_qout(line);
        if(syntaxe1_eror(line) == 1 || syntaxe2_eror(line) == 1 ) 
            ft_putstr_fd("Minishell : Syntaxe_error",2);
        else
        {
            line = expend_herdog(line);
            disperse_cmd(line,envr);
        }
        free(line);
    }
}
