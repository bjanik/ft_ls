/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:17:41 by bjanik            #+#    #+#             */
/*   Updated: 2017/04/11 11:40:38 by bjanik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>

# define HALF_YEAR 86400*365.25 / 2
# define OPTIONS_A  g_options[0]
# define OPTIONS_CAP_A  g_options[1]
# define OPTIONS_D  g_options[2]
# define OPTIONS_F  g_options[3]
# define OPTIONS_G  g_options[4]
# define OPTIONS_L  g_options[5]
# define OPTIONS_O  g_options[6]
# define OPTIONS_R  g_options[7]
# define OPTIONS_CAP_R  g_options[8]
# define OPTIONS_S  g_options[9]
# define OPTIONS_T  g_options[10]
# define OPTIONS_CAP_T  g_options[11]
# define MINOR(dev) (dev & 0xff)
# define MAJOR(dev) ((dev >> 24) & 0xff)
# define MAXPATHLEN 256

char				g_options[13];

typedef struct		s_dir
{
	char			*path;
	char			*sym_link_path;
	DIR				*dir_stream;
	struct dirent	*dir_content;
	char			*file_name;
	struct stat		stat;
	char			*user;
	char			*group;
	char			*mtime;
	char			*ctime;
	char			**date;
	char			*buf_link;
	struct s_dir	*next;
	struct s_dir	*previous;
	int				file;
	int				error;
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
	int				total_blocks;
	int				max_group_name;
	int				max_user_name;
}					t_max;

t_dlist				*parse_arg(int argc, char **argv);
t_dir				*create_dir(struct dirent *dir_content, char *path);
t_dlist				*create_dlist(void);
t_dlist				*read_dir(t_dir *dir_list, char *path, t_max *max);
int					set_options(char **argv, int i, int j);
int					parse_options(int argc, char **argv, int *i, int j);
void				append_file_list(t_dlist *list, struct dirent *dir_content,
					char *path);
void				display_dir(t_dlist *list, t_max *max);
void				display_file_name(t_dir *list, t_max *max);
void				display_reg_files(t_dlist *list, t_max *max);
void				get_maxs(t_dir *dir, t_max *max);
void				display_rights(t_dir *dir);
void				fill_buf_link(t_dir *dir);
void				display_major_minor(t_dir *dir, char *minor_major);
void				sym_links(t_dir *dir);
void				display_symbolic_link(t_dir *dir);
char				*handle_major_minor(t_dir *dir);
void				ft_ls(t_dlist *dir, t_max *max);
void				display_dir_content(t_dlist *list, t_max *max);
void				free_list(t_dlist *list);
t_max				*malloc_max(void);
void				init_max(t_max *max);
t_dir				*ft_merge_sort(t_dir *dir);
void				update_head_tail(t_dlist *file_list);
void				sort_invalid_filename(char **tab);
char				**create_tab(int argc);
void				ft_perror_msg(char *str);
#endif
