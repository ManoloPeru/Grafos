#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// Clase que representa un v�rtice en el grafo
class Vertice {
public:
    char id;  // Identificador del v�rtice (un car�cter)

    // Constructor que inicializa el v�rtice con un identificador
    Vertice(char id) : id(id) {}
};

// Clase que representa una arista entre dos v�rtices en el grafo
class Arista {
public:
    Vertice* src;   // V�rtice de origen
    Vertice* dest;  // V�rtice de destino

    // Constructor que inicializa una arista con sus v�rtices origen y destino
    Arista(Vertice* src, Vertice* dest) : src(src), dest(dest) {}
};

// Clase que representa el grafo utilizando una lista de adyacencia
class Grafo {
private:
    // Mapa que relaciona un identificador con un v�rtice
    map<char, Vertice*> vertices;

    // Mapa que relaciona un v�rtice con una lista de aristas adyacentes
    map<Vertice*, list<Arista*>> adjList;

public:
    // M�todo para insertar un v�rtice en el grafo
    void InsertarVertice(char id) {
        // Verifica si el v�rtice ya existe en el grafo
        if (vertices.find(id) == vertices.end()) {
            // Si no existe, crea un nuevo v�rtice y lo a�ade al mapa de v�rtices
            Vertice* vertice = new Vertice(id);
            vertices[id] = vertice;
            // Tambi�n inicializa una lista vac�a de aristas para el nuevo v�rtice
            adjList[vertice] = list<Arista*>();
            cout << "Vertice " << id << " insertado." << endl;
        }
        else {
            cout << "El vertice ya existe." << endl;
        }
    }

    // M�todo para insertar una arista entre dos v�rtices en el grafo
    void InsertarArista(char srcId, char destId) {
        // Verifica si ambos v�rtices existen en el grafo
        if (vertices.find(srcId) != vertices.end() && vertices.find(destId) != vertices.end()) {
            Vertice* src = vertices[srcId];
            Vertice* dest = vertices[destId];
            // Crea una nueva arista y la a�ade a la lista de aristas del v�rtice origen
            Arista* arista = new Arista(src, dest);
            adjList[src].push_back(arista);
            cout << "Arista desde " << srcId << " hacia " << destId << " insertada." << endl;
        }
        else {
            cout << "Uno o ambos vertices no existen." << endl;
        }
    }

    // M�todo para mostrar la lista de adyacencia del grafo
    void MostrarListaAdyacencia() {
        cout << "Lista de Adyacencia del Grafo:" << endl;
        // Itera sobre cada v�rtice y muestra sus aristas adyacentes
        for (auto const& par : adjList) {
            cout << par.first->id << " -> ";
            for (auto const& arista : par.second) {
                cout << arista->dest->id << " ";
            }
            cout << endl;
        }
    }

    // M�todo para obtener el tama�o del grafo (n�mero de v�rtices)
    int ObtenerTamano() {
        return vertices.size();  // Devuelve el n�mero de v�rtices en el grafo
    }

    // M�todo para eliminar un v�rtice del grafo
    void EliminarVertice(char id) {
        // Verifica si el v�rtice existe en el grafo
        if (vertices.find(id) != vertices.end()) {
            Vertice* vertice = vertices[id];
            // Elimina todas las aristas asociadas al v�rtice en la lista de adyacencia
            adjList.erase(vertice);

            // Tambi�n elimina cualquier arista que apunte al v�rtice desde otros v�rtices
            for (auto& par : adjList) {
                par.second.remove_if([vertice](Arista* arista) { return arista->dest == vertice; });
            }

            // Finalmente, elimina el v�rtice del mapa de v�rtices
            vertices.erase(id);
            delete vertice;  // Libera la memoria ocupada por el v�rtice
            cout << "Vertice " << id << " eliminado." << endl;
        }
        else {
            cout << "El vertice no existe." << endl;
        }
    }

