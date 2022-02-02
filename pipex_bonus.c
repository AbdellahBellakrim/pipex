/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 09:32:35 by abellakr          #+#    #+#             */
/*   Updated: 2022/01/13 22:41:03 by abellakr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

//execute cmd function
static void	execute_cmd(char **env, char *cmd)
{
	int		i;
	int		a;
	char	*path;
	char	**str;
	char	**path2;

	i = 0;
	a = 0;
	while (env[i])
	{
		if (!ft_memcmp (env[i], "PATH=", 5))
			path = ft_strdup (env[i]);
		i++;
	}
	path2 = ft_split(path, ':');
	while (path2[a])
	{
		path2[a] = ft_strjoin (ft_strtrim (path2[a], "PATH="), "/");
		str = ft_split (cmd, ' ');
		if (!access (path2[a], X_OK))
			execve (ft_strjoin(path2[a], str[0]), &str[0], env);
		a++;
	}
	perror ("oops ! invalid command try again ...");
	exit (0);
}

//errors handling just for fucking norminnette
static void	errors_handling(int *fd, int pid)
{
	if (pipe (fd) == -1 || pid == -1)
	{
		perror ("oops somthing wrong try again !!");
		exit (0);
	}
	if (dup2 (fd[1], 1) == -1)
	{
		perror ("oops somthing wrong try again !!");
		exit (0);
	}	
}

// execute cmd parent
static void	excute_parent(int *fd)
{
	if (dup2 (fd[0], 0) == -1)
	{
		perror ("oops somthing wrong try again !!");
		exit (0);
	}
	close (fd[1]);
	wait (NULL);
}

//excute cmd childs
static void	execute_childs(int *fd, int *f_fd, char **env, char **av)
{
	int	index_cmd_counter[2];
	int	pid;

	index_cmd_counter[0] = 1;
	index_cmd_counter[1] = 2;
	while (index_cmd_counter[0] < fd[2])
	{
		if (pipe (fd) == -1)
			errors_handling(fd, pid);
		pid = fork();
		if (pid == -1)
			errors_handling (fd, pid);
		if (pid == 0)
		{
			if (dup2 (fd[1], 1) == -1)
				errors_handling(fd, pid);
			close (fd[0]);
			close (f_fd[0]);
			execute_cmd (env, av[index_cmd_counter[1]]);
		}
		else
			excute_parent(fd);
		index_cmd_counter[0]++;
		index_cmd_counter[1]++;
	}
}

// program()
int	main(int ac, char **av, char **env)
{	
	int	fd_ac[3];
	int	f_fd[2];

	if (ac < 5)
	{
		perror ("too few args !!");
		exit (0);
	}
	f_fd[0] = open (av[1], O_RDONLY);
	f_fd[1] = open (av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
	fd_ac[2] = ac - 3;
	if (f_fd[0] == -1 || f_fd[1] == -1 || dup2 (f_fd[0], 0) == -1)
	{
		perror("oops somthing wrong try again !!");
		exit(0);
	}
	execute_childs(fd_ac, f_fd, env, av);
	if (dup2 (f_fd[1], 1) == -1)
	{
		perror ("oops somthing wrong try again !!");
		exit (0);
	}
	close (fd_ac[1]);
	close (f_fd[1]);
	execute_cmd (env, av[ac - 2]);
}
