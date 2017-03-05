/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 14:10:13 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/05 00:39:44 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_list(t_dlist *list)
{
	t_dir	*dir;
	int	i;

	dir = list->first;
	while (list->first)
	{
		i = 0;
		ft_memdel((void**)&(list->first->path));
		ft_free_string_tab(list->first->date);
		list->first = list->first->next;
		free(dir);
		dir = list->first;
	}
	free(list);
}

t_dlist	*create_dlist(void)
{
	t_dlist	*list;

	if ((list = (t_dlist*)malloc(sizeof(t_dlist))) == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	list->first = NULL;
	list->last = NULL;
	return (list);
}

static void	init_dir(t_dir *dir, struct dirent *dir_content, char *dir_path)
{
	char	*tmp;
	
	dir->dir_stream = NULL;
	dir->dir_content = dir_content;
	dir->path = ft_strdup(dir_path);
	if (dir_content != NULL)
	{
		tmp = dir->path;
		if (ft_strcmp(dir->path, "/") != 0)
			dir->path = ft_strnjoin(dir->path, 2, "/", dir_content->d_name);
		else
			dir->path = ft_strjoin(dir_path, dir_content->d_name);
		free(tmp);
	}
	dir->user = NULL;
	dir->group = NULL;
	dir->date = NULL;
}

t_max	*malloc_max()
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

void	init_max(t_max *max)
{
	max->max_group_name = 0;
	max->max_user_name = 0;
	max->max_nlinks = 0;
	max->max_size = 0;
	max->total_blocks = 0;
}

t_dir	*create_dir(struct dirent *dir_content, char *path)
{
	t_dir	*new;

	if ((new = (t_dir*)malloc(sizeof(t_dir))) == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	init_dir(new, dir_content, path);
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	append_file_list(t_dlist *list, struct dirent *dir_content, char *path)
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
		perror("lstat");
}
