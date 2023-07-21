#include "utils.h"
char *str_allocate_cat(char *first_str, char* second_str) {
    char *str = (char *)malloc(strlen(first_str) + strlen(second_str) + 1);
    strcpy(str, first_str);
    strcat(str, second_str);
    return str;
}
int number_of_operands(opcode command)
{
    switch (command) {
        /*
         * opcode with 2 operands: mov,cmp,add,sub,lea
         */
        case mov:
        case cmp:
        case add:
        case sub:
        case lea:
            return 2;
            /*
            * opcode with 1 operand: not,clr,inc,dec,jmp,bne,red,prn,jsr
            */
        case not:
        case clr:
        case inc:
        case dec:
        case jmp:
        case bne:
        case red:
        case prn:
        case jsr:
            return 1;
            /*
            * opcode with no operands: rts,stop
            */
        case rts:
        case stop:
            return 0;

            /*
             * INVALID command
             */
        case ILLEGAL_OPCODE: return -1;
    }
}

/*
 * Flushes the strtok buffer.
 */
void flush_strtok(void)
{
    char *trash = NULL;
    trash = strtok(NULL," ");
}
/*
 * This functions converts a decimal number into it's binary representation, the user has a control over how many leading-zeros to add.
 * for example if the users inputs the decimal number 3 and 4 as leading zeros, the output will be: 0011;
 */
void decimalToBinary(unsigned int decimal,int zeros) {

    unsigned binary[16]; // Assuming 16-bit short integers
    int i = 0;

    while (decimal > 0) {
        binary[i] = decimal & 1; // Get the least significant bit
        decimal >>= 1; // Right-shift decimal by 1 bit
        i++;
    }
    // Print leading zeros if necessary
    int j;
    for (j = i; j < zeros; j++) {
        printf("0 ");
    }
    for (j= i - 1; j >= 0; j--) {
        printf("%d ", binary[j]);
    }
}
/*
 * This function modifies ASCII values, so it can return the corresponding values to translate to Base64
 */
unsigned int modifyASCII(int num)
{
    if (num >= 0 && num <= 25)
        return num+65;
    else if (num >=26 && num <= 51)
        return num+71;
    else if (num >= 52 && num<= 61)
        return num-4;
    else if (num == 62)
        return 43;
    else if (num == 63)
        return 47;
    return 0;
}
char* remove_newline(char* str)
{
    if (str[strlen(str)-1] == '\n') str[strlen(str)-1] = '\0';
    return str;
}
char* opcode_string(enum opcode index)
{
    char* str[] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};
    return str[index];
}
char* register_string(enum REGISTER reg)
{
    char* str[] = {"@r0","@r1","@r2","@r3","@r4","@r5","@r6","@r7"};
    return str[reg];
}

char* type_string(enum TYPE index)
{
    char* str[] = {".data",".string",".entry",".extern","IC"};
    return str[index];
}
int opcode_no(char* name)
{
    if (name[strlen(name)-1] == '\n') name[strlen(name)-1] = '\0';
    int i;
    for (i = 0; i <= 15; i++) {
        if (strcmp(name, opcode_string(i)) == 0)
            return i;
    }
    return -1;
}
int register_no(char* reg)
{
    if (reg[strlen(reg)-1] == '\n') reg[strlen(reg)-1] = '\0';
    int i;
    for (i = 0; i < 8; ++i) {
        if (strcmp(reg, register_string(i)) == 0) return i;
    }
}
int command_valid(char* opcode)
{
    int result;
    result = opcode_no(opcode);
    if (result == -1){
        fprintf(stderr,"ERROR: ILLEGAL COMMAND\n");
    }
    else return 0;
}
int isValid_macro(char* name)
{
    char* copy;
    copy = (char*) malloc(sizeof(char)* strlen(name));
    strcpy(copy,name);
    int i;

    for (i = 0; i < 15 ; ++i)
    {
        if (strcmp(name,opcode_string(i)) == 0) {
            fprintf(stderr, "INVALID MACRO NAME: MACRO CANNOT BE NAMED AFTER A COMMAND\n");
            return 1;
        }
    }
    i = 0;
    for (i = 0; i < 4; ++i) {
        if (strcmp(name, type_string(i)) == 0){
            fprintf(stderr,"INVALID MACRO NAME: MACRO CANNOT BE NAMED AFTER A TYPE\n");
            return 1;
        }
    }
    i = 0;
    for (i = 0; i <8; ++i) {
        if (strcmp(name, register_string(i)) == 0) {
            fprintf(stderr,"INVALID MACRO NAME: MACRO CANNOT BE NAMED AFTER A REGISTER\n");
            return 1;
        }
    }

    /* Check whether the first letter of the name starts with a non alphabet character,
     * this check is last since we want to inform the user if he used a register/type name. (will count as non-alphabet) */
    if (!isalpha((int)name[0])){
        fprintf(stderr,"INVALID MACRO NAME: MACRO CANNOT START WITH A NON ALPHABET CHARACTER\n");
        return 1;
    }

    return 0;
}
int isValid_label(char *name)
{
    char* copy;
    copy = (char*) malloc(sizeof(char)* strlen(name));
    strcpy(copy,name);
    int i,j,k;
    for (i = 0; i < 15 ; ++i)
        if (strcmp(name,opcode_string(i)) == 0) return 1;
    for (j = 0; j < 4; ++j)
        if (strcmp(name, type_string(j)) == 0) return 1;
    for (k = 0; k <8; ++k)
        if (strcmp(name, register_string(k)) == 0) return 1;
    /* Check whether the first letter of the name starts with a non alphabet character,
     * this check is last since we want to inform the user if he used a register/type name. (will count as non-alphabet) */
    if (!isalpha((int)name[0])) return 1;
    return 0;
}
int comma_check(char* str)
{
    int consecutive_commas = 0;
    while (*str) {
        if (*str == ',') {
            consecutive_commas++;
            if (consecutive_commas == 2) {
                return 1;
            }
        } else {
            consecutive_commas = 0;
        }
        str++;
    }
    return 0;
}

