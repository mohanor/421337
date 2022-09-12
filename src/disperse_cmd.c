/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disperse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:51:26 by mjalloul          #+#    #+#             */
/*   Updated: 2022/09/12 01:29:02 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void disperse_cmd(char *line, t_env *envr)
{
  int i;
  char *last_cmd;

   if(line[0] == '\0') 
      return;
   last_cmd = after_last_operateur(line, &i);
   if(last_cmd)
   {
      disperse_cmd(line, envr);
      if( status!= 0 && i == 1)
            pipe_cmd(last_cmd, envr);
      if( status == 0 && i == 2)
            pipe_cmd(last_cmd, envr);
   }
   else 
      pipe_cmd(line, envr);
}