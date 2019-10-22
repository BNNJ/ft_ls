#include "ft_ls.h"

int	get_args(int const argc, char const **argv, char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			args[j] = (char*)argv[i];
			++j;
		}
		++i;
	}
	args[j] = NULL;
	return (j);
}

void	ls_init(t_ls *ls)
{
	if (ls->opt & F_TIME)
		ls->cmp = ls->opt & F_REVERSE ? cmp_time_rev : cmp_time;
	else
		ls->cmp = ls->opt & F_REVERSE ? cmp_name_rev : cmp_name;
}

int		usage()
{
	ft_printf("Usage:	ft_ls [option]... [file]...\n"
		"List informations about files and directories, "
		"sorted alphabetically by default.\n"
		"If no file or directory is specified, the current directory "
		"is used by default\n"
		"  -h, --help	\tDisplay usage/help\n"
		"  -l, --long	\tDisplay information in a long format\n"
		"  -R, --recursive\tSubdirectories are traversed recursively\n"
		"  -a, --all	\tDisplay entries starting with a '.'\n"
		"  -r, --reverse	\tEntries are sorted in reverse order\n"
		"  -t, --time	\tEntries are sorted by modification time\n");
	return (EXIT_SUCCESS);
} 

int		main(int argc, char const **argv)
{
	t_ls	ls;
	int		status;

	if ((ls.opt = ft_getopt(argv, OPTSTR, (char const *[])OPTTAB)) < 0)
	{
		ft_dprintf(2, "ft_ls: invalid option: %s\n", g_opterr);
		return (EXIT_FAILURE);
	}
	if (ls.opt & F_HELP)
		return (usage());
	ls_init(&ls);
	argc -= g_optind;
	argv += g_optind;
//	if (argc > 1 || ls.opt & F_RECURSIVE)
		status = argc ? traverse(&ls, argv, argc)
					: traverse(&ls, (char const *[]){"."}, 1);
//	else
//		status = single_dir(&ls, argc ? argv[0] : (char const *)".");
	if (status != 0)
		ft_dprintf(2, "ft_ls: %s\n", strerror(errno));
	return (EXIT_SUCCESS);
}
