/*
 * File: checkout-line.cpp
 * -----------------------
 * This program simulates a checkout line, such as one you
 * might encounter in a grocery store. Customers arrive at
 * the checkout stand and get in line. Those customers wait
 * in the line until the cashier is free, at which point
 * they are served and occupy the cashier for some period
 * of time. After the service time is complete, the cashier
 * is free to serve the next customer in the line.
 *
 * In each unit of time, up to the constans SIMULATION_TIME,
 * the following operations are performed:
 *
 * 1. Determing whether a new customer has arrived.
 *    New customers arrive randomly, with a probability
 *    determined by the constant ARRIVAL_PROBABILITY.
 *
 * 2. If the cashier is busy, note that the cashier has
 *    spent another second with that customer. Eventually,
 *    the customer's time request is satisfied, which frees
 *    the cashier.
 *
 * 3. If the cashier is free, server the next customer in line.
 *    The service time is taken to be a random period between
 *    MIN_SERVICE_TIME and MAX_SERVICE_TIME.
 *
 * At the end of the simulation, the program displays the
 * simulation constants and the following computed results:
 *
 * - The number of customers served
 * - The average time spent in line
 * - The average number of people in line
 */

#include <iostream>
#include <iomanip>
#include "queue.h"
#include "random.h"
#include "console.h"

using namespace std;

/* Constants */

constexpr double ARRIVAL_PROBABILITY = .1;
constexpr int MIN_SERVICE_TIME = 5;
constexpr int MAX_SERVICE_TIME = 15;
constexpr int SIMULATION_TIME = 5000;
constexpr int CASHIERS = 3;

enum SimMode {
    MultiLine,
    MultiCashier
};

/**
 * Function: runSimulation
 * -----------------------
 * This function runs the actual simulation. The number of
 * customers served, the sum of the customer waiting times,
 * and the sum of the queue length in each time step are
 * returned through the reference parameters.
 */

void runSimulation(SimMode mode, int& nServied, int& totalWait, int& totalLength);

/**
 * Function: putInShortesQueue
 * ---------------------------
 * TBD.
 */
int getShortestQueue(const Vector<Queue<int>>& lines);

/**
 * Function: printReport
 * ---------------------
 * This function reports the results of the simulation.
 */
void printReport(const string& header, int nServed, int totalWait, int totalLength);

/* Main program */

int main() {
    int nServed;
    int totalWait;
    int totalLength;

    runSimulation(MultiLine, nServed, totalWait, totalLength);
    printReport("Multi Line: ", nServed, totalWait, totalLength);

    cout << endl << endl;

    runSimulation(MultiCashier, nServed, totalWait, totalLength);
    printReport("Multi Cashier: ", nServed, totalWait, totalLength);

    return 0;
}

int numLines(SimMode mode, int cashiers) {
    switch (mode) {
        case MultiLine:
            return cashiers;
        case MultiCashier:
        return 1;
    }
}

void runSimulation(SimMode mode, int& nServed, int& totalWait, int& totalLength) {
    Vector<Queue<int>> lines(numLines(mode, CASHIERS));
    Vector<int> cashiers(CASHIERS);

    nServed = 0;
    totalWait = 0;
    totalLength = 0;

    for (int t = 0; t < SIMULATION_TIME; ++t) {
        if (randomChance(ARRIVAL_PROBABILITY)) {
            int shortestQueue = getShortestQueue(lines);
            lines[shortestQueue].enqueue(t);
        }

        for (int c = 0; c < cashiers.size(); ++c) {
            int line = mode == MultiLine ? c : 0;

            if (cashiers[c] > 0) {
                --cashiers[c];
            } else if (!lines[line].isEmpty()) {
                totalWait += (t - lines[line].dequeue());
                ++nServed;
                cashiers[c] = randomInteger(MIN_SERVICE_TIME, MAX_SERVICE_TIME);
            }
        }

        for (int l = 0; l < lines.size(); ++l) {
            totalLength += lines[l].size();
        }
    }
}

int getShortestQueue(const Vector<Queue<int>>& lines) {
    if (lines.size() == 1) {
        return 0;
    }

    int index = 0;
    int shortest = lines[0].size();

    for (int i = 1; i < lines.size(); ++i) {
        int lenght = lines[i].size();

        if (lenght == 0) {
            return i;
        } else if (lines[i].size() < shortest) {
            shortest = lines[i].size();
            index = i;
        }
    }

    return index;
}

void printReport(const string& header, int nServed, int totalWait, int totalLength) {
    cout << "\t\t\t" << header << endl;
    cout << "Simulation results given the following constants:" << endl;
    cout << fixed << setprecision(2);
    cout << "   SIMULATION_TIME:    " << setw(4) << SIMULATION_TIME << endl;
    cout << "   ARRIVAL_PROBABILITY " << setw(7) << ARRIVAL_PROBABILITY << endl;
    cout << "   MIN_SERVICE_TIME    " << setw(4) << MIN_SERVICE_TIME << endl;
    cout << "   MAX_SERVICE_TIME    " << setw(4) << MAX_SERVICE_TIME << endl;
    cout << endl;
    cout << "Customers served:          " << setw(4) << nServed << endl;
    cout << "Average waiting time:    " << setw(7) << double(totalWait) / nServed << endl;
    cout << "Average queue length:    " << setw(7) << double(totalLength) / SIMULATION_TIME << endl;
}
