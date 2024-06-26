/*

Copyright (C) 2016, David "Davee" Morgan

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include "psp2-dirent.h"
#include <errno.h>
#include <malloc.h>
#include <string.h>

#include <psp2/types.h>
#include <psp2/io/dirent.h>
#include <psp2/kernel/threadmgr.h>

#define SCE_ERRNO_MASK 0xFF

/*int mkdir(const char *path, mode_t mode)
{
	return sceIoMkdir(path, 0777);
}

int rmdir(const char *path)
{
	return sceIoRmdir(path);
}
*/
struct DIR_
{
	SceUID uid;
	struct dirent dir;
	int refcount;
	char *dirname;
	int index;
};

static inline void grab_dir(DIR *dirp)
{
	__sync_add_and_fetch(&dirp->refcount, 1);
}

static inline void drop_dir(DIR *dirp)
{
	if (__sync_add_and_fetch(&dirp->refcount, 1) == 0)
	{
		free(dirp->dirname);
		free(dirp);
	}
}

static inline void release_drop_dir(DIR *dirp)
{
	if (__sync_add_and_fetch(&dirp->refcount, 2) == 0)
	{
		free(dirp->dirname);
		free(dirp);
	}
}

static inline void atomic_exchange(int *obj, int desired)
{
	__sync_synchronize();
	__sync_lock_test_and_set(obj, desired);
}

#ifdef F_closedir
int	closedir(DIR *dirp)
{
	if (!dirp)
	{
		errno = EBADF;
		return -1;
	}

	grab_dir(dirp);

	int res = sceIoDclose(dirp->uid);

	if (res < 0)
	{
		errno = res & SCE_ERRNO_MASK;
		drop_dir(dirp);
		return -1;
	}

	release_drop_dir(dirp);

	errno = 0;
	return 0;
}
#endif

#if F_opendir
DIR *opendir(const char *dirname)
{
	SceUID uid = sceIoDopen(dirname);

	if (uid < 0)
	{
		errno = uid & SCE_ERRNO_MASK;
		return NULL;
	}

	DIR *dirp = (DIR *)calloc(1, sizeof(DIR));

	if (!dirp)
	{
		sceIoDclose(uid);
		errno = ENOMEM;
		return NULL;
	}

	dirp->refcount = 1;
	dirp->uid = uid;
	dirp->dirname = strdup(dirname);
	dirp->index = 0;

	errno = 0;
	return dirp;
}
#endif

#ifdef F_readdir
struct dirent *readdir(DIR *dirp)
{
	if (!dirp)
	{
		errno = EBADF;
		return NULL;
	}

	grab_dir(dirp);

	int res = sceIoDread(dirp->uid, (SceIoDirent *)&dirp->dir);

	if (res < 0)
	{
		errno = res & SCE_ERRNO_MASK;
		drop_dir(dirp);
		return NULL;
	}

	if (res == 0)
	{
		errno = 0;
		drop_dir(dirp);
		return NULL;
	}

	__sync_add_and_fetch(&dirp->index, 1);

	struct dirent *dir = &dirp->dir;
	if(SCE_S_ISDIR(dirp->dir.d_stat.st_mode))
		dir->d_type = DT_DIR;
	else
		dir->d_type = DT_REG;
	drop_dir(dirp);
	return dir;
}
#endif
#ifdef F_readdir_r
int	readdir_r(DIR *dirp, struct dirent *x, struct dirent **y)
{
	errno = ENOSYS;
	return -1;
}
#endif

#ifdef F_rewinddir
void rewinddir(DIR *dirp)
{
	if (!dirp)
	{
		errno = EBADF;
		return;
	}

	grab_dir(dirp);

	SceUID dirfd = sceIoDopen(dirp->dirname);

	if (dirfd < 0)
	{
		errno = dirfd & SCE_ERRNO_MASK;
		drop_dir(dirp);
		return;
	}

	sceIoDclose(dirp->uid);
	atomic_exchange(&dirp->uid, dirfd);
	atomic_exchange(&dirp->index, 0);

	drop_dir(dirp);
}
#endif

#ifdef F_seekdir
void seekdir(DIR *dirp, long int index)
{
	if (!dirp)
	{
		errno = EBADF;
		return;
	}

	grab_dir(dirp);

	if (index < dirp->index)
		rewinddir(dirp);

	if (index < dirp->index)
	{
		drop_dir(dirp);
		return;
	}

	while (index != dirp->index)
	{
		if (!readdir(dirp))
		{
			errno = ENOENT;
			drop_dir(dirp);
			return;
		}
	}

	drop_dir(dirp);
}
#endif

#ifdef F_telldir
long int telldir(DIR *dirp)
{
	if (!dirp)
	{
		errno = EBADF;
		return -1;
	}

	return dirp->index;
}
#endif
