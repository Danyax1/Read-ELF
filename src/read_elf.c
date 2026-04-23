#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "parse_header.h"

void print_usage(){
	printf("Usage: ./read_elf [OPTIONS] <filename>\n");
	printf("Options:\n");
	printf("  -h, --header    Display ELF header\n");
	printf("  -H, --help      Display this help message\n");
}

uint8_t* read_file(const char* filename){
	FILE* file = fopen(filename, "rb");
	if(file == NULL){
		perror("read_elf");
		fprintf(stderr ,"Error opening the file\n");
		return NULL;
	}
	fseek(file, 0L, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	uint8_t* buffer = malloc(file_size);
	if(buffer == NULL){
		perror("read_elf");
		fprintf(stderr, "Allocation failed\n");
		fclose(file);
		return NULL;
	}

	size_t bytes_read = fread(buffer, sizeof(uint8_t), file_size, file);
	if(bytes_read < file_size){
		fprintf(stderr, "Reading file failed\n");
		free(buffer);
		fclose(file);
		return NULL;
	}
	fclose(file);
	return buffer;
}


int main(int argc, char* argv[]){
	if(argc < 2){
		print_usage();
		exit(1);
	}
	
	bool show_header = false;
	char* filename = NULL;
	
	// Parse command line arguments
	for(int i = 1; i < argc; i++){
		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--header") == 0){
			show_header = true;
		}
		else if(strcmp(argv[i], "-H") == 0 || strcmp(argv[i], "--help") == 0){
			print_usage();
			return 0;
		}
		else{
			filename = argv[i];
		}
	}
	
	if(filename == NULL){
		fprintf(stderr, "Error: No filename provided\n");
		print_usage();
		return 1;
	}
	
	uint8_t* elf_file = read_file(filename);
	if(elf_file == NULL){
		return 1;
	}

	bool is_elf = check_if_elf(elf_file);
	if (is_elf){
		printf("%s is ELF executable\n", filename);
	} else{
		printf("%s in NOT ELF executable\n", filename);
	}

	if(show_header){
		parse_elf_header(elf_file);
	}

	free(elf_file);
	return 0;


}
