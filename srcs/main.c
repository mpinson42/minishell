#include "mini.h"

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
	tmp = ft_strjoin(tab[1], "=");
	var = ft_strjoin(tmp, tab[2]);
	free(tmp);
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
	test[i] = NULL;

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

int ft_echo(char *str, char **env, pid_t id)
{
	int i;
	char **tab;

	tab = ft_strsplit(str, ' ');
	if(ft_strcmp("echo", tab[0]) == 0)
	{
		i = 5;
		while(str[i])
		{
			if(str[i] != '"')
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

	i = 0;
	if(ft_strncmp("cd", str, 2) == 0)
	{
		tab = ft_strsplit(str, ' ');
		if (tab[1] && !(rep = opendir(tab[1])))
		{
			ft_putendl("cd: no such file or directory");
			ft_libre(tab);
			return (1);
		}
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
			}
		}
		else if(ft_strncmp(tab[1], "-", 1) == 0)
		{
			while(g->env[i] != NULL && ft_strncmp(g->env[i], "OLDPWD=", 7) != 0)
				i++;
			if(g->env[i] == NULL)
			{
				ft_set_env("setenv OLDPWD /", g->env, id, g);
				chdir("/");
			}
			else
			{
				free(g->env[i]);
				old_pwd = ft_strsub(g->env[i], 7, ft_strlen(g->env[i]));
				g->env[i] = ft_strjoin("OLDPWD=", getcwd(test, 4999));
				chdir(old_pwd);
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
			}
			else
			{
				free(g->env[i]);
				g->env[i] = ft_strjoin("OLDPWD=", getcwd(test, 4999));
				chdir(tab[1]);
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
	if(ft_echo(str, env, id) == 1)
		return(1);
	if(ft_cd(str, env, id, g) == 1)
		return(1);
	if(ft_strncmp("setenv", str, 5) == 0)
	{
		tab = g->env;
		ft_set_env(str, g->env, id, g);
		ft_libre2(&tab);
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
	return(1);
}

int main(int argc, char **argv, char **env)
{
	char str[100];
	pid_t id;
	int i;
	t_glob g;
	setup_env(env, &g);
//	free(env[0]);
	while(1)
	{
		
		ft_bzero(str, 100);
		ft_putstr("$@MPINSON>");
		read(0, &str, 99);
		str[ft_strlen(str) - 1] = 0;
		if(ft_no(str, env, id, &g) == 1)
			continue ;
		//ft_putnbr(str[ft_strlen(str)]);
		// /printf("%d\n", str[5]);
		if(ft_strncmp(str, "exit", 4) == 0)
			return(0);

		if(ft_check(&g, str) == 1)
		{
			ft_putendl("error : commande not fond");
			continue ;
		}


		id = fork();
		if(ft_strncmp("echo", str, 4) && ft_strncmp("cd", str, 2))
			ft_dev(str, id, &g);
		if(id > 0)
			wait(&id);
	}
}