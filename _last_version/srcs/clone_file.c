#include <woody_woodpacker.h>

typedef static struct   s_adrr
{
    void                *adrr;
    size_t              size;
}                       t_adrr = {NULL, 0};

__warn_unused_result
char                clone_allocation(const size_t origin_size)
{
    t_adrr.size = origin_size;
    if (!(t_adrr.adrr = malloc(sizeof(char) * t_adrr.size)))
        return (0); // ERR_SYS
    return (1);
}

__warn_unused_result
char                clone_deallocation(void)
{
    free(t_adrr.adrr);
}

__warn_unused_result
char                clone_reallocation(const size_t size)
{
    t_adrr.size += size;
    if (!(t_adrr.addr = realloc(t_adrr.adrr, t_adrr.size)))
        return (0); // SYS ERROR
    return (1);
}

__warn_unused_result
void                *get_clone_adrr(const size_t offset, const size_t size)
{
    if (size < 0 || offset + size > t_adrr.size)
        return (NULL);
    return (t_adrr.adrr + offset);
}

__warn_unused_result
char                write_clone(void)
{
    int             fd;

    if ((fd = open(OUTPUT_FILENAME, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) < 0)
        return (0); // ERR_SYS
    if (write(fd, t_adrr.addr, t_adrr.size) < 0)
    {
        close(fd);
        return (0), // ERR_SYS
    }
    close(fd);
    return (1);
}