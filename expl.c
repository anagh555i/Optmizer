
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
    entry->trueLabel = NULL;
    entry->falseLabel = NULL;
    entry->Code ="";
    entry->next = NULL;
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

struct TokenAttr* Expr_TAC_Generate(TokenAttr* operand_1,char* op,TokenAttr* operand_2,char* result){
    
    int result_type = isArithOp(op)?INTEGER_TYPE:BOOLEAN_TYPE;

    if((operand_1->Type!=INTEGER_TYPE || operand_2->Type!=INTEGER_TYPE) && isArithOp(op) ){
        printf("Error : Non-int Type in  Arithmetic Operation\n");
        exit(1);//Need not exit....
    }
    //generating 3-address code and storing it as an attribute of the result token
    TokenAttr* result_token = MakeTokenAttr(-1,NULL,result_type,NULL);
    result_token->Addr = strdup(result);
    result_token->Code = malloc(CODE_SIZE);
    sprintf(result_token->Code,"%s = %s %s %s\n",result,operand_1->Addr,op,operand_2->Addr);
    return result_token;
}

struct TokenAttr* Assign_TAC_Generate(TokenAttr* result,TokenAttr* RHS){
    if(result->Type!=RHS->Type){
        printf("Error : Type mismatch in Assignment\n");
        exit(1);//Need not exit....
    }
    //generating 3-address code and storing it as an attribute of the result token
    struct TokenAttr* result_token = MakeTokenAttr(-1,NULL,result->Type,NULL);
    result_token->Addr = strdup(result->Addr);
    result_token->Code = malloc(CODE_SIZE);
    sprintf(result_token->Code,"%s = %s\n",result->Addr,RHS->Addr); 
    return result_token;
}

//handling labels
int Label = 0;

char* newlabel(){
    char* label = malloc(5);
    sprintf(label,"L%d",Label++);
    return label;
}
int isBinaryRelop(char* op){
    if(!strcmp(op,"==") || !strcmp(op,"!=") || !strcmp(op,">") || !strcmp(op,"<") || !strcmp(op,">=") || !strcmp(op,"<=")){
        return 1;
    } 
    else return 0;
}

struct TokenAttr* Boolean_TAC_Generate(TokenAttr* operand_1,char* op,TokenAttr* operand_2,char* trueLabel,char* falseLabel){
   
    if(!isBinaryRelop(op) && operand_1->Type!=BOOLEAN_TYPE && operand_2->Type!=BOOLEAN_TYPE){
        printf("Error: Non-boolean type in logical operation\n");
        exit(1);
    }
    if(operand_1->Type==BOOLEAN_TYPE || operand_2->Type==BOOLEAN_TYPE){
        printf("Error: Chained relational operations are not allowed\n");
        exit(1);
    }
    TokenAttr* result_token = MakeTokenAttr(-1,NULL,BOOLEAN_TYPE,NULL);
    if(isBinaryRelop(op)){  
    result_token->trueLabel = strdup(trueLabel);
    result_token->falseLabel = strdup(falseLabel);
    result_token->Code = malloc(CODE_SIZE);
    sprintf(result_token->Code,"if %s %s %s goto %s\ngoto %s\n",operand_1->Addr,op,operand_2->Addr,trueLabel,falseLabel);
    }
    else{
        if(strcmp(op,"&&")==0){
            result_token->trueLabel = strdup(trueLabel);
            result_token->falseLabel = strdup(falseLabel);
            result_token->Code = malloc(CODE_SIZE);
            sprintf(result_token->Code,"%s%s:\n%s",operand_1->Code,trueLabel,operand_2->Code);
        }
        else if(strcmp(op,"||")==0){
            result_token->trueLabel = strdup(trueLabel);
            result_token->falseLabel = strdup(falseLabel);
            result_token->Code = malloc(CODE_SIZE);
            sprintf(result_token->Code,"%s%s:\n%s",operand_1->Code,falseLabel,operand_2->Code);
        }
    }
    
    return result_token;
}

struct TokenAttr* While_TAC_Generate(TokenAttr* condition,char* Btrue,TokenAttr* while_body,char* Bfalse){
    TokenAttr* result_token = MakeTokenAttr(-1,NULL,BOOLEAN_TYPE,NULL);
    char* begin=newlabel();
    char* breakReplace=malloc(10);
    sprintf(breakReplace,"goto %s",Bfalse);
    char* continueReplace=malloc(10);
    sprintf(continueReplace,"goto %s",begin);
    char* body=tokeniseReplaceString(while_body->Code,breakReplace,continueReplace);
    result_token->Code=malloc(CODE_SIZE);
    sprintf(result_token->Code,"%s:\n%s%s:\n%s%s\n%s:\n",begin,condition->Code,Btrue,body,continueReplace,Bfalse);
    return result_token;
}

char* tokeniseReplaceString(char* code,char* breakReplace,char* continueReplace){
    char* result=malloc(CODE_SIZE);
    result[0]='\0';
    char* token;
    while(token=strtok(code,"\n")){
        if(strcmp(token,"break")==0) {
            strcat(result,breakReplace);
            strcat(result,"\n");
        }
        else if(strcmp(token,"continue")==0) {
            strcat(result,continueReplace);
            strcat(result,"\n");
        }
        else {
            strcat(result,token);
            strcat(result,"\n");
        }
        code+=(strlen(token)+1);
    }
    return result;
}

struct TokenAttr* If_TAC_Generate(TokenAttr* condition,char* Btrue,TokenAttr* if_body,char* Bfalse){
    TokenAttr* result_token = MakeTokenAttr(-1,NULL,BOOLEAN_TYPE,NULL);
    result_token->Code = malloc(CODE_SIZE);
    char* true_label = malloc(5);
    char* false_label = malloc(5);
    sprintf(false_label,"%s:\n",Bfalse);
    sprintf(true_label,"%s:\n",Btrue);
    result_token->Code = strcat(condition->Code,strcat(true_label,strcat(if_body->Code,false_label)));
    return result_token;
}

struct TokenAttr* IfElse_TAC_Generate(TokenAttr* condition,TokenAttr* if_body,TokenAttr* else_Body,char* Btrue,char* Bfalse,char* exitLabel){
    TokenAttr* result_token = MakeTokenAttr(-1,NULL,BOOLEAN_TYPE,NULL);
    result_token->Code = malloc(CODE_SIZE);
    char* true_label = malloc(5);
    char* false_label = malloc(5);
    char* exit_label = malloc(5);
    sprintf(exit_label,"%s:\n",exitLabel);
    sprintf(false_label,"%s:\n",Bfalse);
    sprintf(true_label,"%s:\n",Btrue);
    sprintf(result_token->Code,"%s%s%sgoto %s\n%s%s%s",condition->Code,true_label,if_body->Code,exitLabel,false_label,else_Body->Code,exit_label);
    return result_token;

}

