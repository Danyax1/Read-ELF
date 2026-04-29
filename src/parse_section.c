#include "elf_section.h"

void parse_section_headers(uint8_t* elf_file, unsigned char class){
	if(class == ELFCLASS32){
		Elf32_Ehdr* ehdr = (Elf32_Ehdr*)elf_file;
		print_section_headers_32(elf_file, ehdr);
	}
	else if(class == ELFCLASS64){
		Elf64_Ehdr* ehdr = (Elf64_Ehdr*)elf_file;
		print_section_headers_64(elf_file, ehdr);
	}
	else{
		fprintf(stderr, "Invalid ELF class for section headers\n");
	}
}

const char* get_section_type_name(uint32_t type){
	switch(type){
		case SHT_NULL:       return "NULL";
		case SHT_PROGBITS:   return "PROGBITS";
		case SHT_SYMTAB:     return "SYMTAB";
		case SHT_STRTAB:     return "STRTAB";
		case SHT_RELA:       return "RELA";
		case SHT_HASH:       return "HASH";
		case SHT_DYNAMIC:    return "DYNAMIC";
		case SHT_NOTE:       return "NOTE";
		case SHT_NOBITS:     return "NOBITS";
		case SHT_REL:        return "REL";
		case SHT_SHLIB:      return "SHLIB";
		case SHT_DYNSYM:     return "DYNSYM";
		case SHT_INIT_ARRAY: return "INIT_ARRAY";
		case SHT_FINI_ARRAY: return "FINI_ARRAY";
		case SHT_PREINIT_ARRAY: return "PREINIT_ARRAY";
		case SHT_GROUP:      return "GROUP";
		case SHT_SYMTAB_SHNDX: return "SYMTAB_SHNDX";
		default:             return "UNKNOWN";
	}
}

const char* get_section_flags_str(uint32_t flags){
	static char flag_str[256];
	flag_str[0] = '\0';
	
	if(flags & SHF_WRITE)      strcat(flag_str, "W ");
	if(flags & SHF_ALLOC)      strcat(flag_str, "A ");
	if(flags & SHF_EXECINSTR)  strcat(flag_str, "X ");
	if(flags & SHF_MERGE)      strcat(flag_str, "M ");
	if(flags & SHF_STRINGS)    strcat(flag_str, "S ");
	if(flags & SHF_INFO_LINK)  strcat(flag_str, "I ");
	if(flags & SHF_LINK_ORDER) strcat(flag_str, "L ");
	if(flags & SHF_OS_NONCONFORMING) strcat(flag_str, "O ");
	if(flags & SHF_GROUP)      strcat(flag_str, "G ");
	if(flags & SHF_TLS)        strcat(flag_str, "T ");
	
	if(flag_str[0] == '\0') return "   ";
	return flag_str;
}

void print_section_headers_32(uint8_t* elf_file, Elf32_Ehdr* ehdr){
	if(ehdr->e_shnum == 0 || ehdr->e_shoff == 0){
		printf("  No section headers present\n");
		return;
	}
	
	// Get section header string table
	Elf32_Shdr* shdr = (Elf32_Shdr*)(elf_file + ehdr->e_shoff);
	Elf32_Shdr* shstrtab_hdr = &shdr[ehdr->e_shstrndx];
	char* shstrtab = (char*)(elf_file + shstrtab_hdr->sh_offset);
	
	printf("\nSection Headers (32-bit):\n");
	printf("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");
	
	for(int i = 0; i < ehdr->e_shnum; i++){
		const char* section_name = &shstrtab[shdr[i].sh_name];
		
		printf("  [%2d] %-20s %-13s %08x %06x %06x %02x %-3s %2d %2d %2d\n",
			i,
			section_name,
			get_section_type_name(shdr[i].sh_type),
			shdr[i].sh_addr,
			shdr[i].sh_offset,
			shdr[i].sh_size,
			shdr[i].sh_entsize,
			get_section_flags_str(shdr[i].sh_flags),
			shdr[i].sh_link,
			shdr[i].sh_info,
			shdr[i].sh_addralign);
	}
}

void print_section_headers_64(uint8_t* elf_file, Elf64_Ehdr* ehdr){
	if(ehdr->e_shnum == 0 || ehdr->e_shoff == 0){
		printf("  No section headers present\n");
		return;
	}
	
	// Get section header string table
	Elf64_Shdr* shdr = (Elf64_Shdr*)(elf_file + ehdr->e_shoff);
	Elf64_Shdr* shstrtab_hdr = &shdr[ehdr->e_shstrndx];
	char* shstrtab = (char*)(elf_file + shstrtab_hdr->sh_offset);
	
	printf("\nSection Headers (64-bit):\n");
	printf("  [Nr] Name                 Type          Address          Offset    Size    ES Flg  Lk Inf Al\n");
	
	for(int i = 0; i < ehdr->e_shnum; i++){
		const char* section_name = &shstrtab[shdr[i].sh_name];
		
		printf("  [%2d] %-20s %-13s %016lx %08lx %08lx %02lx %-4s %2d %2d %2ld\n",
			i,
			section_name,
			get_section_type_name(shdr[i].sh_type),
			shdr[i].sh_addr,
			shdr[i].sh_offset,
			shdr[i].sh_size,
			shdr[i].sh_entsize,
			get_section_flags_str(shdr[i].sh_flags),
			shdr[i].sh_link,
			shdr[i].sh_info,
			shdr[i].sh_addralign);
	}
}
