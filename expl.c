
//----------GLOBAL SYMBOL TABLE FUNCTIONS --------------------------

Gsymbol* G_symbol_table = NULL;
int binding_pos = 4096;
int curr_declaration_type = 0;


struct Gsymbol* GLookUp(char* Identifier){
    if(G_symbol_table==NULL)return NULL;
    Gsymbol* temp = G_symbol_table;
    while(temp!=NULL && strcmp(temp->name,Identifier)!=0){
        temp=temp->next;
    }
    if(temp==NULL)return NULL;
    return temp;
}
void G_Install(char* name, int type, int size) {
    Gsymbol* new_Entry = (Gsymbol*)malloc(sizeof(Gsymbol));
    new_Entry->name = strdup(name);
    new_Entry->type = type;
    new_Entry->size = size;
    new_Entry->binding = binding_pos;
    binding_pos += size;  
    new_Entry->next = NULL;

    if (G_symbol_table == NULL) {
        G_symbol_table = new_Entry;
    } else {
        Gsymbol* temp = G_symbol_table;
        while (temp != NULL) {
            if(strcmp(temp->name,name)==0){
                printf("Syntax error:Redeclaration of variable : %s\n",name);
                exit(1);
            }
            if(temp->next==NULL)break;
            temp = temp->next;
        }
        temp->next = new_Entry;
    }
    return;
}

void print_GSymbolTable(){
    Gsymbol* temp = G_symbol_table;
    printf("-----------------------------------GLOBAL SYMBOL TABLE-----------------------------------\n");
    if(temp==NULL)printf("-----------------------------------empty-----------------------------------\n");
    while(temp!=NULL){
        printf("| name: %s , binding:[%d] , type:[%s] |\n",temp->name,temp->binding,(temp->type==9)?"int":"str");
        temp=temp->next;
    }
    printf("\n\n");
};
struct TokenAttr* MakeTokenAttr(int val, char* str_val, int Type, struct Gsymbol* Gentry) {
    struct TokenAttr* entry = (struct TokenAttr*)malloc(sizeof(struct TokenAttr));
    entry->val = val;
    entry->varname = str_val ? strdup(str_val) : NULL;
    entry->Type = Type;
    entry->Gentry = Gentry;
    entry->Addr = NULL;
    return entry;
}



//---------------------------------- THREE ADDRESS CODE GENERATION FUNCTIONS ----------------------------------

int tempAddress = 0;

char* newTemp(){
    char* addr = malloc(5);
    sprintf(addr,"t%d",tempAddress++);
    return addr;
}

int isArithOp(char* op){
    if(!strcmp(op,"+") || !strcmp(op,"*") || !strcmp(op,"-") || !strcmp(op,"/")){
        return 1;
    } 
    else return 0;
}

void CleanupToken(TokenAttr* token){
    if(token->Addr)free(token->Addr);
    if(token->varname)free(token->varname);
    free(token);
}

struct TokenAttr* Expr_TAC_Generate(TokenAttr* operand_1,char* op,TokenAttr* operand_2,char* result,FILE* TAC_FILE){
    
    int result_type = isArithOp(op)?INTEGER_TYPE:BOOLEAN_TYPE;

    if((operand_1->Type!=INTEGER_TYPE || operand_2->Type!=INTEGER_TYPE) && isArithOp(op) ){
        printf("Error : Non-int Type in  Arithmetic Operation\n");
        exit(1);//Need not exit....
    }
    //generating 3-address code
    fprintf(TAC_FILE,"%s = %s %s %s\n",result,operand_1->Addr,op,operand_2->Addr);
    
    TokenAttr* result_token = MakeTokenAttr(-1,NULL,result_type,NULL);
    result_token->Addr = strdup(result);

    
    // CleanupToken(operand_1);
    // CleanupToken(operand_2);

    return result_token;

}


