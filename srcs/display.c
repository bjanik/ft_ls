/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:57:56 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/05 00:39:36 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_symbolic_link(t_dir *dir)
{
	if (dir->stat.st_mode & S_IFLNK)
	{
		if ((dir->buf_link = (char*)malloc(256 * sizeof(char))) == NULL)
		{
			perror("malloc");
			exit(-1);
		}
		readlink(dir->path, dir->buf_link, 255);
		(dir->buf_link[0]) ? printf(" -> %s", dir->buf_link) : 0;
		ft_memdel((void**)&(dir->buf_link));
	}
}

char	*handle_major_minor(t_dir *dir)
{
	char	*minor_major;
	char	*minor;
	char	*major;

	major = ft_itoa(MAJOR(dir->stat.st_dev));
	minor = ft_itoa(MINOR(dir->stat.st_dev));
	if ((minor_major = ft_memalloc(9)) == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	ft_strcpy((minor_major + 3 - ft_strlen(major)), major);
	ft_strcpy((minor_major + 7 - ft_strlen(minor)), minor);
	free(minor);
	free(major);
	return (minor_major);
}

void	display_file_name(t_dir *dir, t_max *max)
{
	char	*minor_major;

	minor_major = NULL;
	if (OPTIONS_L)
	{
		display_rights(dir->stat);
		printf("%*d %-*s  %-*s  ", max->max_nlinks,
			dir->stat.st_nlink, max->max_user_name, dir->user->pw_name,
			max->max_group_name, dir->group->gr_name);
		/*if (S_ISBLK(dir->stat.st_mode) || S_ISCHR(dir->stat.st_mode))
		{
			minor_major = handle_major_minor(dir);
			printf("%s", minor_major);
		}
		else*/
		printf("%*lld", max->max_size, dir->stat.st_size);
		printf(" %s %*s %5.5s %s", dir->date[1], 2, dir->date[2], dir->date[3],
			(dir->dir_content) ? dir->dir_content->d_name : dir->path);
		display_symbolic_link(dir);
		printf("\n");
	}
	else
		(dir->dir_content == NULL) ? printf("%s\n", dir->path) :
			printf("%s\n", dir->dir_content->d_name);
}

void	display_reg_files(t_dlist *list, t_max *max)
{
	t_dir	*dir;

	dir = (OPTIONS_R) ? list->last : list->first;
	while (dir)
	{
		if (!(dir->stat.st_mode & S_IFDIR))
			display_file_name(dir, max);
		dir = (OPTIONS_R) ? dir->previous : dir->next;
	}
}

void	display_dir_content(t_dlist *list, t_max *max)
{
	t_dir	*dir;

	dir = (OPTIONS_R) ? list->last : list->first;
	(OPTIONS_L && dir) ? printf("total %zu\n", max->total_blocks) : 0;
	while (dir)
	{
		if (OPTIONS_A || dir->dir_content->d_name[0] != '.')
			display_file_name(dir, max);
		dir = (OPTIONS_R) ? dir->previous : dir->next;
	}
	}
