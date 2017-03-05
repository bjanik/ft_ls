/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:21:13 by bjanik            #+#    #+#             */
/*   Updated: 2016/12/22 12:53:03 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		init(t_fd *p_fd)
{
	if (p_fd->tmp == NULL)
	{
		if ((p_fd->tmp = ft_memalloc(TEMP_SIZE + 1)) == NULL)
			return (0);
		p_fd->mem_size = TEMP_SIZE + 1;
		p_fd->nl = NULL;
	}
	return (1);
}

char	*ft_realloc(t_fd *p_fd, size_t *mem_size, int ret)
{
	char	*s;

	while (*mem_size < ft_strlen(p_fd->tmp) + ret)
	{
		s = p_fd->tmp;
		*mem_size *= 2;
		p_fd->tmp = ft_memalloc(*mem_size);
		ft_strcpy(p_fd->tmp, s);
		free(s);
	}
	return (p_fd->tmp);
}

int		check_fd(const int fd, t_fd *p_fd, char **line)
{
	int		ret;
	char	c;

	if (line == NULL)
		return (-1);
	if (p_fd->tmp != NULL)
		return (1);
	if ((ret = read(fd, &c, 1)) > -1)
	{
		if (init(p_fd) == 0)
			return (-1);
		if (ret > 0)
			(p_fd->tmp)[0] = c;
	}
	return (1);
}

int		gnl_return_value(t_fd *p_fd, int ret, char **line)
{
	if (ret == -1)
		return (-1);
	if (ft_strlen(p_fd->tmp) > 0 && ret == 0)
	{
		if ((p_fd->nl = ft_strchr(p_fd->tmp, '\n')) != NULL)
		{
			if ((*line = ft_strndup(p_fd->tmp, p_fd->nl - p_fd->tmp)) == NULL)
				return (-1);
			ft_strcpy(p_fd->tmp, p_fd->nl + 1);
		}
		else
		{
			if ((*line = ft_strdup(p_fd->tmp)) == NULL)
				return (-1);
			(p_fd->tmp)[0] = '\0';
		}
	}
	else if (ret == 0 && ft_strlen(p_fd->tmp) == 0)
		return (0);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	static t_fd	p_fd[FD_MAX];

	if (fd < 0 || fd >= FD_MAX || check_fd(fd, p_fd + fd, line) == -1)
		return (-1);
	*line = NULL;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((p_fd + fd)->mem_size < ft_strlen((p_fd + fd)->tmp) + BUFF_SIZE)
			if (((p_fd + fd)->tmp = ft_realloc((p_fd + fd),
							&((p_fd + fd)->mem_size), ret)) == NULL)
				return (-1);
		ft_strcat((p_fd + fd)->tmp, buff);
		if (((p_fd + fd)->nl = ft_strchr((p_fd + fd)->tmp, '\n')) != NULL)
		{
			if ((*line = ft_strndup((p_fd + fd)->tmp, (p_fd + fd)->nl
							- (p_fd + fd)->tmp)) == NULL)
				return (-1);
			ft_strcpy((p_fd + fd)->tmp, (p_fd + fd)->nl + 1);
			break ;
		}
	}
	return (gnl_return_value((p_fd + fd), ret, line));
}
