#include <kernel/process/process.h>


pcb_list proc_list_head;

PCB proc0;

void init_proc(){
    proc0.uid = 0;
    proc0.father = NULL;
    // TODO: more defination for proc0

    
}


void schedule(){

}

void switch_to(PCB *next){

}