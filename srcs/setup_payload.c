#include <woody_woodpacker.h>
#include <elf64.h>

/*
**  Elf64_packer memory overview
**  ============================
**
**         | mem address | file offset | payload rel address      |
**         | ----------- | ----------- | ------------------------ |
**         | p_vaddr     | p_offset    | relative_pt_load_address |
**         |             |             |                          |
**         | sh_addr     | sh_offset   | relative_text_address    |
**         |             |             |                          |
**         | e_entry     |             | relative_entry_address   |
**
**                          .        .
**                          |  ...   |
**              p_offset -> |========| PT_LOAD  - relative_pt_load_address
**                          |  ...   |          ^
**                          |  ...   |          |
**             sh_offset -> |--------| .Text    |- relative_text_address
**                      |   |  ...   |          |^
**                      V   |  ...   |          ||
**    offset_in_section -   |>>>>>>>>| entry    ||- relative_entry_address
**                          |  ...   |          ||^
**                          |--------|          |||
**                          |  ...   |          |||
**                          |  ...   |          |||
**                          |  ...   |          |||
**   end_of_last_section -> |@@@@@@@@| payload  |||
**                          |@      @| |
**                          |@      @| V
**                          |@@@@@@@@| payload_size
**                          |========|
**                          |  ...   |
**                          .        .
*/


struct          s_payload
{
    uint32_t            key[4];
    uint32_t            relative_pt_load_addr;
    uint32_t            relative_text_addr;
    uint32_t            relative_entry_addr;
    uint32_t            pt_load_size;
    uint32_t            text_size;  
}__attribute__((packed));

static void             new_key(char *buff, size_t len)
{
    size_t              i;

    i = -1;
    srand(time(NULL))
    while (++i < len)
        buff + i = rand();
}

static char             init_payload(struct *s_payload payload, const t_data *origin)
{
    // copy the key reserving space for the siganture
    memcpy(payload->key, SECRET_SIGNATURE, SECRET_SIZE);
    new_key((char *)s_payload->key + SECRET_SIZE, 16 - SECRET_SIZE);

    // take all constants values from origin
    const size_t        last_shdr = origin->last_shdr;
    const Elf64_Off     phdr_offset = endian_64bits(origin->phdr_addr->p_offset);
    const Elf64_Off     shdr_offset = endian_64bits(origin->shpr_addr->sh_offset);
    const size_t        shdr_size = endian_64bits(origin->shdr_addr->sh_size);
    const Elf64_Xword   psize = endian_64bits(origin->phdr_addr->p_memsz);

    // put constants into payload struct
    paylaod->relative_pt_load_addr = last_shdr;
    payload->pt_load_size = psize;
    payload->relative_text_addr = last_shdr - shdr_offset;
    payload->relative_entry_addr = payload->relative_text_addr - origin->section_offset;
    payload->text_size = shdr_size;
    return (1);
}

char                    setup_payload(const t_data *origin)
{
    struct s_paylaod    payload;
    void                *payload_addr;
    void                *payload_const_addr;
    void                *text_addr;

    // init constants
    init_payload(&payload, origin);

    // calc payload and text sizes and offsets
    const size_t        payload_size = end_payload - start_paylaod;
    const size_t        text_size = endian_64bits(origin->shdr_addr->sh_size);
    const size_t        payload_offset = origin->last_shdr;
    const size_t        text_offset = payload_offset - payload.relative_text_addr;

    // take to addr where the payload, the payload constants, and the text will be
    if ((!(payload_addr = clone_allocation(payload_offset, payload_size))
            || !(payload_const_addr = clone_allocation(payload_offset + INSTR_SIZE, sizeof(struct s_payload)))
            || !(text_addr = clone_allocation(text_offset, text_size))))
        return (0); // corrupt

    // encrypt the text 
    encrypt();
    // put the payload data
    memcpy(payload_addr, start_payload, payload_offset);
    memcpy(payload_const_addr, &payload, sizeof(struct s_payload));

    return (1);
}