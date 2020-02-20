#ifndef BIN_PACKER_H
# define BIN_PACKER_H

/*
    TO DO:
- Have some bad class in elf_file_injection.c
- Have to code gen key
- Have to code encrypter
- Have to add endians better
- Have to delete all warnings
*/

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
#define SUCCES                  0
#define FAILURE                 -1
#define SECRET_SIGNATURE        "42plamtenz"
#define SECRET_SIZE             sizeof(SECRET_SIGNATURE)
#define OUTPUT_NAME             "woody"
#define ELF_MAGIC               0x464C457F
#define PAYLOAD_SIZE            374
#define PAGE_SIZE               4096
#define ENTRY_SEGMENT           "entry segment"
#define ENTRY_SECTION           "entry section"
#define LAST_SECTION            "last section"

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
#define ERR_SYS                 0 // syscall failure
#define ERR_THROW               1 // throw val from a fct
#define ERR_USE                 2 // bad usage
#define ERR_CORUPT              3 // corrupt file

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
typedef struct                  s_segment
{
    Elf64_Addr                  phdr_addr;
    Elf64_Off                   phdr_off;
    size_t                      phdr_filesz;             
}                               t_segment;

typedef struct                  s_section
{
    Elf64_Addr                  shdr_addr;
    Elf64_Off                   shdr_off;
    size_t                      shdr_filesz;             
}                               t_section;

typedef struct                  s_elf64
{
    Elf64_Ehdr                  *elf64_hdr;
    Elf64_Addr                  original_entry;
    t_segment                   segment;
    t_section                   section;
}                               t_elf64;

/*
**      --> PACKER STRUCTURE
*/
typedef struct                  s_packer
{
    int                         fd;
    size_t                      size;
    char                        *map;
    char                        key[SECRET_SIZE];
}                               t_packer;

/*
**      --> .TEXT
*/

/*
**      --> ERROR MANAGEMENT
*/
bool                            error(char code, char *message);

/*
**      --> PACKER METHODS
*/
t_elf64                         *find_entry(t_packer *data);
bool                            uptade_elf64_header(t_elf64 *elf64_hdr);
bool                            infect_elf_file_x64(t_packer *data);
bool                            identifier_criteria_x64(t_packer *data);
bool                            create_infected_elf_x64(t_packer *pack, t_elf64 *data);

/*
**      --> INIT AND END
*/
bool                            read_file(char *filename, t_packer *data);
bool				            free_map(t_packer *data);

/*
**      --> ITERATORS
*/
Elf64_Shdr                      *goto_next_section_x64(t_packer *data,
        Elf64_Ehdr *elf64_hdr, size_t sect_index);
Elf32_Shdr                      *goto_next_section_x32(t_packer *data,
        Elf32_Ehdr *elf32_hdr, size_t sect_index);
Elf64_Phdr                      *goto_next_segment_x64(t_packer *data,
        Elf64_Ehdr * elf64_hdr, size_t seg_index);
Elf32_Phdr                      *goto_next_segment_x32(t_packer *data,
        Elf32_Ehdr * elf32_hdr, size_t seg_index);

/*
**      --> ENDIAN MANAGEMENT
*/
uint16_t                        endian_16bits(uint16_t x);
uint32_t                        endian_32bits(uint32_t x);
uint64_t                        endian_64bits(uint64_t x);
void                            isbig(char _isbig);

/*
**      --> UTILS
*/
void                            insert_signature(t_packer *pack);
bool                            generate_key(char *key);

/*
**      --> WOODY WOODPACKER
*/
bool                             woody_woodpacker(int ac, char **argv);

#endif