#include "mini.h"

int		ft_no(char *str, t_glob *g)
{
	if (ft_env(str, g) == 1)
		return (1);
	if (ft_echo(str, g) == 1)
		return (1);
	if (ft_cd(str, g) == 1)
		return (1);
	if (ft_strncmp("setenv", str, 5) == 0)
	{
		ft_set_env(str, g);
		return (1);
	}
	if (ft_strncmp("unsetenv", str, 7) == 0)
	{
		ft_unset_env(str, g);
		return (1);
	}
	return (0);
}

void	setup_env(char **env, t_glob *g)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(g->env = (char **)malloc(sizeof(char *) * (ft_strlen_tab(env) + 1))))
		return ;
	while (env[i])
	{
		g->env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	g->env[j] = NULL;
}