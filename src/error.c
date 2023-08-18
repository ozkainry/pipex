/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozozdemi <ozozdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 13:50:02 by ozozdemi          #+#    #+#             */
/*   Updated: 2023/08/15 15:15:32 by ozozdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	msg_perror(char *str)
{
	perror(str);
	exit (1);
}

int	error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
