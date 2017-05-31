#ifndef MINI_H
# define MINI_H

# include "libft.h"
# include <pwd.h>
# include <time.h>
# include <grp.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <sys/xattr.h>

typedef struct	s_glob
{
	char **env;
	char **tab;
	char *tmp;
}				t_glob;

void ft_dev(char *str, pid_t id, t_glob *g);
void ft_libre(char **tab);
char			**ft_strsplit_free(char const *s, char c);
void ft_strsub_free(char const *s, unsigned int start, size_t len, t_glob *g);

char			**ft_strsplit2(char*s, char c);
void ft_set_env(char *str, t_glob *g);
int ft_strlen_tab(char **tab);
void ft_unset_env(char *str, t_glob *g);
int ft_env(char *str, t_glob *g);
int ft_echo(char *str, t_glob *g);
int ft_cd(char *str, t_glob *g);

#endif