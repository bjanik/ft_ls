/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:50:21 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 17:12:41 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_perror_msg(char *str)
{
	perror(str);
	exit(-1);
}

void	sort_invalid_filename(char **tab)
{
	int		i;
	char	*s;

	i = 0;
	while (tab[i] && tab[i + 1])
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			s = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = s;
			i = 0;
		}
		else
			i++;
	}
}

char	**create_tab(int argc)
{
	char	**tab;
	int		k;

	k = 0;
	tab = NULL;
	if (argc > 1)
	{
		if ((tab = (char**)malloc(argc * sizeof(char *))) == NULL)
		{
			perror("malloc");
			exit(-1);
		}
		while (k < argc)
			tab[k++] = NULL;
	}
	return (tab);
}
