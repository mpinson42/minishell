/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 18:30:06 by mpinson           #+#    #+#             */
/*   Updated: 2017/05/31 18:30:28 by mpinson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		main2(char (*str)[5000], char ***tab)
{
	int i;

	ft_bzero(str[0], 5000);
	ft_pronpt();
	if (read(0, str, 5000) == -1)
		return (-1);
	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '\n')
			str[0][i] = 0;
	}
	if (!(tab[0] = ft_strsplit(str[0], ';')))
		return (-1);
	return (0);
}

int		main3(t_main *m, t_glob *g)
{
	m->i = 0;
	while (m->tab[m->j][m->i] == ' ')
		m->i++;
	if (m->i)
	{
		if (!(m->tmp = ft_strsub(m->tab[m->j], m->i,
			ft_strlen(m->tab[m->j]))))
			return (-1);
		free(m->tab[m->j]);
		m->tab[m->j] = m->tmp;
	}
	if ((m->tab[m->j][0] == '/' ||
		ft_strncmp(m->tab[m->j], "./", 2) == 0) && ft_isdir(m->tab[m->j]))
	{
		m->tmp = ft_strjoin("cd ", m->tab[m->j]);
		ft_cd(m->tmp, g);
		free(m->tmp);
		return (-1);
	}
	return (0);
}

int		main4(t_main *m, t_glob *g)
{
	if (ft_check(g, m->tab[m->j]) == 1)
	{
		ft_putendl("error : commande not fond");
		return (-1);
	}
	m->id = fork();
	if (ft_strncmp("echo", m->tab[m->j], 4) &&
		ft_strncmp("cd", m->tab[m->j], 2))
		ft_dev(m->tab[m->j], m->id, g);
	if (m->id > 0)
		wait(&m->id);
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	t_main m;
	t_glob g;

	(void)argc;
	(void)argv;
	if (setup_env(env, &g) == -1)
		return (-1);
	while (1)
	{
		if (main2(&m.str, &m.tab) == -1)
			continue ;
		m.j = -1;
		while (m.tab[++m.j])
		{
			if (main3(&m, &g) == -1)
				continue;
			if (ft_no(m.tab[m.j], &g) == 1)
				continue ;
			if (ft_strncmp(m.tab[m.j], "exit", 4) == 0)
				return (0);
			if (main4(&m, &g) == -1)
				continue ;
		}
		ft_libre(m.tab);
	}
}
