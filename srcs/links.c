/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:17:39 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 16:41:07 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sym_links(t_dir *dir)
{
	char	*tmp;

	fill_buf_link(dir);
	if (!ft_strcmp(dir->path, dir->buf_link))
		ft_printf("%s\n", dir->path);
	if (stat(dir->buf_link, &(dir->stat)) < 0)
	{
		if (dir->buf_link[0] != '/')
		{
			if ((tmp = ft_strrchr(dir->path, '/')) != NULL)
			{
				dir->sym_link_path = ft_strncpy(dir->sym_link_path,
					dir->path, tmp - dir->path + 1);
				ft_strcat(dir->sym_link_path, dir->buf_link);
				stat(dir->sym_link_path, &(dir->stat));
			}
		}
	}
	if (!S_ISDIR(dir->stat.st_mode) && !OPTIONS_D)
		ft_printf("%s\n", dir->path);
}

void	fill_buf_link(t_dir *dir)
{
	if ((dir->buf_link = ft_memalloc(MAXPATHLEN + 1)) == NULL)
		ft_perror_msg("malloc");
	if ((dir->sym_link_path = ft_memalloc(MAXPATHLEN + 1)) == NULL)
		ft_perror_msg("malloc");
	if (readlink(dir->path, dir->buf_link, MAXPATHLEN) < 0)
		ft_perror_msg("readlink");
}

void	display_symbolic_link(t_dir *dir)
{
	if (S_ISLNK(dir->stat.st_mode))
	{
		if ((dir->buf_link = ft_memalloc(MAXPATHLEN + 1)) == NULL)
			ft_perror_msg("malloc");
		readlink(dir->path, dir->buf_link, MAXPATHLEN);
		(dir->buf_link[0]) ? ft_printf(" -> %s\n", dir->buf_link) : 0;
		ft_memdel((void**)&(dir->buf_link));
	}
}
