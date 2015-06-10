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
struct fdata {
    unsigned char * bytes;
    int size; //size of unsigned char  
};

typedef 
struct recordheaders{
    unsigned char[4] name; //record name, ex NPC_
    unsigned char[4] size; //record size 
    unsigned char[8] misc; //other 2 headers, misc headers.
    srh * subrecords; //linked list
} rhead; //record header

typedef 
struct subrecordheaders{
    //linked list implementation
    unsigned char[4] name;
    unsigned char[4] size;
    unsigned char * data; // need to keep track of data
    sr * next; //next item in subrecord linked list
} srh; //subrecord

void copy_data(FILE * read_file, FILE * write_file, num_bytes);
void write_data(FILE * write_file, struct fdata data);
struct fdata read_data(FILE * read_file, int size); 
void find_keyword(char * readbuffer, unsigned char * string);
void read_wrapper(FILE * read_file, FILE * write_file);
int string_is_string(struct fdata filestring, struct fdata itemstring);
//read_wrapper will be the wrapper for reading and writing to file
//use unsigned char for file type

//remember to rename FILENAME

//global variables

int string_is_string(struct fdata filestring, struct fdata itemstring){
//name subrecord should check the size, so check name sub record byte length
//basically filestring.size should = itemstring.size for this function to be called
//returns 1 for false, 0 for true

    if(filestring.size != itemstring.size){
        //sanity check to make sure no weird errors occur
        perror(string_is_string got called at different string lengths)
        exit(1);
    }
    
    int i;
    
    for(i=0; i < filestring.size; i++){
        if(filestring.data[i] != itemstring.data[i]){
            return 1;
        }   
    }
    
    return 0;
}

algorithm{
    //returns size of record if it is an NPC_, else it just returns 0
    
    //-read header string, determine if it's NPCO_item
    //-if it is, find subheader NAME, find it's subrecord data length
    //-if this is equal to the itemstring's string length, compare with string_is_string 
    int record_size;
    int subrecord_size;
    
    if((record_size = isNPC()) == 0){
        continue;
    } else{
        //determine if NPC_ is the player record
        while(record_size != 0){
            if (ISUSER(itemstring, &record_size) == 0){
                if(isNPCO_(&recordsize, &subrecord_size)){
                    isItem(&recordsize, &subrecord_size);
                }
            } //need to somehow pass remaining filesize
        }
    }
    
}

isItem(int * recordsize, int * subrecord_size){
    //determine if they are the item
    //if it's the item being looked for, swap items, and update recordsize
    
    
}

swapItem(int)

int isNPCO_(int * recordsize){
    struct fdata subrecordName = read_data(FILENAME, count_item);
    struct fdata subrecordSize = read_data(FILENAME, count_item);
    struct fdata subrecordDATA = read_data(FILENAME, SIZEOFSIZE);
    
    write_data(subrecordNAME);
    write_data(subrecordSize); //save size somewhere
    
    if string_is_string(subrecordDATA, NPCSTRING){
        write_data(subrecordData);
        return 0;
    } else{
        write_data(subrecordDATA);
        return 1;
    }
    
}

int ISUSER_(struct fdata itemstring, int * recordsize){
    //should only be called if ISNPC_ is true
    struct fdata subrecordName = read_data(FILENAME, count_item); //this should always be NAME, as always NPC_ record
    struct fdata subrecordSize = read_data(FILENAME, count_item);
    //determine what the size is from the little endian 4 byte number, which is SIZEOFSIZE
    struct fdata subrecordData= read_data(FILENAME, SIZEOFSIZE);
    
    write_data(subrecordName);
    write_data(subrecordSize); //save size somewhere 
    
    if string_is_string(subrecordData, USERSTRING){ //player
        write_data(subrecordData);
        return 0; //success
    }
    else
        write_data(subrecordData);
        return 1; //failure 
    //subtract recordsize, and return it as well
}

int ISNPC_(){
   
    struct fdata recordName = read_data(FILENAME, count_item);
    struct fdata recordSize = read_data(FILENAME, count_item);
    //save recordSize somewhere
    
    if string_is_string(recordNAME, NPC_NAME){
        //if it's an NPC_ record
        write_data(WriteName, recordName);
        write_data(WriteName, recordName)
        struct fdata headers = read_data(FILENAME, count_item * 2 ); //the remaining headers
        write_data(WriteNAME, headers);
        return SIZE_OF_RECORD;
    } else{
        write_data(WriteName, recordName);
        struct fdata headers = read_data(FILENAME, count_item * 2); //remaining headers
        //determine size of recordSize
        write_data(WriteNAME, recordSize);
        write_data(WriteName, headers);
        struct fdata wrongrecord = read_data(FILENAME, SIZE_OF_RECORD_SIZE); //writes whole record 
        write_data(WriteName, wrongrecord);
        return 0
    }
}

void write_data(FILE * write_file, struct fdata data); 
    //attempts an fwrite. returns 0 if sucessfull, or 1 in
    //an event of a failure
    int success_checker;
    success_checker = fwrite(data.bytes, 1, data.size, write_file);

    if (success_checker != data.size){
    perror("something went wrong with writing to new save file");
    exit(1);
    }
    
    free(data.data);
}

struct fdata read_data(FILE * read_file, int size){
    //consider shrinking data.data if size is smaller than expected
    struct fdata data;
    data.data = malloc(size);
    data.size = fread(fdata.data, 1, size, read_file);
    
    if(data.size != size){
        //then we are eof
    }
    return data;
}

void copy_data(FILE * read_file, FILE * write_file, int num_bytes){
//make use of the above write_data function
    struct fdata data = read_data(read_file, num_bytes);
    
    write_data(write_file, data);   
}
