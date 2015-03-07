#include <stdio.h>
#include <strings.h>
#include <sys/select.h>

int fd_next(int start, const struct fd_set *set)
{
    const int loc = start / __DARWIN_NFDBITS;
    const int len = sizeof(set->fds_bits) / sizeof(set->fds_bits[0]);
    for (int index = loc; index < len; index++)
    {
        int elem = set->fds_bits[index];
        if (index == loc)
            elem &= ~((1 << start % __DARWIN_NFDBITS) - 1);
        if (elem)
            return index * __DARWIN_NFDBITS + ffs(elem) - 1;
    }
    return -1;
}

int main()
{
    // test & sample
    int fd;
	fd_set	set;
    FD_ZERO(&set);
	while (scanf("%d", &fd) > 0)
		FD_SET(fd, &set);
	printf("\necho:");
    fd = -1;
    while ((fd = fd_next(fd + 1, &set)) >= 0)
        printf(" %d", fd);
    printf("\n");
    return 0;
}