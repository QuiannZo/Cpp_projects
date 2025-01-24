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
            delete kart;
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
            delete kart;
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
            delete kart;
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
    // Para cada carro, llanta y planeador se calcula la velocidad en los n metros tierra. Se devuelve la minima.
    
    //triple for a carro, llantas, y planeador. Crear objeto temporal y sacar su velocidad con calcSpeed(t, w, a).
    //Obtener nombres. con estos se recorreran los arboles.
    std::vector<std::string> karts;
    std::vector<std::string> bikes;
    std::vector<std::string> atvs;
    std::vector<std::string> tires;
    std::vector<std::string> gliders;

    std::ifstream fPieces("data/pieces.csv");
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
                karts.push_back(name);
            } else if(piece == "Tires"){
                std::string name, speedT, speedW, speedA;
                std::getline(ss2, name, ',');
                std::getline(ss2, speedT, ',');
                std::getline(ss2, speedW, ',');
                std::getline(ss2, speedA, ',');
                tires.push_back(name);
            } else if(piece == "Bikes"){
                std::string name, ac, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, ac, ',');
                std::getline(ss2, speed, ',');
                bikes.push_back(name);
            }else if(piece == "ATVs"){
                std::string name, ac, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, ac, ',');
                std::getline(ss2, speed, ',');
                atvs.push_back(name);
            } else if(piece == "Gliders"){
                std::string name, delay, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, delay, ',');
                std::getline(ss2, speed, ',');
                gliders.push_back(name);
            }
        }
        std::string skipLine;
        std::getline(fPieces, skipLine);
    }

    //After names are gathered, cycle.
    std::vector<std::string> bestCombination;
    double minTime = 100000;

    for(int i = 0; i < karts.size(); ++i){
        for(int j = 0; j < tires.size(); ++j){
            for(int k = 0; k < gliders.size(); ++k){
                double kartAc = searchByMember(garageForController.KartsAceleration, karts.at(i));
                int kartSpeed = searchByMember(garageForController.KartsSpeed, karts.at(i));

                int tireT = searchByMember(garageForController.TiresTSpeed, tires.at(j));
                int tireW = searchByMember(garageForController.TiresWSpeed, tires.at(j));
                int tireA = searchByMember(garageForController.TiresASpeed, tires.at(j));

                int gliderDelay = searchByMember(garageForController.glidersDelay, gliders.at(k));
                int gliderSpeed = searchByMember(garageForController.glidersSpeed, gliders.at(k));

                //terrain.
                double terrainSpeed = ((0.5*t) * kartAc) + kartSpeed + (1.1 * tireT) - (0.5 * gliderDelay);
                //water.
                double waterSpeed = ((0.7*w) * kartAc) + kartSpeed + (1.2*tireW) - (0.7*gliderDelay);
                //air.
                double airSpeed = ((0.5*a) * kartAc) + kartSpeed - (0.9*tireA) + (0.7*gliderSpeed);
                //return sum.
                int returnNum = (terrainSpeed + waterSpeed + airSpeed); 

                // Compare
                if(minTime > returnNum){
                    bestCombination.clear();
                    minTime = returnNum;
                    bestCombination.push_back(karts.at(i));
                    bestCombination.push_back(tires.at(j));
                    bestCombination.push_back(gliders.at(k));
                }
            }
        }
    }

    for(int i = 0; i < bikes.size(); ++i){
        for(int j = 0; j < tires.size(); ++j){
            for(int k = 0; k < gliders.size(); ++k){
                double kartAc = searchByMember(garageForController.BikesAceleration, bikes.at(i));
                int kartSpeed = searchByMember(garageForController.BikesSpeed, bikes.at(i));

                int tireT = searchByMember(garageForController.TiresTSpeed, tires.at(j));
                int tireW = searchByMember(garageForController.TiresWSpeed, tires.at(j));
                int tireA = searchByMember(garageForController.TiresASpeed, tires.at(j));

                int gliderDelay = searchByMember(garageForController.glidersDelay, gliders.at(k));
                int gliderSpeed = searchByMember(garageForController.glidersSpeed, gliders.at(k));

                //terrain.
                double terrainSpeed = ((0.5*t) * kartAc) + kartSpeed + (1.1 * tireT) - (0.5 * gliderDelay);
                //water.
                double waterSpeed = ((0.7*w) * kartAc) + kartSpeed + (1.2*tireW) - (0.7*gliderDelay);
                //air.
                double airSpeed = ((0.5*a) * kartAc) + kartSpeed - (0.9*tireA) + (0.7*gliderSpeed);
                //return sum.
                int returnNum = (terrainSpeed + waterSpeed + airSpeed); 

                // Compare
                if(minTime > returnNum){
                    bestCombination.clear();
                    minTime = returnNum;
                    bestCombination.push_back(bikes.at(i));
                    bestCombination.push_back(tires.at(j));
                    bestCombination.push_back(gliders.at(k));
                }
            }
        }
    }

    for(int i = 0; i < atvs.size(); ++i){
        for(int j = 0; j < tires.size(); ++j){
            for(int k = 0; k < gliders.size(); ++k){
                double kartAc = searchByMember(garageForController.ATVsAceleration, atvs.at(i));
                int kartSpeed = searchByMember(garageForController.ATVsSpeed, atvs.at(i));

                int tireT = searchByMember(garageForController.TiresTSpeed, tires.at(j));
                int tireW = searchByMember(garageForController.TiresWSpeed, tires.at(j));
                int tireA = searchByMember(garageForController.TiresASpeed, tires.at(j));

                int gliderDelay = searchByMember(garageForController.glidersDelay, gliders.at(k));
                int gliderSpeed = searchByMember(garageForController.glidersSpeed, gliders.at(k));

                //terrain.
                double terrainSpeed = ((0.5*t) * kartAc) + kartSpeed + (1.1 * tireT) - (0.5 * gliderDelay);
                //water.
                double waterSpeed = ((0.7*w) * kartAc) + kartSpeed + (1.2*tireW) - (0.7*gliderDelay);
                //air.
                double airSpeed = ((0.5*a) * kartAc) + kartSpeed - (0.9*tireA) + (0.7*gliderSpeed);
                //return sum.
                int returnNum = (terrainSpeed + waterSpeed + airSpeed); 

                // Compare
                if(minTime > returnNum){
                    bestCombination.clear();
                    minTime = returnNum;
                    bestCombination.push_back(atvs.at(i));
                    bestCombination.push_back(tires.at(j));
                    bestCombination.push_back(gliders.at(k));
                }
            }
        }
    }

    //Print best combination.
    std::cout << "The best combination is: " << bestCombination.at(0) << ", " <<bestCombination.at(1) 
    << ", " << bestCombination.at(2) << std::endl;
}

