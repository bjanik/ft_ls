/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 10:50:34 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 16:37:38 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dlist		*read_dir(t_dir *dir, char *path, t_max *max)
{
	t_dlist			*file_list;
	struct dirent	*dir_content;

	file_list = create_dlist();
	while ((dir_content = readdir(dir->dir_stream)) != NULL)
	{
		if (dir_content->d_name[0] != '.' || OPTIONS_A ||
				((ft_strcmp(dir_content->d_name, ".") &&
				ft_strcmp(dir_content->d_name, "..")) && OPTIONS_CAP_A))
			append_file_list(file_list, dir_content, path);
	}
	if (closedir(dir->dir_stream) < 0)
		ft_perror_msg("closedir");
	(!OPTIONS_F) ? ft_merge_sort(file_list->first) : 0;
	update_head_tail(file_list);
	(OPTIONS_L || OPTIONS_O) ? get_maxs(file_list->first, max) : 0;
	return (file_list);
}

static void	display_dir_name(t_dir *dir)
{
	if (dir->dir_content == NULL)
	{
		if (!dir->next && !dir->previous && dir->error == 1)
			ft_printf("%s:\n", dir->path);
		else if (dir->file == 1 && (dir->previous || dir->next))
			ft_printf("%s:\n", dir->path);
		else if (dir->next || dir->previous)
			ft_printf("\n%s:\n", dir->path);
	}
	else
		ft_printf("\n%s:\n", dir->path);
}

static void	recursion(t_dir *dir, t_dlist *file_list, t_max *max)
{
	file_list = read_dir(dir, dir->path, max);
	display_dir_content(file_list, max);
	(OPTIONS_CAP_R) ? ft_ls(file_list, max) : 0;
	free_list(file_list);
}

void		ft_ls(t_dlist *list, t_max *max)
{
	t_dlist	*file_list;
	t_dir	*dir;
	char	*s;

	if (list->first == NULL)
		return ;
	file_list = NULL;
	dir = (OPTIONS_R) ? list->last : list->first;
	while (dir)
	{
		s = (dir->dir_content == NULL) ? dir->path : dir->file_name;
		if (S_ISDIR(dir->stat.st_mode) && ((ft_strcmp(".", s) &&
						ft_strcmp("..", s)) || (dir->dir_content == NULL)))
		{
			display_dir_name(dir);
			if ((dir->dir_stream = opendir(dir->path)) == NULL)
			{
				ft_putstr_fd("ft_ls: ", 2);
				perror(dir->file_name);
			}
			else
				recursion(dir, file_list, max);
		}
		dir = (OPTIONS_R) ? dir->previous : dir->next;
	}
}
