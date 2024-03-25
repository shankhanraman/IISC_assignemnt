#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

// Structure to represent a stop
struct Stop {
    string id;
    unordered_set<string> routes;
};

// Structure to represent a route
struct Route {
    string id;
    vector<string> stops;
};

// Function to find direct journeys between source and destination stops
void findDirectJourneys(const unordered_map<string, Stop>& stops, const string& source, const string& destination) {
    cout << "Direct journeys:" << endl;
    for (const auto& stop : stops) {
        if (stop.second.routes.find(source) != stop.second.routes.end() &&
            stop.second.routes.find(destination) != stop.second.routes.end()) {
            cout << stop.second.id << "(so > sd)" << endl;
        }
    }
}

// Function to find journeys with one transfer between source and destination stops
void findJourneysWithOneTransfer(const unordered_map<string, Stop>& stops, const unordered_map<string, Route>& routes, 
                                 const string& source, const string& destination) {
    cout << "Journeys with one transfer:" << endl;
    for (const auto& stop : stops) {
        if (stop.second.routes.find(source) != stop.second.routes.end()) {
            for (const auto& routeId : stop.second.routes) {
                const Route& route = routes.at(routeId);
                for (const auto& nextStopId : route.stops) {
                    if (stops.at(nextStopId).routes.find(destination) != stops.at(nextStopId).routes.end()) {
                        cout << stop.second.id << "(so > " << stop.second.id << ") - " 
                             << route.id << "(" << stop.second.id << " > " << nextStopId << ") - "
                             << stops.at(nextStopId).id << "(" << nextStopId << " > sd)" << endl;
                    }
                }
            }
        }
    }
}

// Function to parse GTFS data and construct stops and routes
void parseGTFS(const vector<Route>& allRoutes, unordered_map<string, Stop>& stops, unordered_map<string, Route>& routes) {
    for (const auto& route : allRoutes) {
        routes[route.id] = route;
        for (const auto& stopId : route.stops) {
            if (stops.find(stopId) == stops.end()) {
                stops[stopId] = {stopId, {route.id}};
            } else {
                stops[stopId].routes.insert(route.id);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Parse command-line arguments for source and destination stop IDs
    string source = argv[1];
    string destination = argv[2];

    // Sample GTFS data representing routes and stops
    vector<Route> allRoutes = {
        {"R1", {"so", "s3", "sd"}},
        {"R2", {"so", "s1"}},
        {"R3", {"s1", "sd"}},
        {"R4", {"so", "s2"}},
        {"R5", {"s2", "sd"}},
        // Add more routes as needed
    };

    // Construct stops and routes from GTFS data
    unordered_map<string, Stop> stops;
    unordered_map<string, Route> routes;
    parseGTFS(allRoutes, stops, routes);

    // Find and print direct journeys
    findDirectJourneys(stops, source, destination);

    // Find and print journeys with one transfer
    findJourneysWithOneTransfer(stops, routes, source, destination);

    // Add logic to find and print journeys with two transfers if needed

    return 0;
}
