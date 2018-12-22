/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 21:24:18 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/11/23 21:24:19 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	char	ds[2];
	int		new;

	if (c >= 0)
		write(fd, &c, 1);
	else
	{
		if (c < -64)
		{
			c += 0x80;
			new = c + 0x80;
			ds[0] = 0xC2;
			ds[1] = new;
			write(fd, ds, 2);
		}
		else
		{
			c += 0x80;
			ds[0] = 0xC3;
			ds[1] = (int)c + 0x80 - 64;
			write(fd, ds, 2);
		}
	}
}
