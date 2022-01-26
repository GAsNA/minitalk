/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <rleseur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:19:41 by rleseur           #+#    #+#             */
/*   Updated: 2022/01/24 15:21:38 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minitalk.h"

static void	put_pid(void)
{
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
}

static void	got_elem(int signal)
{
	ft_putnbr_fd(signal, 1);
}

static void	receive_message(void)
{
	while (1)
	{
		signal(SIGUSR1, got_elem);
		signal(SIGUSR2, got_elem);
		pause();
	}
}

int	main(void)
{
	ft_putstr_fd("Hello, i'm the server.\n", 1);
	put_pid();
	receive_message();
}
