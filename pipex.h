/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 08:24:29 by abellakr          #+#    #+#             */
/*   Updated: 2022/01/13 22:42:06 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PIPEX_H
# define PIPEX_H

// headers
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include<stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <fcntl.h>
//function 
static void	execute_cmd(char **env, char *cmd);
static int	process_check(int pid, char **av, char **env, int *fd);
static void	errors_handling(int *fd, int pid);
static void	excute_parent(int *fd);
static void	execute_childs(int *fd, int *f_fd, char **env, char **av);

#endif