/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:49:44 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/01 18:52:46 by bjanik           ###   ########.fr       */
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

void		display_rights(struct stat stat)
{
	char	rights[13];

	ft_memset(rights, ' ', 13);
	rights[0] = set_file_type(stat);
	rights[1] = (stat.st_mode & S_IRUSR) ? 'r' : '-';
	rights[2] = (stat.st_mode & S_IWUSR) ? 'w' : '-';
	rights[3] = (stat.st_mode & S_IXUSR) ? 'x' : '-';
	rights[4] = (stat.st_mode & S_IRGRP) ? 'r' : '-';
	rights[5] = (stat.st_mode & S_IWGRP) ? 'w' : '-';
	rights[6] = (stat.st_mode & S_IXGRP) ? 'x' : '-';
	rights[7] = (stat.st_mode & S_IROTH) ? 'r' : '-';
	rights[8] = (stat.st_mode & S_IWOTH) ? 'w' : '-';
	rights[9] = (stat.st_mode & S_IXOTH) ? 'x' : '-';
	write(1, rights, 12);
}
