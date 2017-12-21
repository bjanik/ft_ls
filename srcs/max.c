/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 16:59:44 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 11:03:41 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_max(t_max *max)
{
	max->max_group_name = 0;
	max->max_user_name = 0;
	max->max_nlinks = 0;
	max->max_size = 0;
	max->total_blocks = 0;
}

t_max	*malloc_max(void)
{
	t_max	*max;

	if ((max = (t_max*)malloc(sizeof(t_max))) == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	init_max(max);
	return (max);
}
