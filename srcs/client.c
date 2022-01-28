/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:21:37 by rleseur           #+#    #+#             */
/*   Updated: 2022/01/28 12:18:58 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minitalk.h"

static void	fucking_manual(void)
{
	ft_putstr_fd("# Use: ./client [server PID] [message]\n", 1);
	exit(0);
}

static void	get_bin(unsigned int c, char **bin)
{
	char	*c_str;

	c_str = malloc(2 * sizeof(char));
	if (!c_str)
		return ;
	c_str[1] = '\0';
	if (c >= 2)
	{
		get_bin(c / 2, bin);
		c_str[0] = (c % 2) + '0';
		*bin = ft_strjoin(*bin, c_str);
	}
	else
	{
		c_str[0] = c + '0';
		*bin = ft_strjoin(*bin, c_str);
	}
	free(c_str);
}

static void	send_one(int pid, char c)
{
	char	*bin;
	int		i;

	bin = malloc(sizeof(char));
	if (!bin)
		return ;
	bin[0] = '\0';
	get_bin((unsigned int)c, &bin);
	while (ft_strlen(bin) < 7)
		bin = ft_strjoin("0", bin);
	i = -1;
	while (bin[++i])
	{
		if (bin[i] == '0')
			kill(pid, SIGUSR1);
		else if (bin[i] == '1')
			kill(pid, SIGUSR2);
		usleep(1000);
	}
	free(bin);
}

static void	send_message(int pid, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		send_one(pid, str[i]);
	send_one(pid, '\0');
}

int	main(int ac, char **av)
{
	if (ac != 3)
		fucking_manual();
	send_message(ft_atoi(av[1]), av[2]);
	return (0);
}
