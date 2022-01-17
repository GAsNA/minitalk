/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:21:37 by rleseur           #+#    #+#             */
/*   Updated: 2022/01/17 15:06:18 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minitalk.h"

static void	fucking_manual(void)
{
	ft_putstr_fd("# Use: ./client [server PID] [message]\n", 1);
	exit(0);
}

static void	success(int signal)
{
	(void) signal;
	ft_putstr_fd("Success!\n", 1);
}

int	main(int ac, char **av)
{
	struct   sigaction sact;

	(void) av;
	if (ac != 3)
		fucking_manual();
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	sact.sa_handler = success;
	sigaction(SIGUSR1, &sact, NULL);
	//ft_putstr_fd("Hello, i'm the client.\n", 1);
	//signal(SIGUSR1, success);
	kill(getpid(), SIGUSR1);
	return (0);
}
