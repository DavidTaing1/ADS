#include "Ringpuffer.h"
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int menu;
    string descrIn, dataIn;
    Ringpuffer ring;
    cout << "\nRINGPUFFER BACKUP\n";
    do
    {
        cout << "=================================================================================\n";
        cout << "1) Backup einfuegen\n" << "2) Backup suchen\n" << "3) Alle Backups ausgeben\n" << "4) Beenden\n";
        cin >> menu;
        cin.ignore(100,'\n');
        switch(menu)
        {
            case 1:
            {
                cout << "---------------------------------------------------------------------------------\n";
                cout << "+Neuen Datensatz einfuegen" << endl << "Beschreibung ? " << endl;
                getline(cin, descrIn);

                cout << "Daten ? \n";
                getline(cin, dataIn);

                ring.addNode(descrIn, dataIn);
                cout << "+Ihr Datensatz wurde hinzugefuegt.\n";
                break;
            }
            case 2:
            {
                cout << "---------------------------------------------------------------------------------\n";
                cout << "+Nach welchen Daten soll gesucht werden?\n";
                getline(cin, dataIn);
                if(ring.search(dataIn) != nullptr)
                {
                    cout << "Gefunden in Backup: OldAge " << ring.search(dataIn)->getAge() << ", Beschreibung: ";
                    cout << ring.search(dataIn)->getDescription() << ", Daten: " << ring.search(dataIn)->getData() << endl;
                }
                else cout << "Datensatz konnte nicht gefunden werden.\n";
                break;
            }
            case 3:
            {
                cout << "---------------------------------------------------------------------------------\n";
                ring.print(ring.getAnker()->getNext());
                break;
            }
        }
    }while(menu != 4);
    return 0;
}
