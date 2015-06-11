#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define count_item 4
#define NPCO_item 32
#define HEADER 16
#define subHEADER 8

//type definitions
typedef
struct fdata {
    unsigned char * data;
    int size; //size of unsigned char  
} fdata;

typedef 
struct recordheaders{
    unsigned char[4] name; //record name, ex NPC_
    unsigned char[4] size; //record size
    unsigned char[8] misc; //other 2 headers, misc headers.
    srh * subrecords; //linked list
    srh * last; //end of linked list
    srh * obloc; //object location more on comment underneith
} rhead; //record header
//if yorue adding a new object, if the object exists, you need to just update it, rather than adding an entirely new record
//so while traversing it's easier to just keep this in mind, so you can access and change it if need be

typedef 
struct subrecordheaders{
    //linked list implementation
    unsigned char[4] name;
    unsigned char[4] size;
    unsigned char * data; // need to keep track of data
    sr * next; //next item in subrecord linked list
} srh; //subrecord

//prototypes
void remsrh(srh * subrecord, rhead * record);
void addsrh(char * name, char * size, char * data, rhead * record);
int isItem(srh * subrecord, fdata string);
void swapItem(srh * subrecord, fdata string);
rhead record_builder(FILE * read_file);
int subrecord_builder(rhead * record, int * remsize, FILE * read_file);
void rkiller(rhead* record, remsize, FILE * read_file, FILE * write_file);
void srkiller(rhead * record, FILE * write_file);
int string_is_string(char * filestring, int size, fdata * itemstring);
int isr(char * nam, fdata * rnam);
int issr(char * nam, fdata * srnam);
void write_header(FILE * write_file, char * data, int size);
void write_data(FILE * write_file, char * data, int size);
void write_stuff(FILE * write_file, char * data, int size);
void read_header(FILE * read_file, char * data, int size);
void read_data(FILE * read_file, char * data, int size);
void read_stuff(FILE * read_file, char * stuff, int size);


extern char NPCOSTRING[4] = {'N','P','C','O'};
extern char NAMESTRING[4] = {'N', 'A', 'M', 'E'};
extern char PLAYERSTRING[x] = {};
extern char NPCSTRING[4] = {'N','P','C','_'};
