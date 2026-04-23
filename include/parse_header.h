#ifndef PARSE_ELF_H_
#define PARSE_ELF_H_

#include <elf.h>
#include <stdbool.h>
#include <stdio.h>

bool check_if_elf(const uint8_t* e_ident);
void parse_elf_header(uint8_t* elf_file);

#endif //PARSE_ELF_H_