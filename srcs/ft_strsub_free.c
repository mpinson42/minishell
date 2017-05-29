#include "mini.h"

void ft_strsub_free(char const *s, unsigned int start, size_t len, t_glob *g)
{
	unsigned int	i;
	char			*str;

	if (!s)
		return ;
	i = 0;
	if (!(g->tmp = (char *)malloc(sizeof(const char) * len + 1)))
		return ;
	while (i < len)
	{
		g->tmp[i] = s[start];
		start++;
		i++;
	}
	g->tmp[i] = '\0';
}