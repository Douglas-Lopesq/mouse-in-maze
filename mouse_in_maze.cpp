#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Maze {
private:
    vector<string> maze;
    const char wall = '1';

    // Adiciona paredes externas ao labirinto
    void loadWalls() {
        if (maze.empty()) return;
        string wallRow(maze[0].size() + 2, wall);
        for (auto& row : maze) {
            row = wall + row + wall;
        }
        maze.insert(maze.begin(), wallRow);
        maze.push_back(wallRow);
    }

    // Define o ponto inicial e final do labirinto
    void setStartAndExit() {
        if (maze.empty()) return;
        maze[0][0] = 'm'; // Ponto inicial (rato)
        maze[maze.size() - 1][maze[0].size() - 1] = 'e'; // Ponto final (saída)
    }

public:
    // Carrega o labirinto de um arquivo no estilo especificado
    void loadMazeFromFile(const string& filename) {
        maze.clear();
        string line;
        ifstream myfile(filename);

        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                if (line.find_first_not_of("01") == string::npos) { // Filtra linhas inválidas
                    maze.push_back(line);
                } else {
                    cout << "Linha invalida encontrada e ignorada: " << line << endl;
                }
            }
            myfile.close();
        } else {
            cerr << "Erro ao abrir o arquivo\n";
            return;
        }

        if (!maze.empty()) {
            setStartAndExit(); // Define os pontos inicial e final
            loadWalls();       // Adiciona as paredes externas
        }
    }

    // Carrega o labirinto do terminal
    void loadMazeFromTerminal(int rows, int cols) {
        maze.clear();
        string line;

        cout << "Digite as linhas do labirinto (somente 0 e 1):\n";
        for (int i = 0; i < rows; ++i) {
            while (true) {
                cout << "Linha " << i + 1 << ": ";
                getline(cin, line);

                // Valida se a linha contém exatamente `cols` caracteres e somente '0' ou '1'
                if (line.size() == static_cast<size_t>(cols) && line.find_first_not_of("01") == string::npos) {
                    maze.push_back(line);
                    break; // Linha válida
                } else {
                    cout << "Entrada invalida! Insira exatamente " << cols << " caracteres (somente 0 e 1).\n";
                }
            }
        }

        // Garante que (0,0) e (n-1,n-1) estejam livres e marcados corretamente
        maze[0][0] = 'm';
        maze[rows - 1][cols - 1] = 'e';

        loadWalls(); // Adiciona as paredes externas
    }

    // Exibe o labirinto na tela
    void displayMaze() {
        for (const auto& row : maze) {
            cout << row << '\n';
        }
    }
};

int main() {
    Maze maze;
    int option;

    cout << "<!Bem vindo a Mouse in Maze!>\n";
    cout << "1. Digitar o labirinto no terminal\n";
    cout << "2. Carregar o labirinto de um arquivo\n";
    cout << "Digite sua opcao: ";
    cin >> option;
    cin.ignore();

    if (option == 1) {
        int rows, cols;
        cout << "Digite o numero de linhas: ";
        cin >> rows;
        cout << "Digite o numero de colunas: ";
        cin >> cols;
        cin.ignore(); // Limpa o buffer para a entrada das linhas do labirinto

        maze.loadMazeFromTerminal(rows, cols);
    } else if (option == 2) {
        string filename; // pega o nome do arquivo inserido no terminal
        cout << "Digite o nome do arquivo: ";
        getline(cin, filename); // Nome fixo para o arquivo
        maze.loadMazeFromFile(filename);
    } else {
        cout << "Opcao invalida!\n";
        return 1;
    }

    cout << "Labirinto com paredes externas:\n";
    maze.displayMaze();

    return 0;
}
