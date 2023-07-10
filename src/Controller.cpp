#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

#include <Controller.hpp>
#include <Garage.hpp>
#include <RBTree.hxx>

// Has a Garage member.

controller::controller(){}

void controller::runMenu() {
    int choice;

    do {
        std::cout << "---------- Menu ----------" << std::endl;
        std::cout << "1. Display Karts" << std::endl;
        std::cout << "2. Display Tires" << std::endl;
        std::cout << "3. Display Gliders" << std::endl;
        std::cout << "4. Calculate Best Combination (All Tracks)" << std::endl;  // Option for calculating best combination for all tracks
        std::cout << "5. Calculate Best Combination (Specific Track)" << std::endl;  // Option for calculating best combination for a specific track
        std::cout << "6. Calculate Average Finishing Position (Specific Player)" << std::endl;  // Option for calculating average finishing position for a specific player
        std::cout << "7. Calculate Fastest Combination (Four Specific Tracks)" << std::endl;  // Option for calculating fastest combination for a 4 track cup mode
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Display Karts
                std::cout << "Displays Karts and attributes" << std::endl;
                break;
            }
            case 2: {
                // Display Tires
                std::cout << "Displays Tires and attributes" << std::endl;
                break;
            }
            case 3: {
                // Display Gliders
                std::cout << "Displays Gliders and attributes" << std::endl;
                break;
            }
            case 4: {
                // Calculate Best Combination (All Tracks)
                std::cout << "Calculating best combination for all tracks..." << std::endl;
                break;
            }
            case 5: {
                // Calculate Best Combination (Specific Track)
                std::cout << "Enter the track name: ";
                std::string trackName;
                std::cin.ignore();  // Ignore the newline character from the previous input
                std::getline(std::cin, trackName);
                std::cout << "Calculating best combination for track: " << trackName << "..." << std::endl;
                break;
            }
            case 6: {
                // Calculate Average Finishing Position (Specific Player)
                std::cout << "Enter the player name: ";
                std::string playerName;
                std::cin.ignore();  // Ignore the newline character from the previous input
                std::getline(std::cin, playerName);
                std::cout << "Calculating average finishing position for player: " << playerName << "..." << std::endl;
                break;
            }
            case 7: {
                // Calculate Fastest Combination (Four Specific Tracks)
                std::cout << "Enter the names of four tracks (Cup Mode): " << std::endl;
                std::vector<std::string> trackNames;
                std::cin.ignore();  // Ignore the newline character from the previous input

                for (int i = 0; i < 4; ++i) {
                    std::string trackName;
                    std::getline(std::cin, trackName);
                    trackNames.push_back(trackName);
                }

                std::cout << "Calculating fastest combination for the following tracks: " << std::endl;
                for (const std::string& trackName : trackNames) {
                    std::cout << "- " << trackName << std::endl;
                }

                break;
            }
            case 8:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (choice != 8);
}

// Trim function to get the blank lines.
// Code gathered from: https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring
void controller::trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !(std::isspace(ch)); }));

    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !(std::isspace(ch)); }).base(), str.end());
}

void controller::readClassData(int argc, char* argv[]){
    // Open the files on the data folder.
    std::ifstream fPieces("data/pieces.csv");  // Open the pieces file.
    std::ifstream fPlayers("data/players.csv");  // Open the players file. Contains tracks and players.

    if(!fPieces || !fPlayers){
        std::cout << "Failed to open the files." << std::endl;
    }

    //// Read the tracks and players ////

    std::vector<std::string> lines;
    std::string line;

    // Get the tracks.
    while (std::getline(fPlayers, line)) {
        trim(line);
        if(line.empty()){
            break;
        }
        std::istringstream ss(line);
        std::string trackName;
        std::string t, w, a;
        std::vector<std::string> names;
        std::getline(ss, trackName, ',');
        std::getline(ss, t, ',');
        std::getline(ss, w, ',');
        std::getline(ss, a, ',');
        int ti = std::stoi(t);
        int wi = std::stoi(w);
        int ai = std::stoi(a);

        garageForController.TrackT[ti].push_back(trackName);
        garageForController.TrackW[wi].push_back(trackName);
        garageForController.TrackA[ai].push_back(trackName);
    }

    // Get the players.
    std::string newLine;

    // Skip the tags line.
    std::string skip;
    std::getline(fPlayers, skip);
    
    while (std::getline(fPlayers, newLine)) {
        std::vector<std::string> playerData;
        std::string field;
        std::istringstream ss(newLine);
        for(int i = 0; i < 6; i++){
            std::getline(ss, field, ',');
            playerData.push_back(field);
        }
        // Create the driver and store it in the main driver list on the controller garage.
        if(playerData.at(3) == "Kart"){
            Driver* bDriver = new KartDriver(playerData.at(0), playerData.at(1), playerData.at(2), playerData.at(4), 
            playerData.at(5));
            garageForController.DriverList.push_back(bDriver);
        } else if(playerData.at(3) == "Bike"){
            Driver* bDriver = new BikeDriver(playerData.at(0), playerData.at(1), playerData.at(2), playerData.at(4), 
            playerData.at(5));
            garageForController.DriverList.push_back(bDriver);
        } else if(playerData.at(3) == "ATV"){
            Driver* bDriver = new ATVDriver(playerData.at(0), playerData.at(1), playerData.at(2), playerData.at(4), 
            playerData.at(5));
            garageForController.DriverList.push_back(bDriver);
        }
    }

    //// Now read the parts ////
    
    /*
    //// PRINTER OF DATA ////
    std::cout << "Prints trackT" << std::endl;
    // Print tree TrackT in order.
    for(RedBlackTree<int, std::vector<std::string>>::Iterator itr = garageForController.TrackT.begin(); 
    itr != garageForController.TrackT.end(); ++itr){
        for(int i = 0; i < itr.getValue().size(); ++i){
            std::cout << "Test: " << itr.getKey() << ": " << itr.getValue().at(i) << std::endl;
        }
    }

    std::cout << "Prints trackW" << std::endl;
    // Print tree TrackW in order
    for(RedBlackTree<int, std::vector<std::string>>::Iterator itr = garageForController.TrackW.begin(); 
    itr != garageForController.TrackW.end(); ++itr){
        for(int i = 0; i < itr.getValue().size(); ++i){
            std::cout << "Test: " << itr.getKey() << ": " << itr.getValue().at(i) << std::endl;
        }
    }

    std::cout << "Prints trackA" << std::endl;
    // Print tree TrackA in order.
    for(RedBlackTree<int, std::vector<std::string>>::Iterator itr = garageForController.TrackA.begin(); 
    itr != garageForController.TrackA.end(); ++itr){
        for(int i = 0; i < itr.getValue().size(); ++i){
            std::cout << "Test: " << itr.getKey() << ": " << itr.getValue().at(i) << std::endl;
        }
    }

    std::cout << "Prints Players" << std::endl;
    // Prints players(gt, character).
    for(int i = 0; i < garageForController.DriverList.size(); ++i){
        std::cout << garageForController.DriverList.at(i)->gamerTag << ": " << 
        garageForController.DriverList.at(i)->character << "....." << garageForController.DriverList.at(i)->getVehicle().name << std::endl;
    }
    */
}