void controller::bestCombinationForAllTracks(){
    // Get the distances of the track.
    int t = 0, w = 0, a = 0;
    std::vector<std::string> tracks;
    std::ifstream fPlayers("data/players.csv");
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
        tracks.push_back(trackName);
    }

    int avgT = 0, avgW = 0, avgA = 0;

    for(int i = 0; i < tracks.size(); ++i){
        int tt = searchByMember(garageForController.TrackT, tracks.at(i));
        int wt = searchByMember(garageForController.TrackW, tracks.at(i));
        int at = searchByMember(garageForController.TrackA, tracks.at(i));
        avgT += tt;
        avgW += wt;
        avgA += at;
    }

    avgT /= tracks.size();
    avgW /= tracks.size();
    avgA /= tracks.size();
    t = avgT;
    w = avgW;
    a = avgA;

    // Para cada carro, llanta y planeador se calcula la velocidad en los n metros tierra. Se devuelve la minima.
    
    //triple for a carro, llantas, y planeador. Crear objeto temporal y sacar su velocidad con calcSpeed(t, w, a).
    //Obtener nombres. con estos se recorreran los arboles.
    std::vector<std::string> karts;
    std::vector<std::string> bikes;
    std::vector<std::string> atvs;
    std::vector<std::string> tires;
    std::vector<std::string> gliders;

    std::ifstream fPieces("data/pieces.csv");
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
                karts.push_back(name);
            } else if(piece == "Tires"){
                std::string name, speedT, speedW, speedA;
                std::getline(ss2, name, ',');
                std::getline(ss2, speedT, ',');
                std::getline(ss2, speedW, ',');
                std::getline(ss2, speedA, ',');
                tires.push_back(name);
            } else if(piece == "Bikes"){
                std::string name, ac, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, ac, ',');
                std::getline(ss2, speed, ',');
                bikes.push_back(name);
            }else if(piece == "ATVs"){
                std::string name, ac, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, ac, ',');
                std::getline(ss2, speed, ',');
                atvs.push_back(name);
            } else if(piece == "Gliders"){
                std::string name, delay, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, delay, ',');
                std::getline(ss2, speed, ',');
                gliders.push_back(name);
            }
        }
        std::string skipLine;
        std::getline(fPieces, skipLine);
    }

    //After names are gathered, cycle.
    std::vector<std::string> bestCombination;
    double minTime = 100000;

    for(int i = 0; i < karts.size(); ++i){
        for(int j = 0; j < tires.size(); ++j){
            for(int k = 0; k < gliders.size(); ++k){
                double kartAc = searchByMember(garageForController.KartsAceleration, karts.at(i));
                int kartSpeed = searchByMember(garageForController.KartsSpeed, karts.at(i));

                int tireT = searchByMember(garageForController.TiresTSpeed, tires.at(j));
                int tireW = searchByMember(garageForController.TiresWSpeed, tires.at(j));
                int tireA = searchByMember(garageForController.TiresASpeed, tires.at(j));

                int gliderDelay = searchByMember(garageForController.glidersDelay, gliders.at(k));
                int gliderSpeed = searchByMember(garageForController.glidersSpeed, gliders.at(k));

                //terrain.
                double terrainSpeed = ((0.5*t) * kartAc) + kartSpeed + (1.1 * tireT) - (0.5 * gliderDelay);
                //water.
                double waterSpeed = ((0.7*w) * kartAc) + kartSpeed + (1.2*tireW) - (0.7*gliderDelay);
                //air.
                double airSpeed = ((0.5*a) * kartAc) + kartSpeed - (0.9*tireA) + (0.7*gliderSpeed);
                //return sum.
                int returnNum = (terrainSpeed + waterSpeed + airSpeed); 

                // Compare
                if(minTime > returnNum){
                    bestCombination.clear();
                    minTime = returnNum;
                    bestCombination.push_back(karts.at(i));
                    bestCombination.push_back(tires.at(j));
                    bestCombination.push_back(gliders.at(k));
                }
            }
        }
    }

    for(int i = 0; i < bikes.size(); ++i){
        for(int j = 0; j < tires.size(); ++j){
            for(int k = 0; k < gliders.size(); ++k){
                double kartAc = searchByMember(garageForController.BikesAceleration, bikes.at(i));
                int kartSpeed = searchByMember(garageForController.BikesSpeed, bikes.at(i));

                int tireT = searchByMember(garageForController.TiresTSpeed, tires.at(j));
                int tireW = searchByMember(garageForController.TiresWSpeed, tires.at(j));
                int tireA = searchByMember(garageForController.TiresASpeed, tires.at(j));

                int gliderDelay = searchByMember(garageForController.glidersDelay, gliders.at(k));
                int gliderSpeed = searchByMember(garageForController.glidersSpeed, gliders.at(k));

                //terrain.
                double terrainSpeed = ((0.5*t) * kartAc) + kartSpeed + (1.1 * tireT) - (0.5 * gliderDelay);
                //water.
                double waterSpeed = ((0.7*w) * kartAc) + kartSpeed + (1.2*tireW) - (0.7*gliderDelay);
                //air.
                double airSpeed = ((0.5*a) * kartAc) + kartSpeed - (0.9*tireA) + (0.7*gliderSpeed);
                //return sum.
                int returnNum = (terrainSpeed + waterSpeed + airSpeed); 

                // Compare
                if(minTime > returnNum){
                    bestCombination.clear();
                    minTime = returnNum;
                    bestCombination.push_back(bikes.at(i));
                    bestCombination.push_back(tires.at(j));
                    bestCombination.push_back(gliders.at(k));
                }
            }
        }
    }

    for(int i = 0; i < atvs.size(); ++i){
        for(int j = 0; j < tires.size(); ++j){
            for(int k = 0; k < gliders.size(); ++k){
                double kartAc = searchByMember(garageForController.ATVsAceleration, atvs.at(i));
                int kartSpeed = searchByMember(garageForController.ATVsSpeed, atvs.at(i));

                int tireT = searchByMember(garageForController.TiresTSpeed, tires.at(j));
                int tireW = searchByMember(garageForController.TiresWSpeed, tires.at(j));
                int tireA = searchByMember(garageForController.TiresASpeed, tires.at(j));

                int gliderDelay = searchByMember(garageForController.glidersDelay, gliders.at(k));
                int gliderSpeed = searchByMember(garageForController.glidersSpeed, gliders.at(k));

                //terrain.
                double terrainSpeed = ((0.5*t) * kartAc) + kartSpeed + (1.1 * tireT) - (0.5 * gliderDelay);
                //water.
                double waterSpeed = ((0.7*w) * kartAc) + kartSpeed + (1.2*tireW) - (0.7*gliderDelay);
                //air.
                double airSpeed = ((0.5*a) * kartAc) + kartSpeed - (0.9*tireA) + (0.7*gliderSpeed);
                //return sum.
                int returnNum = (terrainSpeed + waterSpeed + airSpeed); 

                // Compare
                if(minTime > returnNum){
                    bestCombination.clear();
                    minTime = returnNum;
                    bestCombination.push_back(atvs.at(i));
                    bestCombination.push_back(tires.at(j));
                    bestCombination.push_back(gliders.at(k));
                }
            }
        }
    }

    //Print best combination.
    std::cout << "The best combination is: " << bestCombination.at(0) << ", " <<bestCombination.at(1) 
    << ", " << bestCombination.at(2) << std::endl;
}

