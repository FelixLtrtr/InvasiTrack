/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Définitions des fonctions du programme principal
################################################
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <typeinfo>
#include <regex>
#include <exception> // pour utiliser les exceptions (try catch)

#include "accueil.hpp"
#include ".nlohmann_3.11.3/json.hpp"

using namespace std;
using json = nlohmann::json;

/// FONCTIONS LECTURE/ÉCRITURE DE FICHIERS JSON

void ecrire_json(string filename, json &data){    
    ofstream output_file(filename);
    output_file << data.dump(4, ' ', false, json::error_handler_t::replace) << endl;
    output_file.close();
};

json lire_json(string filename){
    ifstream input_file(filename);
    json data = json::parse(input_file);
    input_file.close();
    return data;
};

/// FONCTIONS DE CONVERSION OBJET -> JSON
// Déclaration des fonctions de conversion
json to_json_conservatoire (Conservatoire data);
json to_json_utilisateur (Utilisateur data);
json to_json_espece (Espece data);
json to_json_action (Action data);
json to_json_ficheSuivi (FicheSuivi data);
json to_json_date (vector<int> data);
json to_json_umap_conservatoires (unordered_map<string, Conservatoire> data);
json to_json_umap_utilisateurs (unordered_map<string, Utilisateur> data);
json to_json_umap_especes (unordered_map<string, Espece> data);
json to_json_umap_actions (unordered_map<string, Action> data);

// Défintions des fonctions de conversion
json to_json_conservatoire (Conservatoire data){
        
    json json_to_return = {{"nom", data.get_Nom()}, {"especes", "NULL"}, {"utilisateurs", "NULL"},{"utilisateurConnecteId", "NULL"}}; //Ne stocke que l'id de l'utilisateur connecté pour plus de simplicité
    
  
    if (!data.get_Utilisateurs().empty()){
        json utilisateurs_to_json = to_json_umap_utilisateurs(data.get_Utilisateurs());
        json_to_return["utilisateurs"] = utilisateurs_to_json;
    }

    if (!data.get_Especes().empty()){
        json especes_to_json = to_json_umap_especes(data.get_Especes());
        json_to_return["especes"] = especes_to_json;
    }

    if (data.get_utilisateurConnecteId() != "NULL"){
        json_to_return["utilisateurConnecteId"] = data.get_utilisateurConnecteId();
    }
    
    return json_to_return;
};

json to_json_utilisateur (Utilisateur data){
    json json_to_return = {{"id", data.get_Id()}, {"mdp", data.get_Mdp()}, {"email", data.get_Email()}, {"type", data.get_Type()}};

    return json_to_return;
};

json to_json_espece (Espece data){

    json json_to_return = {{"nom", data.get_Nom()}, {"taxonomie", data.get_Taxonomie()}, {"categorieListe", data.get_CategorieListe()}, {"priorite", data.get_Priorite()}, {"cycleBiologique", data.get_CycleBiologique()}, {"modeReproduction", data.get_ModeReproduction()}, {"repartitionGeo", data.get_RepartitionGeo()}, {"nbIndividusRecenses", data.get_NbIndividusRecenses()}, {"voieIntroduction", data.get_VoieIntroduction()}, {"potentielDispersion", data.get_PotentielDispersion()}, {"impacts", data.get_Impacts()}, {"potentielInvasif", data.get_PotentielInvasif()}, {"phaseInvasion", data.get_PhaseInvasion()}, {"commentaires", data.get_Commentaires()}, {"actions", "NULL"}};

    if (!data.get_Actions().empty()){
        json actions_to_json = to_json_umap_actions(data.get_Actions());
        json_to_return["actions"] = actions_to_json;
    }

    return json_to_return;
};

