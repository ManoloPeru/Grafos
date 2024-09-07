#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// Clase que representa un vértice en el grafo
class Vertice {
public:
    char id;  // Identificador del vértice (un carácter)

    // Constructor que inicializa el vértice con un identificador
    Vertice(char id) : id(id) {}
};

// Clase que representa una arista entre dos vértices en el grafo
class Arista {
public:
    Vertice* src;   // Vértice de origen
    Vertice* dest;  // Vértice de destino

    // Constructor que inicializa una arista con sus vértices origen y destino
    Arista(Vertice* src, Vertice* dest) : src(src), dest(dest) {}
};

// Clase que representa el grafo utilizando una lista de adyacencia
class Grafo {
private:
    // Mapa que relaciona un identificador con un vértice
    map<char, Vertice*> vertices;

    // Mapa que relaciona un vértice con una lista de aristas adyacentes
    map<Vertice*, list<Arista*>> adjList;

public:
    // Método para insertar un vértice en el grafo
    void InsertarVertice(char id) {
        // Verifica si el vértice ya existe en el grafo
        if (vertices.find(id) == vertices.end()) {
            // Si no existe, crea un nuevo vértice y lo añade al mapa de vértices
            Vertice* vertice = new Vertice(id);
            vertices[id] = vertice;
            // También inicializa una lista vacía de aristas para el nuevo vértice
            adjList[vertice] = list<Arista*>();
            cout << "Vertice " << id << " insertado." << endl;
        }
        else {
            cout << "El vertice ya existe." << endl;
        }
    }

    // Método para insertar una arista entre dos vértices en el grafo
    void InsertarArista(char srcId, char destId) {
        // Verifica si ambos vértices existen en el grafo
        if (vertices.find(srcId) != vertices.end() && vertices.find(destId) != vertices.end()) {
            Vertice* src = vertices[srcId];
            Vertice* dest = vertices[destId];
            // Crea una nueva arista y la añade a la lista de aristas del vértice origen
            Arista* arista = new Arista(src, dest);
            adjList[src].push_back(arista);
            cout << "Arista desde " << srcId << " hacia " << destId << " insertada." << endl;
        }
        else {
            cout << "Uno o ambos vertices no existen." << endl;
        }
    }

    // Método para mostrar la lista de adyacencia del grafo
    void MostrarListaAdyacencia() {
        cout << "Lista de Adyacencia del Grafo:" << endl;
        // Itera sobre cada vértice y muestra sus aristas adyacentes
        for (auto const& par : adjList) {
            cout << par.first->id << " -> ";
            for (auto const& arista : par.second) {
                cout << arista->dest->id << " ";
            }
            cout << endl;
        }
    }

    // Método para obtener el tamaño del grafo (número de vértices)
    int ObtenerTamano() {
        return vertices.size();  // Devuelve el número de vértices en el grafo
    }

    // Método para eliminar un vértice del grafo
    void EliminarVertice(char id) {
        // Verifica si el vértice existe en el grafo
        if (vertices.find(id) != vertices.end()) {
            Vertice* vertice = vertices[id];
            // Elimina todas las aristas asociadas al vértice en la lista de adyacencia
            adjList.erase(vertice);

            // También elimina cualquier arista que apunte al vértice desde otros vértices
            for (auto& par : adjList) {
                par.second.remove_if([vertice](Arista* arista) { return arista->dest == vertice; });
            }

            // Finalmente, elimina el vértice del mapa de vértices
            vertices.erase(id);
            delete vertice;  // Libera la memoria ocupada por el vértice
            cout << "Vertice " << id << " eliminado." << endl;
        }
        else {
            cout << "El vertice no existe." << endl;
        }
    }

    // Método para eliminar una arista entre dos vértices en el grafo
    void EliminarArista(char srcId, char destId) {
        // Verifica si ambos vértices existen en el grafo
        if (vertices.find(srcId) != vertices.end() && vertices.find(destId) != vertices.end()) {
            Vertice* src = vertices[srcId];
            Vertice* dest = vertices[destId];

            // Elimina la arista correspondiente en la lista de adyacencia del vértice origen
            adjList[src].remove_if([dest](Arista* arista) { return arista->dest == dest; });
            cout << "Arista desde " << srcId << " hacia " << destId << " eliminada." << endl;
        }
        else {
            cout << "Uno o ambos vertices no existen." << endl;
        }
    }

