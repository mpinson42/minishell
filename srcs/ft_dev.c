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
//	while(commande[i] != 0 &&  commande[i] != ' ' && commande[i] != '\n')
//		i++;
//	commande[i] = 0;
//	i = 0;
//	if(ft_strcmp("env", commande) == 0)
//	{
//		ft_putstr("oui");
//		return(0);
//	}
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

void ft_dev2(char *str, pid_t id)
{
	char **tab;
	int i;
	char str2[42];
	char *str3;

	i = 0;
	if(is_in("/usr/bin/", str) && id == 0)
	{
		tab = ft_strsplit(str, ' ');
		ft_strcpy(str2, "/usr/bin/");
		int b = 9;
		i = 0;
		while (ft_isalnum(str[i]))
		{
			str2[b] = str[i];
			i++;
			b++;
		}
		str2[b] = '\0';
		execve(str2, tab, NULL);
		ft_libre(tab);
		return ;
	}
}
/*
void ft_dev(char *str, pid_t id)
{
	//char *tab[4] = {"ls", "-a", "-l", NULL};
	char **tab;
	int i;
	char str2[42];
	char *str3;

	i = 0;
	if(is_in("/bin/", str) && id == 0)
	{
		tab = ft_strsplit(str, ' ');
		ft_strcpy(str2, "/bin/");
		int b = 5;
		i = 0;
		while (ft_isalnum(str[i]))
		{
			str2[b] = str[i];
			i++;
			b++;
		}
		str2[b] = '\0';
		//ft_putstr(tab[1]);
		execve(str2, tab, NULL);
		ft_libre(tab);
	}
	ft_dev2(str, id);
}*/


void ft_dev(char *str, pid_t id, t_glob *g)
{
	//char *tab[4] = {"ls", "-a", "-l", NULL};
	char **tab;
	char **tab2;
	int i;
	int j;
	char str2[42];
	char *str3;

	i = 0;



	if(id == 0)
	{
		while(g->env[i] && ft_strncmp(g->env[i], "PATH=", 5) != 0)
			i++;
		tab2 = ft_strsplit(g->env[i] + 5, ':');

		j = 0;
		while(tab2[j])
		{
			if(is_in(tab2[j], str))
			{
				tab2[j] = ft_strjoin(tab2[j], "/");
				tab = ft_strsplit(str, ' ');
				ft_strcpy(str2, tab2[j]);
				int b = ft_strlen(tab2[j]);
				i = 0;
				while (ft_isalnum(str[i]))
				{
					str2[b] = str[i];
					i++;
					b++;
				}
				str2[b] = '\0';
				ft_putstr(str2);
				execve(str2, tab, NULL);
				return ;
			}
			j++;
		}
		ft_libre(tab);
	}
}














