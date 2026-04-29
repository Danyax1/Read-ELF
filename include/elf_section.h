#ifndef ELF_SECTIONS_H
#define ELF_SECTIONS_H


#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


const char* get_section_type_name(uint32_t type);
const char* get_section_flags(uint32_t flags);
void print_section_headers_32(uint8_t* elf_file, Elf32_Ehdr* ehdr);
void print_section_headers_64(uint8_t* elf_file, Elf64_Ehdr* ehdr);
void parse_section_headers(uint8_t* elf_file, unsigned char class);

#endif // ELF_SECTIONS_H