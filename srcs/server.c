/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:19:41 by rleseur           #+#    #+#             */
/*   Updated: 2022/02/07 18:08:16 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minitalk.h"

static void	got_elem(int signal, siginfo_t *siginfo, void *context)
{
	static char	c = 0;
	static char	*mem;
	static int	i = 0;
	char		*tmp_mem;
	char		tmp_c[2];

	(void) context;
	c |= (signal == SIGUSR2);
	if (++i == 8)
	{
		if (!mem)
		{
			mem = malloc(sizeof(char));
			if (!mem)
				exit(0);
			mem[0] = '\0';
		}
		tmp_mem = mem;
		tmp_c[0] = c;
		tmp_c[1] = '\0';
		mem = ft_strjoin(tmp_mem, tmp_c);
		free(tmp_mem);
		if (c == '\0')
		{
			ft_putstr_fd(mem, 1);
			free(mem);
			mem = NULL;
		}
		c = 0;
		i = 0;
	}
	else
		c <<= 1;
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