void controller::avgFinishingPos(std::string gamerTag){
    // Get the distances of the track.
    int t = 0, w = 0, a = 0;
    std::vector<std::string> tracks;
    std::ifstream fPlayers("data/players.csv");
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
        tracks.push_back(trackName);
    }

    int avgT = 0, avgW = 0, avgA = 0;

    for(int i = 0; i < tracks.size(); ++i){
        int tt = searchByMember(garageForController.TrackT, tracks.at(i));
        int wt = searchByMember(garageForController.TrackW, tracks.at(i));
        int at = searchByMember(garageForController.TrackA, tracks.at(i));
        avgT += tt;
        avgW += wt;
        avgA += at;
    }

    avgT /= tracks.size();
    avgW /= tracks.size();
    avgA /= tracks.size();
    t = avgT;
    w = avgW;
    a = avgA;

    // create rbtree.

    RedBlackTree<double, std::string> driverSpeed;

    for(int i = 0; i < garageForController.DriverList.size(); ++i){
        double speed = garageForController.DriverList.at(i)->calcSpeed(t, w, a);
        driverSpeed.insert(speed, garageForController.DriverList.at(i)->gamerTag);
    }

    //find pos.
    int counter = 1;
    for(RedBlackTree<double, std::string>::Iterator itr = driverSpeed.begin(); itr != driverSpeed.end(); ++itr){
        if(itr.getValue() == gamerTag){
            break;
        } else {
            counter++;
        }
    }

    // Print data.
    std::cout << "Average finishing position of player " << gamerTag << " is: " << counter << std::endl;
}

