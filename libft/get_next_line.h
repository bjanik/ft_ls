/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:32:51 by bjanik            #+#    #+#             */
/*   Updated: 2017/01/09 16:58:02 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# define BUFF_SIZE 4096
# define TEMP_SIZE 50000
# define FD_MAX 7168

int				get_next_line(const int fd, char **line);
typedef struct	s_fd
{
	char		*tmp;
	char		*nl;
	size_t		mem_size;
}				t_fd;
#endif
