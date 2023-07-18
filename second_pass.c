#include "second_pass.h"
#include "includes.h"
#include "utils.h"
#include "LinkedList.h"
#include "symbol_table.h"

void second_pass(node *head, symbol *symbol)
{
    node *curr = head;
    int position;
    while (curr != NULL)
    {
        if (curr->label[0] != 0){
            position = get_symbol(symbol,curr->label);
            curr->code = encode_combine_label(position);
        }
        curr = curr->next;
    }
}