/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:25:19 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 16:56:01 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_dlist	*create_single(void)
{
	t_dlist	*list;

	list = create_dlist();
	list->first = create_dir(NULL, ".");
	list->last = list->first;
	stat(".", &(list->first->stat));
	return (list);
}

int				main(int argc, char **argv)
{
	t_max	*max;
	t_dlist	*list;

	list = NULL;
	max = NULL;
	if (argc == 1)
		list = create_single();
	else if ((list = parse_arg(argc, argv)) == NULL)
		exit(1);
	if (OPTIONS_L || OPTIONS_O)
	{
		max = malloc_max();
		get_maxs(list->first, max);
	}
	(!OPTIONS_F) ? ft_merge_sort(list->first) : 0;
	update_head_tail(list);
	display_reg_files(list, max);
	(!OPTIONS_D) ? ft_ls(list, max) : 0;
	free_list(list);
	ft_memdel((void**)&max);
	return (0);
}
