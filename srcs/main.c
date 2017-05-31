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

int ft_strlen_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
		i++;
	return(i);
}

int ft_no(char *str, t_glob *g)
{
	if(ft_env(str, g) == 1)
		return(1);
	if(ft_echo(str, g) == 1)
		return(1);
	if(ft_cd(str, g) == 1)
		return(1);
	if(ft_strncmp("setenv", str, 5) == 0)
	{
		ft_set_env(str, g);
		return(1);
	}
	if(ft_strncmp("unsetenv", str, 7) == 0)
	{
		ft_unset_env(str, g);
		return(1);
	}

	return(0);
}

void setup_env(char **env, t_glob *g)
{
	int i;
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

	(void)argc;
	(void)argv;
	setup_env(env, &g);
	while(1)
	{
		ft_bzero(str, 5000);
		ft_pronpt();
		read(0, &str, 5000);
		i = -1;
		while(str[++i])
		{
			if(str[i] == '\n')
				str[i] = 0;
		}
		tab = ft_strsplit(str, ';');
		j = -1;
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
			i = -1;
			while(tab[j][++i] != 0)
			{
				if(tab[j][i] == '\t')
				{
					ft_putendl("warning tab");
					return (0);
				}
			}
			if((tab[j][0] == '/' || ft_strncmp(tab[j], "./", 2) == 0) && ft_isdir(tab[j]))
			{
				tmp = ft_strjoin("cd ", tab[j]);
				ft_cd(tmp, &g);
				free(tmp);
				continue;
			}
			if(ft_no(tab[j], &g) == 1)
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