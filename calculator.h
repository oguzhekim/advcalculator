int eval (int count, Token *postfix){
    stackNode* top = NULL;
    for (int i = 0; i < count; i++)
    {
        Token tk = *(postfix+i);
        if (tk.type == TOKEN_INT) push(tk, &top);
        else if (tk.type == TOKEN_ADD){
            int fac2 = atoi(pop(&top).value);
            int fac1 = atoi(pop(&top).value);
            int num = fac1+fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};            
            push(newtk, &top);
        }
        else if (tk.type == TOKEN_SUBS){
            int fac2 = atoi(pop(&top).value);
            int fac1 = atoi(pop(&top).value);
            int num = fac1-fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};            
            push(newtk, &top);
        }
        else if (tk.type == TOKEN_MUL){
            int fac2 = atoi(pop(&top).value);
            int fac1 = atoi(pop(&top).value);
            int num = fac1*fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};            
            push(newtk, &top);
        }
        else if (tk.type == TOKEN_DIV){
            int fac2 = atoi(pop(&top).value);
            int fac1 = atoi(pop(&top).value);
            int num = fac1/fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};            
            push(newtk, &top);
        }
        else if (tk.type == TOKEN_AND){
            int fac2 = atoi(pop(&top).value);
            int fac1 = atoi(pop(&top).value);
            int num = fac1&fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};            
            push(newtk, &top);
        }
        else if (tk.type == TOKEN_OR){
            int fac2 = atoi(pop(&top).value);
            int fac1 = atoi(pop(&top).value);
            int num = fac1|fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};            
            push(newtk, &top);
        }
        else if (tk.type == TOKEN_FUNC){
            if (strcmp(tk.value, "not")!=0){
                int fac2 = atoi(pop(&top).value);
                int fac1 = atoi(pop(&top).value);     
                if (strcmp(tk.value, "xor")==0){
                    int num = fac1^fac2;
                    int length = snprintf( NULL, 0, "%d", num );
                    char* str = malloc( length + 1 );
                    snprintf( str, length + 1, "%d", num );
                    Token newtk = {str, TOKEN_INT};            
                    push(newtk, &top);
                }
                else if (strcmp(tk.value, "ls")==0){
                    int num = fac1<<fac2;
                    int length = snprintf( NULL, 0, "%d", num );
                    char* str = malloc( length + 1 );
                    snprintf( str, length + 1, "%d", num );
                    Token newtk = {str, TOKEN_INT};            
                    push(newtk, &top);
                }
                else if (strcmp(tk.value, "rs")==0){
                    int num = fac1>>fac2;
                    int length = snprintf( NULL, 0, "%d", num );
                    char* str = malloc( length + 1 );
                    snprintf( str, length + 1, "%d", num );
                    Token newtk = {str, TOKEN_INT};            
                    push(newtk, &top);
                }
                else if (strcmp(tk.value, "lr")==0){
                    int num = (fac1 << fac2)|(fac1 >> (sizeof(int)*CHAR_BIT - fac2));
                    int length = snprintf( NULL, 0, "%d", num );
                    char* str = malloc( length + 1 );
                    snprintf( str, length + 1, "%d", num );
                    Token newtk = {str, TOKEN_INT};            
                    push(newtk, &top);
                }
                else if (strcmp(tk.value, "rr")==0){
                    int num = (fac1 >> fac2)|(fac1 << (sizeof(int)*CHAR_BIT - fac2));
                    int length = snprintf( NULL, 0, "%d", num );
                    char* str = malloc( length + 1 );
                    snprintf( str, length + 1, "%d", num );
                    Token newtk = {str, TOKEN_INT};            
                    push(newtk, &top);
                }
            }
            else {
                int fac1 = atoi(pop(&top).value);
                int num = ~fac1;
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};            
                push(newtk, &top);
            }
        }
    }
    return atoi((*top).tk.value);
}