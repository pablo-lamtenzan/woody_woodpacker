#ifndef WOODY_WOODPACKER_H
# define WOODY_WOODPACKER_H 

/*
**      -> INCLUDES
*/
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/mman.h>

/*
**      -> ERROR CONSTANTS
*/
#define ERR_SYS                 0 //syscall failure
#define ERR_THROW               1 // throw val from a fct
#define ERR_USE                 2 // bad usage
#define ERR_CORUPT              3 // corrupt file
#define ERR_TOTAL               4 // nb of err

/*
**      -> FORMAT CONSTANTS
*/
#define FRMT_ELF64              0
#define FRMT_ELF32              1
#define FRMT_MACHO64            2
#define FRMT_MACHO32            3
#define FRMT_SIZE               4

/*
**      - > ATTRIBUTES (NO WARNINGS)
*/
# define __unused               __attribute__((unused))
# define __noreturn			    __attribute__((noreturn))
# define __warn_unused_result	__attribute__((warn_unused_result))
# define __nonull			    __attribute__((nonnull))

/*
**      -> FILE ACCESS AND ERROR
*/
size_t                          read_file(const char *name);
char                            free_adrr(void);
void                            *get_origin_adrr(const size_t offset, const size_t size);
char                            clone_allocation(const size_t origin_size);
char                            clone_deallocation(void);
char                            clone_reallocation(const size_t size);
void                            *get_clone_adrr(const size_t offset, const size_t size);
char                            write_clone(void);
size_t                          get_format(void);

/*
**      - > ENDIAN HANDLING
*/
uint16_t                        endian_16bits(uint16_t x);
uint32_t                        endian_32bits(uint32_t x);
uint64_t                        endian_64bits(uint64_t x);
void                            isbig(char _isbig);

/*
**      -> WOODY WOODPACKER
*/
int                             woody_woodpacker(char ac, char **argv);

/*
** f_identifier
**   returns true if identifies valid file format, sets endian globally
** f_packer
**   encrypts entry section, adds decryption routine before original entry
*/

typedef bool			(*f_identifier)(void);
typedef bool			(*f_packer)(size_t original_file_size);

struct				format
{
	f_identifier		format_identifier;
	f_packer		packer;
};

#endif
