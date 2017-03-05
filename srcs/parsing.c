/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 12:41:15 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/04 23:02:48 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	set_options(char **argv, int i, int j)
{
	if (argv[i][j] == 'a')
		OPTIONS_A = 'a';
	else if (argv[i][j] == 'l')
		OPTIONS_L = 'l';
	else if (argv[i][j] == 'r')
		OPTIONS_R = 'r';
	else if (argv[i][j] == 'R')
		OPTIONS_CAP_R = 'R';
	else if (argv[i][j] == 't')
		OPTIONS_T = 't';
	else if (j != 1 || argv[i][j] != '-')
	{
		printf("ls: illegal option -- %c\nusage : ls [-Ralrt] [file ...]\n",
				argv[i][j]);
		return (-1);
	}
	return (1);
}

static int	parse_options(int argc, char **argv, int *i, int j)
{
	if (argc > 1)
	{
		while (argv[*i] && argv[*i][0] == '-')
		{
			j = 1;
			if (ft_strcmp("-", argv[*i]) == 0)
				break ;
			if (ft_strncmp(argv[*i], "--", 2) == 0 && argv[*i][2])
			{
				printf("ls: illegal option -- -\n");
				printf("usage : ls [-Ralrt] [file ...]\n");
				return (-1);
			}
			while (argv[*i][j])
			{
				if (set_options(argv, *i, j) < 0)
					return (-1);
				j++;
			}
			(*i)++;
		}
	}
	return (1);
}

static int	valid_file(char *path)
{
	struct stat st;

	return (stat(path, &st));
}

static void	sort_invalid_filename(char **tab)
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

static char	**create_tab(int argc)
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
	}
	return (tab);
}

void	elem_dir(t_dlist *list, char **argv, int i)
{
	if (list->first == NULL)
	{
		list->first = create_dir(NULL, argv[i]);
		list->last = list->first;
	}
	else
	{
		list->last->next = create_dir(NULL, argv[i]);
		list->last->next->previous = list->last;
		list->last = list->last->next;
	}
	(list->last->next) ? lstat(list->last->next->path, &(list->last->next->stat)) :
		lstat(list->last->path, &(list->last->stat));
}

static t_dlist		*fill_tab_and_dir_list(char **argv, char **tab, int *i)
{
	t_dlist	*list;
	int		k;

	list = create_dlist();
	k = 0;
	list->first = NULL;
	while (argv[*i])
	{
		if (valid_file(argv[*i]) < 0)
			tab[k++] = ft_strdup(argv[*i]);
		else
			elem_dir(list, argv, *i);
		(*i)++;
	}
	tab[k] = NULL;
	return (list);
}

t_dlist		*parse_arg(int argc, char **argv)
{
	int		i;
	int		j;
	char	**tab;
	t_dlist	*arg_list;

	i = 1;
	j = 1;
	if (parse_options(argc, argv, &i, j) < 0)
		return (NULL);
	tab = create_tab(argc);
	arg_list = fill_tab_and_dir_list(argv, tab, &i);
	if (arg_list->first == NULL && !tab[0])
	{
		if ((arg_list->first = create_dir(NULL, ".")) == NULL)
			return (NULL);
		arg_list->last = arg_list->first;
		lstat(".", &(arg_list->first->stat));
	}
	sort_invalid_filename(tab);
	i = 0;
	while (tab[i])
		printf("ls : %s: No such file or directory\n", tab[i++]);
	if (arg_list->first == NULL)
		return (NULL);
	return (arg_list);
}

