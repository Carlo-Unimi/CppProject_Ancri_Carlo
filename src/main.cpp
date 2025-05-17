#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <limits>

#include "APInstance.h"
#include "GAPInstance.h"
#include "UFLPInstance.h"

#include "APSolver.h"
#include "GAPSolver.h"
#include "UFLPSolver.h"

#include "ProblemInstance.h"
#include "ProblemSolution.h"
#include "ProblemSolver.h"


// prints the menu
void printMainMenu() {
    std::cout
      << " ============ MENU ============\n"
      << "1) Select problem (AP, GAP, UFLP)\n"
      << "2) Import instance and solve it\n"
      << "3) Print solution\n"
      << "4) Export solution to a file\n"
      << "5) Exit the program\n"
      << "Choose an option: ";
}

// legge un valore da tastiera finchè non è un numero
int safeReadInt() {
    int choice;
    while (true) {
        if (std::cin >> choice) {
            return choice;
        } else {
            std::cout << "[ERROR] Non valid input.\nOption: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// clears the terminal after given delay
void clearScreen(int seconds) {
    if (seconds > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }
  #ifdef _WIN32
    std::system("cls");
  #else
    std::system("clear");
  #endif
}

// funzione generale che crea un'istanza del problema scelto
std::unique_ptr<ProblemInstance> CreateProblemInstance(int problem, const std::string& filename) {
    std::unique_ptr<ProblemInstance> instance;

    try {
        switch (problem) {
        case 1:
            instance = std::make_unique<APInstance>();
            break;
        case 2:
            instance = std::make_unique<GAPInstance>();
            break;
        case 3:
            instance = std::make_unique<UFLPInstance>();
            break;
        default:
            std::cerr << "[ERROR] Non valid problem.\n";
            return nullptr;
        }
        
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            std::cerr << "[ERROR] Unable to open file: " << filename << "\n";
            return nullptr;
        }
        instance->loadFromFile(filename);
        infile.close();

    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Error loading file: " << e.what() << "\n";
        return nullptr;
    }
    return instance;
}

std::unique_ptr<ProblemSolver> CreateProblemSolver(int problem) {
    switch (problem) {
        case 1:
            return std::make_unique<APSolver>();
        case 2:
            return std::make_unique<GAPSolver>();
        case 3:
            return std::make_unique<UFLPSolver>();
        default:
            throw std::invalid_argument("Tipo di problema non valido in CreateProblemSolver");
    }
}

bool checkIfRightInstance(const int& currentProblem, std::string& filename) {
    if (filename.empty()) return false; // se la stringa è vuota

    std::ifstream infile(filename);
    if (!infile.is_open()) return false; // se il file è inesistente

    std::string line;

    getline(infile, line);
    infile.close();

    switch(currentProblem) {
        case 1: return line[6] == 'A';
        case 2: return line[6] == 'G';
        case 3: return line[6] == 'U';
        default: return false;
    }
}


int main() {
    int currentProblem = 0, running = 1;
    std::unique_ptr<ProblemInstance> instance;
    std::unique_ptr<ProblemSolution> solution;
    std::unique_ptr<ProblemSolver> solver;

    while (running) {
        clearScreen(0);
        printMainMenu();
        int op = safeReadInt();

        switch (op) {
        case 1: {
            clearScreen(0);
            std::cout << "Choose problem:\n"
                      << "  1) Assignment Problem (AP)\n"
                      << "  2) Generalized Assignment Problem (GAP)\n"
                      << "  3) Uncapacitated Facility Location (UFLP)\n"
                      << "Option: ";
            int p = safeReadInt();
            if (p >= 1 && p <= 3) {
                if (currentProblem != p) {
                    instance = nullptr;
                    solution = nullptr;
                }
                currentProblem = p;
                solver = CreateProblemSolver(currentProblem);
                std::cout << "Current problem selected: " << p << ".\n";
            } else {
                std::cout << "[ERROR] Problem not recognized. Return to main menu.\n";
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }
        case 2: {
            if (currentProblem == 0) {
                std::cout << "[ERROR] First select a problem (option 1).\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
            std::cout << "Select the istance's file name: ";
            std::string filename;
            std::cin >> filename;
            if (checkIfRightInstance(currentProblem, filename)) {
                instance = CreateProblemInstance(currentProblem, filename);
                solution = solver->solve(instance.get());
                std::cout << "Instance imported and resolved successfully.\n";
            } else { // se non è del tipo giusto
                std::cout << "[ERROR] Wrong type of instance, retry.\n";
            }
            
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }
        case 3: {
            
            if (!solution) {
                std::cout << "[ERROR] No solution available. Please resolve an instance first.\n";
            } else {
                clearScreen(0);
                std::cout << *solution;
            }
            std::cout << "Press enter to continue...";
            std::cin.ignore(); 
            std::cin.get();
            break;
        }
        case 4: {
            if (!solution) {
                std::cout << "[ERROR] No solution to export.\n";
            } else {
                std::cout << "\nInsert the output file name: ";
                std::string outfile;
                std::cin >> outfile;
                std::ofstream ofs(outfile);
                ofs << *solution;
                ofs.close();
                std::cout << "Solution exported in: " << outfile << ".\n";
            }
            std::cout << "Press enter to continue...";
            std::cin.ignore(); std::cin.get();
            break;
        }
        case 5:
            running = 0;
            break;
        default:
            std::cout << "[ERROR] Non-existent option. Retry.\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }

    std::cout << "\nProgram terminated.\n";
    return 0;
}