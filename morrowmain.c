#include "morrowh.h"

extern unsigned char a[4] = {'N','P','C','O'};
extern unsigned char b[4] = {'N', 'A', 'M', 'E'};
extern unsigned char c[6] = {'p','l','a','y','e','r'};
extern unsigned char d[4] = {'N','P','C','_'};
extern fdata NPCOSTRING = {&a[0], 4};
extern fdata name = {&b[0], 4};
extern fdata player = {&c[0], 6};
extern fdata NPCSTRING = {&d[0], 4};

int main(){
    //returns size of record if it is an NPC_, else it just returns 0
    
    //-read header string, determine if it's NPCO_item
    //-if it is, find subheader NAME, find it's subrecord data length
    //-if this is equal to the itemstring's string length, compare with string_is_string 
    int remaining_size;
    fdata find_file;
    unsigned char a[] = {'d','d','d','d','p','_','r','e','s','t','o','r','e','_','h','e','a','l','t','h','_','b','d','d','d','d','d','d','d','d','d','d','d','d','d','d'};
    unsigned char b[] ={'d','d','d','d','t','e','s','t','_','t','e','s','t','_','t','e','s','t','_','t','e','s','d','d','d','d','d','d','d','d','d','d','d','d','d','d'}; 
    find_file.data = &a[0];
    find_file.size = 32;
    unsigned char * new_data = &b[0];
    FILE * read_file = fopen("MWsave2003.ess", "rb");
    FILE * write_file = fopen("test.ess", "wb");
    rhead record;
    while(1){    
        record = record_builder(read_file);
        remaining_size = record.size;
        if(isr(record.name, &NPCSTRING) == 1){
            //not right header type
            rkiller(&record, remaining_size, read_file, write_file);
        } else{
            //determine if NPC_ is the player record
                if (string_is_string(record.last->data, 6, &player) == 0){

            while(subrecord_builder(&record, &remaining_size, read_file) == 0){
                    if(issr(record.last->name, &NPCOSTRING) == 0){
                        //determine if item
                        printf("test");
                    }
                } //need to somehow pass remaining filesize
            //either if statement failing means this subrecord isn't right 
                
            }rkiller(&record, remaining_size, read_file, write_file);
        }
    }
}
