/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_digit_base_umax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 15:12:51 by bjanik            #+#    #+#             */
/*   Updated: 2017/01/08 16:50:23 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nb_digit_base_umax(uintmax_t nb, int base)
{
	int i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= (uintmax_t)base;
		i++;
	}
	return (i);
}
