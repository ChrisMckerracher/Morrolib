#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define count_item 4
#define NPCO_item 32
#define HEADER 16
#define subHEADER 8

//all headers are defined by byte size
//top_const deals with bytes up to MAST
//count_item is the size of an int, the count for an item
//NPCO_item is the size of one item, ex ring_vampiric_unique
//HEADER is just any preceeding header, like NPCO

//file data
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

char NPCOSTRING[4] = {'N','P','C','O'};
char NAMESTRING[4] = {'N', 'A', 'M', 'E'};
char PLAYERSTRING[x] = {};
char NPCSTRING[4] = {'N','P','C','_'};
