#include "mini.h"

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

int main(int argc, char **argv, char **env)
{
	char str[100];
	pid_t id;

	while(1)
	{
		if(id > 0 || ft_strncmp(str, "exit", 4) == 0)
			wait(&id);
		ft_bzero(str, 100);
		ft_putstr("$>");
		read(0, &str, 99);
		id = fork();
		
		ft_dev(str, id);

		


		if(ft_strncmp(str, "exit", 4) == 0)
			return(0);
	}
}