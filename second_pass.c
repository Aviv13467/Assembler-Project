#include "second_pass.h"
#include "includes.h"
#include "utils.h"
#include "LinkedList.h"
#include "symbol_table.h"
#include "entry_table.h"
void second_pass(node *head, symbol *label, entry_table *entry)
{
    entry_table *curr_entry;
    int position_entry;
    node *curr = head;

    /*
    while (curr_entry != NULL)
    {
        position_entry = get_symbol(label,curr_entry->label);

    }
     */

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
}