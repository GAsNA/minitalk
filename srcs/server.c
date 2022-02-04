/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:19:41 by rleseur           #+#    #+#             */
/*   Updated: 2022/02/04 04:28:31 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minitalk.h"

static void	double_free(char **s1, char **s2)
{
	free(*s1);
	*s1 = NULL;
	free(*s2);
	*s2 = NULL;
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

static void	get_signal(int signal, char **c, char **mem, int *i)
{
	char	*tmp;

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
	tmp = *c;
	if (signal == SIGUSR1)
		*c = ft_strjoin(tmp, "0");
	else if (signal == SIGUSR2)
		*c = ft_strjoin(tmp, "1");
	free(tmp);
}

static void	got_elem(int signal, siginfo_t *siginfo, void *context)
{
	static char	*mem;
	static char	*c;
	char		*tmp;
	char		*tmp2;
	static int	i;

	(void) context;
	get_signal(signal, &c, &mem, &i);
	if (ft_strlen(c) == 8)
	{
		tmp = mem;
		tmp2 = get_char(c);
		mem = ft_strjoin(tmp, tmp2);
		double_free(&tmp, &tmp2);
		c[0] = '\0';
		if (mem[i] == '\0')
		{
			ft_putstr_fd(mem, 1);
			double_free(&c, &mem);
		}
		else
			i++;
	}
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sig;

	ft_putstr_fd("Hello, i'm the server.\n", 1);
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	ft_memset(&sig, '\0', sizeof(sig));
	sig.sa_sigaction = &got_elem;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (0);
}
