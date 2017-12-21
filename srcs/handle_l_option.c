/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_l_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 14:57:21 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 13:53:51 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*handle_major_minor(t_dir *dir)
{
	char	*minor_major;
	char	*minor;
	char	*major;

	major = ft_itoa(MAJOR(dir->stat.st_rdev));
	minor = ft_itoa(MINOR(dir->stat.st_rdev));
	if ((minor_major = ft_memalloc(9)) == NULL)
	{
		perror("malloc");
		exit(-1);
	}
	ft_memset((void*)minor_major, ' ', 8);
	ft_strcpy((minor_major + 3 - ft_strlen(major)), major);
	minor_major[3] = ',';
	ft_strcpy((minor_major + 8 - ft_strlen(minor)), minor);
	ft_strdel(&minor);
	ft_strdel(&major);
	return (minor_major);
}

void		display_major_minor(t_dir *dir, char *minor_major)
{
	minor_major = handle_major_minor(dir);
	ft_printf("%s", minor_major);
	ft_strdel(&minor_major);
}

static void	set_maxs(t_dir *dir, t_max *max)
{
	int	len;

	len = 0;
	if (dir->stat.st_nlink > max->max_nlinks)
		max->max_nlinks = dir->stat.st_nlink;
	if (dir->stat.st_size > max->max_size)
		max->max_size = dir->stat.st_size;
	if (S_ISBLK(dir->stat.st_mode) || S_ISCHR(dir->stat.st_mode))
	{
		if (max->max_size < 8)
			max->max_size = 12345678;
	}
	if ((len = ft_strlen(dir->user)) > max->max_user_name)
		max->max_user_name = len;
	if ((len = ft_strlen(dir->group)) > max->max_group_name)
		max->max_group_name = len;
}

static void	fill_max(t_dir *dir, t_max *max)
{
	int				i;
	struct group	*grp;
	struct passwd	*user;

	i = 0;
	if ((user = getpwuid(dir->stat.st_uid)) == NULL)
		ft_perror_msg("getpwuid");
	if ((grp = getgrgid(dir->stat.st_gid)) == NULL)
		ft_perror_msg("getgrgid");
	dir->user = ft_strdup(user->pw_name);
	dir->group = ft_strdup(grp->gr_name);
	dir->ctime = ctime(&(dir->stat.st_mtime));
	dir->date = ft_strsplit(dir->ctime, ' ');
	if ((time(NULL) - HALF_YEAR > dir->stat.st_mtime) && !OPTIONS_CAP_T)
	{
		ft_strncpy(dir->date[3], dir->date[4], 4);
		dir->date[3][4] = '\0';
	}
	set_maxs(dir, max);
	max->total_blocks += dir->stat.st_blocks;
}

void		get_maxs(t_dir *dir, t_max *max)
{
	if (dir == NULL)
		return ;
	init_max(max);
	while (dir)
	{
		if (((dir->dir_content == NULL && !S_ISDIR(dir->stat.st_mode)) ||
				OPTIONS_D) || dir->dir_content != NULL)
			fill_max(dir, max);
		dir = dir->next;
	}
	max->max_nlinks = ft_nb_digit_base(max->max_nlinks, 10);
	max->max_size = ft_nb_digit_base(max->max_size, 10);
}
