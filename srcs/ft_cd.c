#include "mini.h"

int ft_cd(char *str, t_glob *g)
{
	int i;
	char **tab;
	char *old_pwd;
	DIR *rep;
	char test[5000];
	char *tmp;

	i = 0;
	if(ft_strncmp("cd", str, 2) == 0)
	{
		tab = ft_strsplit(str, ' ');
		if (tab[1] && ft_strncmp(tab[1], "-", 1) != 0 && !(rep = opendir(tab[1])))
		{
			ft_putendl("cd: no such file or directory");
			ft_libre(tab);
			return (1);
		}
		if(tab[1] && ft_strncmp(tab[1], "-", 1) != 0)
			closedir(rep);
		if(tab[1] == NULL)
		{
			while(g->env[i] != NULL && ft_strncmp(g->env[i], "OLDPWD=", 7) != 0)
				i++;
			if(g->env[i] == NULL)
			{
				ft_set_env("setenv OLDPWD /", g);
				i = 0;
				while(g->env[i] != NULL && ft_strncmp(g->env[i], "HOME=", 5) != 0)
					i++;
				if(g->env[i] == NULL)
					ft_set_env("setenv HOME /Users/mpinson", g);
				chdir("/Users/mpinson");
				ft_set_env("setenv PWD /Users/mpinson", g);
			}
			else
			{
				free(g->env[i]);
				g->env[i] = ft_strjoin("OLDPWD=", getcwd(test, 4999));
				i = 0;
				while(g->env[i] != NULL && ft_strncmp(g->env[i], "HOME=", 5) != 0)
					i++;
				if(g->env[i] == NULL)
					ft_set_env("setenv HOME /Users/mpinson", g);
				chdir("/Users/mpinson");
				ft_set_env("setenv PWD /Users/mpinson", g);
			}
		}
		else if(ft_strncmp(tab[1], "-", 1) == 0)
		{
			while(g->env[i] != NULL && ft_strncmp(g->env[i], "OLDPWD=", 7) != 0)
				i++;
			if(g->env[i] == NULL)
			{
				ft_set_env("setenv OLDPWD /", g);
				ft_set_env("setenv PWD /", g);
				chdir("/");
			}
			else
			{
				free(g->env[i]);
				old_pwd = ft_strsub(g->env[i], 7, ft_strlen(g->env[i]));
				g->env[i] = ft_strjoin("OLDPWD=", getcwd(test, 4999));
				chdir(old_pwd);
				tmp = ft_strjoin("setenv PWD ", old_pwd);
				ft_set_env(tmp, g);
				free(tmp);
				free(old_pwd);
			}
		}
		else
		{
			while(g->env[i] != NULL && ft_strncmp(g->env[i], "OLDPWD=", 7) != 0)
				i++;
			if(g->env[i] == NULL)
			{
				ft_set_env("setenv OLDPWD /", g);
				chdir(tab[1]);
				tmp = ft_strjoin("setenv PWD ", getcwd(test, 4999));
				ft_set_env(tmp, g);
				free(tmp);
			}
			else
			{
				free(g->env[i]);
				g->env[i] = ft_strjoin("OLDPWD=", getcwd(test, 4999));
				chdir(tab[1]);
				tmp = ft_strjoin("setenv PWD ", getcwd(test, 4999));
				ft_set_env(tmp, g);
				free(tmp);
			}
		}
		ft_libre(tab);
		return(1);
	}
	return (0);
}