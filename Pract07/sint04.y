/**************************************************/
/* Ejemplo de YACC para convertir expresiones a */
/* notación postfija y quedar listo para ser */
/* evaluada por una maquina de pila abstracta */
/* */
/* Gramática con acciones semánticas */
/* */
/* exp -> exp + term {printf("+");} */
/* exp -> exp - term {printf("-");} */
/* exp -> term */
/* term -> ( exp ) */
/* term -> num {printf(num.val);} */
/* */
/* Pruebe con la entrada: 1+12+(4-21-(5+(3)))-8 */
/**************************************************/
%{
#include <stdio.h>
#include <ctype.h>
#include <math.h>
%}
%token num 
%left '+' /* + es asociativo por la izquierda */
%left '-' 
%%
 exp : exp '+' term {printf("+ \n");} ; 
 exp : exp '-' term {printf("- \n");} ;
 exp : term ;
term : '(' exp ')'; 
term : num {printf("inserta %d \n",$1);} ; /* $1 contiene el valor del token num */
%%
yylex() /* analizador léxico */
{ 
 int c; 
 do c=getchar(); while (c==' '|| c=='\t');
 
 if (c=='\n') return EOF; /* fin de archivo para yylex */
 if (isdigit(c)) /* regla de NUM */
 {
 ungetc(c,stdin);
 scanf("%d",&yylval); /* yylval contiene el lexema del token NUM */
 return(num);
 }
 return c;
}
yyerror(char *m) /* función de yacc para error */
{ 
 printf("%s",m); 
 exit(0); 
}
main() 
{ 
 while(1)
 { 
 yyparse(); /* analizador sintáctico */
 printf("\n"); 
 }
}
