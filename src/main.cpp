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

/**
 * @brief Prints the main menu of the program.
 */
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

/**
 * @brief Reads an integer from the standard input, ensuring that is valid.
 * @details This function will keep prompting the user until a valid integer is entered.
 * @return The valid integer input from the user.
 */
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

/**
 * @brief Clears the console screen. (Works for both Windows and Unix-like systems)
 * @details This function waits for a specified number of seconds before clearing the screen.
 * @param seconds The number of seconds to wait before clearing the screen.
 */
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

/**
 * @brief Creates a ProblemInstance based on the selected problem and loads data from a file.
 * @param problem The type of problem (1 for AP, 2 for GAP, 3 for UFLP).
 * @param filename The name of the file containing the instance data.
 * @return A unique pointer to the created ProblemInstance, or nullptr if an error occurs.
 * 
 * @throws std::runtime_error if the file cannot be opened or if the data is invalid.
 */
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

/**
 * @brief Creates a ProblemSolver based on the selected problem.
 * @param problem The type of problem (1 for AP, 2 for GAP, 3 for UFLP).
 * @return A unique pointer to the created ProblemSolver.
 * @throws std::invalid_argument if the problem type is not recognized.
 */
std::unique_ptr<ProblemSolver> CreateProblemSolver(int problem) {
    switch (problem) {
        case 1:
            return std::make_unique<APSolver>();
        case 2:
            return std::make_unique<GAPSolver>();
        case 3:
            return std::make_unique<UFLPSolver>();
        default:
            throw std::invalid_argument("Non valid problem in CreateProblemSolver");
    }
}

/**
 * @brief Checks if the provided filename corresponds to the expected instance type for the current problem.
 * @param currentProblem The currently selected problem (1 for AP, 2 for GAP, 3 for UFLP).
 * @param filename The name of the file to check.
 * @return true if the file is valid for the current problem, false otherwise.
 */
bool checkIfRightInstance(const int& currentProblem, std::string& filename) {
    if (filename.empty()) return false;

    std::ifstream infile(filename);
    if (!infile.is_open()) return false;

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

/// ***************************************************************************
/// *                             Main Function                               *
/// ***************************************************************************
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
            } else {
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