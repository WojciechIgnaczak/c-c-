#include <iostream>
using namespace std;

class Foo {
private:
    int id;
    static int count; 

public:
    
    Foo() {
        id =count++;
    }

    
    int getId() {
        return id;
    }
};


int Foo::count = 1;

int main() {
    Foo a, b, c, d;
    cout << a.getId() << endl; // Powinno zostać wypisane 1
    cout << b.getId() << endl; // Powinno zostać wypisane 2
    cout << c.getId() << endl; // Powinno zostać wypisane 3
    cout << d.getId() << endl; // Powinno zostać wypisane 4

    return 0;
}

