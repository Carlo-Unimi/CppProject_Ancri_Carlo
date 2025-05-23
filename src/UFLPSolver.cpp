#include "UFLPSolver.h"
#include "UFLPInstance.h"
#include "UFLPSolution.h"

#include <stdexcept>
#include <limits>
#include <vector>
#include <algorithm>

std::unique_ptr<ProblemSolution> UFLPSolver::solve(const ProblemInstance* instance) {
    // 1. Cast sicuro a UFLPInstance
    const UFLPInstance* uflpInst = dynamic_cast<const UFLPInstance*>(instance);
    if (!uflpInst) {
        throw std::invalid_argument("UFLPSolver::solve richiede un UFLPInstance valido");
    }

    // 2. Estrai dimensioni e dati
    int m = uflpInst->getNumFacilities();  // numero depositi
    int n = uflpInst->getNumClients();   // numero clienti
    const auto& cost = uflpInst->getServiceCosts();      // m x n (costi trasporto)
    const auto& fixedCost = uflpInst->getOpeningCosts(); // m (costi fissi apertura)

    // 3. Inizializza strutture dati soluzione
    std::vector<bool> facilityOpen(m, false);          // depositi aperti
    std::vector<int> customerAssignment(n, -1);        // cliente -> deposito assegnato
    
    // 4. Algoritmo greedy: per ogni cliente, trova la migliore opzione
    // Considera sia il costo di trasporto che il costo di apertura (se necessario)
    
    for (int j = 0; j < n; ++j) {
        int bestFacility = -1;
        int bestTotalCost = std::numeric_limits<int>::max();
        
        // 5. Per ogni deposito, calcola il costo totale per servire questo cliente
        for (int i = 0; i < m; ++i) {
            int totalCost = cost[i][j]; // costo trasporto
            
            // Se il deposito non è ancora aperto, aggiungi il costo fisso
            if (!facilityOpen[i]) {
                totalCost += fixedCost[i];
            }
            
            // 6. Scegli il deposito con costo totale minimo
            if (totalCost < bestTotalCost) {
                bestTotalCost = totalCost;
                bestFacility = i;
            }
        }
        
        // 7. Assegna il cliente al miglior deposito e aprilo se necessario
        if (bestFacility != -1) {
            customerAssignment[j] = bestFacility;
            facilityOpen[bestFacility] = true;
        } else {
            throw std::runtime_error("UFLPSolver::solve: impossibile assegnare cliente " + std::to_string(j));
        }
    }
    
    // 8. Controlla che tutti i clienti siano assegnati (sanity check)
    for (int j = 0; j < n; ++j) {
        if (customerAssignment[j] == -1) {
            throw std::runtime_error("UFLPSolver::solve: cliente non assegnato");
        }
    }
    
    // 9. Costruisci lista dei depositi aperti
    std::vector<int> openFacilities;
    for (int i = 0; i < m; ++i) {
        if (facilityOpen[i]) {
            openFacilities.push_back(i);
        }
    }
    
    // 10. Crea e popola la soluzione
    auto solution = std::make_unique<UFLPSolution>();
    solution->setOpenFacilities(facilityOpen);
    solution->setAssignment(customerAssignment);
    
    // 11. Calcola costi totali (se la classe UFLPSolution ha questi metodi)
    solution->computeCost(fixedCost, cost);
    
    return solution;
}