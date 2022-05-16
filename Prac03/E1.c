#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#define MAYOR '>'
#define MENOR '<'
#define PUNTOYCOMA ';'
#define COMA ','
#define PO '('
#define PC ')'
#define LO '{'
#define LC '}'
#define CO '['
#define CC ']'
#define HASH '#'
#define ID 256
#define NUM 257
#define MAS '+'
#define MENOS '-'
#define MULTI '*'
#define DIV '/'
#define EQU '='
#define MAYORIGUAL 258
#define MENORIGUAL 259
#define WHILE 260
#define FOR 261
#define IF 262
#define ELSE 263
#define COMP 264
#define DIF 265
#define RETURN 266
#define INT 267
int scaner();
void mostrar(int);
int espalres();
FILE *f;
char lexema[80];
int main(int n, char *pal[])
{
    int token;
    f = stdin;  // entrada estandar del teclado
    if (n == 2) // si se especifico un archivo de lectura
    {
        f = fopen(pal[1], "rt"); // lectura modo texto
        if (f == NULL)
            f = stdin;
    }
    if (f == stdin) // la lectura sera desde la entrada estandar
        printf("Ingrese texto ........ termine con Ctrl z \n");
    while (1)
    {
        token = scaner();
        if (token == EOF)
            break;
        mostrar(token);
    }
    if (f != stdin) // si la entrada fue de un archivo
        fclose(f);  // entonces cerrar el archivo.
} // fin del main
int scaner()
{
    int c;
    int i;
    do
        c = fgetc(f);
    while (isspace(c)); // ignora blancos
    if (c == EOF)
        return EOF;
    if (c == '/')
    {
        c = fgetc(f);
        if (c == '/')
        {
            while (c != '\n')
                c = fgetc(f);
        }
    }
    if (isalpha(c)) // regla del ID
    {
        i = 0;
        do
        {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isalnum(c) || c == '_');
        lexema[i] = 0;
        ungetc(c, f);   // se devuelve c al flujo de entrada
        i = espalres(); // verifica si es palabra reservada
                        // WHILE , IF
        if (i >= 0)
            return i;
        return ID; // se trata de un ID
    }
    if (isdigit(c)) // regla del NUM
    {
        i = 0;
        do
        {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isdigit(c));
        lexema[i] = 0;
        ungetc(c, f);
        return NUM;
    }
    // regla de PUNTOYCOMA y PARI
    if ((c == '#') || (c == ';') || (c == ',') || (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '(') || (c == ')') || (c == '{') || (c == '}') || (c == '[') || (c == ']'))
        return c; // regla del ";" y "("

    if (c == '>') // regla de ">" o ">="
    {
        c = fgetc(f);
        if (c == '=') // return MAYORIGUAL
        {
            lexema[0] = '>';
            lexema[1] = '=';
            lexema[2] = 0;
            return MAYORIGUAL;
        }
        ungetc(c, f);
        return MAYOR; // return MAYOR
    }
    if (c == '<') // regla de ">" o ">="
    {
        c = fgetc(f);
        if (c == '=') // return MAYORIGUAL
        {
            lexema[0] = '<';
            lexema[1] = '=';
            lexema[2] = 0;
            return MENORIGUAL;
        }
        ungetc(c, f);
        return MENOR; // return MAYOR
    }
    if (c == '=') // regla de ">" o ">="
    {
        c = fgetc(f);
        if (c == '=') // return MAYORIGUAL
        {
            lexema[0] = '=';
            lexema[1] = '=';
            lexema[2] = 0;
            return COMP;
        }
        ungetc(c, f);
        return EQU; // return MAYOR
    }

    if (c == '!') // regla de ">" o ">="
    {
        c = fgetc(f);
        if (c == '=') // return MAYORIGUAL
        {
            lexema[0] = '!';
            lexema[1] = '=';
            lexema[2] = 0;
            return DIF;
        }
        ungetc(c, f);
    }

} // fin de scaner
int espalres()
{
    if (strcmp(lexema, "while") == 0)
        return WHILE;
    if (strcmp(lexema, "if") == 0)
        return IF;
    if (strcmp(lexema, "for") == 0)
        return FOR;
    if (strcmp(lexema, "else") == 0)
        return ELSE;
    if (strcmp(lexema, "return") == 0)
        return RETURN;
    if (strcmp(lexema, "int") == 0)
        return INT;
    return -1;
}
void mostrar(int token)
{
    switch (token)
    {
    case ID:
        printf("token = ID [%s] \n", lexema);
        break;
    case NUM:
        printf("token = NUM [%s] \n", lexema);
        break;
    case MAS:
        printf("token = MAS [%c] \n", token);
        break;
    case MENOS:
        printf("token = MENOS [%c] \n", token);
        break;
    case MULTI:
        printf("token = MULTI [%c] \n", token);
        break;
    case DIV:
        printf("token = DIV [%c] \n", token);
        break;
    case EQU:
        printf("token = EQU [%c] \n", token);
        break;
    case COMP:
        printf("token = COMP [%s] \n", token);
        break;
    case DIF:
        printf("token = DIF [%s] \n", token);
        break;
    case MAYORIGUAL:
        printf("token = MAYORIGUAL [%s]\n", lexema);
        break;
    case MENORIGUAL:
        printf("token = MENORIGUAL [%s]\n", lexema);
        break;
    case WHILE:
        printf("token = WHILE [%s] \n", lexema);
        break;
    case FOR:
        printf("token = FOR [%s] \n", lexema);
        break;
    case IF:
        printf("token = IF [%s] \n", lexema);
        break;
    case ELSE:
        printf("token = ELSE [%s] \n", lexema);
        break;
    case PO:
        printf("token = PO [%c] \n", token);
        break;
    case PC:
        printf("token = PC [%c] \n", token);
        break;
    case LO:
        printf("token = LO [%c] \n", token);
        break;
    case LC:
        printf("token = LC [%c] \n", token);
        break;
    case CO:
        printf("token = CO [%c] \n", token);
        break;
    case CC:
        printf("token = CC [%c] \n", token);
        break;
    case MAYOR:
        printf("token = MAYOR [%c] \n", token);
        break;
    case MENOR:
        printf("token = MENOR [%c] \n", token);
        break;
    case PUNTOYCOMA:
        printf("token = PUNTOYCOMA [%c]\n", token);
        break;
    case COMA:
        printf("token = COMA [%c]\n", token);
        break;
    case HASH:
        printf("token = HASH [%c]\n", token);
        break;
    case RETURN:
        printf("token = RETURN [%s] \n", lexema);
        break;
    case INT:
        printf("token = INT [%s] \n", lexema);
        break;
    }
}