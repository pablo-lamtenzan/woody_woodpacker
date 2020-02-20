#include <woody_woodpacker.h>

int         woody_woodpacker(char ac, char **argv)
{
    size_t  size_of_file;
    char    format;

    if (ac != 2)
        return (0); // ERR_USE
    if (!(size_of_file = read_file(argv[1])))
        return (0);
    if ((format = get_format()) == FRMT_SIZE)
        return (0);  // ERR_USE not a valid file as input
    if (!(clone_allocation(size_of_file)))
        return (0);
    if (!t_format[format].packer(size_of_file))
        return (0); // ERR_CORRUPT 
    if (!write_clone())
        return (0);
    return (1);
}
/* when i ret i have to create a function err who
 will clone_dealLocation() and
 free_addr()
 */