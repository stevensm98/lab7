#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int op_diff(struct tokenStack *stack);
static int op_product(struct tokenStack *stack);
static int op_quotient(struct tokenStack *stack);
static int op_GT(struct tokenStack *stack);
static int op_LT(struct tokenStack *stack);
static int op_GE(struct tokenStack *stack);
static int op_LE(struct tokenStack *stack);
static int op_EQ(struct tokenStack *stack);
static int op_HELP();
static int op_DROP(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_diff},
  {"*", op_product},
  {"/", op_quotient},
  {"GT", op_GT},
  {"LT", op_LT},
  {"GE", op_GE},
  {"LE", op_LE},
  {"EQ", op_EQ},
  {"DROP", op_DROP},
  {"HELP", op_HELP},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
  return atoi(s->e[--(s->top)]->symbol);  
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
  char convert[129];
  int i;
  sprintf(convert, "%d", v);
  
  s->e[(s->top)]->kind = 3;
  for(i = 0; convert[i] != '\0'; i++) {
  s->e[(s->top)]->symbol[i] = convert[i];
  }
  s->e[(s->top)++]->symbol[i] = '\0';

}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_diff(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2-v1);
  return(0);
}

static int op_product(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1*v2);
  return(0);
}

static int op_quotient(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1 / v2);
  return(0);
}

static int op_GT(struct tokenStack *stack)
{
  int v1,v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v1 > v2)
    pushInt(stack, 1);
  else
    pushInt(stack, 0);
  return(0);
}

static int op_LT(struct tokenStack *stack) 
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if (v1 < v2)
    pushInt(stack, 1);
  else
   pushInt(stack, 0);
return (0);
}

static int op_GE(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1 >= v2)
    pushInt(stack, 1);
  else
    pushInt(stack, 0);
  return (0);
}

static int op_LE(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1 <= v2)
    pushInt(stack, 1);
  else
    pushInt(stack, 0);
return (0);
}

static int op_EQ(struct tokenStack *stack) 
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1 == v2)
    pushInt(stack, 1);
  else 
    pushInt(stack, 0);
return (0);
}

static int op_DROP(struct tokenStack *stack) 
{
  popTokenStack(stack);
  return (0);
}

static int op_HELP() 
{
  printf("+ Command, add of two numbers\n");
  printf("- Command, diff of two numbers\n");
  printf("* Command, product of two numbers \n");
  printf("\\ Command, quotient of two numbers \n");
  printf("GT Command, Greater than, boolean result\n"); 
  printf("LT Command, Less than, boolean result\n");
  printf("GE Command, Greater than or equal, boolean result\n");
  printf("LE Command, Less than or equal, boolean result\n");
  printf("EQ Command, Equal command, boolean result\n");
  printf("DROP Command, Drop last token off stack\n");
  printf("HELP Command, print out commands\n");
  return (0);
}
