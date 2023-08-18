/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozozdemi <ozozdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:12:13 by ozozdemi          #+#    #+#             */
/*   Updated: 2023/08/18 15:04:12 by ozozdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec(t_pipex pipex, char **envp)
{
	pipex.cmd = find_cmd(pipex.cmd_path, pipex.options[0]);
	if (!pipex.cmd)
	{
		freechild(&pipex);
		parent_free(&pipex);
		error("Command not found\n");
		exit(127);
	}
	if (execve(pipex.cmd, pipex.options, envp) == -1)
	{
		freechild(&pipex);
		parent_free(&pipex);
		error("execve error\n");
		exit(127);
	}
}

void	child(t_pipex pipex, char **av, char **envp)
{
	char	*str;
	int		i;

	i = 0;
	if (dup2(pipex.tube[1], 1) == -1)
		freexit(pipex);
	if (close(pipex.tube[0]) == -1)
		freexit(pipex);
	if (dup2(pipex.infile, 0) == -1)
		freexit(pipex);
	str = strspace_cpy(av[2], i);
	if (!str)
		freexit(pipex);
	pipex.options = ft_split(str, ' ');
	free (str);
	if (!pipex.options)
		freexit(pipex);
	ft_exec(pipex, envp);
}

void	child2(t_pipex pipex, char **av, char **envp)
{
	char	*str;
	int		i;

	i = 0;
	if (dup2(pipex.tube[0], 0) == -1)
		freexit(pipex);
	if (close(pipex.tube[1]) == -1)
		freexit(pipex);
	if (dup2(pipex.outfile, 1) == -1)
		freexit(pipex);
	str = strspace_cpy(av[3], i);
	if (!str)
		freexit(pipex);
	pipex.options = ft_split(str, ' ');
	if (!pipex.options)
		freexit(pipex);
	free (str);
	ft_exec(pipex, envp);
}
