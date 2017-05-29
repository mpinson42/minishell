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
}				t_glob;

void ft_dev(char *str, pid_t id);
void ft_libre(char **tab);

#endif