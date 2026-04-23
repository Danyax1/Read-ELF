#include "parse_header.h"


bool check_if_elf(const uint8_t* e_ident){
	return e_ident[EI_MAG0] == ELFMAG0   &&
	       e_ident[EI_MAG1] == ELFMAG1   &&
	       e_ident[EI_MAG2] == ELFMAG2   &&
	       e_ident[EI_MAG3] == ELFMAG3;
}

const char* get_elf_class(unsigned char class){
	switch(class){
		case ELFCLASSNONE: return "Invalid class";
		case ELFCLASS32:   return "32-bit";
		case ELFCLASS64:   return "64-bit";
		default:           return "Unknown";
	}
}

const char* get_elf_data(unsigned char data){
	switch(data){
		case ELFDATANONE: return "Invalid data encoding";
		case ELFDATA2LSB: return "2's complement, little endian";
		case ELFDATA2MSB: return "2's complement, big endian";
		default:          return "Unknown";
	}
}

const char* get_elf_osabi(unsigned char osabi){
	switch(osabi){
		case ELFOSABI_NONE:     return "UNIX System V ABI";
		case ELFOSABI_HPUX:     return "HP-UX";
		case ELFOSABI_NETBSD:   return "NetBSD";
		case ELFOSABI_GNU:      return "GNU/Linux";
		case ELFOSABI_SOLARIS:  return "Solaris";
		case ELFOSABI_AIX:      return "AIX";
		case ELFOSABI_IRIX:     return "IRIX";
		case ELFOSABI_FREEBSD:  return "FreeBSD";
		case ELFOSABI_TRU64:    return "TRU64 UNIX";
		case ELFOSABI_MODESTO:  return "Novell Modesto";
		case ELFOSABI_OPENBSD:  return "OpenBSD";
		default:                return "Unknown";
	}
}

const char* get_elf_type(uint16_t type){
	switch(type){
		case ET_NONE: return "No file type";
		case ET_REL:  return "Relocatable file";
		case ET_EXEC: return "Executable file";
		case ET_DYN:  return "Shared object file";
		case ET_CORE: return "Core file";
		default:      return "Unknown";
	}
}

const char* get_elf_machine(uint16_t machine){
	switch(machine){
		case EM_NONE:  return "No machine";
		case EM_386:   return "Intel 80386";
		case EM_X86_64:return "AMD x86-64 architecture";
		case EM_ARM:   return "ARM";
		case EM_AARCH64: return "ARM AARCH64";
		case EM_MIPS:  return "MIPS";
		case EM_PPC:   return "PowerPC";
		case EM_PPC64: return "PowerPC 64-bit";
		case EM_SPARC: return "SPARC";
		default:       return "Unknown";
	}
}

void print_elf_header_32(Elf32_Ehdr* ehdr){
	printf("\nELF Header (32-bit):\n");
	printf("  Magic:   ");
	for(int i = 0; i < EI_NIDENT; i++){
		printf("%02x ", ehdr->e_ident[i]);
	}
	printf("\n");
	printf("  Class:                             %s\n", get_elf_class(ehdr->e_ident[EI_CLASS]));
	printf("  Data:                              %s\n", get_elf_data(ehdr->e_ident[EI_DATA]));
	printf("  Version:                           %d (current)\n", ehdr->e_ident[EI_VERSION]);
	printf("  OS/ABI:                            %s\n", get_elf_osabi(ehdr->e_ident[EI_OSABI]));
	printf("  ABI Version:                       %d\n", ehdr->e_ident[EI_ABIVERSION]);
	printf("  Type:                              %s\n", get_elf_type(ehdr->e_type));
	printf("  Machine:                           %s\n", get_elf_machine(ehdr->e_machine));
	printf("  Version:                           0x%x\n", ehdr->e_version);
	printf("  Entry point address:               0x%x\n", ehdr->e_entry);
	printf("  Start of program headers:          %u (bytes into file)\n", ehdr->e_phoff);
	printf("  Start of section headers:          %u (bytes into file)\n", ehdr->e_shoff);
	printf("  Flags:                             0x%x\n", ehdr->e_flags);
	printf("  Size of this header:               %u (bytes)\n", ehdr->e_ehsize);
	printf("  Size of program headers:           %u (bytes)\n", ehdr->e_phentsize);
	printf("  Number of program headers:         %u\n", ehdr->e_phnum);
	printf("  Size of section headers:           %u (bytes)\n", ehdr->e_shentsize);
	printf("  Number of section headers:         %u\n", ehdr->e_shnum);
	printf("  Section header string table index: %u\n", ehdr->e_shstrndx);
}

void print_elf_header_64(Elf64_Ehdr* ehdr){
	printf("\nELF Header (64-bit):\n");
	printf("  Magic:   ");
	for(int i = 0; i < EI_NIDENT; i++){
		printf("%02x ", ehdr->e_ident[i]);
	}
	printf("\n");
	printf("  Class:                             %s\n", get_elf_class(ehdr->e_ident[EI_CLASS]));
	printf("  Data:                              %s\n", get_elf_data(ehdr->e_ident[EI_DATA]));
	printf("  Version:                           %d (current)\n", ehdr->e_ident[EI_VERSION]);
	printf("  OS/ABI:                            %s\n", get_elf_osabi(ehdr->e_ident[EI_OSABI]));
	printf("  ABI Version:                       %d\n", ehdr->e_ident[EI_ABIVERSION]);
	printf("  Type:                              %s\n", get_elf_type(ehdr->e_type));
	printf("  Machine:                           %s\n", get_elf_machine(ehdr->e_machine));
	printf("  Version:                           0x%x\n", ehdr->e_version);
	printf("  Entry point address:               0x%lx\n", ehdr->e_entry);
	printf("  Start of program headers:          %lu (bytes into file)\n", ehdr->e_phoff);
	printf("  Start of section headers:          %lu (bytes into file)\n", ehdr->e_shoff);
	printf("  Flags:                             0x%x\n", ehdr->e_flags);
	printf("  Size of this header:               %u (bytes)\n", ehdr->e_ehsize);
	printf("  Size of program headers:           %u (bytes)\n", ehdr->e_phentsize);
	printf("  Number of program headers:         %u\n", ehdr->e_phnum);
	printf("  Size of section headers:           %u (bytes)\n", ehdr->e_shentsize);
	printf("  Number of section headers:         %u\n", ehdr->e_shnum);
	printf("  Section header string table index: %u\n", ehdr->e_shstrndx);
}

void parse_elf_header(uint8_t* elf_file){
	unsigned char class = elf_file[EI_CLASS];
	
	if(class == ELFCLASS32){
		Elf32_Ehdr* ehdr = (Elf32_Ehdr*)elf_file;
		print_elf_header_32(ehdr);
	}
	else if(class == ELFCLASS64){
		Elf64_Ehdr* ehdr = (Elf64_Ehdr*)elf_file;
		print_elf_header_64(ehdr);
	}
	else{
		fprintf(stderr, "Invalid ELF class\n");
	}
}