#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
    int menu;
    Tree tree;
    do
    {
        cout << "1) Datensatz einfuegen, manuell\n" << "2) Datensatz einfuegen, CSV Datein\n" << "3) Datensatz loeschen\n";
        cout << "4) Suchen\n" << "5) Datenstruktur anzeigen\n" << "6) Beenden\n";
        cin >> menu;
        cin.ignore(100,'\n');

        switch(menu)
        {
            case 1:
            {
                string name;
                int age, PLZ;
                double income;
                cout << "Bitte geben Sie den Datensatz ein.\n" << "Name?\n";
                getline(cin, name);
                cout << "Alter?\n";
                cin >> age;
                cin.ignore(100, '\n');
                cout << "Einkommen?\n";
                cin >> income;
                cin.ignore(100, '\n');
                cout << "PLZ?\n";
                cin >> PLZ;
                cin.ignore(100, '\n');

                tree.add(age, income, PLZ, name);
                cout << "Ihr Datensatz wurde eingefuegt.\n\n";
                break;
            }
            case 2:
            {
                char input;
                cout << "Möchten Sie die Daten aus der Datei 'ExportZielanalyse_Fall3.csv' importieren (j/n) ? ";
                cin >> input;
                cin.ignore(100, '\n');
                if(input == 'j') tree.import();
                else cout << "Importieren abgebrochen.\n\n";
                break;
            }
            case 3:
            {
                int pos;
                cout << "Bitte geben Sie den zu löschenden Datensatz an.\n" << "PosID ?\n";
                cin >> pos;
                tree.del(pos);
                cout << std::endl;
                break;
            }
            case 4:
            {
                string name;
                cout << "Bitte geben Sie den zu suchenden Datensatz an.\n" << "Name ?\n";
                getline(cin, name);
                if(!tree.searchAndPrint(tree.getAnker(), name)) cout << "Datensatz nicht gefunden.\n";
                cout << std::endl;
                break;
            }
            case 5:
            {
                if(tree.getAnker() == nullptr)
                {
                    cout << "Leerer Baum.";
                    break;
                }
                cout << "ID |    Name    | Alter | Einkommen |  PLZ  |  Pos\n";
                cout << "---+------------+-------+-----------+-------+-------\n";
                tree.print(tree.getAnker());
                cout << std::endl;
                break;
            }
        }
    }while(menu != 6);

    return 0;
}