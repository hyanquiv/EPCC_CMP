#include <bits/stdc++.h>
using namespace std;

int main()
{
    FILE *dat1, *dat2;
    char c;
    int trans;

    cout << "Seleccione translacion de encriptacion Cesar: ";
    cin >> trans;

    if (fopen("toRead.txt", "r") == NULL)
        cout << "El documento no existe.\n";
    else
    {
        dat1 = fopen("toRead.txt", "r");
        dat2 = fopen("encriptado.txt", "w");
        fscanf(dat1, "%c", &c);
        while (!feof(dat1))
        {
            c += trans;

            fprintf(dat2, "%c", c);
            fscanf(dat1, "%c", &c);
        }
        fclose(dat1);
        fclose(dat2);

        dat1 = fopen("encriptado.txt", "r");
        dat2 = fopen("desencriptado.txt", "w");
        fscanf(dat1, "%c", &c);
        while (!feof(dat1))
        {
            c -= trans;

            fprintf(dat2, "%c", c);
            fscanf(dat1, "%c", &c);
        }
        fclose(dat1);
        fclose(dat2);
    }
    return 0;
}