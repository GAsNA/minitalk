/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:19:41 by rleseur           #+#    #+#             */
/*   Updated: 2022/02/14 14:09:38 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librairies/Libft/libft.h"
#include <signal.h>

typedef struct s_info	t_info;

struct s_info
{
	char	c;
	char	*mem;
	int		i;
	int		ok;
	int		pid;
};

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

static void	check_pid(t_info *infos, int sig_pid)
{	
	if (!infos->pid || infos->pid != sig_pid)
	{
		infos->c = 0;
		free(infos->mem);
		infos->mem = 0;
		infos->i = 0;
		infos->ok = 1;
		infos->pid = sig_pid;
	}
}

static void	handler(int signal, siginfo_t *siginfo, void *context)
{
	static t_info	infos;

	(void) context;
	check_pid(&infos, siginfo->si_pid);
	infos.c |= (signal == SIGUSR2);
	if (++infos.i == 8)
	{
		if (init(&infos.mem, &infos.c) && infos.c == '\0')
		{
			infos.ok = 0;
			ft_putstr_fd(infos.mem, 1);
			kill(siginfo->si_pid, SIGUSR2);
			free(infos.mem);
			infos.mem = 0;
		}
		infos.c = 0;
		infos.i = 0;
	}
	else
		infos.c <<= 1;
	if (infos.ok)
		kill(siginfo->si_pid, SIGUSR1);
	infos.ok = 1;
}

int	main(void)
{
	struct sigaction	sig;

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
