/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:21:37 by rleseur           #+#    #+#             */
/*   Updated: 2022/01/20 10:35:27 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minitalk.h"

static void	fucking_manual(void)
{
	ft_putstr_fd("# Use: ./client [server PID] [message]\n", 1);
	exit(0);
}

/*static void	success(int signal)
{
	(void) signal;
	ft_putstr_fd("Success!\n", 1);
}*/

static void	send_one(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit > -1)
	{
		if (c)
		{
		//	1 << bit;
			kill(pid, SIGUSR1);
		}
		else
			kill(pid, SIGUSR2);
		bit--;
		//sleep(10);
	}
}

static void	send_message(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		send_one(pid, str[i]);
	sed_one(pid, '\0');
}

int	main(int ac, char **av)
{
//	struct   sigaction sact;

	(void) av;
	if (ac != 3)
		fucking_manual();
	send_message(ft_atoi(av[1]), av[2]);
//	sigemptyset(&sact.sa_mask);
//	sact.sa_flags = 0;
//	sact.sa_handler = success;
//	sigaction(SIGUSR1, &sact, NULL);
//	kill(getpid(), SIGUSR1);
	return (0);
}
