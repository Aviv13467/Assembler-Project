char *str_allocate_cat(char *first_str, char* second_str);
void flush_strtok(void);
void decimalToBinary(unsigned int decimal,int zeros);
unsigned int modifyASCII(int num);
char* remove_newline(char* str);
char* opcode_string(enum opcode index);
char* register_string(enum REGISTER reg);
char* type_string(enum TYPE index);
int opcode_no(char* name);
int command_valid(char* opcode);
int doesExist_macro(char* name);
void print_arr(char* arr);
int isValid_macro(char* name);