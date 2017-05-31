#include "mini.h"

int ft_env(char *str, t_glob *g)
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