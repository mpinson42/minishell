#include "mini.h"

void ft_cd_tild(char ***tab)
{
	char *tmp;

	tab[0][1]++;
	tmp = ft_strjoin("/Users/mpinson/", tab[0][1]);
	free(tab[0][1] - 1);
	tab[0][1] = tmp;
}