#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define count_item 4
#define NPCO_item 32
#define HEADER 16
#define subHEADER 8
typedef struct subrecordheaders srh;
typedef struct fdata fdata;
typedef struct recordheaders rhead;
//type definitions
struct fdata {
    unsigned char * data;
    int size; //size of unsigned char  
};


struct subrecordheaders{
    //linked list implementation
    unsigned char name[4];
    int size;
    unsigned char * data; // need to keep track of data
    srh * next; //next item in subrecord linked list
}; //subrecord

struct recordheaders{
    unsigned char name[4]; //record name, ex NPC_
    int size; //record size
    unsigned char misc[8]; //other 2 headers, misc headers.
    srh * subrecords; //linked list
    srh * last; //end of linked list
    srh * obloc; //object location more on comment underneith
}; //record header
//if yorue adding a new object, if the object exists, you need to just update it, rather than adding an entirely new record
//so while traversing it's easier to just keep this in mind, so you can access and change it if need be

//prototypes
void remsrh(srh * subrecord, rhead * record);
void addsrh(unsigned char * name, int size, unsigned char * data, rhead * record);
int isItem(srh * subrecord, fdata string);
void swapItem(srh * subrecord, fdata string);
rhead record_builder(FILE * read_file);
int subrecord_builder(rhead * record, int * remsize, FILE * read_file);
void rkiller(rhead* record, int remsize, FILE * read_file, FILE * write_file);
void srkiller(rhead * record, FILE * write_file);
int string_is_string(unsigned char * filestring, int size, fdata * itemstring);
int isr(unsigned char * nam, fdata * rnam);
int issr(unsigned char * nam, fdata * srnam);
void write_header(FILE * write_file, void * data, int size);
void write_data(FILE * write_file, void * data, int size);
void read_header(FILE * read_file, void * data, int size);
void read_data(FILE * read_file, void * data, int size);
