/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:39:34 by ablaamim          #+#    #+#             */
/*   Updated: 2022/02/22 21:15:19 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include <time.h>
#include <stdio.h>

static void	count_byte(int sig, siginfo_t *siginfo, void *context)
{
	static int	count = 0;

	(void)siginfo;
	(void)context;
	if (sig == SIGUSR1)
		++count;
	else
	{
		ft_putnbr(count);
		ft_putstr(" byte\n");
		exit(EXIT_FAILURE);
	}
}

static void	ft_last_bit(int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (kill(pid, SIGUSR1) == -1)
			ft_putstr("\nError : Kill failed\n");
		usleep(5);
	}
}

static void	ft_error(void)
{
	ft_putstr("\nError : Invalid PID\n");
	exit(EXIT_FAILURE);
}

static void	ft_send_to_server(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					ft_error();
			}
			else
				if (kill(pid, SIGUSR1) == -1)
					ft_error();
			usleep(20);
		}
	}
	ft_last_bit(pid);
}
int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr("Arguments to run the program: ./client [pid] [string]\n");
		exit(EXIT_FAILURE);
	}
	ft_putstr("Client sent     : ");
	ft_putnbr(ft_strlen(argv[2]));
	ft_putstr(" byte\n");
	ft_putstr("Server received : ");
	sa.sa_sigaction = count_byte;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, 0) == -1)
		return (EXIT_FAILURE);
	if (sigaction(SIGUSR2, &sa, 0) == -1)
		return (EXIT_FAILURE);
	ft_send_to_server(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
