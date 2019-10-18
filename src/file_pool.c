#include "ft_ls.h"

/*
** Maintains an array of t_file that the program can pick from.
** Returns a pointer to the next unused t_file in the array,
** if none are left (size >= capacity), POOL_INC more are allocated.
*/

static t_file	*g_pool = NULL;
static size_t	g_index = 0;
static size_t	g_capacity = POOL_INC;

t_file	*new_file(t_file *dir)
{
	t_file	*tmp;
	size_t	dir_offset;
	size_t	i;

	dir_offset = (size_t)(dir - g_pool);
	if (g_index >= g_capacity)
	{
		g_capacity += POOL_INC;
		if (!(tmp = malloc(sizeof(t_file) * g_capacity)))
			return (NULL);
		i = 0;
		while (i < g_index - 1)
		{
			tmp[i] = g_pool[i];
			++i;
		}
		free(g_pool);
		g_pool = tmp;
	}
	++g_index;
	return (g_pool + dir_offset);
}

t_file	*new_dir(void)
{
	ft_printf("capacity: %llu\n", g_capacity);
	if (g_pool == NULL)
		if (!(g_pool = malloc(sizeof(t_file) * g_capacity)))
			return (NULL);
	return (g_pool + g_index);
}

void	delete_dir(t_file *dir)
{
	g_index -= (size_t)(&g_pool[g_index] - dir);
}

void	free_files(void)
{
	free(g_pool);
}
