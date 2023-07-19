#include "second_pass.h"
#include "includes.h"
#include "utils.h"
#include "LinkedList.h"
#include "symbol_table.h"
#include "entry_table.h"
#include "extern_table.h"
void second_pass(char* ifp,node *head, symbol *label, entry_table *entry)
{
    node *curr = head;
    int position;
    while (curr != NULL)
    {
        if (curr->label[0] != 0){
            position = get_symbol(label,curr->label);
            if (position == -2)
                curr->code = encode_combine_extern();
            else
            curr->code = encode_combine_label(position);
            /* curr->code = position; */
        }
        curr = curr->next;
    }
    entry_table *curr_entry = entry;
    int pos_entry;
    while (curr_entry != NULL)
    {
        pos_entry = get_symbol(label,curr_entry->label);
        if (pos_entry != -1) curr_entry->label_pos = pos_entry;
        curr_entry = curr_entry->next;
    }
    curr = head;
    extern_table *ext = NULL, *curr_ext = NULL;

    while(curr != NULL)
    {
        if (curr->code == 1){
            curr_ext = add_extern(&ext,curr->label,curr->pos+100);
            curr_ext = curr_ext->next;
        }
        curr = curr->next;
    }
    if (!isEmpty_ext(ext)){
        export_extern(ifp,ext);
        fprintf(stderr,".ext file has been generated\n");
    }
    if (!isEmpty_entry(entry)){
        export_entry(ifp,entry);
        fprintf(stderr,".ent file has been generated\n");
    }
    int IC = get_IC(head);
    int DC = get_DC(label);
    write_counter(ifp,IC-DC,DC);
    if(export_obj(ifp,head) == 0) fprintf(stderr,".ob file has been generated\n");;
    free_extern(ext);

}