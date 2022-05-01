#include <bits/stdc++.h>

using namespace std;

int main()
{
    string filename("toRead.txt");
    vector<char> text;
    char letter = 0;
    regex num("[0-9]+");
    regex word("[A-Za-z]+");

    ifstream input_file(filename);
    if (!input_file.is_open())
    {
        cerr << "No se pudo abrir - '" << filename << "'" << endl;
        return 0;
    }

    while (input_file.get(letter))
    {
        if (letter == '\t' || letter == ' ' || letter == '\n')
        {
            string tester(text.begin(), text.end());
            if (regex_search(tester, word))
            {
                cout << "palabra :" << tester << "\n";
            }
            else if (regex_search(tester, num))
            {
                cout << "numero :" << tester << "\n";
            }
            else
            {
                cout << "caracter especial :" << tester << "\n";
            }
            text.clear();
        }
        text.push_back(letter);
    }
    cout << endl;
    input_file.close();

    return 0;
}