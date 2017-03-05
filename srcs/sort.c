/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 11:38:03 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/04 14:51:52 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	refresh(t_dir *a)
{
	if (a->previous != NULL)
		a->previous->next = a;
	if (a->next != NULL)
		a->next->previous = a;
}

void	swap_nodes(t_dir *a, t_dir *b)
{
	b->previous = a->previous;
	a->previous = a->next;
	a->next = b->next;
	b->next = b->previous;
	refresh(a);
	refresh(b);
}

void	sort_name(t_dlist *list)
{
	t_dir	*dir;

	if (list == NULL || !list->first || !list->last)
		return ;
	dir = list->first;
	while (dir->next)
	{
		if (ft_strcmp(dir->dir_content->d_name,
					dir->next->dir_content->d_name) > 0)
		{
			if (dir->previous == NULL)
				list->first = dir->next;
			swap_nodes(dir, dir->next);
			if (dir->previous && dir->previous->previous)
				dir = dir->previous->previous;
		}
		else
			dir = dir->next;
	}
	list->last = dir;
}

void	ascii_sort_after_time_sort(t_dlist *list)
{
	t_dir	*dir;

	dir = list->first;
	while (dir->next)
	{
		if (dir->stat.st_mtime == dir->next->stat.st_mtime)
		{
			if (ft_strcmp(dir->path, dir->next->path) > 0)
			{
				if (dir->previous == NULL)
					list->first = dir->next;
				swap_nodes(dir, dir->next);
				dir = list->first;
			}
		}
		dir = dir->next;
	}
	list->last = dir;
	dir = list->first;
}

void	sort_time(t_dlist *list)
{
	t_dir	*dir;

	if (list == NULL)
		return ;
	dir = list->first;
	while (dir->next)
	{
		if (dir->stat.st_mtime < dir->next->stat.st_mtime)
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
	ascii_sort_after_time_sort(list);
}
