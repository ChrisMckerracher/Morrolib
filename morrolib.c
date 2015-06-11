#include "morrowh.h"

//function prototypes
static void read_stuff(FILE * read_file, char * stuff, int size);
static void write_stuff(FILE * write_file, char * data, int size);

//function definitions
void remsrh(srh * subrecord, rhead * record){
    //removes subrecord from record, updates record size
    //remaining size shouldnt change since this would be an already read record
    srh * deadrecord = subrecord;
    int size = deadrecord->size;
    subrecord = subrecord->next;
    free(deadrecord->data);
    free(deadrecord);
    record->size -= size;
    
}

void addsrh(char * name, char * size, char * data, rhead * record){
    //adds srh, updates record size
    
    srh * new_subr = malloc(sizeof(srh));
    new_subr->name = name;
    new_subr->size = size;
    new_subr->data = data;
    
    if(record->subrecords = NULL){
        record->subrecords = new_subr;
        record->last = new_subr;
    }else{
        record->last->next = new_subr;
        record->last = record->last->next;
    }
    
    record->last->next = NULL;
    
    rhead->size += size;
}

int isItem(srh * subrecord, fdata string){
    //determine if they are the item
    //if it's the item being looked for, swap items, and update recordsize
    int i;
    
    if(string.size != 32){
        perror("incorrectly formatted string");
        exit(1);
    }
    for(i=4; i < 36; i++){
        if(subrecord->data[i] != string.data[i-4])
            return 1; //not same item
    }
    
    return 0; //same item
}

void swapItem(srh * subrecord, fdata string){
    //string is the inputted item to switch
    
    int i;
    
    if(string.size != 32){
        perror("incorrectly formatted string");
        exit(1);
    }
    
    for(i=4; i < 36; i++){
        subrecord->data[i] = string.data[i-4];
    }
}


rhead record_builder(){
    //builds record header type
    
    rhead record;
    
    read_header(read_file, record.name, 4);
    read_header(read_file, record.size, 4);
    read_header(read_file, record.misc, 8);
    record.subrecords = NULL;
    record.last = NULL;
    record.obloc = NULL;
    
    return record;
}

int subrecord_builder(rhead * record, int * remsize){
    //1 means that the record cannot be bigger
    //remsize is remaining size before record is empty
    if(remsize == 0){
        return 1;
    }

    if(record->subrecords == NULL){
        record->subrecords = malloc(sizeof(srh));
        record->last = record->subrecords;
    } else{
        record->last->next = malloc(sizeof(srh));
        record->last = record->last->next;
    }
    read_header(read_file, record->last->name, 4);
    read_header(read_file, record->last->size, 4);
    read_data(read_file, record->last->data, SIZEEE);
    record->last->next = NULL;
    
    *remsize -= SIZEEE + 8;
    
    return 0;
}

void rkiller(rhead* record, remsize){
    //writes record
    write_header(write_file, record->name, 4);
    write_header(write_file, record->name, 4);
    write_header(write_file, record->name, 8);
    srkiller(record);
    
    if(remsize != 0){
        //we'll just read and write the rest of the record as a big block;
        char * bigblock = malloc(remsize);
        read_data(read_file, bigblock, remsize);
        write_data(write_file, bigblock, remsize);
        free(bigblock);
    }
}

void srkiller(rhead * record){
    //writes all subrecords that have been read
    srh * next;
    
    if(record->subrecord->last == NULL){
        //we're done;
    }
    
    while(record->subrecord != record->last){
        next = record->subrecord->next;
        write_header(write_file, record->subrecord->name, 4);
        write_header(write_file, record->subrecord->size, 4);
        write_data(write_file, record->subrecord->data, SIZE);
        free(record->subrecord);
        record->subrecord = next;
    }
    
    free(record->last);
    record->last = NULL;
    record->subrecord = NULL;
    record->obloc = NULL;
}

int string_is_string(char * filestring, int size, fdata * itemstring){
//name subrecord should check the size, so check name sub record byte length
//basically filestring's size should = itemstring.size for this function to be called
//returns 1 for false, 0 for true
//size is size of filestring

    if(size != itemstring->size){
        //sanity check to make sure no weird errors occur
        perror(string_is_string got called at different string lengths)
        exit(1);
    }
    
    int i;
    
    for(i=0; i < size; i++){
        if(filestring[i] != itemstring->data[i]){
            return 1;
        }   
    }
    
    return 0;
}

int isr(char * nam, fdata * rnam){
    //is record
    //same naming convention is issr, rnam is record name
    
    return string_is_string(name, 4, rnam);
}

int issr(char * nam, fdata * srnam){
    //is subrecord
    //nam is the subrecord type's name
    //srnam is the name youre seeing if your sr record has
    
    return string_is_string(name, 4, srnam)
}

void write_header(FILE * write_file, char * data, int size){
    write_stuff(write_file, data, size);
}

void write_data(FILE * write_file, char * data, int size); 
    write_stuff(write_file, data, size);
    
    free(data);
}

void write_stuff(FILE * write_file, char * data, int size){
    int success_checker = fwrite(data, 1, size, write_file);
    
    if (success_checker != size){
        perror("something went wrong with writing to new save file");
        exit(1);
    }
}

void read_header(FILE * read_file, char * data, int size){
    //since it's an array, it's already mallocd
    read_stuf(read_file, data, size);
}

void read_data(FILE * read_file, char * data, int size){
    data = malloc(size);
    read_stuff(read_file, data, size);
}

void read_stuff(FILE * read_file, char * stuff, int size){
    int read_size;
    
    read_size = fread(stuff, 1, size, read_file);
    
    if(data.size != size){
        //do stuff
    }
}
