#include <bits/stdc++.h>

using namespace std;

int main()
{
    string filename("toRead.txt");
    vector<char> text;
    char letter = 0;

    ifstream input_file(filename);
    if (!input_file.is_open())
    {
        cerr << "No se pudo abrir - '"<< filename << "'" << endl;
        return 0;
    }

    while (input_file.get(letter))
    {
        text.push_back(letter);
    }
    for (const auto &i : text)
    {
        cout << i << " ";
    }
    cout << endl;
    input_file.close();

    return 0;
}