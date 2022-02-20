/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:39:34 by ablaamim          #+#    #+#             */
/*   Updated: 2022/02/20 00:51:01 by ablaamim         ###   ########.fr       */
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

static void	ft_zero(int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}

static void	ft_check(void)
{
	ft_putstr("\nError : Invalid PID\n");
	exit(EXIT_FAILURE);
}

static void	send2s(int pid, char *str)
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
					ft_check();
			}
			else
				if (kill(pid, SIGUSR1) == -1)
					ft_check();
			usleep(200);
		}
	}
	ft_zero(pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3 || !ft_strlen(argv[2]))
	{
		ft_putstr("Arguments to run : ./client [pid] [string]\n");
		exit(EXIT_FAILURE);
	}
	ft_putstr("Client sent     : ");
	ft_putnbr(ft_strlen(argv[2]));
	ft_putstr(" byte\n");
	ft_putstr("Server received : ");
	sa.sa_sigaction = count_byte;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	send2s(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	clock_t t;
	t = clock();
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("fun() took %f seconds to execute \n", time_taken);
	return (EXIT_SUCCESS);
}
