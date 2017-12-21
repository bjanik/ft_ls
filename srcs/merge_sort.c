/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 16:23:23 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 13:09:30 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			update_head_tail(t_dlist *file_list)
{
	while (file_list->first && file_list->first->previous)
		file_list->first = file_list->first->previous;
	while (file_list->last && file_list->last->next)
		file_list->last = file_list->last->next;
}

static t_dir	*split_list(t_dir *first)
{
	t_dir	*fast;
	t_dir	*slow;
	t_dir	*tmp;

	fast = first;
	slow = first;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	tmp = slow->next;
	slow->next = NULL;
	return (tmp);
}

static int		select_key(t_dir *first, t_dir *second)
{
	int	key;
	int	size_first;
	int	size_second;

	key = 0;
	size_first = first->stat.st_size;
	size_second = second->stat.st_size;
	if (OPTIONS_T && !OPTIONS_S)
	{
		if (second->stat.st_mtime - first->stat.st_mtime == 0)
			key = ft_strcmp(first->file_name, second->file_name);
		else
			key = second->stat.st_mtime - first->stat.st_mtime;
	}
	else if (OPTIONS_S)
	{
		if ((S_ISBLK(first->stat.st_mode) || S_ISCHR(first->stat.st_mode)) ||
			(S_ISBLK(second->stat.st_mode) || S_ISCHR(second->stat.st_mode)))
			key = ft_strcmp(first->file_name, second->file_name);
		else
			key = second->stat.st_size - first->stat.st_size;
	}
	else
		key = ft_strcmp(first->file_name, second->file_name);
	return (key);
}

static t_dir	*merge_lists(t_dir *first, t_dir *second)
{
	int	key;

	key = 0;
	if (first == NULL)
		return (second);
	if (second == NULL)
		return (first);
	key = select_key(first, second);
	if (key <= 0)
	{
		first->next = merge_lists(first->next, second);
		first->next->previous = first;
		first->previous = NULL;
		return (first);
	}
	else
	{
		second->next = merge_lists(first, second->next);
		second->next->previous = second;
		second->previous = NULL;
		return (second);
	}
}

t_dir			*ft_merge_sort(t_dir *first)
{
	t_dir	*second;

	if (first == NULL || first->next == NULL)
		return (first);
	second = split_list(first);
	first = ft_merge_sort(first);
	second = ft_merge_sort(second);
	return (merge_lists(first, second));
}
