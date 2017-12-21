/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 12:41:15 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 17:12:48 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			elem_dir(t_dlist *list, char **argv, int i)
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
	lstat(list->last->path, &(list->last->stat));
}

static t_dlist	*fill_tab_and_dir_list(char **argv, char **tab, int *i)
{
	t_dlist	*list;
	int		k;

	list = create_dlist();
	k = 0;
	list->first = NULL;
	while (argv[*i])
	{
		if (ft_valid_file(argv[*i]) < 0)
			tab[k++] = ft_strdup(argv[*i]);
		else
			elem_dir(list, argv, *i);
		(*i)++;
	}
	tab[k] = NULL;
	return (list);
}

static void		display_invalid_file(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(tab[i++], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

static void		set_current_dir(t_dlist *arg_list)
{
	arg_list->first = create_dir(NULL, ".");
	arg_list->last = arg_list->first;
	stat(".", &(arg_list->first->stat));
}

t_dlist			*parse_arg(int argc, char **argv)
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
		set_current_dir(arg_list);
	if (arg_list && arg_list->first)
		arg_list->first->error = (tab[0]) ? 1 : 0;
	sort_invalid_filename(tab);
	display_invalid_file(tab);
	ft_free_string_tab(tab);
	if (arg_list->first == NULL)
		return (NULL);
	return (arg_list);
}
