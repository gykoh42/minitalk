/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:53:31 by gykoh             #+#    #+#             */
/*   Updated: 2023/08/24 17:17:44 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;
	char		char_num;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		char_num = num % 10 + '0';
		write(fd, &char_num, 1);
	}
	else
	{
		char_num = num + '0';
		write(fd, &char_num, 1);
	}
}

void	ft_handler(int signal)
{
	static int	bit;
	static char	c;

	if (signal == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, ft_handler);
	write(1, "PID: ", 5);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