    // Método para eliminar todo el grafo (todos los vértices y aristas)
    void EliminarTodo() {
        // Elimina todas las aristas y vértices del grafo
        for (auto& par : adjList) {
            for (Arista* arista : par.second) {
                delete arista;  // Libera la memoria ocupada por cada arista
            }
            delete par.first;  // Libera la memoria ocupada por cada vértice
        }
        adjList.clear();  // Limpia la lista de adyacencia
        vertices.clear();  // Limpia el mapa de vértices
        cout << "Grafo eliminado por completo." << endl;
    }

    // Método para realizar un recorrido en anchura (BFS) desde un vértice dado
    void RecorridoAnchura(char startId) {
        // Verifica si el vértice inicial existe en el grafo
        if (vertices.find(startId) == vertices.end()) {
            cout << "El vertice no existe." << endl;
            return;
        }

        queue<Vertice*> q;  // Cola para el recorrido en anchura
        map<Vertice*, bool> visitado;  // Mapa para marcar los vértices visitados

        Vertice* start = vertices[startId];
        q.push(start);  // Añade el vértice inicial a la cola
        visitado[start] = true;  // Marca el vértice inicial como visitado

        // Realiza el recorrido en anchura
        while (!q.empty()) {
            Vertice* actual = q.front();
            q.pop();
            cout << actual->id << " ";

            // Añade los vértices adyacentes no visitados a la cola
            for (Arista* arista : adjList[actual]) {
                if (!visitado[arista->dest]) {
                    visitado[arista->dest] = true;
                    q.push(arista->dest);
                }
            }
        }
        cout << endl;
    }

    // Método para realizar un recorrido en profundidad (DFS) desde un vértice dado
    void RecorridoProfundidad(char startId) {
        // Verifica si el vértice inicial existe en el grafo
        if (vertices.find(startId) == vertices.end()) {
            cout << "El vertice no existe." << endl;
            return;
        }

        stack<Vertice*> s;  // Pila para el recorrido en profundidad
        map<Vertice*, bool> visitado;  // Mapa para marcar los vértices visitados

        Vertice* start = vertices[startId];
        s.push(start);  // Añade el vértice inicial a la pila
        visitado[start] = true;  // Marca el vértice inicial como visitado

        // Realiza el recorrido en profundidad
        while (!s.empty()) {
            Vertice* actual = s.top();
            s.pop();
            cout << actual->id << " ";

            // Añade los vértices adyacentes no visitados a la pila
            for (Arista* arista : adjList[actual]) {
                if (!visitado[arista->dest]) {
                    visitado[arista->dest] = true;
                    s.push(arista->dest);
                }
            }
        }
        cout << endl;
    }

    // Método para generar un archivo DOT
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

    // Bucle que muestra el menú y procesa la opción seleccionada
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

        // Procesa la opción seleccionada
        switch (opcion) {
        case '1': {
            char id;
            cout << "Ingrese el ID del vertice (A-Z): ";
            cin >> id;
            grafo.InsertarVertice(id);  // Inserta un nuevo vértice en el grafo
            break;
        }
        case '2': {
            char src, dest;
            cout << "Ingrese el ID del vertice origen (A-Z): ";
            cin >> src;
            cout << "Ingrese el ID del vertice destino (A-Z): ";
            cin >> dest;
            grafo.InsertarArista(src, dest);  // Inserta una nueva arista entre dos vértices
            break;
        }
        case '3': {
            cout << "Tamano del grafo: " << grafo.ObtenerTamano() << endl;  // Muestra el tamaño del grafo
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
            grafo.EliminarVertice(id);  // Elimina un vértice del grafo
            break;
        }
        case '6': {
            char src, dest;
            cout << "Ingrese el ID del vertice origen (A-Z): ";
            cin >> src;
            cout << "Ingrese el ID del vertice destino (A-Z): ";
            cin >> dest;
            grafo.EliminarArista(src, dest);  // Elimina una arista entre dos vértices
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
            grafo.RecorridoAnchura(startId);  // Realiza un recorrido en anchura desde un vértice dado
            break;
        }
        case '9': {
            char startId;
            cout << "Ingrese el ID del vertice inicial para el recorrido en profundidad (A-Z): ";
            cin >> startId;
            grafo.RecorridoProfundidad(startId);  // Realiza un recorrido en profundidad desde un vértice dado
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
            cout << "Saliendo..." << endl;  // Opción para salir del programa
            break;
        }
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;  // Mensaje de error para opciones inválidas
        }
    } while (opcion != 'X');  // El bucle se repite hasta que el usuario elige salir

    return 0;
}
