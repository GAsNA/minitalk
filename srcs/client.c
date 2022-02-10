/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:21:37 by rleseur           #+#    #+#             */
/*   Updated: 2022/02/10 15:03:51 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minitalk.h"

typedef struct s_info	t_info;

struct s_info
{
	int		pid;
	char	*mess;
};

t_info					g_info;

static void	handler(int signal)
{
	int			ret;
	static int	byte = 8;
	static int	i = 0;

	if (signal == SIGUSR2)
	{
		ft_putstr_fd("All received!\n", 1);
		exit(0);
	}
	if (--byte == -1)
	{
		byte = 8;
		i++;
		handler(SIGUSR1);
	}
	else
	{
		if (g_info.mess[i] >> byte & 1)
			ret = kill(g_info.pid, SIGUSR2);
		else
			ret = kill(g_info.pid, SIGUSR1);
		if (ret == -1)
			exit(0);
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_putstr_fd("# Use: ./client [server PID] [message]\n", 1);
		return (0);
	}
	g_info.pid = ft_atoi(av[1]);
	if (g_info.pid <= 0)
		return (0);
	g_info.mess = av[2];
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	handler(SIGUSR1);
	while (1)
		pause();
	return (0);
}
