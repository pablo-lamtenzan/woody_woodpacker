#ifndef ELF64_H
# define ELF64_H

#include "linux/elf.h"

#define PAGE_SIZE           4096
#define SECRET_SIGNATURE    "42plamtenz"
#define SECRET_SIZE         sizeof(SECRET_SIGNATURE)
#define INSTR_SIZE          5

/*
**      - > TYEPDEF STRUCT FOR ELF HEADER
*/
typedef struct elf64_phdr   t_elf64_phdr;
typedef struct elf64_shdr   t_elf64_shdr;

/*
**      -> DATA STRUCT
*/
typedef                     s_data
{
    t_elf64_phder           *phdr_addr;
    t_elf64_shdr            *shdr_addr;
    t_elf64_shdr            *last_shdr;
    size_t                  last_section_end;
    size_t                  section_offset;
}                           t_data;

/*
**      -> ELF64 METHODS AND PAYLOAD
*/
char                        get_entry(t_data *origin, f_safe_accesor safe);
char                        calc_shift_amount(const t_data *origin, size_t *shift_amount);
char                        copy_into_clone(size_t last_section_end, size_t shift_amount, size_t origin_size);
char                        adjust_offset(size_t shift_amount, const t_data *origin);
char                        adjust_sizes(size_t shift_amount);
char                        foreach_phdr(f_safe_accessor safe, f_iter_callback callback);
char                        foreach_shdr(f_safe_accessor safe, f_iter_callback callback);
char                        check_elf64_identifier(void);
char                        setup_payload(const t_data *origin);
char                        change_entry(const t_data *origin);
char                        elf64_packer(size_t origin_file_size);


typedef	void	*(*f_safe_accessor)(const size_t offset, const size_t size);
typedef	bool	(*f_iter_callback)(f_safe_accessor safe, const size_t offset);

#endif