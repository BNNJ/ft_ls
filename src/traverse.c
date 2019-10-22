#include "ft_ls.h"
#include "qsort.h"

int		read_file_stat(t_file *file, const char *path, const char *f)
{
	t_stat	st;
	size_t	path_len;
	size_t	file_len;

	path_len = ft_strlen(path);
	file_len = ft_strlen(f);
	ft_memcpy(file->fullname, path, path_len);
	if (path[path_len - 1] != '/')
		file->fullname[path_len++] = '/';
	ft_memcpy(file->fullname + path_len, f, file_len + 1);
	ft_memcpy(file->name, f, file_len + 1);
	if (lstat(file->fullname, &st) < 0)
	{
		ft_dprintf(2, "ft_ls: %s: %s\n", f, strerror(errno));
		return (-1);
	}
	file->mode = st.st_mode;
	file->uid = st.st_uid;
	file->gid = st.st_gid;
	file->sec = st.st_mtimespec.tv_sec;
	file->nsec = st.st_mtimespec.tv_nsec;
	return (0);
}

int		single_file(t_ls *ls, char const *path)
{
	t_stat	st;

	(void)ls;
	if (lstat(path, &st) == -1)
	{
		ft_dprintf(2, "ft_ls: %s: %s\n", path, strerror(errno));
		return (0);
	}
	ft_printf("%s\n", path);
	return (0);
}

int		single_dir(t_ls *ls, char const *path)
{
	DIR				*dirp;
	struct dirent	*entry;
	t_file			*dir;
	size_t			i;

	errno = 0;
	if (!(dirp = opendir(path)))
		return (single_file(ls, path));
	if (!(dir = new_dir()))
		return (-1);
	i = 0;
	while ((entry = readdir(dirp)))
	{
		if (!(dir = new_file(dir))
			|| read_file_stat(dir + i, path, entry->d_name))
			return (-1);
		++i;
	}
	ft_qsort(dir, i, sizeof(t_file), ls->cmp);
	display_dir(dir, i);
	delete_dir(dir);
	closedir(dirp);
	return (0);
}

void	swap_tfile(t_file *a, t_file *b)
{
	t_file	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_file	*sort_args(t_ls *ls, char const **dirtab, int *len)
{
	t_file	*paths;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(paths = malloc(sizeof(t_file) * *len)))
		return (NULL);
	while (i < *len)
	{
		if (read_file_stat(&paths[i], ".", dirtab[j]) < 0)
		{
			swap_tfile(&paths[i], &paths[(*len) - 1]);
			ft_printf(">> removing something\n");
			--(*len);
		}
		else
			++i;
		++j;
	}
	i = 0;
	j = (*len) - 1;
	while (i < j)
	{
		while (S_ISREG(paths[i].mode))
			++i;
		while (S_ISDIR(paths[j].mode))
			--j;
		if (i < j)
			swap_tfile(&paths[i], &paths[j]);
	}
	ft_printf(">>> %d, %d, %d\n", i, j, *len);
	ft_qsort(paths, i, sizeof(t_file), ls->cmp);
	ft_qsort(paths + i, *len, sizeof(t_file), ls->cmp);
	for (int k = 0; k < *len; ++k)
		ft_printf("%s\n", paths[k].name);
	return (paths);
}

int		traverse(t_ls *ls, char const **dirtab, int len)
{
	int		i;
	t_file	*files;

	i = 0;
	if (!(files = sort_args(ls, dirtab, &len)))
		return (-1);
	ft_printf("####################################\n");
	while (S_ISREG(files[i].mode))
	{
		ft_printf("%s%c", files[i].name, 
			"\n "[i < len - 1 && S_ISREG(files[i + 1].mode)]);
		++i;
	}
	if (i != 0)
		ft_printf("\n");
	while (i < len)
	{
		ft_printf("%s:\n", dirtab[i]);
		if (single_dir(ls, dirtab[i]) == -1)
			return (-1);
		if (i < len - 1)
			ft_printf("\n");
		++i;
	}
	return (0);
}
