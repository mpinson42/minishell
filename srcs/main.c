#include "mini.h"

int isex(char *str)
{
	struct stat s;
	if (lstat(str, &s) == -1)
		return (0);
	if(s.st_mode & S_IXUSR && s.st_mode & S_IXGRP && s.st_mode & S_IXOTH)
	{
		return(1);
	}
	return(0);
}

void ft_libre(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void ft_libre2(char ***tab)
{
	int i;

	i = 0;
	while(tab[0][i] != NULL)
	{
		free(tab[0][i]);
		i++;
	}
	free(tab[0]);
}

void ft_libre3(t_glob *g)
{
	int i;

	i = 0;
	while(g->env[i] != NULL)
	{
		free(g->env[i]);
		i++;
	}
	free(g->env);
}

int ft_strlen_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
		i++;
	return(i);
}

void ft_set_env(char *str, char **env, pid_t id, t_glob *g)
{
	char *tmp;
	char **tab;
	char *var;
	char **test;
	int i = 0;
	int j = 0;


	tab = ft_strsplit(str, ' ');
	if(tab[1] == NULL)
	{
		ft_libre(tab);
		return ;
	}
	tmp = ft_strjoin(tab[1], "=");
	if(tab[2])
		var = ft_strjoin(tmp, tab[2]);
	else
		var = ft_strjoin(tab[1], "=");
	free(tmp);


	i = 0;
	while(g->env[i] && ft_strncmp(g->env[i], tab[1], ft_strlen(tab[1])) != 0)
			i++;
	if(g->env[i] != NULL)
	{
		ft_libre(tab);
		free(g->env[i]);
		g->env[i] = var;
		return;
	}



	i = 0;
	j = 0;
	test = (char**)malloc(sizeof(char*) * (ft_strlen_tab(g->env) + 2));
	while(g->env[i])
	{
		test[j] = ft_strdup(g->env[i]);
		i++;
		j++;
	}
	test[i] = NULL;

	//ft_libre3(g);
	i = 0;
	j = 0;
	ft_libre(g->env);
	if(!(g->env = (char **)malloc(sizeof(char *) * (ft_strlen_tab(test) + 1))))
		return ;
	while(test[i] != NULL)
	{
		
		g->env[j] = ft_strdup(test[i]);
		i++;
		j++;
	}
	g->env[j] = var;
	g->env[j + 1] = NULL;
	ft_libre(tab);
	ft_libre(test);
}


void ft_unset_env(char *str, char **env, pid_t id, t_glob *g)
{
	char **tmp;
	char **tab;
	char *var;
	int i;
	int j;
	char **test;


	tab = ft_strsplit(str, ' ');
	i = 0;
	while(g->env[i] != NULL && ft_strncmp(g->env[i], tab[1], ft_strlen(tab[1])) != 0)
		i++;
	if(tab[1] == NULL || g->env[i] == NULL)
	{
		ft_putstr("error\n");
		ft_libre(tab);
		return ;
	}
	i = 0;
	j = 0;
	test = (char**)malloc(sizeof(char*) * (ft_strlen_tab(g->env) + 2));
	while(g->env[i])
	{
		test[j] = ft_strdup(g->env[i]);
		i++;
		j++;
	}
	test[j] = NULL;

	i = 0;
	j = 0;
	ft_libre(g->env);
	if(!(g->env = (char **)malloc(sizeof(char *) * (ft_strlen_tab(test)))))
		return ;
	while(env[i])
	{
		if(ft_strncmp(test[i], tab[1], ft_strlen(tab[1])) != 0)
		{
			g->env[j] = ft_strdup(test[i]);
			j++;
		}
		i++;
	}
	g->env[j] = NULL;
	ft_libre(tab);
	ft_libre(test);

}

int ft_env(char *str, char **env, pid_t id, t_glob *g)
{
	int i;
	char **tab;

	tab = ft_strsplit(str, ' ');
	i = 0;
	if(ft_strcmp("env", tab[0]) == 0)
	{
		while(g->env[i] != NULL)
		{
			ft_putendl(g->env[i]);
			i++;
		}
		ft_libre(tab);
		return(1);
	}
	ft_libre(tab);
	return(0);
}

