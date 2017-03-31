/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:49:44 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/24 15:26:43 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	set_file_type(struct stat stat)
{
	if (S_ISREG(stat.st_mode))
		 return ('-');
	else if (S_ISDIR(stat.st_mode))
		return ('d');
	else if (S_ISFIFO(stat.st_mode))
		return ('p');
	else if (S_ISLNK(stat.st_mode))
		return ('l');
	else if (S_ISBLK(stat.st_mode))
		return ('b');
	else if (S_ISSOCK(stat.st_mode))
		return ('s');
	else if (S_ISCHR(stat.st_mode))
		return ('c');
	return (0);
}

static void	set_exec_field(char *rights, struct stat stat)
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

void		display_rights(struct stat stat)
{
	char	rights[13];

	ft_memset(rights, ' ', 12);
	rights[12] = '\0';
	rights[0] = set_file_type(stat);
	rights[1] = (stat.st_mode & S_IRUSR) ? 'r' : '-';
	rights[2] = (stat.st_mode & S_IWUSR) ? 'w' : '-';
	set_exec_field(&rights[3], stat);
	rights[4] = (stat.st_mode & S_IRGRP) ? 'r' : '-';
	rights[5] = (stat.st_mode & S_IWGRP) ? 'w' : '-';
	set_exec_field(&rights[6], stat);
	rights[7] = (stat.st_mode & S_IROTH) ? 'r' : '-';
	rights[8] = (stat.st_mode & S_IWOTH) ? 'w' : '-';
	if ((stat.st_mode & S_IXOTH) && (stat.st_mode & S_ISVTX))
		rights[9] = 't';
	else if (!(stat.st_mode & S_IXOTH) && (stat.st_mode & S_ISVTX))
		rights[9] = 'T';
	else if (stat.st_mode & S_IXOTH)
		rights[9] = 'x';
	else
		rights[9] = '-';
	printf("%s", rights);
}
