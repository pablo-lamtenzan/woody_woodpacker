#ifndef BIN_PACKER_H
# define BIN_PACKER_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/types.h>
# include <unistd.h>
//# include <linux/elf.h>
#include <stdbool.h>


/*
**      --> DEFINE GLOBAL CONSTANTS
*/
#define SUCCES              0
#define FAILURE             -1
#define SECRET_SIGNATURE    "42plamtenz"
#define SECRET_SIZE         sizeof(SECRET_SIGNATURE)
#define OUTPUT_NAME         "woody"
#define ELF_MAGIC           0x464C457F
#define PAYLOAD_SIZE        374
#define PAGE_SIZE           4096

/*
**      --> FORMAT CONSTANTS
*/
#define FRMT_ELF64              0
#define FRMT_ELF32              1
#define FRMT_MACHO64            2
#define FRMT_MACHO32            3
#define FRMT_SIZE               4

/*
**      --> ERROR CONSTANTS
*/
#define ERR_SYS                 0 //syscall failure
#define ERR_THROW               1 // throw val from a fct
#define ERR_USE                 2 // bad usage
#define ERR_CORUPT              3 // corrupt file
#define ERR_TOTAL               4 // nb of err

/*
**      --> ATTRIBUTES (NO WARNINGS)
*/
# define __unused               __attribute__((unused))
# define __noreturn			    __attribute__((noreturn))
# define __warn_unused_result	__attribute__((warn_unused_result))
# define __nonull			    __attribute__((nonnull))

/*
**      --> DATA STRUCTURES
*/
typedef struct              s_segment
{
    Elf64_Addr              phdr_addr;
    Elf64_Off               phdr_off;
    size_t                  phdr_filesz;             
}                           t_segment;

typedef struct              s_section
{
    Elf64_Addr              shdr_addr;
    Elf64_Off               shdr_off;
    size_t                  shdr_filesz;             
}                           t_section;

typedef struct              s_elf64
{
    Elf64_Ehdr              *elf64_hdr;
    Elf64_Addr              original_entry;
    t_segment               segment;
    t_section               section;
}                           t_elf64;

/*
**      --> PACKER STRUCTURE
*/
typedef struct              s_packer
{
    int                     fd;
    size_t                  size;
    char                    *map;
    char                    key[SECRET_SIZE];
}                           t_packer;

/*
**      --> .TEXT
*/
void                        error(char *code, char *message);


uint16_t                        endian_16bits(uint16_t x);
uint32_t                        endian_32bits(uint32_t x);
uint64_t                        endian_64bits(uint64_t x);
void                            isbig(char _isbig);


#endif