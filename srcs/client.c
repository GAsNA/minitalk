/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:21:37 by rleseur           #+#    #+#             */
/*   Updated: 2022/02/07 18:09:19 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minitalk.h"

static void	got(int signal)
{
	(void) signal;
}

static void	send_one(int pid, char c)
{
	int	byte;
	int	ret;

	byte = 7;
	while (byte >= 0)
	{
		if (c >> byte & 1)
			ret = kill(pid, SIGUSR2);
		else
			ret = kill(pid, SIGUSR1);
		if (ret == -1)
			exit(0);
		byte--;
		pause();
	}
}

int	main(int ac, char **av)
{
	int		i;
	int		pid;
	char	*str;

	if (ac != 3)
	{
		ft_putstr_fd("# Use: ./client [server PID] [message]\n", 1);
		return (0);
	}
	pid = ft_atoi(av[1]);
	str = av[2];
	signal(SIGUSR1, got);
	signal(SIGUSR2, got);
	i = -1;
	while (str[++i])
		send_one(pid, str[i]);
	send_one(pid, '\0');
	return (0);
}
