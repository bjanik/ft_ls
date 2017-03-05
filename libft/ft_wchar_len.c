/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_lenght.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 12:59:42 by bjanik            #+#    #+#             */
/*   Updated: 2017/01/15 18:28:08 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wchar_len(wchar_t wc)
{
	if (wc <= 0x7F)
		return (1);
	if (wc <= 0x7FF)
		return (2);
	if (wc <= 0xFFFF)
		return (3);
	if (wc <= 0x10FFFF)
		return (4);
	return (0);
}
