#include "mini.h"

void ft_dev4(char *str, pid_t id)
{
	char **tab;
	int i;

	if(id == 0 && ft_strncmp(str, "cp", 2) == 0)
	{
		tab = ft_strsplit(str, ' ');
		while(tab[++i] != NULL)
			tab[i][ft_strlen(tab[i]) - 1] = 0;
		execve("/bin/cp", tab, NULL);
		ft_libre(tab);
	}
	if(id == 0 && ft_strncmp(str, "csh", 3) == 0)
	{
		tab = ft_strsplit(str, ' ');
		while(tab[++i] != NULL)
			tab[i][ft_strlen(tab[i]) - 1] = 0;
		execve("/bin/csh", tab, NULL);
		ft_libre(tab);
	}
	// /ft_dev4(str, id)
}

void ft_dev3(char *str, pid_t id)
{
	char **tab;
	int i;

	if(id == 0 && ft_strncmp(str, "chmod", 5) == 0)
	{
		tab = ft_strsplit(str, ' ');
		while(tab[++i] != NULL)
			tab[i][ft_strlen(tab[i]) - 1] = 0;
		execve("/bin/chmod", tab, NULL);
		ft_libre(tab);
	}
	if(id == 0 && ft_strncmp(str, "cat", 3) == 0)
	{
		tab = ft_strsplit(str, ' ');
		while(tab[++i] != NULL)
			tab[i][ft_strlen(tab[i]) - 1] = 0;
		execve("/bin/cat", tab, NULL);
		ft_libre(tab);
	}
	ft_dev4(str, id);
}

void ft_dev2(char *str, pid_t id)
{
	char **tab;
	int i;

	if(id == 0 && ft_strncmp(str, "[", 1) == 0)
	{
		tab = ft_strsplit(str, ' ');
		while(tab[++i] != NULL)
			tab[i][ft_strlen(tab[i]) - 1] = 0;
		execve("/bin/[", tab, NULL);
		ft_libre(tab);
	}
	if(id == 0 && ft_strncmp(str, "bash", 4) == 0)
	{
		tab = ft_strsplit(str, ' ');
		while(tab[++i] != NULL)
			tab[i][ft_strlen(tab[i]) - 1] = 0;
		execve("/bin/bash", tab, NULL);
		ft_libre(tab);
	}
	ft_dev3(str, id);
}



void ft_dev(char *str, pid_t id)
{
	char **tab;
	int i;
	char str2[42];
	char *str3;

	i = 0;
	if(id == 0)
	{
		tab = ft_strsplit(str, ' ');
		while(tab[++i] != NULL)
			tab[i][ft_strlen(tab[i]) - 1] = 0;

		str2[0] = '/';
		str2[1] = 'b';
		str2[2] = 'i';
		str2[3] = 'n';
		str2[4] = '/';
		int b = 5;
		i = 0;
		while (ft_isalnum(str[i]))
		{
			str2[b] = str[i];
			i++;
			b++;
		}
		str2[b] = '\0';
		//ft_putstr(str2);
		execve(str2, tab, NULL);
		//ft_libre(tab);
	}
/*	if(id == 0 && ft_strncmp(str, "pwd", 3) == 0)
	{
		tab = ft_strsplit(str, ' ');
		while(tab[++i] != NULL)
			tab[i][ft_strlen(tab[i]) - 1] = 0;
		execve("/bin/pwd", tab, NULL);
		ft_libre(tab);
	}*/
	//ft_dev2(str, id);
}