    // M�todo para eliminar una arista entre dos v�rtices en el grafo
    void EliminarArista(char srcId, char destId) {
        // Verifica si ambos v�rtices existen en el grafo
        if (vertices.find(srcId) != vertices.end() && vertices.find(destId) != vertices.end()) {
            Vertice* src = vertices[srcId];
            Vertice* dest = vertices[destId];

            // Elimina la arista correspondiente en la lista de adyacencia del v�rtice origen
            adjList[src].remove_if([dest](Arista* arista) { return arista->dest == dest; });
            cout << "Arista desde " << srcId << " hacia " << destId << " eliminada." << endl;
        }
        else {
            cout << "Uno o ambos vertices no existen." << endl;
        }
    }

    // M�todo para eliminar todo el grafo (todos los v�rtices y aristas)
    void EliminarTodo() {
        // Elimina todas las aristas y v�rtices del grafo
        for (auto& par : adjList) {
            for (Arista* arista : par.second) {
                delete arista;  // Libera la memoria ocupada por cada arista
            }
            delete par.first;  // Libera la memoria ocupada por cada v�rtice
        }
        adjList.clear();  // Limpia la lista de adyacencia
        vertices.clear();  // Limpia el mapa de v�rtices
        cout << "Grafo eliminado por completo." << endl;
    }

    // M�todo para realizar un recorrido en anchura (BFS) desde un v�rtice dado
    void RecorridoAnchura(char startId) {
        // Verifica si el v�rtice inicial existe en el grafo
        if (vertices.find(startId) == vertices.end()) {
            cout << "El vertice no existe." << endl;
            return;
        }

        queue<Vertice*> q;  // Cola para el recorrido en anchura
        map<Vertice*, bool> visitado;  // Mapa para marcar los v�rtices visitados

        Vertice* start = vertices[startId];
        q.push(start);  // A�ade el v�rtice inicial a la cola
        visitado[start] = true;  // Marca el v�rtice inicial como visitado

        // Realiza el recorrido en anchura
        while (!q.empty()) {
            Vertice* actual = q.front();
            q.pop();
            cout << actual->id << " ";

            // A�ade los v�rtices adyacentes no visitados a la cola
            for (Arista* arista : adjList[actual]) {
                if (!visitado[arista->dest]) {
                    visitado[arista->dest] = true;
                    q.push(arista->dest);
                }
            }
        }
        cout << endl;
    }

    // M�todo para realizar un recorrido en profundidad (DFS) desde un v�rtice dado
    void RecorridoProfundidad(char startId) {
        // Verifica si el v�rtice inicial existe en el grafo
        if (vertices.find(startId) == vertices.end()) {
            cout << "El vertice no existe." << endl;
            return;
        }

        stack<Vertice*> s;  // Pila para el recorrido en profundidad
        map<Vertice*, bool> visitado;  // Mapa para marcar los v�rtices visitados

        Vertice* start = vertices[startId];
        s.push(start);  // A�ade el v�rtice inicial a la pila
        visitado[start] = true;  // Marca el v�rtice inicial como visitado

        // Realiza el recorrido en profundidad
        while (!s.empty()) {
            Vertice* actual = s.top();
            s.pop();
            cout << actual->id << " ";

            // A�ade los v�rtices adyacentes no visitados a la pila
            for (Arista* arista : adjList[actual]) {
                if (!visitado[arista->dest]) {
                    visitado[arista->dest] = true;
                    s.push(arista->dest);
                }
            }
        }
        cout << endl;
    }

    // M�todo para generar un archivo DOT
    void GenerarArchivoDOT(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo." << endl;
            return;
        }

        archivo << "digraph G {" << endl;  // Inicia el grafo en formato DOT

        for (const auto& par : adjList) {
            for (const auto& arista : par.second) {
                archivo << "    " << par.first->id << " -> " << arista->dest->id << ";" << endl;
            }
        }

        archivo << "}" << endl;  // Cierra el grafo en formato DOT
        archivo.close();
        cout << "Archivo DOT generado: " << nombreArchivo << endl;
    }
};

