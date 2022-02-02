/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abellakr <abellakr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 08:24:19 by abellakr          #+#    #+#             */
/*   Updated: 2022/01/13 18:19:54 by abellakr         ###   ########.fr       */
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
	perror ("oops !! invalid command try again .");
	exit (0);
}

//process check 
static int	process_check(int pid, char **av, char **env, int *fd)
{
	int	f_fd[2];

	if (pid == 0)
	{
		f_fd[0] = open (av[1], O_RDONLY);
		if (f_fd[0] == -1 || dup2 (fd[1], 1) == -1 || dup2 (f_fd[0], 0) == -1)
		{
			perror ("oops somthing wrong try again !!");
			exit (1);
		}
		return (close (fd[0]), close (f_fd[0]), execute_cmd (env, av[2]), 1);
	}
	else
	{
		f_fd[1] = open (av[4], O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (f_fd[1] == -1 || dup2 (fd[0], 0) == -1 || dup2 (f_fd[1], 1) == -1)
		{
			perror ("oops somthing wrong try again !!");
			exit (1);
		}
		return (close (fd[1]), close (f_fd[1]), execute_cmd (env, av[3]), 1);
	}	
}

// program()
int	main(int ac, char **av, char **env)
{	
	int	fd[2];
	int	pid;

	if (ac != 5)
	{
		perror ("too few args !!");
		exit (0);
	}
	if (pipe(fd) == -1)
	{
		perror ("Oops something is wrong");
		exit (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror ("Oops something is wrong");
		exit (0);
	}	
	process_check (pid, av, env, fd);
	wait (NULL);
	return (0);
}
