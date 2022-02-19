/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablaamim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 13:38:58 by ablaamim          #+#    #+#             */
/*   Updated: 2022/02/19 13:40:56 by ablaamim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

static void	count_byte(int sig, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (sig == SIGUSR2)
		return ;
	else
	{
		ft_putstr("sent\n");
		exit(0);
	}
}

static void	ft_zero(int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR2);
		usleep(50);
	}
}

static void	ft_check(void)
{
	ft_putstr("\ncheck pid!\n");
	exit(0);
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
				if (kill(pid, SIGUSR1) == -1)
					ft_check();
			}
			else
				if (kill(pid, SIGUSR2) == -1)
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
		ft_putstr("carefully! -> ./client [pid] [string]\n");
		exit(0);
	}
	sa.sa_sigaction = count_byte;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	send2s(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