void controller::bestCombinationForTracks(std::string track1, std::string track2, std::string track3, std::string track4){
    // Distances.
    int t = 0, w = 0, a = 0;
    int tt1 = searchByMember(garageForController.TrackT, track1);
    int wt1 = searchByMember(garageForController.TrackW, track1);
    int at1 = searchByMember(garageForController.TrackA, track1);

    int tt2 = searchByMember(garageForController.TrackT, track2);
    int wt2 = searchByMember(garageForController.TrackW, track2);
    int at2 = searchByMember(garageForController.TrackA, track2);
    
    int tt3 = searchByMember(garageForController.TrackT, track3);
    int wt3 = searchByMember(garageForController.TrackW, track3);
    int at3 = searchByMember(garageForController.TrackA, track3);
    
    int tt4 = searchByMember(garageForController.TrackT, track4);
    int wt4 = searchByMember(garageForController.TrackW, track4);
    int at4 = searchByMember(garageForController.TrackA, track4);

    int avgt = (tt1 + tt2 + tt3 + tt4) / 4;
    int avgw = (wt1 + wt2 + wt3 + wt4) / 4;
    int avga = (at1 + at2 + at3 + at4) / 4;
    t = avgt;
    w = avgw;
    a = avga;

    //

    //triple for a carro, llantas, y planeador. Crear objeto temporal y sacar su velocidad con calcSpeed(t, w, a).
    //Obtener nombres. con estos se recorreran los arboles.
    std::vector<std::string> karts;
    std::vector<std::string> bikes;
    std::vector<std::string> atvs;
    std::vector<std::string> tires;
    std::vector<std::string> gliders;

    std::ifstream fPieces("data/pieces.csv");
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
                karts.push_back(name);
            } else if(piece == "Tires"){
                std::string name, speedT, speedW, speedA;
                std::getline(ss2, name, ',');
                std::getline(ss2, speedT, ',');
                std::getline(ss2, speedW, ',');
                std::getline(ss2, speedA, ',');
                tires.push_back(name);
            } else if(piece == "Bikes"){
                std::string name, ac, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, ac, ',');
                std::getline(ss2, speed, ',');
                bikes.push_back(name);
            }else if(piece == "ATVs"){
                std::string name, ac, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, ac, ',');
                std::getline(ss2, speed, ',');
                atvs.push_back(name);
            } else if(piece == "Gliders"){
                std::string name, delay, speed;
                std::getline(ss2, name, ',');
                std::getline(ss2, delay, ',');
                std::getline(ss2, speed, ',');
                gliders.push_back(name);
            }
        }
        std::string skipLine;
        std::getline(fPieces, skipLine);
    }

    //After names are gathered, cycle.
    std::vector<std::string> bestCombination;
    double minTime = 100000;

    for(int i = 0; i < karts.size(); ++i){
        for(int j = 0; j < tires.size(); ++j){
            for(int k = 0; k < gliders.size(); ++k){
                double kartAc = searchByMember(garageForController.KartsAceleration, karts.at(i));
                int kartSpeed = searchByMember(garageForController.KartsSpeed, karts.at(i));

                int tireT = searchByMember(garageForController.TiresTSpeed, tires.at(j));
                int tireW = searchByMember(garageForController.TiresWSpeed, tires.at(j));
                int tireA = searchByMember(garageForController.TiresASpeed, tires.at(j));

                int gliderDelay = searchByMember(garageForController.glidersDelay, gliders.at(k));
                int gliderSpeed = searchByMember(garageForController.glidersSpeed, gliders.at(k));

                //terrain.
                double terrainSpeed = ((0.5*t) * kartAc) + kartSpeed + (1.1 * tireT) - (0.5 * gliderDelay);
                //water.
                double waterSpeed = ((0.7*w) * kartAc) + kartSpeed + (1.2*tireW) - (0.7*gliderDelay);
                //air.
                double airSpeed = ((0.5*a) * kartAc) + kartSpeed - (0.9*tireA) + (0.7*gliderSpeed);
                //return sum.
                int returnNum = (terrainSpeed + waterSpeed + airSpeed); 

                // Compare
                if(minTime > returnNum){
                    bestCombination.clear();
                    minTime = returnNum;
                    bestCombination.push_back(karts.at(i));
                    bestCombination.push_back(tires.at(j));
                    bestCombination.push_back(gliders.at(k));
                }
            }
        }
    }

    for(int i = 0; i < bikes.size(); ++i){
        for(int j = 0; j < tires.size(); ++j){
            for(int k = 0; k < gliders.size(); ++k){
                double kartAc = searchByMember(garageForController.BikesAceleration, bikes.at(i));
                int kartSpeed = searchByMember(garageForController.BikesSpeed, bikes.at(i));

                int tireT = searchByMember(garageForController.TiresTSpeed, tires.at(j));
                int tireW = searchByMember(garageForController.TiresWSpeed, tires.at(j));
                int tireA = searchByMember(garageForController.TiresASpeed, tires.at(j));

                int gliderDelay = searchByMember(garageForController.glidersDelay, gliders.at(k));
                int gliderSpeed = searchByMember(garageForController.glidersSpeed, gliders.at(k));

                //terrain.
                double terrainSpeed = ((0.5*t) * kartAc) + kartSpeed + (1.1 * tireT) - (0.5 * gliderDelay);
                //water.
                double waterSpeed = ((0.7*w) * kartAc) + kartSpeed + (1.2*tireW) - (0.7*gliderDelay);
                //air.
                double airSpeed = ((0.5*a) * kartAc) + kartSpeed - (0.9*tireA) + (0.7*gliderSpeed);
                //return sum.
                int returnNum = (terrainSpeed + waterSpeed + airSpeed); 

                // Compare
                if(minTime > returnNum){
                    bestCombination.clear();
                    minTime = returnNum;
                    bestCombination.push_back(bikes.at(i));
                    bestCombination.push_back(tires.at(j));
                    bestCombination.push_back(gliders.at(k));
                }
            }
        }
    }

    for(int i = 0; i < atvs.size(); ++i){
        for(int j = 0; j < tires.size(); ++j){
            for(int k = 0; k < gliders.size(); ++k){
                double kartAc = searchByMember(garageForController.ATVsAceleration, atvs.at(i));
                int kartSpeed = searchByMember(garageForController.ATVsSpeed, atvs.at(i));

                int tireT = searchByMember(garageForController.TiresTSpeed, tires.at(j));
                int tireW = searchByMember(garageForController.TiresWSpeed, tires.at(j));
                int tireA = searchByMember(garageForController.TiresASpeed, tires.at(j));

                int gliderDelay = searchByMember(garageForController.glidersDelay, gliders.at(k));
                int gliderSpeed = searchByMember(garageForController.glidersSpeed, gliders.at(k));

                //terrain.
                double terrainSpeed = ((0.5*t) * kartAc) + kartSpeed + (1.1 * tireT) - (0.5 * gliderDelay);
                //water.
                double waterSpeed = ((0.7*w) * kartAc) + kartSpeed + (1.2*tireW) - (0.7*gliderDelay);
                //air.
                double airSpeed = ((0.5*a) * kartAc) + kartSpeed - (0.9*tireA) + (0.7*gliderSpeed);
                //return sum.
                int returnNum = (terrainSpeed + waterSpeed + airSpeed); 

                // Compare
                if(minTime > returnNum){
                    bestCombination.clear();
                    minTime = returnNum;
                    bestCombination.push_back(atvs.at(i));
                    bestCombination.push_back(tires.at(j));
                    bestCombination.push_back(gliders.at(k));
                }
            }
        }
    }

    //Print best combination.
    std::cout << "The best combination for the 4 tracks is: " << bestCombination.at(0) << ", " <<bestCombination.at(1) 
    << ", " << bestCombination.at(2) << std::endl;
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
                bestCombinationForAllTracks();
                break;
            }
            case 5: {
                // Calculate Best Combination (Specific Track)
                std::cout << "Enter the track name: ";
                std::string trackName;
                std::cin.ignore();  // Ignore the newline character from the previous input
                std::getline(std::cin, trackName);
                std::cout << "Calculating best combination for track: " << trackName << "..." << std::endl;
                bestCombinationForTrack(trackName);
                break;
            }
            case 6: {
                // Calculate Average Finishing Position (Specific Player)
                std::cout << "Enter the player name: ";
                std::string gamerTag;
                std::cin.ignore();  // Ignore the newline character from the previous input
                std::getline(std::cin, gamerTag);
                std::cout << "Calculating average finishing position for player: " << gamerTag << "..." << std::endl;
                avgFinishingPos(gamerTag);
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

                bestCombinationForTracks(trackNames.at(0), trackNames.at(1), trackNames.at(2), trackNames.at(3));

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
