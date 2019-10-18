#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"

# define F_HELP			0x01
# define F_LONG			0x02
# define F_RECURSIVE	0x04
# define F_ALL			0x08
# define F_REVERSE		0x10
# define F_TIME			0x20

# define POOL_INC		32;

# define OPTSTR	"hlRart"
# define OPTTAB	{"help", "long", "recursive", "all", "reverse", "time", NULL}

# define VARNAME(x)	(#x)

typedef struct stat	t_stat;

typedef struct		s_file
{
	char			name[256];
	char			fullname[512];
	mode_t			mode;
	uid_t			uid;
	gid_t			gid;
	time_t			time;
	time_t			ntime;
}					t_file;

typedef struct		s_ls
{
	int				opt;
	int 			(*cmp)(const void *a, const void *b);
}					t_ls;

/*
** sorting
*/

int					cmp_time(const void *a, const void *b);
int					cmp_time_rev(const void *a, const void *b);
int					cmp_name(const void *a, const void *b);
int					cmp_name_rev(const void *a, const void *b);

/*
** traversal
*/

int					traverse(t_ls *ls, char const **dirtab, int len);
int					single_dir(t_ls *ls, char const *dir);

/*
** display
*/

void				display_dir(t_file *dir, size_t size);

/*
** t_file pool handling
*/

t_file				*new_file(t_file *dir);
t_file				*new_dir(void);
void				free_files(void);
void				delete_dir(t_file *dir);

#endif
