#include "mini.h"

int		ft_test(char *str)
{
	int				i;
	struct dirent	*fichierlu[2];
	DIR				*rep;

	i = 0;
	rep = NULL;
	if (str == NULL || !(rep = opendir(str)))
		return (0);
	while ((fichierlu[0] = readdir(rep)) != NULL)
		i++;
	closedir(rep);
	return (i);
}

int is_in(char *path, char *commande)
{
	DIR *rep;
	struct dirent	*fichierlu[ft_test(path) + 1];
	int i;

	i = 0;
	if (!(rep = opendir(path)))
		return (-1);
	while ((fichierlu[i] = readdir(rep)) != NULL)
	{
		if(ft_strncmp(fichierlu[i]->d_name, commande, ft_strlen(fichierlu[i]->d_name)) == 0)
		{
			closedir(rep);
			return (1);
		}
		i++;
	}
	closedir(rep);
	return(0);
}

int ft_dev1(char *str)
{
	int i;
	int b;
	char **tab;
	char str2[5000];
	char test[5000];

	if(is_in(getcwd(test, 4999), str + 2))
	{
		tab = ft_strsplit(str, ' ');
		ft_strcpy(str2, "./");
		b = 2;
		i = 0;
		while (str[i])
		{
			str2[b] = str[i];
			i++;
			b++;
		}
		str2[b] = '\0';
		execve(str2, tab, NULL);
		return (-1);
	}
	return(0);
}

int ft_dev2(char *str, int j, char **tab2)
{
	char **tab;
	int i;
	int b;
	char str2[5000];

	if(is_in(tab2[j], str))
	{
		tab2[j] = ft_strjoin(tab2[j], "/");
		tab = ft_strsplit(str, ' ');
		ft_strcpy(str2, tab2[j]);
		b = ft_strlen(tab2[j]);
		i = 0;
		while (ft_isalnum(str[i]))
		{
			str2[b] = str[i];
			i++;
			b++;
		}
		str2[b] = '\0';
		execve(str2, tab, NULL);
		return (-1);
	}
	return (0);
}

void ft_dev(char *str, pid_t id, t_glob *g)
{
	char **tab2;
	int i;

	i = 0;
	if(id == 0)
	{
		if(ft_dev1(str) == -1)
			return ;
		while(g->env[i] && ft_strncmp(g->env[i], "PATH=", 5) != 0)
			i++;
		tab2 = ft_strsplit(g->env[i] + 5, ':');

		i = -1;
		while(tab2[++i])
		{
			if(ft_dev2(str, i, tab2) == -1)
				return ;
		}
	}
}














