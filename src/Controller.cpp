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

controller::~controller(){}

int searchByMember(RedBlackTree<int, std::vector<std::string>> tree, std::string memberValue){
    for(RedBlackTree<int, std::vector<std::string>>::Iterator itr = tree.begin(); 
    itr != tree.end(); ++itr){
        for(int i = 0; i < itr.getValue().size(); ++i){
            if(itr.getValue().at(i) == memberValue){
                return itr.getKey();
            }
        }
    }
    return 1;
}

double searchByMember(RedBlackTree<double, std::vector<std::string>> tree, std::string memberValue){
    for(RedBlackTree<double, std::vector<std::string>>::Iterator itr = tree.begin(); 
    itr != tree.end(); ++itr){
        for(int i = 0; i < itr.getValue().size(); ++i){
            if(itr.getValue().at(i) == memberValue){
                return itr.getKey();
            }
        }
    }
    return 1;
}

// Trim function to get the blank lines.
// Code gathered from: https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring
void controller::trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !(std::isspace(ch)); }));

    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !(std::isspace(ch)); }).base(), str.end());
}

void controller::readClassData(){
    // Open the files on the data folder.
    std::ifstream fPieces("data/pieces.csv");  // Open the pieces file.
    std::ifstream fPlayers("data/players.csv");  // Open the players file. Contains tracks and players.

    if(!fPieces || !fPlayers){
        std::cout << "Failed to open the files." << std::endl;
    }

    //// Now read the parts ////
    std::string partLine;
    while(std::getline(fPieces, partLine)){
        std::string piece;
        std::string ammount;
        std::istringstream ss(partLine);
        std::getline(ss, piece, ',');
        std::getline(ss, ammount, ',');
        int limit = std::stoi(ammount);
        for(int i = 0; i < limit; i++){
            std::string currentLine;
            std::vector<std::string> fields;
            std::getline(fPieces, currentLine);
            std::istringstream ss2(currentLine);
            if(piece == "Karts"){
                std::string name, ac, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, ac, ',');
                std::getline(ss2, speed, ',');
                double acc;
                int speedd;
                acc = std::stod(ac);
                speedd = std::stoi(speed);
                // Add to garage.
                garageForController.KartsAceleration[acc].push_back(name);
                garageForController.KartsSpeed[speedd].push_back(name);
            } else if(piece == "Tires"){
                std::string name, speedT, speedW, speedA;
                std::getline(ss2, name, ',');
                std::getline(ss2, speedT, ',');
                std::getline(ss2, speedW, ',');
                std::getline(ss2, speedA, ',');
                int speedTT, speedWW, speedAA;
                speedTT = std::stoi(speedT);
                speedWW = std::stoi(speedW);
                speedAA = std::stoi(speedA);
                // Add to garage.
                garageForController.TiresTSpeed[speedTT].push_back(name);
                garageForController.TiresWSpeed[speedWW].push_back(name);
                garageForController.TiresASpeed[speedAA].push_back(name);
            } else if(piece == "Bikes"){
                std::string name, ac, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, ac, ',');
                std::getline(ss2, speed, ',');
                double acc;
                int speedd;
                acc = std::stod(ac);
                speedd = std::stoi(speed);
                // Add to garage.
                garageForController.BikesAceleration[acc].push_back(name);
                garageForController.BikesSpeed[speedd].push_back(name);
            }else if(piece == "ATVs"){
                std::string name, ac, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, ac, ',');
                std::getline(ss2, speed, ',');
                double acc;
                int speedd;
                acc = std::stod(ac);
                speedd = std::stoi(speed);
                // Add to garage.
                garageForController.ATVsAceleration[acc].push_back(name);
                garageForController.ATVsSpeed[speedd].push_back(name);
            } else if(piece == "Gliders"){
                std::string name, delay, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, delay, ',');
                std::getline(ss2, speed, ',');
                int delayy, speedd;
                delayy = std::stoi(delay);
                speedd = std::stoi(speed);
                // Add to garage.
                garageForController.glidersDelay[delayy].push_back(name);
                garageForController.glidersSpeed[speedd].push_back(name);
            }
        }
        std::string skipLine;
        std::getline(fPieces, skipLine);
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
        // Hay que hacer las partes de 1 y guardarlas. Se busca el nombre en el arbol para hallar los otros dos atributos.
        // Usar el metodo de arriba.
        if(playerData.at(3) == "Kart"){
            // Crear parte kart, tire y glider.
            // playerData at index 3, 4 and 5.

            double aceleration = searchByMember(garageForController.KartsAceleration, playerData.at(2));
            int speed = searchByMember(garageForController.KartsSpeed, playerData.at(2));
            Part* kart = new Kart(playerData.at(2), aceleration, speed);

            int tSpeed = searchByMember(garageForController.TiresTSpeed, playerData.at(4));
            int wSpeed = searchByMember(garageForController.TiresWSpeed, playerData.at(4));
            int aSpeed = searchByMember(garageForController.TiresASpeed, playerData.at(4));
            Tire tires(playerData.at(4), tSpeed, wSpeed, aSpeed);

            int gDelay = searchByMember(garageForController.glidersDelay, playerData.at(5));
            int gAirSpeed = searchByMember(garageForController.glidersSpeed, playerData.at(5));
            Glider glider(playerData.at(5), gDelay, gAirSpeed);

            Driver* bDriver = new KartDriver(playerData.at(0), playerData.at(1), *kart, tires, glider);
            garageForController.DriverList.push_back(bDriver);
        } else if(playerData.at(3) == "Bike"){
            // Crear parte kart, tire y glider.
            // playerData at index 3, 4 and 5.

            double aceleration = searchByMember(garageForController.KartsAceleration, playerData.at(2));
            int speed = searchByMember(garageForController.KartsSpeed, playerData.at(2));
            Part* kart = new Kart(playerData.at(2), aceleration, speed);

            int tSpeed = searchByMember(garageForController.TiresTSpeed, playerData.at(4));
            int wSpeed = searchByMember(garageForController.TiresWSpeed, playerData.at(4));
            int aSpeed = searchByMember(garageForController.TiresASpeed, playerData.at(4));
            Tire tires(playerData.at(4), tSpeed, wSpeed, aSpeed);

            int gDelay = searchByMember(garageForController.glidersDelay, playerData.at(5));
            int gAirSpeed = searchByMember(garageForController.glidersSpeed, playerData.at(5));
            Glider glider(playerData.at(5), gDelay, gAirSpeed);

            Driver* bDriver = new BikeDriver(playerData.at(0), playerData.at(1), *kart, tires, glider);
            garageForController.DriverList.push_back(bDriver);
        } else if(playerData.at(3) == "ATV"){
            // Crear parte kart, tire y glider.
            // playerData at index 3, 4 and 5.

            double aceleration = searchByMember(garageForController.KartsAceleration, playerData.at(2));
            int speed = searchByMember(garageForController.KartsSpeed, playerData.at(2));
            Part* kart = new Kart(playerData.at(2), aceleration, speed);

            int tSpeed = searchByMember(garageForController.TiresTSpeed, playerData.at(4));
            int wSpeed = searchByMember(garageForController.TiresWSpeed, playerData.at(4));
            int aSpeed = searchByMember(garageForController.TiresASpeed, playerData.at(4));
            Tire tires(playerData.at(4), tSpeed, wSpeed, aSpeed);

            int gDelay = searchByMember(garageForController.glidersDelay, playerData.at(5));
            int gAirSpeed = searchByMember(garageForController.glidersSpeed, playerData.at(5));
            Glider glider(playerData.at(5), gDelay, gAirSpeed);

            Driver* bDriver = new ATVDriver(playerData.at(0), playerData.at(1), *kart, tires, glider);
            garageForController.DriverList.push_back(bDriver);
        }
    }

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

    std::cout << "Prints kartAceleration" << std::endl;
    // Print tree kartAceleration in order.
    for(RedBlackTree<double, std::vector<std::string>>::Iterator itr = garageForController.KartsAceleration.begin(); 
    itr != garageForController.KartsAceleration.end(); ++itr){
        for(int i = 0; i < itr.getValue().size(); ++i){
            std::cout << "Test: " << itr.getKey() << ": " << itr.getValue().at(i) << std::endl;
        }
    }

    std::cout << "Test: " << garageForController.DriverList.at(0)->tires.airSpeed << std::endl;
    */

    //Close files.
    fPlayers.close();
    fPieces.close();
}