int isDigit(char *c)
{
    char* ptr;
    int result;
    result = (int)strtol(c,&ptr,10);
    return (ptr[0]=='\0')? 1:0;
}
int isRegister(char*str)
{
    if (str[strlen(str)-1] =='\n' ||str[strlen(str)-1] ==' ')  str[strlen(str)-1] = '\0';
    int i;
    for (i = 0; i < 8; ++i) {
        if (strcmp(str, register_string(i)) == 0) return 1;
    }
    return 0;
}
void print_arr(char* arr)
{
    int i = 0, j;
    for (i = 0; i < strlen(arr)+1; ++i) {
        printf("%c ",arr[i]);
    }
    putchar('\n');
    for (j = 0; j < strlen(arr)+1; ++j) {
        printf("%d ",arr[j]);
    }
    /*
     * prints the machine code
     *
    putchar('\n');
    for (j = 0; j < strlen(arr)+1; ++j) {
        decimalToBinary(encode_combine_direct(arr[j],ABSOLUTE),12);
        putchar('\n');
    }
     */

    putchar('\n');
}
void export_extern(char *ofp,extern_table *head)
{
    char *output_file_name = str_allocate_cat(ofp, ".ext");
    FILE *output_file_des = fopen(output_file_name,"w+");
    if (output_file_des == NULL) {
        fprintf(stderr,"Error occurred while opening the file %s\n", output_file_name);
        free(output_file_name);
        return;
    }
    fprint_extern_table(head,output_file_des);
}

void export_entry(char *ofp,entry_table *entry)
{
    char *output_file_name = str_allocate_cat(ofp, ".ent");
    FILE *output_file_des = fopen(output_file_name,"w+");
    if (output_file_des == NULL) {
        fprintf(stderr,"Error occurred while opening the file %s\n", output_file_name);
        free(output_file_name);
        return;
    }
    fprint_entry_table(entry,output_file_des);
}
void write_counter(char *ofp, int IC,int DC)
{
    char *output_file_name = str_allocate_cat(ofp, ".ob");
    FILE *output_file_des = fopen(output_file_name,"w+");
    if (output_file_des == NULL) {
        fprintf(stderr,"Error occurred while opening the file %s\n", output_file_name);
        free(output_file_name);
        return;
    }
    fprintf(output_file_des,"%d %d\n",IC,DC);
}
int export_obj(char *ofp, node *head)
{
    char *output_file_name = str_allocate_cat(ofp, ".ob");
    FILE *output_file_des = fopen(output_file_name,"a+");
    if (output_file_des == NULL) {
        fprintf(stderr,"Error occurred while opening the file %s\n", output_file_name);
        free(output_file_name);
        exit(1);
    }
    fprint_node(head,output_file_des);
    return 0;
}
void b64(node *head)
{
    while(head!=NULL) {
        encodeBase64(head->code);
        putchar('\n');
        head = head->next;
    }

}

