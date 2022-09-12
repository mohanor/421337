/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matef <matef@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 00:16:11 by mjalloul          #+#    #+#             */
/*   Updated: 2022/09/12 21:37:26 by matef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char *befor_first_pipe(char *line, int *k)
{
   int i;
   char *c;
   int f;

   f = *k;
   i = *k;
   while(line[i])
   {
      scape_paren_quot_in(line,&i);
      if(line[i] == '|' && line[i+1] != '|' )
      {
         c = ft_substr(line,f,i - f);
         line[i] = ' '; 
         *k = i;
         return(c);
      }
      i++;
   }
   if(line[i] == '\0')
      i = -1;
   *k = i;
   return(ft_substr(line,f,i - f));
}



void pipe_cmd(char *line,t_env *envr)
{
   char *first_cmd_pipe;
   int fd[2];
   int len;
   int tmp_fd;
   int pid;
   
   tmp_fd = 0;
   len = 0;
   (void)envr;
   while(len != -1)
   {
      first_cmd_pipe = befor_first_pipe(line,&len);
      //printf("%s\n", first_cmd_pipe);
      pipe(fd);
      pid = fork();
      if(pid== 0)
      {

         dup2(tmp_fd, 0);
         if (len != -1)
         {
             dup2(fd[1], 1);
         }

         close(fd[0]);
         red_cmd(first_cmd_pipe, envr);
         exit(1);
      }
      else
      {
         wait(NULL);
         
         close(fd[1]);
         tmp_fd = fd[0];
         
      }
      //tmp_fd = fd[0];
   }
   //printf("%d\n", status);
}