int ft_echo(char *str, char **env, pid_t id, t_glob *g)
{
	int i;
	int j;
	char **tab;
	char *tmp;

	tab = ft_strsplit(str, ' ');
	if(ft_strcmp("echo", tab[0]) == 0)
	{
		i = 5;
		while(str[i])
		{
			if(str[i] == '$')
			{
				i++;
				j = i;
				while(str[j] && str[j] != ' ')
					j++;
				tmp = ft_strsub(str, i, ft_absolut(i - j));
				i = i + ft_strlen(tmp) - 1;
				j = 0;
				while(g->env[j] && ft_strncmp(g->env[j], tmp, ft_strlen(tmp)) != 0)
					j++;
				if(g->env[j] != NULL)
				{
					ft_putstr(g->env[j] + ft_strlen(tmp) + 1);
				}

				free(tmp);


			//	ft_putstr("-->");
			//	ft_putstr(tmp);
				//ft_putstr("\n");

			}
			else if(str[i] == '\\')
			{
				ft_putstr("\n");
			}
			else if(str[i] != '"')
				ft_putchar(str[i]);
			i++;
		}
		if(tab[1])
			ft_putchar('\n');
		ft_libre(tab);
		return (1);
	}
	ft_libre(tab);
	return(0);
}

int ft_cd(char *str, char **env, pid_t id, t_glob *g)
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
				ft_set_env("setenv OLDPWD /", g->env, id, g);
				i = 0;
				while(g->env[i] != NULL && ft_strncmp(g->env[i], "HOME=", 5) != 0)
					i++;
				if(g->env[i] == NULL)
					ft_set_env("setenv HOME /Users/mpinson", g->env, id, g);
				chdir("/Users/mpinson");
				ft_set_env("setenv PWD /Users/mpinson", g->env, id, g);
			}
			else
			{
				free(g->env[i]);
				g->env[i] = ft_strjoin("OLDPWD=", getcwd(test, 4999));
				i = 0;
				while(g->env[i] != NULL && ft_strncmp(g->env[i], "HOME=", 5) != 0)
					i++;
				if(g->env[i] == NULL)
					ft_set_env("setenv HOME /Users/mpinson", g->env, id, g);
				chdir("/Users/mpinson");
				ft_set_env("setenv PWD /Users/mpinson", g->env, id, g);
			}
		}
		else if(ft_strncmp(tab[1], "-", 1) == 0)
		{
			while(g->env[i] != NULL && ft_strncmp(g->env[i], "OLDPWD=", 7) != 0)
				i++;
			if(g->env[i] == NULL)
			{
				ft_set_env("setenv OLDPWD /", g->env, id, g);
				ft_set_env("setenv PWD /", g->env, id, g);
				chdir("/");
			}
			else
			{
				free(g->env[i]);
				old_pwd = ft_strsub(g->env[i], 7, ft_strlen(g->env[i]));
				g->env[i] = ft_strjoin("OLDPWD=", getcwd(test, 4999));
				chdir(old_pwd);
				tmp = ft_strjoin("setenv PWD ", old_pwd);
				ft_set_env(tmp, g->env, id, g);
				free(tmp);
			}
		}
		else
		{
			while(g->env[i] != NULL && ft_strncmp(g->env[i], "OLDPWD=", 7) != 0)
				i++;
			if(g->env[i] == NULL)
			{
				ft_set_env("setenv OLDPWD /", g->env, id, g);
				chdir(tab[1]);
				tmp = ft_strjoin("setenv PWD ", getcwd(test, 4999));
				ft_set_env(tmp, g->env, id, g);
				free(tmp);
			}
			else
			{
				free(g->env[i]);
				g->env[i] = ft_strjoin("OLDPWD=", getcwd(test, 4999));
				chdir(tab[1]);
				tmp = ft_strjoin("setenv PWD ", getcwd(test, 4999));
				ft_set_env(tmp, g->env, id, g);
				free(tmp);
			}
		}
		ft_libre(tab);
		return(1);
	}
	return (0);
}

int ft_no(char *str, char **env, pid_t id, t_glob *g)
{
	int i;
	char **tab;
	char *old_pwd;
	char test[42];

	i = 0;
	if(ft_env(str, env, id, g) == 1)
	{
		return(1);
	}
	if(ft_echo(str, env, id, g) == 1)
		return(1);
	if(ft_cd(str, env, id, g) == 1)
		return(1);
	if(ft_strncmp("setenv", str, 5) == 0)
	{

		ft_set_env(str, g->env, id, g);

		i = 0;
		return(1);
	}
	if(ft_strncmp("unsetenv", str, 7) == 0)
	{
		ft_unset_env(str, g->env, id, g);
		i = 0;
		return(1);
	}

	return(0);
}

