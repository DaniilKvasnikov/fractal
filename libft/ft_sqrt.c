/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:39:57 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/11/19 18:39:59 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int index;

	if (nb <= 0)
		return (0);
	else if (nb == 1)
		return (1);
	index = 0;
	while (index < 46341 && index <= nb / 2)
	{
		if (index * index >= nb)
			return (index);
		index++;
	}
	return (0);
}
