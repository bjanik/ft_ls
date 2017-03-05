/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 15:24:16 by bjanik            #+#    #+#             */
/*   Updated: 2017/02/17 15:36:38 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


t_dlist	*read_dir(t_dir *dir)
{
	t_dlist			*file_list;
	struct dirent	*dir_content;

	if ((file_list = (t_dlist*)malloc(sizeof(t_dlist*))) == NULL)
		return (NULL);
	while ((dir_content = readdir(dir->dir_stream)) != NULL)
		append_file_list(&dir, file_list, dir_content);
	return (file_list);
}

static void	recursion(t_dir *dir_list)
{
	t_dlist	*file_list;
	t_dir	*dir;
	t_dir	*dir2;

	dir = NULL;
	dir2 = NULL;
	if (dir_list == NULL)
		return ;
	while (ft_strcmp(".", dir->name) && ft_strcmp("..", dir->name))
		
	{
		file_list = read_dir(dir_list);
		while (dir2)
		{
			if (ft_strcmp(".", dir2->name) || ft_strcmp("..", dir2->name))
				if ((dir = set_dir_list(dir2)) == NULL)
					return ;
			recursion(dir2->next);
			//dir2 = (OPTIONS_R) ? dir2->next : dir2->previous;
		}
	}
}

void	ft_ls(t_dlist *list)
{
	t_dir			*dir;

	dir = list->first;
	while (dir)
	{
		if (ft_strcmp(".", dir->name) && ft_strcmp("..", dir->name))
		{
			if ((dir->dir_stream = opendir(dir->name)) != NULL)
				OPTIONS_CAP_R ? recursion(dir) : 0;
		}
		dir = dir->next;
	}
	/*	if ((dir_stream = opendir(dir->name)) != NULL)
			dir->dir = dir_stream;
		printf("%s:\n\n", dir->name);
		while ((dir_content = readdir(dir->dir)) != NULL)
			printf("%s\n", dir_content->d_name);
		dir = dir->next;
	}*/
}