void controller::printParts(std::string piece){
    //// Store the parts ////
    std::vector<std::string> Karts;
    std::vector<std::string> Tires;
    std::vector<std::string> Gliders;

    std::ifstream fPieces("data/pieces.csv");
    std::string partLine;
    while(std::getline(fPieces, partLine)){
        std::string piecee;
        std::string ammount;
        std::istringstream ss(partLine);
        std::getline(ss, piecee, ',');
        std::getline(ss, ammount, ',');
        int limit = std::stoi(ammount);
        for(int i = 0; i < limit; i++){
            std::string currentLine;
            std::getline(fPieces, currentLine);
            if(piecee == "Karts"){
                Karts.push_back(currentLine);
            } else if (piecee == "Bikes"){
                Karts.push_back(currentLine);
            } else if (piecee == "ATVs"){
                Karts.push_back(currentLine);
            } else if(piecee == "Tires"){
                Tires.push_back(currentLine);
            } else if(piecee == "Gliders"){
                Gliders.push_back(currentLine);
            } 
        }
        std::string skip;
        std::getline(fPieces, skip);
    }
    // Print the selected part.
    if(piece == "Karts"){
        for(int i = 0; i < Karts.size(); i++){
            std::cout << Karts.at(i) << std::endl;
        }
    }else if(piece == "Tires"){
        for(int i = 0; i < Tires.size(); i++){
            std::cout << Tires.at(i) << std::endl;
        }
    } else if(piece == "Gliders"){
        for(int i = 0; i < Gliders.size(); i++){
            std::cout << Gliders.at(i) << std::endl;
        }
    }
    fPieces.close();
}

void controller::bestCombinationForTrack(std::string track) {
    // Get the distances of the track.
    int t = 0, w = 0, a = 0;
    t = searchByMember(garageForController.TrackT, track);
    w = searchByMember(garageForController.TrackW, track);
    a = searchByMember(garageForController.TrackA, track);

    // Look for the shortest time possible on all track places.
    // Terrain
    
    // Water

    // Air
    
}

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
                printParts("Karts");
                break;
            }
            case 2: {
                // Display Tires
                std::cout << "Displays Tires and attributes" << std::endl;
                printParts("Tires");
                break;
            }
            case 3: {
                // Display Gliders
                std::cout << "Displays Gliders and attributes" << std::endl;
                printParts("Gliders");
                break;
            }
            case 4: {
                // Calculate Best Combination (All Tracks)
                std::cout << "Calculating best combination for all tracks..." << std::endl;
                bestCombinationForTrack("Mach 8");
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
