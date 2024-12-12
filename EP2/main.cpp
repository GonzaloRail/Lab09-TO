#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;

// Clase base abstracta que define el método clone
class Planta {
protected:
    string nombre;
    string tipo;

public:
    Planta(const string &nombre, const string &tipo) : nombre(nombre), tipo(tipo) {}
    virtual ~Planta() {}

    virtual shared_ptr<Planta> clone() const = 0;

    void mostrarInfo() const {
        cout << "Planta: " << nombre << ", Tipo: " << tipo << endl;
    }
};

// Clases concretas para cada sector
class Trepadora : public Planta {
public:
    Trepadora(const string &nombre) : Planta(nombre, "Trepadora") {}

    shared_ptr<Planta> clone() const override {
        return make_shared<Trepadora>(*this);
    }
};

class ArbolNormal : public Planta {
public:
    ArbolNormal(const string &nombre) : Planta(nombre, "Arbol Normal") {}

    shared_ptr<Planta> clone() const override {
        return make_shared<ArbolNormal>(*this);
    }
};

class Ornamental : public Planta {
public:
    Ornamental(const string &nombre) : Planta(nombre, "Ornamental") {}

    shared_ptr<Planta> clone() const override {
        return make_shared<Ornamental>(*this);
    }
};

class Bonsai : public Planta {
public:
    Bonsai(const string &nombre) : Planta(nombre, "Bonsai") {}

    shared_ptr<Planta> clone() const override {
        return make_shared<Bonsai>(*this);
    }
};

// Clase que gestiona el prototipo
class Vivero {
private:
    map<string, shared_ptr<Planta>> prototipos;

public:
    void registrarPrototipo(const string &tipo, shared_ptr<Planta> planta) {
        prototipos[tipo] = planta;
    }

    shared_ptr<Planta> crearPlanta(const string &tipo) {
        if (prototipos.find(tipo) != prototipos.end()) {
            return prototipos[tipo]->clone();
        }
        cerr << "Tipo de planta no registrado." << endl;
        return nullptr;
    }
};

int main() {
    Vivero vivero;

    // Registrar prototipos
    vivero.registrarPrototipo("Trepadora", make_shared<Trepadora>("Hiedra"));
    vivero.registrarPrototipo("Arbol Normal", make_shared<ArbolNormal>("Roble"));
    vivero.registrarPrototipo("Ornamental", make_shared<Ornamental>("Rosa"));
    vivero.registrarPrototipo("Bonsai", make_shared<Bonsai>("Arce Japones"));

    // Crear plantas utilizando prototipos
    auto planta1 = vivero.crearPlanta("Trepadora");
    auto planta2 = vivero.crearPlanta("Bonsai");

    if (planta1) planta1->mostrarInfo();
    if (planta2) planta2->mostrarInfo();

    return 0;
}
