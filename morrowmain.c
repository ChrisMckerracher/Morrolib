#include "morrowh.h"

algorithm{
    //returns size of record if it is an NPC_, else it just returns 0
    
    //-read header string, determine if it's NPCO_item
    //-if it is, find subheader NAME, find it's subrecord data length
    //-if this is equal to the itemstring's string length, compare with string_is_string 
    int remaining_size;
    rhead record = record_builer();
    remaining_size = ...;
    
    if(isr(record.name, NPCSTRING) == 1){
        //not right header type
        rkiller(record);
    } else{
        //determine if NPC_ is the player record
        while(subrecord_builder(record) == 0){
            if (string_in_string(record.name, 4, playerstring) == 0){
                if(issr(record->last->name, NPCOSTRING) == 0){
                    //determine if item
                }
            } //need to somehow pass remaining filesize
        //either if statement failing means this subrecord isn't right 
            
        }
    }
}
