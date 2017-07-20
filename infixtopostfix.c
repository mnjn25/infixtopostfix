#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct stack
{
   int top;
   int capacity;
   int *array;
};
struct stack* createstack(int capacity)
{
 struct stack *STACK;
 STACK=malloc(sizeof(struct stack));
 STACK->top=-1;
 STACK->capacity=capacity;
 STACK->array=malloc(sizeof(int)*STACK->capacity);
 return(STACK);
}
int isfull(struct stack *STACK)
{
    return(STACK->top==STACK->capacity-1);
}
char peek(struct stack* STACK)
{
    return STACK->array[STACK->top];
}
int isempty(struct stack *STACK)
{
    return(STACK->top==-1);
}
int push(struct stack *STACK,char item)
{
    if(!isfull(STACK))
    {
        STACK->top++;
        STACK->array[STACK->top]=item;
    }
    else
        return(-1);
}
char pop(struct stack *STACK)
{
    char item;
    if(!isempty(STACK))
    {
        item=STACK->array[STACK->top];
        STACK->top--;
        return(item);
    }
}
int isoperand(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
int isdigit(char ch)
{
    return(ch>='0' && ch<='9');
}
int prec(char ch)
{
     switch (ch)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;
    }
    return -1;
}
char* infixtopostfix(char* p)
{
    int i,k,length;
    length=strlen(p);
    struct stack *STACK;
    STACK=createstack(length);
    if(!STACK)
        return -1;
    for(i=0,k=-1;p[i];++i)
    {
        if(isoperand(p[i]))
            p[++k]=p[i];
        else if(p[i]=='(')
            push(STACK,p[i]);
        else if(p[i]==')')
        {
            while(!isempty(STACK)&&peek(STACK)!='(')
                    p[++k]=pop(STACK);
            if (!isempty(STACK) && peek(STACK) != '(')
                return -1;
            else
                pop(STACK);
        }
        else
        {
            while(!isempty(STACK)&&prec(p[i])<=prec(peek(STACK)))
            {
             p[++k]=pop(STACK);
            }
             push(STACK,p[i]);
        }
    }
    while(!isempty(STACK))
        p[++k]=pop(STACK);
    p[++k]='\0';
    printf("\n%s\n",p);
    return(p);
}
int evaluatepostfix(char* p)
{
    int i,length;
    length=strlen(p);
    struct stack *STACK;
    STACK=createstack(length);
    if(!STACK)
        return(-1);
    for(i=0;p[i];++i)
    {
        if(isdigit(p[i]))
            push(STACK,p[i]-'0');
        else
        {
            int val1=pop(STACK);
            int val2=pop(STACK);
            switch(p[i])
            {
                case '+':push(STACK,val2+val1);
                          break;
                case '-':push(STACK,val2-val1);
                          break;
                case '*':push(STACK,val2*val1);
                          break;
                case '/':push(STACK,val2/val1);
                          break;
                default:printf("invalid choice\n");
                         break;
            }
        }
    }
    return(pop(STACK));
}
int main()
{
    char p[50],*q;
    int choice,item;
    struct stack *STACK;
    while(1)
    {
        printf("\n1.to convert infix to postfix\n");
        printf("2.to evaluate postfix\n");
        printf("3.DO BOTH\n");
        printf("enter your choice\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:printf("enter your expression\n");
               scanf("%s",&p);
               infixtopostfix(p);
               break;
        case 2:printf("enter your expression\n");
               scanf("%s",&p);
               item=evaluatepostfix(p);
               printf("%d\n",item);
               break;
        case 3:printf("enter your expression\n");
               scanf("%s",&p);
               q=infixtopostfix(p);
               item=evaluatepostfix(q);
               printf("%d\n",item);
               break;
        default:printf("invalid choice\n");
                break;
        }
    }
}

