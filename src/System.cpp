//
// Created by Loreas Clonen on 3/9/17.
//

#include "System.h"
#include <memory>


using namespace std;

System::System() {
    _initCheck = this;
}

bool System::properlyInitialized() {
    return _initCheck == this;
}

map<string, Station *> System::getStations() {
    return stations;
}

map<int, Tram *> System::getTrams() {
    return trams;
}

void System::addStation(string naam, Station* station) {

        System::stations[naam] = station;
}

void System::addTram(int lijnNr, Tram* tram){
    System::trams[lijnNr] = tram;
}

void System::addPassagier(string naam, Passagier* passagier) {

    System::passagiers[naam] = passagier;
}

string System::Output(){
    ofstream outputLog;
    outputLog.open("LogFiles/outputLog.txt");

    string output =  "--== STATIONS ==--\n";
    for(auto c : System::stations){
        output += "Station " + c.first + "\n";
        output += "Type: " + c.second->getType() + "\n";
        output += "--== SPOREN ==--\n";
        for(auto x : c.second->getSporen()){
            output += "Spoor " + to_string(x.second->getSpoorNr()) + "\n";
            output += "-> Station " + x.second->getVolgende() + "\n";
            output += "<- Station " + x.second->getVorige() + "\n";
        }
        output += "Wachtende passagiers:\n";
        for(auto q : c.second->getPassagier()){
            Passagier* current_passagier = System::passagiers.find(q)->second;
            output += " - " + q + ", " + to_string(current_passagier->getHoeveelheid()) + " mensen, ";
            output += "reist naar Station: " + current_passagier->getEindStation() + "\n";
        }
    }

    output += "\n--== TRAMS ==--\n";
    for(auto c : System::trams){
        output += "Tram " + to_string(c.first) + " nr " + to_string(c.second->getVoertuigNr()) + "\n";
        output += "Zitplaatsen: " + to_string(c.second->getZitplaatsen()) + "\n";
        output += "Snelheid: " + to_string(c.second->getSnelheid()) + "km/h" + "\n";
        if(c.second->getHuidigStation() == "") {
            output += "Huidig Station: " + c.second->getBeginStation() + "\n";
        }
        else{
            output += "Huidig Station: " + c.second->getHuidigStation() + "\n";
        }
        }

    outputLog << output;
    outputLog.close();
    return output;
}

Station* System::findNextStation(Station* station, int spoorNr, string type){
    //fout spoor zit niet in station!!!
    Spoor* spoor = station->getSporen().find(spoorNr)->second;
    string naam_volgend_station = spoor->getVolgende();
    Station * volgendStation = stations.find(naam_volgend_station)->second;

    if(type == "PCC"){
        return volgendStation;
    }
    else {
        if(volgendStation->getType() == "metrostation"){
            return volgendStation;
        }
        else{
            return findNextStation(volgendStation, spoorNr, type);
        }
    }
}

string System::verplaatsTram(Tram* tram){

    string stationsNaam = tram->getHuidigStation();

    if(stationsNaam == ""){
        stationsNaam = tram ->getBeginStation();
    }

    Station* volgendStation = findNextStation(System::getStations().find(stationsNaam)->second, tram->getLijnNr(),
            tram->getType());

    string volgende = volgendStation->getNaam();

    tram->setHuidigStation(volgende);
    string output = "Tram " + to_string(tram->getVoertuigNr()) + " reed van station " + stationsNaam
                    + " naar station " + volgende + "\n";
    return output;
}

bool System::Valid_circuit() {
    for (auto it_stations : stations) {
        for(auto it_spoor : it_stations.second->getSporen()){
            Station* current_station = it_stations.second;
            string next_naam = current_station->getSporen().find(it_spoor.first)->second->getVolgende();
            Station* next_station = stations.find(next_naam)->second;
            if(next_station == stations.end()->second){
                return false;
            }
            Spoor* next_spoor = next_station->getSporen().find(it_spoor.first)->second;
            if(next_spoor->getVorige() != it_stations.first){
                return false;
            }
        }
    }
    return true;
}

void System::properlyparsed() {
    REQUIRE(System::properlyParsed, "XML File wasn't properly parsed.");
    ENSURE(System::Valid_circuit(), "Circuit is not valid.");
}

string System::help_ronde_rijden(int aantal_klaar, int aantal_trams, string output){

    for(auto it_tram: trams){

        if(it_tram.second->getHuidigStation() != it_tram.second->getBeginStation()){
            string huidigStation;
            if(it_tram.second->getHuidigStation() == ""){
                huidigStation = it_tram.second->getBeginStation();
            }
            else{
                huidigStation = it_tram.second->getHuidigStation();
            }
            // Afstappen
            if(it_tram.second->getPassagiers().size() != 0){
                set<string> copy_passagiers = it_tram.second->getPassagiers();
                for(auto &passagier : copy_passagiers) {
                    if(huidigStation == passagiers.find(passagier)->second->getEindStation()) {
                        stations.find(huidigStation)->second->addPassagier(passagier);
                        output += it_tram.second->removePassagiers(passagier, passagiers.find(
                                passagier)->second->getHoeveelheid(), huidigStation);
                    }
                }
            }
            // Opstappen
            if(stations.find(huidigStation)->second->getPassagier().size() != 0){
                set<string> copy_passagiers = stations.find(huidigStation)->second->getPassagier();
                for(auto &passagier : copy_passagiers) {
                    if(huidigStation != passagiers.find(passagier)->second->getEindStation()) {
                        output += it_tram.second->addPassagiers(passagier,
                                            passagiers.find(passagier)->second->getHoeveelheid(), huidigStation);
                        stations.find(huidigStation)->second->removePassagier(passagier);
                    }
                }
            }
            output += verplaatsTram(it_tram.second);
        }
        else{
            aantal_klaar += 1;
        }
    }
    if(aantal_klaar < aantal_trams){

        return help_ronde_rijden(aantal_klaar,aantal_trams, output);
    }
    else{
        return output;
    }

}


string System::ronde_rijden() {
    int aantal_klaar = 0;
    int aantal_trams = trams.size();
    string output = "";
    output = help_ronde_rijden(aantal_klaar,aantal_trams,output);
    // alle huidige stations leeg zetten voor sys reset
    for(auto it_trams : trams){
        it_trams.second->setHuidigStation("");
    }
    return output;
}

void System::setProperlyParsed(bool properlyParsed) {
    System::properlyParsed = properlyParsed;
}

map<string, Passagier *> System::getPassagiers() {
    return passagiers;
}

void System::autoSimulation() {
    ofstream file;
    file.open("LogFiles/autoSimulation.txt");

    file << "===================" << endl;
    file << "Starting Simulation" << endl;
    file << "===================" << endl;

    file << ronde_rijden();
    for(auto &tram : trams){
        if(tram.second->getPassagiers().size() != 0){
            file << endl << "De passagiers in Tram " << tram.second->getVoertuigNr() <<
                 " raken niet op hun eindbestemming" << endl;
        }
    }
    file << "===================" << endl;
    file << "Simulation finished" << endl;
    file << "===================";

    file.close();
}


