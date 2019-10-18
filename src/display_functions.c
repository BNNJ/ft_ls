#include "ft_ls.h"

void	display_dir(t_file *dir, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%- 40s%s", dir[i].name, ctime(&dir[i].time));
		++i;
	}
}
