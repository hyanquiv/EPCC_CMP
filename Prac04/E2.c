#include <stdio.h>
#include <conio.h>
#include <ctype.h>
int *preanalisis; 
int *temp;
void parea(int);
void Entero();
void con_signo();
void sin_signo();
void digito();
void error();

int main()
{
    *preanalisis = getchar(); // lee un carácter
                             // de la entrada
    Entero();
}

void Entero()
{
    if (*preanalisis == '+' || *preanalisis == '-')
    {
        con_signo();
    }

    else if (isdigit(*preanalisis))
    {
        sin_signo();
    }
    else
        error();
}
void con_signo()
{
    if (1)
    {
        if (*preanalisis == '+')
        {
            parea('+');
        }
        else if (*preanalisis == '-')
        {
            parea('-');
        }
        sin_signo();
    }
    else
        error();
}
void sin_signo()
{
    temp = preanalisis;
    preanalisis++;
    if (preanalisis==NULL)
    {
        preanalisis = temp;
        digito();
    }

    else if (isdigit(*preanalisis))
    {
        preanalisis = temp;
        digito();
        sin_signo();
    }
    else
    {
        preanalisis = temp;
        error();
    }
}
void digito()
{
    if (*preanalisis == '0')
    {
        parea('0');
    }
    else if (*preanalisis == '1')
    {
        parea('1');
    }
    else if (*preanalisis == '2')
    {
        parea('2');
    }
    else if (*preanalisis == '3')
    {
        parea('3');
    }
    else if (*preanalisis == '4')
    {
        parea('4');
    }
    else if (*preanalisis == '5')
    {
        parea('5');
    }
    else if (*preanalisis == '6')
    {
        parea('6');
    }
    else if (*preanalisis == '7')
    {
        parea('7');
    }
    else if (*preanalisis == '8')
    {
        parea('8');
    }
    else if (*preanalisis == '9')
    {
        parea('9');
    }
    else
        error();
}
void error()
{
    printf("Error de sintaxis\n");
}
void parea(int t)
{
    if (*preanalisis == t)
        preanalisis++;
    else
        error();
}