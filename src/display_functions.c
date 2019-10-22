#include "ft_ls.h"

void	display_dir(t_file *dir, size_t size)
{
	size_t	i;

	i = 0;
//	ft_printf("size: %llu\n", size);
	while (i < size)
	{
		ft_printf("%s\n", dir[i].name);
		++i;
	}
}
