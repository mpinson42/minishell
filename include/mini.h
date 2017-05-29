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

void ft_dev(char *str, pid_t id);
void ft_libre(char **tab);
char			**ft_strsplit_free(char const *s, char c);
void ft_strsub_free(char const *s, unsigned int start, size_t len, t_glob *g);
void ft_unset_env(char *str, char **env, pid_t id, t_glob *g);

#endif