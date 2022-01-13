/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:21:37 by rleseur           #+#    #+#             */
/*   Updated: 2022/01/13 19:57:44 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minitalk.h"

static void	manual(void)
{
	ft_putstr_fd("# Use: ./client [server PID] [message]\n", 1);
	exit(0);
}

static void	success(int signal)
{
	(void) signal;
	ft_putstr_fd("Success!", 1);
}

int	main(int ac, char **av)
{
	(void) av;
	ft_putstr_fd("Hello, i'm the client.\n", 1);
	if (ac != 3)
		manual();
	signal(SIGUSR1, success);
	return (0);
}
