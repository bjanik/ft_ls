/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:57:56 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 16:19:16 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	set_colors(t_dir *dir)
{
	if (OPTIONS_G)
	{
		if (S_ISBLK(dir->stat.st_mode))
			return (ft_printf("%s%s", BLU, BACK_CYN));
		if (S_ISCHR(dir->stat.st_mode))
			return (ft_printf("%s%s", BLU, BACK_YEL));
		if (S_ISLNK(dir->stat.st_mode))
			return (ft_putstr(MAG));
		if (S_ISDIR(dir->stat.st_mode) && ((dir->stat.st_mode & S_IXOTH) &&
				dir->stat.st_mode & S_ISVTX) && (dir->stat.st_mode & S_IWUSR &&
				dir->stat.st_mode & S_IWGRP && dir->stat.st_mode & S_IWOTH))
			return (ft_printf("%s%s", BLK, BACK_GRN));
		if (S_ISDIR(dir->stat.st_mode))
			return (ft_putstr(BOLD_CYAN));
		if (S_ISFIFO(dir->stat.st_mode))
			return (ft_putstr(YEL));
		if (S_ISSOCK(dir->stat.st_mode))
			return (ft_putstr(GRN));
		if (S_ISREG(dir->stat.st_mode) && (dir->stat.st_mode & S_IXUSR ||
				dir->stat.st_mode & S_IXGRP || dir->stat.st_mode & S_IXOTH))
			return (ft_putstr(RED));
	}
	return (0);
}

static void	display_name(t_dir *dir)
{
	int	colors;

	colors = set_colors(dir);
	(dir->dir_content == NULL) ? ft_printf("%s", dir->path) :
			ft_printf("%s", dir->file_name);
	(colors) ? ft_putstr(RESET) : 0;
	if ((S_ISLNK(dir->stat.st_mode) && !OPTIONS_L && !OPTIONS_O) ||
			!S_ISLNK(dir->stat.st_mode))
		ft_putchar('\n');
}

void		display_file_name(t_dir *dir, t_max *max)
{
	char	*minor_major;
	int		secs;

	secs = (OPTIONS_CAP_T) ? 3 : 0;
	minor_major = NULL;
	if (OPTIONS_L || OPTIONS_O)
	{
		display_rights(dir);
		ft_printf("%*d %-*s  ", max->max_nlinks,
			dir->stat.st_nlink, max->max_user_name, dir->user);
		(!OPTIONS_O) ? ft_printf("%-*s  ", max->max_group_name, dir->group) : 0;
		if (S_ISBLK(dir->stat.st_mode) || S_ISCHR(dir->stat.st_mode))
			display_major_minor(dir, minor_major);
		else
			ft_printf("%*lld", max->max_size, dir->stat.st_size);
		ft_printf(" %s %*s %*.*s ", dir->date[1], 2, dir->date[2], 5 + secs,
				5 + secs, dir->date[3]);
		(OPTIONS_CAP_T) ? ft_printf("%.*s ", 4, dir->date[4]) : 0;
		display_name(dir);
		display_symbolic_link(dir);
	}
	else
		display_name(dir);
}

void		display_reg_files(t_dlist *list, t_max *max)
{
	t_dir	*dir;
	int		directory;
	int		file;

	directory = 0;
	file = 0;
	dir = (OPTIONS_R) ? list->last : list->first;
	while (dir)
	{
		if (S_ISDIR(dir->stat.st_mode) && !directory)
		{
			directory = 1;
			dir->file = 1;
		}
		if (!S_ISDIR(dir->stat.st_mode) || OPTIONS_D)
		{
			if (S_ISLNK(dir->stat.st_mode) && !OPTIONS_L && !OPTIONS_D)
				sym_links(dir);
			else
				display_file_name(dir, max);
			(!S_ISDIR(dir->stat.st_mode)) ? file = 1 : 0;
		}
		dir = (OPTIONS_R) ? dir->previous : dir->next;
	}
	(directory && file && !OPTIONS_D) ? ft_putchar('\n') : 0;
}

void		display_dir_content(t_dlist *list, t_max *max)
{
	t_dir	*dir;

	dir = (OPTIONS_R) ? list->last : list->first;
	if ((OPTIONS_L || OPTIONS_O) && dir)
		ft_printf("total %d\n", max->total_blocks);
	if (OPTIONS_R)
	{
		while (dir)
		{
			display_file_name(dir, max);
			dir = dir->previous;
		}
	}
	else
	{
		while (dir)
		{
			display_file_name(dir, max);
			dir = dir->next;
		}
	}
}