int main() {
    Grafo grafo;  // Instancia del grafo
    char opcion;

    // Bucle que muestra el men� y procesa la opci�n seleccionada
    do {
        cout << "=========================================================" << endl;
        cout << "1. Insertar vertice" << endl;
        cout << "2. Insertar arista" << endl;
        cout << "3. Obtener tamano" << endl;
        cout << "4. Mostrar lista de adyacencia" << endl;
        cout << "5. Eliminar vertice" << endl;
        cout << "6. Eliminar arista" << endl;
        cout << "7. Eliminar todo" << endl;
        cout << "8. Recorrido en anchura" << endl;
        cout << "9. Recorrido en profundidad" << endl;
        cout << "A. Genera el archivo DOT" << endl;
        cout << "X. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << "=========================================================" << endl;

        // Procesa la opci�n seleccionada
        switch (opcion) {
        case '1': {
            char id;
            cout << "Ingrese el ID del vertice (A-Z): ";
            cin >> id;
            grafo.InsertarVertice(id);  // Inserta un nuevo v�rtice en el grafo
            break;
        }
        case '2': {
            char src, dest;
            cout << "Ingrese el ID del vertice origen (A-Z): ";
            cin >> src;
            cout << "Ingrese el ID del vertice destino (A-Z): ";
            cin >> dest;
            grafo.InsertarArista(src, dest);  // Inserta una nueva arista entre dos v�rtices
            break;
        }
        case '3': {
            cout << "Tamano del grafo: " << grafo.ObtenerTamano() << endl;  // Muestra el tama�o del grafo
            break;
        }
        case '4': {
            grafo.MostrarListaAdyacencia();  // Muestra la lista de adyacencia del grafo
            break;
        }
        case '5': {
            char id;
            cout << "Ingrese el ID del vertice a eliminar (A-Z): ";
            cin >> id;
            grafo.EliminarVertice(id);  // Elimina un v�rtice del grafo
            break;
        }
        case '6': {
            char src, dest;
            cout << "Ingrese el ID del vertice origen (A-Z): ";
            cin >> src;
            cout << "Ingrese el ID del vertice destino (A-Z): ";
            cin >> dest;
            grafo.EliminarArista(src, dest);  // Elimina una arista entre dos v�rtices
            break;
        }
        case '7': {
            grafo.EliminarTodo();  // Elimina todo el grafo
            break;
        }
        case '8': {
            char startId;
            cout << "Ingrese el ID del vertice inicial para el recorrido en anchura (A-Z): ";
            cin >> startId;
            grafo.RecorridoAnchura(startId);  // Realiza un recorrido en anchura desde un v�rtice dado
            break;
        }
        case '9': {
            char startId;
            cout << "Ingrese el ID del vertice inicial para el recorrido en profundidad (A-Z): ";
            cin >> startId;
            grafo.RecorridoProfundidad(startId);  // Realiza un recorrido en profundidad desde un v�rtice dado
            break;
        }
        case 'A': {
            cout << "Generando el archivo DOT..." << endl;  
            grafo.GenerarArchivoDOT("grafo.dot");
            cout << "El archivo grafo.dot se ha creado en la Carpeta Grafos" << endl;
            cout << "Puede abrir el archivo Usando Microsoft Word o Libre Office Writer..." << endl;
            //Instala Graphviz: https://graphviz.org/download/
            cout << "Puedes ejecutar el siguiente comando en tu terminal para convertir el archivo DOT en un archivo PNG:" << endl;
            cout << "dot -Tpng grafo.dot -o grafo.png" << endl;
            break;
        }
        case 'X': {
            cout << "Saliendo..." << endl;  // Opci�n para salir del programa
            break;
        }
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;  // Mensaje de error para opciones inv�lidas
        }
    } while (opcion != 'X');  // El bucle se repite hasta que el usuario elige salir

    return 0;
}
