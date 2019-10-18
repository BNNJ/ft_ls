#include "ft_ls.h"

int	cmp_time(const void *a, const void *b)
{
	t_file	f1;
	t_file	f2;

	f1 = *(t_file*)a;
	f2 = *(t_file*)b;
	if (f1.time == f2.time)
	{
		if (f1.ntime == f2.ntime)
			return (ft_strcmp(f1.name, f2.name));
		return (f2.ntime - f1.ntime);
	}
	return (f1.time > f2.time ? -1 : 1);
}

int	cmp_time_rev(const void *a, const void *b)
{
	t_file	f1;
	t_file	f2;

	f1 = *(t_file*)a;
	f2 = *(t_file*)b;
	if (f1.time == f2.time)
	{
		if (f1.ntime == f2.ntime)
			return (ft_strcmp(f1.name, f2.name));
		return (f1.ntime - f2.ntime);
	}
	return (f1.time < f2.time ? -1 : 1);
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
	t_file	f1;
	t_file	f2;

	f1 = *(t_file*)a;
	f2 = *(t_file*)b;
	return (-ft_strcmp(f1.name, f2.name));
}

/*
int	cmp_time(t_file *a, t_file *b)
{
	if (a->time == b->time)
		return (0);
	return (a->time > b->time ? -1 : 1);
}

int	cmp_time_rev(t_file *a, t_file *b)
{
	if (a->time == b->time)
		return (0);
	return (b->time > a->time ? -1 : 1);
}

int	cmp_name(t_file *a, t_file *b)
{
	return (ft_strcmp(a->name, b->name));
}

int	cmp_name_rev(t_file *a, t_file *b)
{
	return (-ft_strcmp(a->name, b->name));
}
*/