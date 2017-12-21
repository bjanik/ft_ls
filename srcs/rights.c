/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:49:44 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/09 17:05:23 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	set_file_type(struct stat stat)
{
	if (S_ISREG(stat.st_mode))
		return ('-');
	if (S_ISDIR(stat.st_mode))
		return ('d');
	if (S_ISFIFO(stat.st_mode))
		return ('p');
	if (S_ISLNK(stat.st_mode))
		return ('l');
	if (S_ISBLK(stat.st_mode))
		return ('b');
	if (S_ISSOCK(stat.st_mode))
		return ('s');
	if (S_ISCHR(stat.st_mode))
		return ('c');
	return (0);
}

static void	set_user_exec_field(char *rights, struct stat stat)
{
	if ((stat.st_mode & S_IXUSR) && (stat.st_mode & S_ISUID))
		*rights = 's';
	else if (!(stat.st_mode & S_IXUSR) && (stat.st_mode & S_ISUID))
		*rights = 'S';
	else if (stat.st_mode & S_IXUSR)
		*rights = 'x';
	else
		*rights = '-';
}

static void	set_group_exec_field(char *rights, struct stat stat)
{
	if ((stat.st_mode & S_IXGRP) && (stat.st_mode & S_ISUID))
		*rights = 's';
	else if (!(stat.st_mode & S_IXGRP) && (stat.st_mode & S_ISUID))
		*rights = 'S';
	else if (stat.st_mode & S_IXGRP)
		*rights = 'x';
	else
		*rights = '-';
}

void		display_rights(t_dir *dir)
{
	char	rights[13];

	ft_memset(rights, ' ', 12);
	rights[12] = '\0';
	rights[0] = set_file_type(dir->stat);
	rights[1] = (dir->stat.st_mode & S_IRUSR) ? 'r' : '-';
	rights[2] = (dir->stat.st_mode & S_IWUSR) ? 'w' : '-';
	set_user_exec_field(&rights[3], dir->stat);
	rights[4] = (dir->stat.st_mode & S_IRGRP) ? 'r' : '-';
	rights[5] = (dir->stat.st_mode & S_IWGRP) ? 'w' : '-';
	set_group_exec_field(&rights[6], dir->stat);
	rights[7] = (dir->stat.st_mode & S_IROTH) ? 'r' : '-';
	rights[8] = (dir->stat.st_mode & S_IWOTH) ? 'w' : '-';
	if ((dir->stat.st_mode & S_IXOTH) && (dir->stat.st_mode & S_ISVTX))
		rights[9] = 't';
	else if (!(dir->stat.st_mode & S_IXOTH) && (dir->stat.st_mode & S_ISVTX))
		rights[9] = 'T';
	else if (dir->stat.st_mode & S_IXOTH)
		rights[9] = 'x';
	else
		rights[9] = '-';
	ft_printf("%s", rights);
}
