/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:19:41 by rleseur           #+#    #+#             */
/*   Updated: 2022/02/10 16:28:50 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minitalk.h"

typedef struct s_info	t_info;

struct s_info
{
	char	c;
	char	*mem;
	int		i;
	int		ok;
	int		pid;
};

t_info					g_info;

static void	put_pid(void)
{
	ft_putstr_fd("Hello, i'm the server.\n", 1);
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
}

static int	init(char **mem, char *c)
{
	char		*tmp_mem;
	char		tmp_c[2];

	if (!*mem)
	{
		*mem = malloc(sizeof(char));
		if (!*mem)
			exit(0);
		*mem[0] = '\0';
	}
	tmp_mem = *mem;
	tmp_c[0] = *c;
	tmp_c[1] = '\0';
	*mem = ft_strjoin(tmp_mem, tmp_c);
	free(tmp_mem);
	return (1);
}

static void	check_pid(int sig_pid)
{	
	if (!g_info.pid || g_info.pid != sig_pid)
	{
		g_info.c = 0;
		free(g_info.mem);
		g_info.mem = 0;
		g_info.i = 0;
		g_info.ok = 1;
		g_info.pid = sig_pid;
	}
}

static void	handler(int signal, siginfo_t *siginfo, void *context)
{
	(void) context;
	check_pid(siginfo->si_pid);
	g_info.c |= (signal == SIGUSR2);
	if (++g_info.i == 8)
	{
		if (init(&g_info.mem, &g_info.c) && g_info.c == '\0')
		{
			g_info.ok = 0;
			ft_putstr_fd(g_info.mem, 1);
			kill(siginfo->si_pid, SIGUSR2);
			free(g_info.mem);
			g_info.mem = 0;
		}
		g_info.c = 0;
		g_info.i = 0;
	}
	else
		g_info.c <<= 1;
	if (g_info.ok)
		kill(siginfo->si_pid, SIGUSR1);
	g_info.ok = 1;
}

int	main(void)
{
	struct sigaction	sig;

	g_info.pid = 0;
	g_info.mem = 0;
	put_pid();
	ft_memset(&sig, '\0', sizeof(sig));
	sig.sa_sigaction = &handler;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (0);
}
