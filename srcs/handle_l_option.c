/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_l_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 14:57:21 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/24 14:08:11 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_maxs(t_dir *dir, t_max *max)
{
	int	len;

	len = 0;
	if (dir->stat.st_nlink > max->max_nlinks)
		max->max_nlinks = dir->stat.st_nlink;
	if (dir->stat.st_size > max->max_size)
		max->max_size = dir->stat.st_size;
	if (dir->stat.st_mode & S_IFBLK || dir->stat.st_mode & S_IFCHR)
	{
		if (max->max_size < 8)
			max->max_size = 12345678;
	}
	if ((len = ft_strlen(dir->user->pw_name)) > max->max_user_name)
		max->max_user_name = len;
	if ((len = ft_strlen(dir->group->gr_name)) > max->max_group_name)
		max->max_group_name = len;
}

static void	fill_max(t_dir *dir, t_max *max)
{
	if ((dir->user = getpwuid(dir->stat.st_uid)) == NULL)
		perror("getpwuid");
	if ((dir->group = getgrgid(dir->stat.st_gid)) == NULL)
		perror("getgrgid");
	dir->ctime = ctime(&(dir->stat.st_mtime));
	dir->date = ft_strsplit(dir->ctime, ' ');
	if (time(NULL) - HALF_YEAR > dir->stat.st_mtime)
	{
		ft_strncpy(dir->date[3], dir->date[4], 4);
		dir->date[3][4] = '\0';
	}
	set_maxs(dir, max);
	if (OPTIONS_A || (dir->dir_content && dir->dir_content->d_name[0] != '.'))
		max->total_blocks += dir->stat.st_blocks;
}

void	get_maxs(t_dir *dir, t_max *max)
{
	if (dir == NULL)
		return ;
	init_max(max);
	while (dir)
	{
		if ((dir->dir_content == NULL && !(dir->stat.st_mode & S_IFDIR)) ||
				dir->dir_content != NULL)
			fill_max(dir, max);
		dir = dir->next;
	}
	max->max_nlinks = ft_nb_digit_base(max->max_nlinks, 10);
	max->max_size = ft_nb_digit_base(max->max_size, 10);
}
