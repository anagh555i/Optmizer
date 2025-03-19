#define INTEGER_TYPE 9
#define BOOLEAN_TYPE 10
#define STRING_TYPE 17



typedef struct Gsymbol
{
    char *name;  // name of the variable
    int type;    // type of the variable
    int size;    // size of the type of the variable
    int binding; // stores the static memory address allocated to the variable
    struct Gsymbol *next;
}Gsymbol;

typedef struct TokenAttr
{
    int val; // For NUM Tokens              
    char* varname; //For STRING tokens and For Accessing Identifier Names              
    char *op;                   //For Operator Tokens
    struct Gsymbol* Gentry;
    
} TokenAttr;

extern Gsymbol* G_symbol_table;
extern int binding_pos;
extern int curr_declaration_type;

struct Gsymbol* GLookUp(char* varName);

struct TokenAttr* MakeTokenAttr(int val,char* str_val,char* op,struct Gsymbol* Gentry);

void G_Install(char* name,int type,int size);

void print_GSymbolTable();
