#include "libft.h"

int main(int argc, char **argv)
{
	int i;

	i = 1;
	while(argv[i])
	{
		ft_putendl(argv[i]);
		i++;
	}
	return(0);
}