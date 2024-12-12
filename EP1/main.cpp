#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <ctime>

using namespace std;

struct Transaccion {
    string tipo;
    double monto;
    time_t fecha;
};

class OperacionesCuentas {
private:
    static shared_ptr<OperacionesCuentas> instancia;
    map<string, double> tasasInteres;
    map<int, vector<pair<string, double>>> cuentasClientes; // idCliente -> lista de cuentas y saldos
    map<int, vector<Transaccion>> historialTransacciones;   // idCliente -> historial de transacciones

    OperacionesCuentas() {
        // Inicializamos las tasas de interés por defecto
        tasasInteres["ahorro"] = 0.5;
        tasasInteres["joven"] = 1.0;
        tasasInteres["pluss"] = 2.0;
        tasasInteres["empresarial"] = 3.0;
        tasasInteres["tarjeta_credito"] = 15.0;
        tasasInteres["prestamo_personal"] = 8.0; // Base
        tasasInteres["transferencia"] = 0.5;    // Base
    }

public:
    static shared_ptr<OperacionesCuentas> getInstancia() {
        if (!instancia)
            instancia = shared_ptr<OperacionesCuentas>(new OperacionesCuentas);
        return instancia;
    }

    void agregarTasa(const string &tipoCuenta, double tasa) {
        tasasInteres[tipoCuenta] = tasa;
    }

    double calcularInteres(const string &tipoCuenta, double monto) {
        if (tasasInteres.find(tipoCuenta) != tasasInteres.end()) {
            return monto * tasasInteres[tipoCuenta] / 100;
        }
        cerr << "Tipo de cuenta no encontrado.\n";
        return 0.0;
    }

    void mostrarTasas() {
        cout << "Tasas de interés por tipo de cuenta:\n";
        for (const auto &tasa : tasasInteres) {
            cout << "Tipo: " << tasa.first << " - Tasa: " << tasa.second << "%\n";
        }
    }

    void agregarCuenta(int idCliente, const string &tipoCuenta, double saldoInicial) {
        cuentasClientes[idCliente].emplace_back(tipoCuenta, saldoInicial);
    }

    void registrarTransaccion(int idCliente, const string &tipoCuenta, const string &tipoTransaccion, double monto) {
        Transaccion transaccion = {tipoTransaccion, monto, time(0)};
        historialTransacciones[idCliente].push_back(transaccion);
        for (auto &cuenta : cuentasClientes[idCliente]) {
            if (cuenta.first == tipoCuenta) {
                cuenta.second += monto;
                break;
            }
        }
    }

    void mostrarCuentas(int idCliente) {
        if (cuentasClientes.find(idCliente) != cuentasClientes.end()) {
            cout << "Cuentas del cliente " << idCliente << ":\n";
            for (const auto &cuenta : cuentasClientes[idCliente]) {
                cout << "Tipo: " << cuenta.first << " - Saldo: " << cuenta.second << "\n";
            }
        } else {
            cout << "No se encontraron cuentas para el cliente " << idCliente << ".\n";
        }
    }

    void mostrarHistorial(int idCliente, time_t fechaCorte) {
        if (historialTransacciones.find(idCliente) != historialTransacciones.end()) {
            cout << "Historial de transacciones hasta la fecha " << ctime(&fechaCorte) << ":\n";
            for (const auto &transaccion : historialTransacciones[idCliente]) {
                if (difftime(fechaCorte, transaccion.fecha) >= 0) {
                    cout << "Tipo: " << transaccion.tipo << " - Monto: " << transaccion.monto << " - Fecha: " << ctime(&transaccion.fecha);
                }
            }
        } else {
            cout << "No se encontraron transacciones para el cliente " << idCliente << ".\n";
        }
    }

    double calcularEstadoCuenta(int idCliente, const string &tipoCuenta) {
        double total = 0.0;
        if (cuentasClientes.find(idCliente) != cuentasClientes.end()) {
            for (const auto &cuenta : cuentasClientes[idCliente]) {
                if (tipoCuenta == "global" || cuenta.first == tipoCuenta) {
                    total += cuenta.second;
                }
            }
        } else {
            cerr << "Cliente no encontrado.\n";
        }
        return total;
    }

    void liquidarDeuda(int idCliente, const string &tipoCuenta, double monto) {
        if (cuentasClientes.find(idCliente) != cuentasClientes.end()) {
            for (auto &cuenta : cuentasClientes[idCliente]) {
                if (cuenta.first == tipoCuenta) {
                    cuenta.second -= monto;
                    cout << "Deuda liquidada. Nuevo saldo en " << tipoCuenta << ": " << cuenta.second << "\n";
                    registrarTransaccion(idCliente, tipoCuenta, "Liquidacion de deuda", -monto);
                    return;
                }
            }
        }
        cerr << "No se encontró la cuenta especificada.\n";
    }

    void generarEstadoDeCuenta(int idCliente, const string &tipoCuenta = "global", time_t fechaCorte = time(0)) {
        cout << "Estado de cuenta generado el " << ctime(&fechaCorte) << "\n";
        double total = calcularEstadoCuenta(idCliente, tipoCuenta);
        cout << "Estado de cuenta para el cliente " << idCliente << " (" << tipoCuenta << "): " << total << "\n";
        mostrarHistorial(idCliente, fechaCorte);
    }
};

shared_ptr<OperacionesCuentas> OperacionesCuentas::instancia = nullptr;

int main() {
    auto operaciones = OperacionesCuentas::getInstancia();

    operaciones->mostrarTasas();

    int idCliente = 1;
    operaciones->agregarCuenta(idCliente, "ahorro", 5000.0);
    operaciones->agregarCuenta(idCliente, "tarjeta_credito", -2000.0);

    operaciones->registrarTransaccion(idCliente, "ahorro", "Deposito", 2000.0);
    operaciones->registrarTransaccion(idCliente, "tarjeta_credito", "Compra", -500.0);

    operaciones->mostrarCuentas(idCliente);

    time_t fechaCorte = time(0);
    operaciones->generarEstadoDeCuenta(idCliente, "global", fechaCorte);
    operaciones->liquidarDeuda(idCliente, "tarjeta_credito", 500.0);
    operaciones->mostrarCuentas(idCliente);

    return 0;
}
