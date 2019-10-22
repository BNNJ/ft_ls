#include "ft_ls.h"

int	cmp_time(const void *a, const void *b)
{
	t_file	f1;
	t_file	f2;

	f1 = *(t_file*)a;
	f2 = *(t_file*)b;
	if (f1.sec == f2.sec)
	{
		if (f1.nsec == f2.nsec)
			return (ft_strcmp(f1.name, f2.name));
		return (f2.nsec - f1.nsec);
	}
	return (f1.sec > f2.sec ? -1 : 1);
}

int	cmp_time_rev(const void *a, const void *b)
{
	return (cmp_time(b, a));
}

int	cmp_name(const void *a, const void *b)
{
	t_file	f1;
	t_file	f2;

	f1 = *(t_file*)a;
	f2 = *(t_file*)b;
	return (ft_strcmp(f1.name, f2.name));
}

int	cmp_name_rev(const void *a, const void *b)
{
	return (cmp_name(b, a));
}
