/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 10:50:34 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/24 16:05:31 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dlist	*read_dir(t_dir *dir, char *path, t_max *max)
{
	t_dlist			*file_list;
	struct dirent	*dir_content;

	file_list = create_dlist();
	while ((dir_content = readdir(dir->dir_stream)) != NULL)
	{
		if (dir_content->d_name[0] != '.' || OPTIONS_A)
			append_file_list(file_list, dir_content, path);
	}
	closedir(dir->dir_stream);
	(OPTIONS_T) ? sort_time(file_list) : sort_name(file_list);
	(OPTIONS_L) ? get_maxs(file_list->first, max) : 0;
	return (file_list);
}

static void	display_dir_name(t_dir *dir)
{
	if ((dir->previous && !dir->next && OPTIONS_R) ||
			(!dir->previous && dir->next && !OPTIONS_R))
		printf("%s:\n", dir->path);
	else if (dir->next || dir->previous)
		printf("\n%s:\n", dir->path);
}

void	recursion(t_dlist *list, t_max *max)
{
	t_dlist	*file_list;
	t_dir	*dir;
	char	*s;

	if (list->first == NULL)
		return ;
	dir = (OPTIONS_R) ? list->last : list->first;
	while (dir)
	{
		s = (dir->dir_content == NULL) ? dir->path : dir->dir_content->d_name;
		if ((dir->stat.st_mode & S_IFDIR) && ((ft_strcmp(".", s) &&
						ft_strcmp("..", s)) || (dir->dir_content == NULL)))
		{
			if ((OPTIONS_A || s[0] != '.') || dir->dir_content == NULL)
			{
				display_dir_name(dir);
				if ((dir->dir_stream = opendir(dir->path)) == NULL)
					perror("ls");
				else
				{
					file_list = read_dir(dir, dir->path, max);
					//display_list_first(file_list);
					//printf("\n\n");
					display_dir_content(file_list, max);
					(OPTIONS_CAP_R) ? recursion(file_list, max) : 0;
					free_list(file_list);
				}
			}
		}
		dir = (OPTIONS_R) ? dir->previous : dir->next;
	}
}
