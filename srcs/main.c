/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:25:19 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/05 00:39:43 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*void	display_list_first(t_dlist *dir)
{
	t_dir	*p;

	if (dir != NULL)
	{
		p = dir->first;
		while (p)
		{
			if (p->dir_content == NULL)
				printf("%s    ", ft_strrchr(p->path, '/') + 1);
			else
				printf("%s    ", p->dir_content->d_name);
			p = p->next;
		}
	}
}

void	display_list_last(t_dlist *dir)
{
	t_dir	*p;

	if (dir != NULL)
	{
		p = dir->last;
		while (p)
		{
			printf("%s    ", p->path);
			p = p->previous;
		}
	}
}*/

void	sort_arg_list(t_dlist *list)
{
	t_dir	*dir;

	if (!list || !list->first || !list->last)
		return ;
	dir = list->first;
	while (dir->next)
	{
		if (ft_strcmp(dir->path, dir->next->path) > 0)
		{
			if (dir->previous == NULL)
				list->first = dir->next;
			swap_nodes(dir, dir->next);
			dir = list->first;
		}
		else
			dir = dir->next;
	}
	list->last = dir;
}

int	main(int argc, char **argv)
{
	t_max	*max;
	t_dlist	*list;

	list = NULL;
	max = NULL;
	if (argc == 1)
	{
		list = create_dlist();
		list->first = create_dir(NULL, ".");
		list->last = list->first;
		lstat(".", &(list->first->stat));
	}
	else if ((list = parse_arg(argc, argv)) == NULL)
		exit(-1);
	if (OPTIONS_L)
	{
		max =  malloc_max();
		get_maxs(list->first, max);
	}
	sort_arg_list(list);
	display_reg_files(list, max);
	recursion(list, max);
	free_list(list);
	return (0);
}
