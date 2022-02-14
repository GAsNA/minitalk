/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:21:37 by rleseur           #+#    #+#             */
/*   Updated: 2022/02/14 13:40:30 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librairies/Libft/libft.h"
#include <signal.h>

char	*g_mess;

static void	if_no_signal_1(int *pid, int signal)
{
	if (signal < 0)
		*pid = -signal;
	if (signal == SIGUSR2)
	{
		ft_putstr_fd("All received!\n", 1);
		exit(0);
	}
}

static void	handler(int signal)
{
	int			ret;
	static int	pid;
	static int	byte = 8;
	static int	i = 0;

	if_no_signal_1(&pid, signal);
	if (--byte == -1)
	{
		byte = 8;
		i++;
		handler(SIGUSR1);
	}
	else
	{
		if (g_mess[i] >> byte & 1)
			ret = kill(pid, SIGUSR2);
		else
			ret = kill(pid, SIGUSR1);
		if (ret == -1)
			exit(0);
	}
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
	{
		ft_putstr_fd("# Use: ./client [server PID] [message]\n", 1);
		return (0);
	}
	pid = ft_atoi(av[1]);
	if (pid <= 0)
		return (0);
	g_mess = av[2];
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	handler(-pid);
	while (1)
		pause();
	return (0);
}
