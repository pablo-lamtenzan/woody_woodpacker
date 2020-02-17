
#include "woody_woodpacker.h"

typedef static struct   s_adrr
{
    void                *adrr;
    size_t              size;
}                       t_adrr = {NULL, 0};

__warn_unused_result
size_t              read_file(const char *name)
{
    void            *addr;
    struct stat     buff;
    int             fd;

    if ((fd = open(name, O_RDONLY)) < 0)
        return (0); // SYS ERROR
    if (fstat(fd, &buff) < 0)
        return (0); // SYS ERROR
    if (buff.st_mode & S_IFDIR)
        return (0); // SYS ERROR can t parse directories
    if ((addr = mmap(0, buff.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_MAILED)
        return (0); // SYS ERROR
    if (close(fd))
        return (0); // SYS ERROR 

    t_adrr.adrr = addr;
    t_adrr.size = buff.st_size;
    return (buff.st_size);
}

__warn_unused_result
char                free_adrr(void)
{
    if (adrr)
        if (munmap(t_adrr.addr, t_adrr.size))
            return (0); // SYS ERROR
    return (1);
}

// get the original adrr of the file if posible
__warn_unused_result
void                *get_origin_adrr(const size_t offset, const size_t size)
{
    if (size < 0 || offset + size > t_adrr.size)
        return (NULL);
    return (t_adrr.adrr + offset);
}