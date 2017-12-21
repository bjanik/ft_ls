/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 14:10:13 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 16:39:55 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_list(t_dlist *list)
{
	t_dir	*dir;

	dir = list->first;
	while (list->first)
	{
		ft_strdel(&(list->first->path));
		ft_strdel(&(list->first->file_name));
		if (OPTIONS_L)
		{
			ft_strdel(&(dir->user));
			ft_free_string_tab(list->first->date);
			ft_strdel(&(dir->group));
		}
		ft_strdel(&(dir->sym_link_path));
		ft_strdel(&(dir->buf_link));
		list->first = list->first->next;
		ft_memdel((void**)&dir);
		dir = list->first;
	}
	ft_memdel((void**)&list);
}

t_dlist		*create_dlist(void)
{
	t_dlist	*list;

	if ((list = (t_dlist*)malloc(sizeof(t_dlist))) == NULL)
		ft_perror_msg("malloc");
	list->first = NULL;
	list->last = NULL;
	return (list);
}

static void	init_dir(t_dir *dir, struct dirent *dir_content, char *dir_path)
{
	char	*tmp;

	dir->dir_stream = NULL;
	dir->dir_content = dir_content;
	dir->file_name = NULL;
	(dir_content) ? dir->file_name = ft_strdup(dir->dir_content->d_name) : 0;
	(!dir_content) ? dir->file_name = ft_strdup(dir_path) : 0;
	dir->path = ft_strdup(dir_path);
	if (dir_content != NULL)
	{
		tmp = dir->path;
		if (ft_strcmp(dir->path, "/") != 0)
			dir->path = ft_strnjoin(dir->path, 2, "/", dir->file_name);
		else
			dir->path = ft_strjoin(dir_path, dir->file_name);
		ft_strdel(&tmp);
	}
	dir->buf_link = NULL;
	dir->sym_link_path = NULL;
	dir->user = NULL;
	dir->group = NULL;
	dir->date = NULL;
	dir->file = 0;
}

t_dir		*create_dir(struct dirent *dir_content, char *path)
{
	t_dir	*new;

	if ((new = (t_dir*)malloc(sizeof(t_dir))) == NULL)
		ft_perror_msg("malloc");
	init_dir(new, dir_content, path);
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void		append_file_list(t_dlist *list, struct dirent *dir_content,
			char *path)
{
	if (list->first == NULL)
	{
		list->first = create_dir(dir_content, path);
		list->last = list->first;
	}
	else
	{
		list->last->next = create_dir(dir_content, path);
		list->last->next->previous = list->last;
		list->last = list->last->next;
	}
	if (lstat(list->last->path, &(list->last->stat)) < 0)
	{
		perror("ft_ls");
		if (list->last == list->first)
		{
			ft_memdel((void**)&(list->last));
			list->first = NULL;
		}
		else
		{
			list->last = list->last->previous;
			ft_memdel((void**)&(list->last->next));
		}
	}
}
