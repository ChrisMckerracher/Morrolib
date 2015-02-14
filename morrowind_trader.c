#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define top_const 320
#define count_item 4
#define NPCO_item 32
#define HEADER 8

//all headers are defined by byte size
//top_const deals with bytes up to MAST
//count_item is the size of an int, the count for an item
//NPCO_item is the size of one item, ex ring_vampiric_unique
//HEADER is just any preceeding header, like NPCO

void copy_data(FILE * read_file, FILE * write_file, num_bytes);
void write_data(FILE * write_file, char * bytes, int size);
void find_keyword(char * readbuffer, char * string);
