/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:19:41 by rleseur           #+#    #+#             */
/*   Updated: 2022/01/29 21:21:20 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minitalk.h"

static void	put_pid(void)
{
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
}

static char	*get_char(char *c)
{
	char	*str;
	int		i;
	int		res;

	str = malloc(2 * sizeof(char));
	if (!str)
		return (0);
	i = -1;
	res = 0;
	while (c[++i])
	{
		res *= 2;
		res += (c[i] - '0');
	}
	str[0] = (char)res;
	str[1] = '\0';
	return (str);
}

static void	init(char **c, char **mem, int *i)
{
	if (!*c)
	{
		*c = malloc(sizeof(char));
		if (!*c)
			exit(0);
		*c[0] = '\0';
	}
	if (!*mem)
	{
		*mem = malloc(sizeof(char));
		if (!*mem)
			exit(0);
		*mem[0] = '\0';
		*i = 0;
	}
}

static void	got_elem(int signal)
{
	static char	*mem;
	static char	*c;
	static int	i;

	init(&c, &mem, &i);
	if (signal == SIGUSR1)
		c = ft_strjoin(c, "0");
	if (signal == SIGUSR2)
		c = ft_strjoin(c, "1");
	if (ft_strlen(c) == 8)
	{
		mem = ft_strjoin(mem, get_char(c));
		c[0] = '\0';
		if (mem[i] == '\0')
		{
			ft_putstr_fd(mem, 1);
			mem[0] = '\0';
			i = 0;
		}
		else
			i++;
	}
}

int	main(void)
{
	ft_putstr_fd("Hello, i'm the server.\n", 1);
	put_pid();
	while (1)
	{
		signal(SIGUSR1, got_elem);
		signal(SIGUSR2, got_elem);
		pause();
	}
	return (0);
}
