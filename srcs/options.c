/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 17:11:03 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 17:15:07 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	error(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage : ls [-AGRSTadflort] [file ...]", 2);
	return (-1);
}

static void	more_options(char c)
{
	if (c == 'S')
		OPTIONS_S = 'S';
	else if (c == 't')
		OPTIONS_T = 't';
	else if (c == 'T')
		OPTIONS_CAP_T = 'T';
}

int			set_options(char **argv, int i, int j)
{
	if (argv[i][j] == 'a')
		OPTIONS_A = 'a';
	else if (argv[i][j] == 'A')
		OPTIONS_CAP_A = 'A';
	else if (argv[i][j] == 'f')
		OPTIONS_F = 'f';
	else if (argv[i][j] == 'd')
		OPTIONS_D = 'd';
	else if (argv[i][j] == 'G')
		OPTIONS_G = 'G';
	else if (argv[i][j] == 'l')
		OPTIONS_L = 'l';
	else if (argv[i][j] == 'o')
		OPTIONS_O = 'o';
	else if (argv[i][j] == 'r')
		OPTIONS_R = 'r';
	else if (argv[i][j] == 'R')
		OPTIONS_CAP_R = 'R';
	else if (argv[i][j] == 't' || argv[i][j] == 'S' || argv[i][j] == 'T')
		more_options(argv[i][j]);
	else if (j != 1 || argv[i][j] != '-')
		return (error(argv[i][j]));
	return (1);
}

int			parse_options(int argc, char **argv, int *i, int j)
{
	if (argc > 1)
	{
		while (argv[*i] && argv[*i][0] == '-')
		{
			j = 1;
			if (ft_strcmp("-", argv[*i]) == 0)
				break ;
			if (ft_strncmp(argv[*i], "--", 2) == 0 && argv[*i][2])
				return (error('-'));
			if (!ft_strcmp(argv[*i], "--"))
			{
				(*i)++;
				break ;
			}
			while (argv[*i][j])
			{
				if (set_options(argv, *i, j++) < 0)
					return (-1);
			}
			(*i)++;
		}
	}
	(OPTIONS_F) ? OPTIONS_A = 'a' : 0;
	(OPTIONS_F) ? OPTIONS_R = '\0' : 0;
	return (1);
}
