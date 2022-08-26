%{
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
%}
%token INT FLOAT ID IF ELSE NUM WHILE
%left '+' '-'
%left '*' '/'
%%
programC: listaDeclC;
listaDeclC: listaDeclC declC | ;
declC: Tipo listaVar ';';
declC: Tipo ID '(' listaPar ')' bloque;
Tipo: INT | FLOAT;
listaVar: ID ',' listaVar | ID;
listaPar: Tipo ID ',' listaPar | Tipo ID;
bloque: '{' listaVarLoc listaProp '}';
listaVarLoc: Tipo listaVar ';' listaVarLoc | ;
listaProp: listaProp prop | ;
prop: ';'
prop: IF '(' EXPRESION ')' prop;
prop: IF '(' EXPRESION ')' prop ELSE prop;
prop: WHILE '(' EXPRESION ')' prop;
prop: ID '=' EXPRESION ';' ;
prop: bloque
EXPRESION: NUM;
EXPRESION: EXPRESION '+' EXPRESION
EXPRESION: EXPRESION '-' EXPRESION
EXPRESION: EXPRESION '*' EXPRESION
EXPRESION: EXPRESION '/' EXPRESION
EXPRESION: '(' EXPRESION ')'
EXPRESION: ID
%%
int yylex()
{
 int c;
 char lexema[30];
 char *p;
 do c=getchar(); while (isspace(c));
 if(c==27) return EOF;
 if (isalpha(c))
 {
 p=lexema;
 do { *p++=c; c=getchar(); } while (isalpha(c));
 ungetc(c,stdin);
 *p=0;
 if (strcmp(lexema,"if")==0) return IF;
 if (strcmp(lexema,"else")==0) return ELSE;
 if (strcmp(lexema,"int")==0) return INT;
 if (strcmp(lexema,"float")==0) return FLOAT;
 if (strcmp(lexema,"while")==0) return WHILE;
 return ID;
 }
 if(c=='(' || c==')' || c==';' || c==',' || c=='{' || c=='}') return c;
 if(c=='+' || c=='-' || c=='*' || c=='/') return c;
 if(c=='=') return c;
 if(isdigit(c))
 {
 ungetc(c,stdin);
 scanf("%d",&c);
 return NUM;
 }
 yyerror("--- caracter ilegal !!!");
}
yyerror(char *m)
{
 fprintf(stderr,"error de sintasis %s\n",m);
 exit(0);
}
void main()
{
 yyparse();
}
