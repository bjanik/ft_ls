/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:17:41 by bjanik            #+#    #+#             */
/*   Updated: 2017/03/05 00:39:38 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <stdio.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>

# define CYAN "\033[036m"
# define YELLOW "\033[036m"
# define RESET "\033[0m"
# define IS_FIFO 1
# define IS_DIR 4
# define IS_REG 8
# define IS_LINK 10
# define HALF_YEAR 86400*365.25 / 2
# define OPTIONS_A  g_options[0]
# define OPTIONS_L  g_options[1]
# define OPTIONS_R  g_options[2]
# define OPTIONS_CAP_R  g_options[3]
# define OPTIONS_T  g_options[4]
# define MINOR(dev) (dev & 0xff)
# define MAJOR(dev) ((dev >> 24) & 0xff)

char	g_options[6];

typedef struct		s_dir
{
	char			*path;
	DIR				*dir_stream;
	struct dirent	*dir_content;
	struct stat		stat;
	struct passwd	*user;
	struct group	*group;
	char			*ctime;
	char			**date;
	char			*buf_link;
	struct s_dir	*next;
	struct s_dir	*previous;
}					t_dir;

typedef struct		s_dlist
{
	t_dir			*first;
	t_dir			*last;
}					t_dlist;

typedef struct		s_max
{
	int				max_nlinks;
	int				max_size;
	size_t			total_blocks;
	int				max_group_name;
	int				max_user_name;
}					t_max;

void	init_max(t_max *max);
t_dlist	*parse_arg(int argc, char **argv);
t_dir	*create_dir(struct dirent *dir_content, char *path);
t_dlist	*create_dlist(void);
t_dlist	*read_dir(t_dir *dir_list, char *path, t_max *max);
void	append_file_list(t_dlist *list, struct dirent *dir_content, char *path);
void	display_list(t_dlist *dir);
void	display_l(t_dir *dir, t_max *max);
void	display_list_first(t_dlist *dir);
void	display_dir(t_dlist *list, t_max *max);
void	display_file_name(t_dir *list, t_max *max);
void	display_reg_files(t_dlist *list, t_max *max);
void	get_maxs(t_dir *dir, t_max *max);
void	display_rights(struct stat info);
void	sort_name(t_dlist *list);
void	sort_time(t_dlist *list);
void	swap_nodes(t_dir *a, t_dir *b);
int		ft_printf(const char *format, ...);
void	recursion(t_dlist *dir, t_max *max);
void	display_dir_content(t_dlist *list, t_max *max);
void	free_list(t_dlist *list);
t_max	*malloc_max(void);

#endif