json to_json_action (Action data){

    json json_to_return = {{"intitule", data.get_Intitule()}, {"type", data.get_Type()}, {"espece", data.get_Espece()}, {"date", "NULL"}, {"lieu", data.get_Lieu()}, {"idAuteur", data.get_IdAuteur()}, {"statut", data.get_Statut()}, {"commentaires", data.get_Commentaires()}, {"ficheSuivi", "NULL"}};

    if (!data.get_Date().empty()){
        json_to_return["date"] = to_json_date(data.get_Date());
    }

    if (data.get_FicheSuivi().get_IntituleAction() != ""){
        json_to_return["ficheSuivi"] = to_json_ficheSuivi(data.get_FicheSuivi());
    }

    return json_to_return;
};


json to_json_ficheSuivi (FicheSuivi data){
    
    json json_to_return = {{"intituleAction", data.get_IntituleAction()}, {"typeAction", data.get_TypeAction()}, {"idAuteur", data.get_IdAuteur()}, {"descriptif", data.get_Descriptif()}, {"date", "NULL"}, {"lieu", data.get_Lieu()}, {"acteurs", data.get_Acteurs()}, {"materiel", data.get_Materiel()}, {"coutAction", data.get_CoutAction()}, {"financement", data.get_Financement()}};

    if (!data.get_Date().empty()){
        json_to_return["date"] = to_json_date(data.get_Date());
    }

    return json_to_return;
};

json to_json_date (vector<int> data){
    json json_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        json_to_return += *i;
    }

    return json_to_return;
};

// Fonctions de conversion des unordered_map (ne doivent pas recevoir des variables vides)
json to_json_umap_conservatoires (unordered_map<string, Conservatoire> data){
    json json_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        json_to_return[i->first] = to_json_conservatoire(i->second);
    }

    return json_to_return;
};

json to_json_umap_utilisateurs (unordered_map<string, Utilisateur> data){
    json json_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        json_to_return[i->first] = to_json_utilisateur(i->second);
    }

    return json_to_return;
};

json to_json_umap_especes (unordered_map<string, Espece> data){
    json json_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        json_to_return[i->first] = to_json_espece(i->second);
    }

    return json_to_return;
};

json to_json_umap_actions (unordered_map<string, Action> data){
    json json_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        json_to_return[i->first] = to_json_action(i->second);
    }

    return json_to_return;
};


/// FONCTIONS DE CONVERSION JSON -> OBJET
// Déclaration des fonctions de conversion
Conservatoire json_to_conservatoire(json &data);
Utilisateur json_to_utilisateur(json &data);
Espece json_to_espece(json &data);
Action json_to_action(json &data);
FicheSuivi json_to_ficheSuivi(json &data);
vector<int> json_to_date(json &data);
unordered_map<string, Conservatoire> json_to_umap_conservatoires(json &data);
unordered_map<string, Utilisateur> json_to_umap_utilisateurs(json &data);
unordered_map<string, Espece> json_to_umap_especes(json &data);
unordered_map<string, Action> json_to_umap_actions(json &data);

// Définitions des fonctions de conversion
Conservatoire json_to_conservatoire(json &data){
    Conservatoire conservatoire_to_return(data["nom"], false);

    if (data["utilisateurs"] != "NULL"){
        conservatoire_to_return.set_Utilisateurs(json_to_umap_utilisateurs(data["utilisateurs"]));
    }

    if (data["especes"] != "NULL"){
        conservatoire_to_return.set_Especes(json_to_umap_especes(data["especes"]));
    }

    if (data["utilisateurConnecteId"] != "NULL"){
        conservatoire_to_return.set_utilisateurConnecteId(data["utilisateurConnecteId"]);
    }

    return conservatoire_to_return;
};

Utilisateur json_to_utilisateur(json &data){

    if (data["type"] == "reporter"){
        Reporter utilisateur_to_return(data["id"], data["mdp"], data["email"], false);
        return utilisateur_to_return;
    }

    Consultant utilisateur_to_return(data["id"], data["mdp"], data["email"], false);

    return utilisateur_to_return;
};

