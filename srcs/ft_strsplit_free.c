#include <stdlib.h>
#include "libft.h"



static int		ft_cnt_parts(const char *s, char c)
{
	int		cnt;
	int		in_substring;

	in_substring = 0;
	cnt = 0;
	while (*s != '\0')
	{
		if(in_substring == 0 && *s == '"')
		{
			s++;
			while(*s == ' ')
				s++;
			c = '"';
		}
		if(in_substring == 0 && *s == ' ')
			c = ' ';
		if (in_substring == 1 && *s == c)
			in_substring = 0;
		if (in_substring == 0 && *s != c)
		{
			in_substring = 1;
			cnt++;
		}
		s++;
	}
	return (cnt);
}



static int		ft_wlen(char *s, char c)
{
	int		len;
	char *tmp = s;
	len = 0;
	while(*tmp == ' ')
		tmp++;
	
	if(*tmp == '"')
	{
		s = tmp + 1;
		while ((*s != '"' ) && *s != '\0')
		{
			len++;
			s++;
		}
		len += 1;
	}
	else
	{
		while ((*s != ' ' ) && *s != '\0')
		{
			len++;
			s++;
		}
	}
	return (len);
}

char			**ft_strsplit2(char*s, char c)
{
	char	**t;
	int		nb_word;
	int		index;

	if (!s)
		return (NULL);
	index = 0;
	nb_word = ft_cnt_parts((const char *)s, c);
	t = (char **)malloc(sizeof(*t) * (ft_cnt_parts((const char *)s, c)));
	if (t == NULL)
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		t[index] = ft_strsub((const char *)s, 0, ft_wlen(s, c) + 1);
		if (t[index] == NULL)
			return (NULL);
		if(t[index][0] == '"')
		{
			t[index]++;
			t[index][ft_strlen(t[index]) - 1] = 0;
		}
		s = s + ft_wlen(s, c) + 1;
		index++;
	}
	t[index] = NULL;
	return (t);
}

/*
int main()
{
	int i = 0;
	char **tab = ft_strsplit2("    coucou les gens \"   sa va ?   \"\" lol je suis magique     \"  ", ' ');
	while(tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
}*/