void setup_env(char **env, t_glob *g)
{
	int i;
	char **tmp;
	int j;

	i = 0;
	j = 0;
	if(!(g->env = (char **)malloc(sizeof(char *) * (ft_strlen_tab(env) + 1))))
		return ;
	while(env[i])
	{
		g->env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	g->env[j] = NULL;
}

int ft_check(t_glob *g, char *str)
{
	char **tab;
	char **commande;
	DIR *rep;
	struct dirent	*fichierlu[5000];
	int i;
	int j;

	i = 0;
	while(g->env[i] && ft_strncmp(g->env[i], "PATH=", 5) != 0)
		i++;
	if(g->env[i] == NULL)
		return(1);
	tab = ft_strsplit(g->env[i] + 5, ':');
	commande = ft_strsplit(str, ' ');
	i = -1;
	while(tab[++i])
	{
		//ft_putendl(tab[i]);
		if (!(rep = opendir(tab[i])))
			continue ;
		j = 0;
		while ((fichierlu[j] = readdir(rep)) != NULL)
		{
			if(ft_strcmp(fichierlu[j]->d_name, commande[0]) == 0)
			{
				ft_libre(tab);
				ft_libre(commande);
				closedir(rep);
				return (0);
			}
			j++;
		}
		closedir(rep);
	}
	ft_libre(tab);
	ft_libre(commande);
	if(strncmp(str, "./", 2) == 0 && isex(str) == 1)
	{
		//ft_putstr()
		commande = ft_strsplit(str + 2, ' ');
		if (!(rep = opendir("./")))
			return(1);
		j = 0;
		while ((fichierlu[j] = readdir(rep)) != NULL)
		{
			if(ft_strcmp(fichierlu[j]->d_name, commande[0]) == 0)
			{
				//ft_libre(tab);
				ft_libre(commande);
				closedir(rep);
				return (0);
			}
			j++;
		}
		closedir(rep);
	}
	return(1);
}

int ft_isdir(char *str)
{
	DIR *rep;

	if(!(rep = opendir(str)))
		return(0);
	closedir(rep);
	return(1);
}

void ft_pronpt()
{
	int i;
	char test[1000];
	char c;

	getcwd(test, 4999);
	i = ft_strlen(test);
	while(i > 0 && test[i] != '/')
		i--;
	write(1, "\e[1;32m", 8);
	ft_putchar(0xe2);
	ft_putchar(0x9e);
	ft_putchar(0x9c);
	ft_putstr("  ");
	write(1, "\e[1;36m", 8);
	ft_putstr(test + i + 1);
	write(1, "\e[0;m", 6);
	ft_putchar(0xf0);
	ft_putchar(0x9f);
	ft_putchar(0xa6);
	ft_putchar(0x84);
	ft_putstr("  > ");
}

int main(int argc, char **argv, char **env)
{
	char str[5000];
	pid_t id;
	int i;
	int j;
	t_glob g;
	char *tmp;
	char **tab;


	setup_env(env, &g);
//	free(env[0]);
	while(1)
	{
		
		ft_bzero(str, 5000);
		ft_pronpt();
		read(0, &str, 5000);
		i = 0;
		while(str[i])
		{
			if(str[i] == '\n')
				str[i] = 0;
			i++;
		}
		tab = ft_strsplit(str, ';');
		j =-1;
		while(tab[++j])
		{
			i = 0;
			while(tab[j][i] == ' ')
				i++;
			if(i)
			{
				tmp = ft_strsub(tab[j], i, ft_strlen(tab[j]));
				free(tab[j]);
				tab[j] = tmp;
			}
			i = 0;
			while(tab[j][i] != 0)
			{
				if(tab[j][i] == '\t')
				{
					ft_putendl("warning tab");
					return (0);
				}
				i++;
			}
			if((tab[j][0] == '/' || ft_strncmp(tab[j], "./", 2) == 0) && ft_isdir(tab[j]))
			{
				tmp = ft_strjoin("cd ", tab[j]);
				ft_cd(tmp, env, id, &g);
				free(tmp);
				continue;
			}
			if(ft_no(tab[j], env, id, &g) == 1)
				continue ;
			//ft_putnbr(str[ft_strlen(str)]);
			// /printf("%d\n", str[5]);
			if(ft_strncmp(tab[j], "exit", 4) == 0)
				return(0);
	
			if(ft_check(&g, tab[j]) == 1)
			{
				ft_putendl("error : commande not fond");
				continue ;
			}


			id = fork();
			if(ft_strncmp("echo", tab[j], 4) && ft_strncmp("cd", tab[j], 2))
				ft_dev(tab[j], id, &g);
			if(id > 0)
				wait(&id);
		}
		ft_libre(tab);
	}
}