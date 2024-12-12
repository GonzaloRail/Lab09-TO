#include <iostream>
#include "FooManager.h"

using namespace std;

int main() {
    cout << "Patron Singleton" << endl;

    // Crear la instancia única
    FooManager::Create();

    FooManager* pMyFoo1 = FooManager::GetInst();
    if (pMyFoo1 != nullptr) {
        cout << "Primera instancia - Inst sample data: " << pMyFoo1->GetSampleData() << endl;
        cout << pMyFoo1 << endl;
    }

    FooManager* pMyFoo2 = FooManager::GetInst();
    if (pMyFoo2 != nullptr) {
        cout << "Segunda instancia? - Inst sample data: " << pMyFoo2->GetSampleData() << endl;
        cout << pMyFoo2 << endl;
    }

    // Liberar la instancia única
    FooManager::Destroy();
    return 0;
}
