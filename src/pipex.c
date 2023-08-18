/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozozdemi <ozozdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:42:54 by ozozdemi          #+#    #+#             */
/*   Updated: 2023/08/18 13:18:49 by ozozdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_child_process(char **envp, char **av, t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		end_pipeprocess(pipex);
		parent_free(pipex);
		msg_perror("fork error\n");
	}
	if (pipex->pid == 0)
		child(*pipex, av, envp);
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		end_pipeprocess(pipex);
		parent_free(pipex);
		msg_perror("fork error\n");
	}
	if (pipex->pid1 == 0)
		child2(*pipex, av, envp);
}

void	init_fd(t_pipex *pipex, char **av, char **envp)
{
	pipex->path = NULL;
	pipex->cmd_path = NULL;
	pipex->options = NULL;
	pipex->cmd = NULL;
	pipex->infile = open(av[1], O_RDONLY);
	pipex->outfile = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->infile < 0)
		perror("zsh");
	if (pipex->outfile < 0)
		perror("zsh");
	if (pipe(pipex->tube) == -1)
		msg_perror("Pipe Error\n");
	pipex->path = find_path(envp);
	pipex->cmd_path = ft_split(pipex->path, ':');
	if (!pipex->cmd_path)
	{
		free(pipex->cmd_path);
		exit(EXIT_FAILURE);
	}
}

void	ft_wait(t_pipex pipex, int status)
{
	if (waitpid(pipex.pid, &status, 0) == -1)
	{
		end_pipeprocess(&pipex);
		parent_free(&pipex);
		msg_perror("waitpid error\n");
	}
	if (waitpid(pipex.pid1, &status, 0) == -1)
	{
		end_pipeprocess(&pipex);
		parent_free(&pipex);
		msg_perror("waitpid error\n");
	}
	if (WIFEXITED(status) != 0)
	{
		parent_free(&pipex);
		exit(WEXITSTATUS(status));
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		status;

	status = 0;
	if (envp[0] == NULL)
	{
		write(2, "envp incorrect\n", 16);
		exit(EXIT_FAILURE);
	}
	if (ac == 5)
	{
		init_fd(&pipex, av, envp);
		init_child_process(envp, av, &pipex);
		end_pipeprocess(&pipex);
		ft_wait(pipex, status);
		parent_free(&pipex);
	}
	else
		return (error(ARG));
}