Espece json_to_espece(json &data){
    Espece espece_to_return(data["nom"], data["taxonomie"], data["categorieListe"], data["priorite"], data["cycleBiologique"], data["modeReproduction"], data["repartitionGeo"], data["nbIndividusRecenses"], data["voieIntroduction"], data["potentielDispersion"], data["impacts"], data["potentielInvasif"], data["phaseInvasion"], data["commentaires"], false);

    if (data["actions"] != "NULL"){
        espece_to_return.set_Actions(json_to_umap_actions(data["actions"]));
    }

    return espece_to_return;
};

Action json_to_action(json &data){
    Action action_to_return(data["intitule"], data["type"], data["espece"], json_to_date(data["date"]), data["lieu"], data["idAuteur"], data["statut"], data["commentaires"], false);

    if (data["ficheSuivi"] != "NULL"){
        action_to_return.set_FicheSuivi(json_to_ficheSuivi(data["ficheSuivi"]));
    }

    return action_to_return;
};

FicheSuivi json_to_ficheSuivi(json &data){
    FicheSuivi ficheSuivi_to_return(data["intituleAction"], data["typeAction"], data["idAuteur"], data["descriptif"], json_to_date(data["date"]), data["lieu"], data["acteurs"], data["materiel"], data["coutAction"], data["financement"], false);

    return ficheSuivi_to_return;
};

vector<int> json_to_date(json &data){
    vector<int> date_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        date_to_return.push_back(*i);
    }

    return date_to_return;
};

// Fonctions de conversion des unordered_map (ne doivent pas recevoir des variables vides)
unordered_map<string, Conservatoire> json_to_umap_conservatoires(json &data){
    unordered_map<string, Conservatoire> umap_conservatoires_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        umap_conservatoires_to_return[i.key()] = json_to_conservatoire(i.value());
    }

    return umap_conservatoires_to_return;
};

unordered_map<string, Utilisateur> json_to_umap_utilisateurs(json &data){
    unordered_map<string, Utilisateur> umap_utilisateurs_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        umap_utilisateurs_to_return[i.key()] = json_to_utilisateur(i.value());
    }

    return umap_utilisateurs_to_return;
};

unordered_map<string, Espece> json_to_umap_especes(json &data){
    unordered_map<string, Espece> umap_especes_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        umap_especes_to_return[i.key()] = json_to_espece(i.value());
    }

    return umap_especes_to_return;
};

unordered_map<string, Action> json_to_umap_actions(json &data){
    unordered_map<string, Action> umap_actions_to_return;

    for (auto i = data.begin(); i != data.end(); i++){
        umap_actions_to_return[i.key()] = json_to_action(i.value());
    }

    return umap_actions_to_return;
};

/// GESTION DES EXCEPTIONS
struct too_much_connection_try : public exception {
   const char * what () const throw () {
      return "Trop de tentatives de connexion échouées. Sortie du programme.";
   }
};

/// SAUVEGARDE DES CONSERVATOIRES
void sauvegarde_conservatoires(Accueil &accueil, unique_ptr<Conservatoire> &conservatoireCourant){
    unordered_map<string, Conservatoire> conservatoires = accueil.get_Conservatoires();
    conservatoires[accueil.get_ConservatoireSelectionneNom()] = *conservatoireCourant;
    accueil.set_Conservatoires(conservatoires);

    json save_conservatoires = to_json_umap_conservatoires(conservatoires);

    for (auto item=conservatoires.begin(); item != conservatoires.end();++item) {
        json tmp_utilisateurs = to_json_umap_utilisateurs(item->second.get_Utilisateurs());

        json tmp_especes = to_json_umap_especes(item->second.get_Especes());

        save_conservatoires.merge_patch({{item->first, {{"utilisateurs", tmp_utilisateurs}, {"especes", tmp_especes}}}});
    }

    ecrire_json("conservatoires.json", save_conservatoires);
}