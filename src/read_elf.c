#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <elf.h>

void print_usage(){
	printf("Usage: ./read_elf [OPTIONS] <filename>\n");
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

bool check_if_elf(const uint8_t* elf_file){
	return elf_file[0] == 0x7F   &&
	       elf_file[1] == 'E'    &&
	       elf_file[2] == 'L'    &&
	       elf_file[3] == 'F';
}


int main(int argc, char* argv[]){
	if(argc !=2 ){ // later more args
		print_usage();
		exit(1);
	}

	// right now only accepts filename

	uint8_t* elf_file = read_file(argv[1]);
	if(elf_file == NULL){
		return 1;
	}

	bool is_elf = check_if_elf(elf_file);
	if (is_elf){
		printf("%s is ELF executable\n", argv[1]);
	} else{
		printf("%s in NOT ELF executable\n", argv[1]);
	}

	free(elf_file);
	return 0;


}
