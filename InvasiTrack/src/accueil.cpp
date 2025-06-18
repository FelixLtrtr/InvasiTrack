/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Définitions des méthodes de la classe Accueil et code de test
################################################
*/

#include <iostream>
#include <cstring>
#include <unordered_map>
#include <list>
#include <iterator> // pour utiliser les itérateurs, ici advance()
#include <fstream>
#include <limits> // pour utiliser numeric_limits
#include <memory> // pour utiliser les pointeurs intelligents


#include "accueil.hpp"

using namespace std;
using json = nlohmann::json;


void Accueil::choix_conservatoire(){
    
    unordered_map<string, Conservatoire> listeConservatoires = this->get_Conservatoires();

    // Récupération des noms des conservatoires dans une liste
    int cpt = 1;
    string affichage_liste;
    list<string> liste_noms;
    affichage_liste += "0. Quitter    ";

    for (auto item=listeConservatoires.begin(); item != listeConservatoires.end();++item, ++cpt) {
        affichage_liste += to_string(cpt) + ". " + item -> first + "    ";
        liste_noms.push_back(item -> first);
    }

    // Sélection du conservatoire avec vérification de la saisie
    int reponse;

    // Vérification de la saisie de l'utilisateur
    verification_saisie_nombre(reponse, affichage_liste, 0, listeConservatoires.size(), "", true, "MENU DE SELECTION DU CONSERVATOIRE", "", "", "");

    // Quitter le programme
    if (reponse == 0) {
        cout << "\nInvasiTrack a été fermé.\n" << endl;
        exit(0);
    }

    // Attribution du conservatoire sélectionné à l'attribut conservatoire_selectionne
    
    auto liste_emplacement = liste_noms.begin(); // L'itérateur de la liste est initialisé à la première valeur de la liste

    advance(liste_emplacement,reponse-1); // L'itératuer est déplacé jusqu'à l'emplacement de la liste correspondant à la réponse, -1 car la liste commence des noms ne contient pas l'option 0 (quitter) et le premier élément de la liste est à le numéro 1 dans la liste affichée
    
    this->set_ConservatoireSelectionneNom(*liste_emplacement);

    cout << "\nConservatoire sélectionné : " << this->get_ConservatoireSelectionneNom() << endl;
};

unique_ptr<Conservatoire> Accueil::get_ConservatoireSelectionne(){
    return make_unique<Conservatoire>(this->get_Conservatoires()[this->get_ConservatoireSelectionneNom()]);
};