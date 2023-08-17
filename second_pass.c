#include "second_pass.h"

void second_pass(char* ifp,node *head, symbol *label, entry_table *entry)
{
    node *curr = head;
    int position,pos_entry;
    entry_table *curr_entry;
    extern_table *ext;
    int IC,DC;
    while (curr != NULL)
    {
        if (curr->label[0] != 0){
            position = get_symbol(label,curr->label);
            if (position == -2)
                curr->code = encode_extern();
            else
            curr->code = encode_relocatable(position);
        }
        curr = curr->next;
    }
    curr_entry = entry;
    while (curr_entry != NULL)
    {
        pos_entry = get_symbol(label,curr_entry->label);
        if (pos_entry != -1) curr_entry->label_pos = pos_entry;
        curr_entry = curr_entry->next;
    }
    curr = head;
    ext = NULL;

    while(curr != NULL)
    {
        if (curr->code == 1) add_extern(&ext,curr->label,curr->pos+100);
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
    IC = get_IC(head);
    DC = get_DC(label);
    write_counter(ifp,IC-DC,DC);
    if(export_obj(ifp,head) == 0) fprintf(stderr,".ob file has been generated\n");
    free_extern(ext);

}
