#include "mini.h"

int ft_strlen_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
		i++;
	return(i);
}

char **ft_set_env(char *str, char **env, pid_t id, t_glob *g)
{
	char **tmp;
	char **tab;
	char *var;
	int i = 0;
	int j = 0;


	tab = ft_strsplit(str, ' ');
	var = ft_strjoin(ft_strjoin(tab[1], "="), tab[2]);
	
	i = 0;
	j = 0;
	if(!(g->env = (char **)malloc(sizeof(char *) * (ft_strlen_tab(env) + 1))))
		return (NULL);
	while(env[i])
	{
		g->env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	g->env[j] = var;
	g->env[j + 1] = NULL;

	return(tmp);

}


char **ft_unset_env(char *str, char **env, pid_t id, t_glob *g)
{
	char **tmp;
	char **tab;
	char *var;
	int i = 0;
	int j = 0;


	tab = ft_strsplit(str, ' ');
	
	
	i = 0;
	j = 0;
	if(!(g->env = (char **)malloc(sizeof(char *) * (ft_strlen_tab(env)))))
		return (NULL);
	while(env[i])
	{
		if(ft_strncmp(env[i], tab[1], ft_strlen(tab[1])) != 0)
		{
			g->env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	g->env[j] = NULL;

	return(tmp);

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

int ft_env(char *str, char **env, pid_t id, t_glob *g)
{
	int i;

	i = 0;
	if(ft_strncmp("env", str, 3) == 0)
	{
		while(g->env[i] != NULL)
		{
			ft_putendl(g->env[i]);
			i++;
		}
		return(1);
	}
	return(0);
}

int ft_echo(char *str, char **env, pid_t id)
{
	int i;

	if(ft_strncmp("echo", str, 4) == 0)
	{
		i = 5;
		while(str[i])
		{
			if(str[i] != '"')
				ft_putchar(str[i]);
			i++;
		}
		ft_putchar('\n');
		return (1);
	}
	return(0);
}

int ft_cd(char *str, char **env, pid_t id, t_glob *g)
{
	int i;
	char **tab;
	char *old_pwd;
	char test[5000];

	i = 0;
	if(ft_strncmp("cd", str, 2) == 0)
	{
		tab = ft_strsplit(str, ' ');
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
				g->env[i] = ft_strjoin("OLDPWD=", getcwd(test, 4999));
				chdir(tab[1]);
			}
		}
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
		return(1);
	if(ft_echo(str, env, id) == 1)
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

char **setup_env(char **env, t_glob *g)
{
	int i;
	char **tmp;
	int j;

	i = 0;
	j = 0;
	if(!(g->env = (char **)malloc(sizeof(char *) * (ft_strlen_tab(env) + 1))))
		return (NULL);
	while(env[i])
	{
		g->env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	g->env[j] = NULL;

	return(g->env);

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
		ft_putstr("$>");
		read(0, &str, 99);
		str[ft_strlen(str) - 1] = 0;
		if(ft_no(str, env, id, &g) == 1)
			continue ;
		//ft_putnbr(str[ft_strlen(str)]);
		// /printf("%d\n", str[5]);
		if(ft_strncmp(str, "exit", 4) == 0)
			return(0);




		id = fork();
		if(ft_strncmp("echo", str, 4) && ft_strncmp("cd", str, 2))
			ft_dev(str, id);
		if(id > 0)
			wait(&id);
	}
}