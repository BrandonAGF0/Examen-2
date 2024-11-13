#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>

using namespace std;
	

	
// almacena datos de candidatos

struct Candidato {
    int id;
    string nombre;
    string partido;
    int votos;
};

class SistemaVotacion {
private:
    vector<Candidato> candidatos;
    bool votacionIniciada;
    int totalVotos;

    // Limpiar la pantalla
    void limpiarPantalla() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    // entrada de texto
    string obtenerEntradaValida() {
        string entrada;
        getline(cin, entrada);
        while (entrada.empty()) {
            cout << "La entrada no puede estar vacía. Intente nuevamente: ";
            getline(cin, entrada);
        }
        return entrada;
    }

    // entrada numérica
    int obtenerNumeroValido() {
        int numero;
        while (!(cin >> numero)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Por favor, ingrese un número válido: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return numero;
    }

public:
    // Constructor
    SistemaVotacion() {
        votacionIniciada = false;
        totalVotos = 0;
    }

    // Menú
    void ejecutar() {
        int opcion;
        do {
            limpiarPantalla();
            cout << "\n=== SISTEMA DE VOTACIÓN ===" << endl;
            cout << "1. Inicio" << endl;
            cout << "2. Ingresar Candidatos" << endl;
            cout << "3. Votaciones" << endl;
            cout << "4. Resultados" << endl;
            cout << "5. Salir" << endl;
            cout << "Seleccione una opción: ";

            opcion = obtenerNumeroValido();

            switch (opcion) {
                case 1: iniciarSistema(); break;
                case 2: ingresarCandidatos(); break;
                case 3: realizarVotacion(); break;
                case 4: mostrarResultados(); break;
                case 5: cout << "¡Gracias por usar el sistema!" << endl; break;
                default: cout << "Opción no válida" << endl;
            }
            
            if (opcion != 5) {
                cout << "\nPresione Enter para continuar...";
                cin.get();
            }
        } while (opcion != 5);
    }

    // Iniciar sistema
    void iniciarSistema() {
        if (!votacionIniciada) {
            candidatos.clear();
            totalVotos = 0;
            votacionIniciada = true;
            cout << "Sistema iniciado correctamente" << endl;
        } else {
            cout << "El sistema ya está iniciado" << endl;
        }
    }

    // candidatos
    void ingresarCandidatos() {
        if (!votacionIniciada) {
            cout << "Debe iniciar el sistema primero" << endl;
            return;
        }

        cout << "Ingrese el número de candidatos: ";
        int numCandidatos = obtenerNumeroValido();

        for (int i = 0; i < numCandidatos; i++) {
            Candidato candidato;
            candidato.id = i + 1;
            candidato.votos = 0;

            cout << "\nCandidato " << (i + 1) << endl;
            cout << "Nombre: ";
            candidato.nombre = obtenerEntradaValida();

            cout << "Partido: ";
            candidato.partido = obtenerEntradaValida();

            candidatos.push_back(candidato);
        }
    }

    // votación
    void realizarVotacion() {
        if (candidatos.empty()) {
            cout << "No hay candidatos registrados" << endl;
            return;
        }

        cout << "\nCANDIDATOS DISPONIBLES:" << endl;
        for (size_t i = 0; i < candidatos.size(); i++) {
            cout << candidatos[i].id << ". " 
                 << candidatos[i].nombre << " - " 
                 << candidatos[i].partido << endl;
        }

        cout << "\nIngrese el número del candidato para votar (0 para terminar): ";
        int voto = obtenerNumeroValido();

        while (voto != 0) {
            if (voto > 0 && voto <= static_cast<int>(candidatos.size())) {
                candidatos[voto - 1].votos++;
                totalVotos++;
                cout << "Voto registrado exitosamente" << endl;
            } else {
                cout << "Candidato no válido" << endl;
            }

            cout << "\nIngrese el número del candidato para votar (0 para terminar): ";
            voto = obtenerNumeroValido();
        }
    }

    // resultados
    void mostrarResultados() {
        if (totalVotos == 0) {
            cout << "No hay votos registrados" << endl;
            return;
        }

        cout << "\n=== RESULTADOS DE LA VOTACIÓN ===" << endl;
        cout << setw(5) << "ID" << setw(20) << "Nombre" << setw(20) << "Partido" 
             << setw(10) << "Votos" << setw(15) << "Porcentaje" << endl;
        cout << string(70, '-') << endl;

        int maxVotos = 0;
        size_t indiceGanador = 0;

        for (size_t i = 0; i < candidatos.size(); i++) {
            float porcentaje = (static_cast<float>(candidatos[i].votos) / totalVotos) * 100;
            cout << setw(5) << candidatos[i].id 
                 << setw(20) << candidatos[i].nombre 
                 << setw(20) << candidatos[i].partido 
                 << setw(10) << candidatos[i].votos 
                 << setw(14) << fixed << setprecision(2) << porcentaje << "%" << endl;

            if (candidatos[i].votos > maxVotos) {
                maxVotos = candidatos[i].votos;
                indiceGanador = i;
            }
        }

        cout << "\nTotal de votos: " << totalVotos << endl;
        cout << "\nGANADOR: " << candidatos[indiceGanador].nombre 
             << " con " << candidatos[indiceGanador].votos << " votos" << endl;
    }
};

int main() {
    SistemaVotacion sistema;
    sistema.ejecutar();
    return 0;
}

