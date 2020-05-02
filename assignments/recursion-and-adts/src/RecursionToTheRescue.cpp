#include "RecursionToTheRescue.h"
#include "map.h"
#include <climits>
#include <iostream>
#include "Disasters.h"
#include "sparsegrid.h"
using namespace std;

bool canAllPatientsBeSeenHelper(Vector<Doctor>& doctors,
                          Vector<Patient>& patients,
                          Map<string, Set<string>>& schedule);

void addToSchedule(Doctor doctor, Patient patient,
                   Map<string,Set<string>>& schedule);

bool disasterReadyHelper(const Map<string, Set<string>>& roadNetwork, int numCities,
                         Set<string> citiesToCover, Set<string>& locations);

/**
 * Given a road network and cities which are still needed to be covered
 * ethier beeing a disaster supplier or having a neighbor with supplies,
 * returns the city which needs to be covered first.
 *
 * @param roadNetwork The road network between cities.
 * @param citiesToCover The set of all the cities which need to be covered.
 * @return the city which needs to be covered first.
 */
string findCityToCover(const Map<string, Set<string>>& roadNetwork,
                       const Set<string>& citiesToCover);

/**
 * Make the given city a supplier. That means removing the city
 * and all its neighbors from the citiesToCover collection and
 * adding the city itself to the suppliers collection. Returns
 * cities which still need covering.
 *
 * @param city City is to be a supplier.
 * @param neighbors All the neighbors of the given city.
 * @param citiesToCover Cities which need covering before making the given one a supplier.
 * @param suppliers The collection of all the cities which are suppliers.
 * @return The set of cities which still need covering after make the given city a supplier.
 */
Set<string> makeSupplier(string city, const Set<string>& neighbors,
                         Set<string>& citiesToCover, Set<string>& suppliers);

/* * * * Doctors Without Orders * * * */

/**
 * Given a list of doctors and a list of patients, determines whether all the patients can
 * be seen. If so, this function fills in the schedule outparameter with a map from doctors
 * to the set of patients that doctor would see.
 *
 * @param doctors  The list of the doctors available to work.
 * @param patients The list of the patients that need to be seen.
 * @param schedule An outparameter that will be filled in with the schedule, should one exist.
 * @return Whether or not a schedule was found.
 */
bool canAllPatientsBeSeen(const Vector<Doctor>& doctors,
                          const Vector<Patient>& patients,
                          Map<string, Set<string>>& schedule) {
    Vector<Doctor> d = doctors;
    Vector<Patient> p = patients;

    return canAllPatientsBeSeenHelper(d, p, schedule);
}

bool canAllPatientsBeSeenHelper(Vector<Doctor>& doctors,
                          Vector<Patient>& patients,
                          Map<string, Set<string>>& schedule) {

    if (patients.isEmpty()) {
        return true;
    }

    Patient patient = patients.removeBack();

    for (int d = 0; d < doctors.size(); d++) {
        Doctor& doctor = doctors[d];

        if (doctor.hoursFree >= patient.hoursNeeded) {
            addToSchedule(doctor, patient, schedule);
            doctor.hoursFree -= patient.hoursNeeded;

            if (canAllPatientsBeSeen(doctors, patients, schedule)) {
                return true;
            }

            doctor.hoursFree += patient.hoursNeeded;
            schedule.remove(doctor.name);
        }
    }

    patients.add(patient);

    return false;

}

void addToSchedule(Doctor doctor, Patient patient, Map<string, Set<string>>& schedule) {
    if (!schedule.containsKey(doctor.name)) {
        schedule.add(doctor.name, Set<string>());
    }

    schedule[doctor.name].add(patient.name);
}

/* * * * Disaster Planning * * * */

/**
 * Given a transportation grid for a country or region, along with the number of cities where disaster
 * supplies can be stockpiled, returns whether it's possible to stockpile disaster supplies in at most
 * the specified number of cities such that each city either has supplies or is connected to a city that
 * does.
 * <p>
 * This function can assume that every city is a key in the transportation map and that roads are
 * bidirectional: if there's a road from City A to City B, then there's a road from City B back to
 * City A as well.
 *
 * @param roadNetwork The underlying transportation network.
 * @param numCities   How many cities you can afford to put supplies in.
 * @param locations   An outparameter filled in with which cities to choose if a solution exists.
 * @return Whether a solution exists.
 */
bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& locations) {
    Set<string> citiesToCover;
    for (string city: roadNetwork) {
        citiesToCover.add(city);
    }

    return disasterReadyHelper(roadNetwork, numCities, citiesToCover, locations);
}

bool disasterReadyHelper(const Map<string, Set<string>>& roadNetwork, int numCities,
                         Set<string> citiesToCover, Set<string>& locations) {
    if (locations.size() > numCities) {
        return false;
    } else if (citiesToCover.isEmpty()) {
        return true;
    } else {
        string uncovered = findCityToCover(roadNetwork, citiesToCover);
        Set<string> remaining = makeSupplier(uncovered, roadNetwork[uncovered], citiesToCover, locations);
        if (disasterReadyHelper(roadNetwork, numCities, remaining, locations)) {
            return true;
        }
        locations.remove(uncovered);

        for (string neigh: roadNetwork[uncovered]) {
            Set<string> remaining = makeSupplier(neigh, roadNetwork[neigh], citiesToCover, locations);
            if (disasterReadyHelper(roadNetwork, numCities, remaining, locations)) {
                return true;
            }
            locations.remove(neigh);
        }
    }

    return false;
}

string findCityToCover(const Map<string, Set<string>>& roadNetwork, const Set<string>& citiesToCover) {
    for (string city: roadNetwork) {
        if (citiesToCover.contains(city)) {
            return city;
        }
    }
    return "";
}

Set<string> makeSupplier(string city, const Set<string>& neighbors, Set<string>& citiesToCover, Set<string>& suppliers) {
    Set<string> remaining = citiesToCover;
    remaining.remove(city);
    remaining.removeAll(neighbors);
    suppliers.add(city);

    return remaining;
}

/* * * * Winning the Election * * * */

/**
 * Given a list of the states in the election, including their popular and electoral vote
 * totals, and the number of electoral votes needed, as well as the index of the lowest-indexed
 * state to consider, returns information about how few popular votes you'd need in order to
 * win that at least that many electoral votes.
 *
 * @param electoralVotesNeeded the minimum number of electoral votes needed
 * @param states All the states in the election (plus DC, if appropriate)
 * @param minStateIndex the lowest index in the states Vector that should be considered
 */
MinInfo minPopularVoteToGetAtLeast(int electoralVotesNeeded, const Vector<State>& states, int minStateIndex, SparseGrid<MinInfo>& memos) {
    if (electoralVotesNeeded <= 0) {
        return { 0, {} };
    } else if (minStateIndex == states.size()) {
        return { INT_MAX, {} };
    } else if (memos.isSet(electoralVotesNeeded, minStateIndex)) {
        return memos[electoralVotesNeeded][minStateIndex];
    } else {
        State currState = states[minStateIndex];
        int currPopularVotes = currState.popularVotes / 2 + 1;

        MinInfo withCurrState = minPopularVoteToGetAtLeast(electoralVotesNeeded - currState.electoralVotes, states, minStateIndex + 1, memos);
        MinInfo withoutCurrState = minPopularVoteToGetAtLeast(electoralVotesNeeded, states, minStateIndex + 1, memos);

        MinInfo min;

        if (withCurrState.popularVotesNeeded == withoutCurrState.popularVotesNeeded) {
            min = withoutCurrState;
        } else if (withCurrState.popularVotesNeeded + currPopularVotes < withoutCurrState.popularVotesNeeded) {
            withCurrState.popularVotesNeeded += currPopularVotes;
            withCurrState.statesUsed += currState;
            min = withCurrState;
        } else {
            min = withoutCurrState;
        }

        memos[electoralVotesNeeded][minStateIndex] = min;

        return min;
    }
}

int majorityElectoral(const Vector<State>& states) {
    int votesNeeded = 0 ;
    for (State s : states) {
        votesNeeded += s.electoralVotes ;
    }
    return votesNeeded / 2 + 1 ;
}

/**
 * Given a list of all the states in an election, including their popular and electoral vote
 * totals, returns information about how few popular votes you'd need to win in order to win
 * the presidency.
 *
 * @param states All the states in the election (plus DC, if appropriate)
 * @return Information about how few votes you'd need to win the election.
 */
MinInfo minPopularVoteToWin(const Vector<State>& states) {
    int electoralNeeded = majorityElectoral(states);
    SparseGrid<MinInfo> memos(electoralNeeded + 1, states.size());

    return minPopularVoteToGetAtLeast(electoralNeeded, states, 0, memos);
}
