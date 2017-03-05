/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 15:15:36 by bjanik            #+#    #+#             */
/*   Updated: 2017/02/16 09:14:59 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_directory_size(t_directory *start_directory)
{
	int	size;

	size = 0;
	while (start_directory)
	{
		size++;
		start_directory = start_directory->next;
	}
	return (size);
}

t_directory	*create_elem(DIR *dir)
{
	t_directory	*p;

	if ((p = (t_directory*)malloc(sizeof(t_directory))) == NULL)
		return (NULL);
	p->next = NULL;
	return (p);
}

void	push_back_directory(t_directory **first_directory, DIR *dir)
{
	t_directory	*p;
	t_directory	*d;

	p = create_elem(dir);
	d = *first_directory;
	if (*first_directory)
	{
		while (d->next)
			d = d->next;
		d->next = p;
	}
	else
		*first_directory = p;
}

void	push_front_directory(t_directory **first_directory, DIR *dir)
{
	t_directory	*p;

	p = create_elem(dir);
	if (*first_directory)
	{
		p->next = *first_directory;
		*first_directory = p;
	}
	else
		*first_directory = p;
}
