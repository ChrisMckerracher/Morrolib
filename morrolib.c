#include "morrowh.h"

//function prototypes
static void read_stuff(FILE * read_file, void * stuff, int size);
static void write_stuff(FILE * write_file, void * data, int size);
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

void addsrh(unsigned char * name, int size, unsigned char * data, rhead * record){
    //adds srh, updates record size
    
    srh * new_subr = malloc(sizeof(srh));
    new_subr->name[0] = name[0];
    new_subr->name[1] = name[1];
    new_subr->name[2] = name[2];
    new_subr->name[3] = name[3];
    new_subr->size = size;
    new_subr->data = data;
    
    if(record->subrecords == NULL){
        record->subrecords = new_subr;
        record->last = new_subr;
    }else{
        record->last->next = new_subr;
        record->last = record->last->next;
    }
    
    record->last->next = NULL;
    
    record->size += size;
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


rhead record_builder(FILE * read_file){
    //builds record header type
    
    rhead record;
    
    read_header(read_file, record.name, 4);
    read_header(read_file, &record.size, 4);
    read_header(read_file, record.misc, 8);
    record.subrecords = NULL;
    record.last = NULL;
    record.obloc = NULL;
    
    return record;
}

int subrecord_builder(rhead * record, int * remsize, FILE * read_file){
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
    read_header(read_file, &record->last->size, 4);
    read_data(read_file, record->last->data, record->last->size);
    record->last->next = NULL;
    
    *remsize -= record->last->size + 8;
    
    return 0;
}

void rkiller(rhead* record, int remsize, FILE * read_file, FILE * write_file){
    //writes record
    write_header(write_file, record->name, 4);
    write_header(write_file, &(record->size), 4);
    printf("test1\n");
    write_header(write_file, record->misc, 8);
    srkiller(record, write_file);
    printf("test2\n");  
    if(remsize != 0){
        //we'll just read and write the rest of the record as a big block;
        printf("test3\n");
        printf("%d",remsize);
        char * bigblock;
        printf("test4\n");
        bigblock = (char *) read_data(read_file, bigblock, remsize);
        write_data(write_file, bigblock, remsize);
        printf("test5\n");
    }
}

void srkiller(rhead * record, FILE * write_file){
    //writes all subrecords that have been read
    srh * next;
    
    if(record->last == NULL){
        return;
        //we're done;
    }
    
    while(record->subrecords != record->last){
        next = record->subrecords->next;
        write_header(write_file, record->subrecords->name, 4);
        write_header(write_file, &(record->subrecords->size), 4);
        write_data(write_file, record->subrecords->data, record->subrecords->size);
        free(record->subrecords);
        record->subrecords = next;
    }
    
    free(record->last);
    record->last = NULL;
    record->subrecords = NULL;
    record->obloc = NULL;
}

int string_is_string(unsigned char * filestring, int size, fdata * itemstring){
//name subrecord should check the size, so check name sub record byte length
//basically filestring's size should = itemstring.size for this function to be called
//returns 1 for false, 0 for true
//size is size of filestring

    if(size != itemstring->size){
        //sanity check to make sure no weird errors occur
        perror("string_is_string got called at different string lengths");
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

int isr(unsigned char * nam, fdata * rnam){
    //is record
    //same naming convention is issr, rnam is record name
    
    return string_is_string(nam, 4, rnam);
}

int issr(unsigned char * nam, fdata * srnam){
    //is subrecord
    //nam is the subrecord type's name
    //srnam is the name youre seeing if your sr record has
    
    return string_is_string(nam, 4, srnam);
}

void write_header(FILE * write_file, void * data, int size){
    write_stuff(write_file, data, size);
}

void write_data(FILE * write_file, void * data, int size){ 
    write_stuff(write_file, data, size);
   printf("test6\n"); 
    free(data);
}

static void write_stuff(FILE * write_file, void * data, int size){
    int success_checker = fwrite(data, 1, size, write_file);
    
    if (success_checker != size){
        perror("something went wrong with writing to new save file");
        exit(1);
    }
}

void read_header(FILE * read_file, void * data, int size){
    //since it's an array, it's already mallocd when mallocing whole subarray
    read_stuff(read_file, data, size);
}

void * read_data(FILE * read_file, void * data, int size){
    data = malloc(size);
    read_stuff(read_file, data, size);
    return data;
}

static void read_stuff(FILE * read_file, void * stuff, int size){
    int read_size;
    
    read_size = fread(stuff, 1, size, read_file);
    printf("%d\n",read_size); 
    if(read_size != size){
        if (read_size != 0){
            perror("read error on read_stuff");
        }else{
            exit(0);
        }
    }
}
