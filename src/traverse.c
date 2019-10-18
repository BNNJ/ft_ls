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
	if (lstat(file->fullname, &st) == -1)
	{
		ft_dprintf(2, "ft_ls: %s: %s\n", f, strerror(errno));
		return (-1);
	}
	file->mode = st.st_mode;
	file->uid = st.st_uid;
	file->gid = st.st_gid;
	file->time = st.st_mtime;
	file->ntime = st.st_mtim.tv_nsec;
	return (0);
}

int		traverse(t_ls *ls, char const **dirtab, int len)
{
	(void)ls;
	for (int i = 0; i < len; ++i)
		ft_printf(">> %s\n", dirtab[i]);
	return (0);
}

int		single_dir(t_ls *ls, char const *path)
{
	DIR				*dirp;
	struct dirent	*entry;
	t_file			*dir;
	size_t			i;

	(void)ls;
	errno = 0;
	if (!(dirp = opendir(path)))
		return (-1);
	if (!(dir = new_dir()))
		return (-1);
	i = 0;
	while ((entry = readdir(dirp)))
	{
//		ft_printf("ft_ls: %llu %s\n", i, entry->d_name);
		if (!(dir = new_file(dir)) || read_file_stat(dir + i, path, entry->d_name))
			return (-1);
		++i;
	}
	ft_qsort(dir, i, sizeof(t_file), ls->cmp);
	display_dir(dir, i);
	delete_dir(dir);
	closedir(dirp);
	return (0);
}
