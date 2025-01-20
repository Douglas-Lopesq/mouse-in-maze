#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

class Maze {
private:
    vector<string> maze;
    const char wall = '1';

    //cria as paredes externas
    void loadWalls() {
        string wallRow(maze[0].size() + 2, wall);
        for (auto& row : maze) {
            row = wall + row + wall;
        }
        maze.insert(maze.begin(), wallRow);
        maze.push_back(wallRow);
    }

public:
    // Carrega o labirinto pelo arquivo .txt
    void loadMaze(istream& input) {
        string line;
        while (getline(input, line)) {
            maze.push_back(line);
        }
        loadWalls();
    }

    // Lê o labirinto do terminal
    void loadMazeFromTerminal() {
        cout << "Insira o labirinto linha por linha. Digite uma linha vazia para terminar:\n";
        string line;
        while (true) {
            getline(cin, line);
            if (line.empty()) break; // Linha vazia termina a entrada
            maze.push_back(line);
        }
        loadWalls(); // Adiciona as paredes externas
    }

    // Exibe o labirinto carregado
    void displayMaze() {
        for (const auto& row : maze) {
            cout << row << '\n';
        }
    }
};

int main() {
    Maze maze;
    int option;

    // Menu inicial
    cout << "<!Bem vindo a Mouse in Maze!>\n";
    cout << "1. Construa  seu labirinto\n";
    cout << "2. Carregue um labirinto ja construido\n";
    cout << "Digite sua opcao: ";
    cin >> option;
    cin.ignore();

    if (option == 1) {
        // Insere o labirinto diretamente pelo terminal
        maze.loadMazeFromTerminal();
    } else if (option == 2) {
        // Lê o labirinto de um arquivo
        string filename;
        cout << "Digite o nome do arquivo: ";
        getline(cin, filename);

        ifstream file(filename);
        if (!file) {
            cerr << "Erro ao abrir o arquivo!\n";
            return 1;
        }

        maze.loadMaze(file); // Carrega o labirinto a partir do arquivo
        file.close();
    } else {
        cout << "Opção inválida!\n";
        return 1;
    }

    // Exibe o labirinto carregado
    cout << "Labirinto com paredes externas:\n";
    maze.displayMaze();

    return 0;
}
