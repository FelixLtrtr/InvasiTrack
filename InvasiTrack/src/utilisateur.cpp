/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Définitions des méthodes de la classe Utilisateur et code de test
################################################
*/

#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm> // pour utiliser la fonction sort()
#include <memory> // pour utiliser les pointeurs intelligents
#include <limits> // pour utiliser numeric_limits
#include <iomanip> // pour utiliser setfill()

#include "utilisateur.hpp"


using namespace std;

void verification_saisie_nombre_utilisateur(auto &saisie, string affichage_liste, int index_choix_min, int index_choix_max, string phrase_selection, bool afficher_menu, string menu, string conservatoire, string utilisateur, string type_utilisateur, string nom_espece_choisie, unordered_map<string, Espece> &especes , string nom_action_choisie){
    
    if (afficher_menu) {
        cout << "\n\n------------------" + string(menu.size(), '-') + "-" << endl;
            cout << "| InvasiTrack -- " << menu << " |" << endl;
            cout << "------------------" + string(menu.size(), '-') + "-" << endl;

        if (conservatoire != "") {cout << "\n# Conservatoire sélectionné : " << conservatoire << endl;}

        if (utilisateur != "") {cout << "# Utilisateur connecté : " << utilisateur << endl;}

        if (type_utilisateur != "") {cout << "# Type : " << type_utilisateur << endl;}

        if (phrase_selection == "") {phrase_selection = "Veuillez choisir une option (merci de sélectionner le numéro correspondant).";}

        if (nom_espece_choisie != "" && nom_action_choisie == "") { // Fiche espèce
            cout << "\n# Espèce sélectionnée : " << nom_espece_choisie << endl;
            cout << "\t -- Taxonomie : " << especes[nom_espece_choisie].get_Taxonomie() << endl;
            cout << "\t -- Catégorie de la liste : " << especes[nom_espece_choisie].get_CategorieListe() << endl;
            cout << "\t -- Priorité : " << especes[nom_espece_choisie].get_Priorite() << endl;
            cout << "\t -- Cycle biologique : " << especes[nom_espece_choisie].get_CycleBiologique() << endl;
            cout << "\t -- Mode de reproduction : " << especes[nom_espece_choisie].get_ModeReproduction() << endl;
            cout << "\t -- Répartition géographique : " << especes[nom_espece_choisie].get_RepartitionGeo() << endl;
            cout << "\t -- Nombre d'individus recensés : " << especes[nom_espece_choisie].get_NbIndividusRecenses() << endl;
            cout << "\t -- Voie d'introduction : " << especes[nom_espece_choisie].get_VoieIntroduction() << endl;
            cout << "\t -- Potentiel de dispersion : " << especes[nom_espece_choisie].get_PotentielDispersion() << endl;
            cout << "\t -- Impacts : " << especes[nom_espece_choisie].get_Impacts() << endl;
            cout << "\t -- Potentiel invasif : " << especes[nom_espece_choisie].get_PotentielInvasif() << endl;
            cout << "\t -- Phase d'invasion : " << especes[nom_espece_choisie].get_PhaseInvasion() << endl;
            cout << "\t -- Nombre d'actions : " << especes[nom_espece_choisie].get_Actions().size() << endl;
            cout << "\t -- Commentaires : " << especes[nom_espece_choisie].get_Commentaires() << endl;
        }

        if (nom_action_choisie != "") {
            unordered_map<string, Action> actions = especes[nom_espece_choisie].get_Actions();

            if (menu.find("FICHE DE SUIVI") != string::npos) {
                cout << "\n# Espèce sélectionnée : " << nom_espece_choisie << endl;
                cout << "\n# Action sélectionnée : " << nom_action_choisie << endl;
                cout << "\t -- Type : " << actions[nom_action_choisie].get_FicheSuivi().get_TypeAction() << endl;
                cout << "\t -- Auteur de l'action : " << actions[nom_action_choisie].get_FicheSuivi().get_IdAuteur() << endl;
                cout << "\t -- Lieu : " << actions[nom_action_choisie].get_FicheSuivi().get_Lieu() << endl;
                cout << "\t -- Date : " << actions[nom_action_choisie].get_FicheSuivi().get_Date()[2] << "/" << actions[nom_action_choisie].get_FicheSuivi().get_Date()[1] << "/" << actions[nom_action_choisie].get_FicheSuivi().get_Date()[0] << endl;
                cout << "\t -- Acteurs : " << actions[nom_action_choisie].get_FicheSuivi().get_Acteurs() << endl;
                cout << "\t -- Coût de l'action : " << actions[nom_action_choisie].get_FicheSuivi().get_CoutAction() << endl;
                cout << "\t -- Financement : " << actions[nom_action_choisie].get_FicheSuivi().get_Financement() << endl;
                cout << "\t -- Matériel : " << actions[nom_action_choisie].get_FicheSuivi().get_Materiel() << endl;
                cout << "\t -- Descriptif : " << actions[nom_action_choisie].get_FicheSuivi().get_Descriptif() << endl;
            } else if (menu.find("ACTION") != string::npos && menu.find("FICHE DE SUIVI") == string::npos) {
                cout << "\n# Espèce sélectionnée : " << nom_espece_choisie << endl;
                cout << "\n# Action sélectionnée : " << nom_action_choisie << endl;
                cout << "\t -- Type : " << actions[nom_action_choisie].get_Type() << endl;
                cout << "\t -- Date : " << actions[nom_action_choisie].get_Date()[2] << "/" << actions[nom_action_choisie].get_Date()[1] << "/" << actions[nom_action_choisie].get_Date()[0] << endl;
                cout << "\t -- Auteur de l'action : " << actions[nom_action_choisie].get_IdAuteur() << endl;
                cout << "\t -- Lieu : " << actions[nom_action_choisie].get_Lieu() << endl;
                cout << "\t -- Statut : " << actions[nom_action_choisie].get_Statut() << endl;
                cout << "\t -- Commentaires : " << actions[nom_action_choisie].get_Commentaires() << endl;
            } 
        }
    }
    
    // Boucle de vérification de la saisie (uniquement des nombres)
    bool bonne_reponse = false;
    while (!bonne_reponse) {
        if (afficher_menu) { // Espacement
            cout << "\n" << phrase_selection << endl;
        } else {
            cout << phrase_selection << endl;
        }
        cout << affichage_liste << endl;
        cin >> saisie;

        if (cin.fail()) { // si une lettre est entrée, saisie = 0 et cin est en erreur car saisie est de type int
            cout << "\n\nERREUR DE SAISIE : CECI N'EST PAS UN NOMBRE.\n" << endl;
            cin.clear(); // supprime le code d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
        } else if (saisie <= index_choix_max && saisie >= index_choix_min){ // saisie doit être compris entre index_choix_min et index_choix_max
            bonne_reponse = true;
        } else {
            cout << "\n\nERREUR DE SAISIE : CE NOMBRE NE CORRESPOND À AUCUNE OPTION.\n" << endl;
        }
    }
};

bool Utilisateur::verifier_espece(string nom_espece, unordered_map<string, Espece> &especes){
    if (especes.find(nom_espece) != especes.end()) {
        return true;
    } else {
        return false;
    }
};

bool Utilisateur::verifier_action(string nom_action, unordered_map<string, Action> &actions){
    if (actions.find(nom_action) != actions.end()) {
        return true;
    } else {
        return false;
    }
};

bool Utilisateur::nom_valide(string &nom_a_valider, string type_nom, bool selection_recherche, string verbe_menu){
    bool nom_maj = false;
    int cpt_valide = 0;
    do {
        cpt_valide++;

        if (selection_recherche){
            cout << "\nVeuillez entrer le nom de l'" + type_nom + " à " + verbe_menu + "." << endl;
        } else {
            cout << "\nNom de l'" + type_nom + " ? (En majuscules et sans accent uniquement).\nSi vous voulez revenir au menu précédent, veuillez entrer 'ANNULER'." << endl;
        }
        
        getline(cin, nom_a_valider,'\n'); cout << endl;

        for (size_t i=0; i<nom_a_valider.size(); i++) {
            if (islower(nom_a_valider[i])) {
                if (cpt_valide == 3) {
                    cout << "\nERREUR DE SAISIE : LE NOM DOIT ÊTRE EN MAJUSCULES." << endl;
                } else {
                    cout << "\nERREUR DE SAISIE : LE NOM DOIT ÊTRE EN MAJUSCULES.\n\nSi vous voulez annuler l'opération en cours, veuillez entrer 'ANNULER'." << endl;
                }
                
                break;
            } else if (i == nom_a_valider.size()-1) {
                return true;
            }
        }
    } while (!nom_maj && cpt_valide<3);

    return false;
};

string Utilisateur::selection_recherche(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes, string nom_espece_choisie, string menu){

    string type_recherche;
    string type_recherche_maj;
    string nom_item_choisi;
    
    if (nom_espece_choisie == "") {
        type_recherche = "espèce";
        type_recherche_maj = "ESPECE";
    } else if (nom_espece_choisie != "") {
        type_recherche = "action";
        type_recherche_maj = "ACTION";
    }

    // Affichage du menu de sélection de l'espèce/action
    menu_selection:
    string affichage_liste = "0. Retour    1. Afficher la liste des " + type_recherche +"s   2. Rechercher par nom";

    int reponse;
    verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 2, "", true, menu + " -- SELECTION DE L'" + type_recherche_maj, conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes, "");

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    string verbe_menu;
    if (menu.find("MENU DE MODIFICATION D'UNE")== 0) {
        verbe_menu = "modifier";
    } else if (menu.find("MENU DE SUPPRESSION D'UNE")== 0) {
        verbe_menu = "supprimer";
    } else if (menu.find("MENU DE CONSULTATION D'UNE")== 0) {
        verbe_menu = "consulter";
    } else {
        verbe_menu = "sélectionner";
    }

    // Retour au menu principal
    if (reponse == 0) {
        return ("RETOUR");
    } else if (reponse == 1) { // Affichage de la liste des espèces/actions
        map<int, vector<string>> liste_items;

        if (type_recherche == "espèce") { // Filtre les espèces par première lettre
            for (auto item = especes.begin(); item != especes.end(); item++) {
                switch (item->second.get_Nom()[0]){
                    case 'A':
                        liste_items[1].push_back(item->second.get_Nom());
                        break;
                    case 'B':
                        liste_items[2].push_back(item->second.get_Nom());
                        break;
                    case 'C':
                        liste_items[3].push_back(item->second.get_Nom());
                        break;
                    case 'D':
                        liste_items[4].push_back(item->second.get_Nom());
                        break;
                    case 'E':
                        liste_items[5].push_back(item->second.get_Nom());
                        break;
                    case 'F':
                        liste_items[6].push_back(item->second.get_Nom());
                        break;
                    case 'G':
                        liste_items[7].push_back(item->second.get_Nom());
                        break;
                    case 'H':
                        liste_items[8].push_back(item->second.get_Nom());
                        break;
                    case 'I':
                        liste_items[9].push_back(item->second.get_Nom());
                        break;
                    case 'J':
                        liste_items[10].push_back(item->second.get_Nom());
                        break;
                    case 'K':
                        liste_items[11].push_back(item->second.get_Nom());
                        break;
                    case 'L':
                        liste_items[12].push_back(item->second.get_Nom());
                        break;
                    case 'M':
                        liste_items[13].push_back(item->second.get_Nom());
                        break;
                    case 'N':
                        liste_items[14].push_back(item->second.get_Nom());
                        break;
                    case 'O':
                        liste_items[15].push_back(item->second.get_Nom());
                        break;
                    case 'P':
                        liste_items[16].push_back(item->second.get_Nom());
                        break;
                    case 'Q':
                        liste_items[17].push_back(item->second.get_Nom());
                        break;
                    case 'R':
                        liste_items[18].push_back(item->second.get_Nom());
                        break;
                    case 'S':
                        liste_items[19].push_back(item->second.get_Nom());
                        break;
                    case 'T':
                        liste_items[20].push_back(item->second.get_Nom());
                        break;
                    case 'U':
                        liste_items[21].push_back(item->second.get_Nom());
                        break;
                    case 'V':
                        liste_items[22].push_back(item->second.get_Nom());
                        break;
                    case 'W':
                        liste_items[23].push_back(item->second.get_Nom());
                        break;
                    case 'X':
                        liste_items[24].push_back(item->second.get_Nom());
                        break;
                    case 'Y':
                        liste_items[25].push_back(item->second.get_Nom());
                        break;
                    case 'Z':
                        liste_items[26].push_back(item->second.get_Nom());
                        break;
                    default:
                        break;
                }
            }
        } else if (type_recherche == "action") { // Filtre les actions par première lettre
            unordered_map<string, Action> actions = especes[nom_espece_choisie].get_Actions();

            for (auto item = actions.begin(); item != actions.end(); item++) {
                switch (item->second.get_Intitule()[0]){
                    case 'A':
                        liste_items[1].push_back(item->second.get_Intitule());
                        break;
                    case 'B':
                        liste_items[2].push_back(item->second.get_Intitule());
                        break;
                    case 'C':
                        liste_items[3].push_back(item->second.get_Intitule());
                        break;
                    case 'D':
                        liste_items[4].push_back(item->second.get_Intitule());
                        break;
                    case 'E':
                        liste_items[5].push_back(item->second.get_Intitule());
                        break;
                    case 'F':
                        liste_items[6].push_back(item->second.get_Intitule());
                        break;
                    case 'G':
                        liste_items[7].push_back(item->second.get_Intitule());
                        break;
                    case 'H':
                        liste_items[8].push_back(item->second.get_Intitule());
                        break;
                    case 'I':
                        liste_items[9].push_back(item->second.get_Intitule());
                        break;
                    case 'J':
                        liste_items[10].push_back(item->second.get_Intitule());
                        break;
                    case 'K':
                        liste_items[11].push_back(item->second.get_Intitule());
                        break;
                    case 'L':
                        liste_items[12].push_back(item->second.get_Intitule());
                        break;
                    case 'M':
                        liste_items[13].push_back(item->second.get_Intitule());
                        break;
                    case 'N':
                        liste_items[14].push_back(item->second.get_Intitule());
                        break;
                    case 'O':
                        liste_items[15].push_back(item->second.get_Intitule());
                        break;
                    case 'P':
                        liste_items[16].push_back(item->second.get_Intitule());
                        break;
                    case 'Q':
                        liste_items[17].push_back(item->second.get_Intitule());
                        break;
                    case 'R':
                        liste_items[18].push_back(item->second.get_Intitule());
                        break;
                    case 'S':
                        liste_items[19].push_back(item->second.get_Intitule());
                        break;
                    case 'T':
                        liste_items[20].push_back(item->second.get_Intitule());
                        break;
                    case 'U':
                        liste_items[21].push_back(item->second.get_Intitule());
                        break;
                    case 'V':
                        liste_items[22].push_back(item->second.get_Intitule());
                        break;
                    case 'W':
                        liste_items[23].push_back(item->second.get_Intitule());
                        break;
                    case 'X':
                        liste_items[24].push_back(item->second.get_Intitule());
                        break;
                    case 'Y':
                        liste_items[25].push_back(item->second.get_Intitule());
                        break;
                    case 'Z':
                        liste_items[26].push_back(item->second.get_Intitule());
                        break;
                }
            }
        }
        
        menu_affichage_selection:
        affichage_liste = "0. Retour";
        int index_affichage = 0;
        vector<int> index_items_non_vide;

        for (int index=1; index<=26; index++) {
            if (liste_items[index].size() != 0) {
                index_affichage++;
                index_items_non_vide.push_back(index);

                affichage_liste += "    " + to_string(index_affichage) + ". " + char(index+64) + " (" + to_string(liste_items[index].size()) + ")";
                // Code ASCII des majuscules : 65-90, d'où char(index+64)
            }
        }

        string param_nom_espece_choisie;
        if (type_recherche == "espèce") {
            param_nom_espece_choisie = "";
        } else if (type_recherche == "action") {
            param_nom_espece_choisie = nom_espece_choisie;
        }

        // Sélection de la première lettre avec vérification de la saisie
        if (index_items_non_vide.size() != 0) {
            verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, index_affichage, "Veuillez sélectionner le numéro correspond à la première lettre de l'" + type_recherche + " à " + verbe_menu + ". Le nombre d'" + type_recherche + "s est indiqué entre parenthèses.", true, menu + " -- SELECTION D'UNE " + type_recherche_maj + " -- AFFICHAGE DES " + type_recherche_maj + "S", conservatoire, utilisateur, type_utilisateur, param_nom_espece_choisie, especes, "");
        } else {
            verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, index_affichage, "Il n'y a pas d'" + type_recherche + " à " + verbe_menu + ".", true, menu + " -- SELECTION D'UNE " + type_recherche_maj + " -- AFFICHAGE DES " + type_recherche_maj + "S", conservatoire, utilisateur, type_utilisateur, param_nom_espece_choisie, especes, "");
        }

        // Retour au menu précédent
        if (reponse == 0) {
            goto menu_selection;
        } else {
            // Affichage de la liste des espèces commençant par la lettre choisie
            reponse = index_items_non_vide[reponse-1]; // reponse prend la valeur de l'index de la lettre choisie dans la liste liste_items (A=1, B=2, etc) car le numéro choisi à l'étape précédente correspond à celui d'une liste triée ne contenant que les indexs des lettres ayant au moins une valeur, ce qui serait faux. -1 car la liste commence à l'index 0.

            // Tri alphabétique dans le vecteur correspondant à la lettre choisie
            sort(liste_items[reponse].begin(), liste_items[reponse].end());

            
            affichage_liste = "0. Retour";
            vector<string> liste_items_triees;

            int index = 1;
            for (auto item : liste_items[reponse]) {
                affichage_liste += "    " + to_string(index) + ". " + item;
                index++;
                liste_items_triees.push_back(item);
            }
        

            // Vérification de la saisie de l'utilisateur   
            verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, liste_items[reponse].size(), "Veuillez choisir une " + type_recherche + " à " + verbe_menu + "." , true, menu + " -- SELECTION D'UNE " + type_recherche_maj + " -- AFFICHAGE DES " + type_recherche_maj + "S", conservatoire, utilisateur, type_utilisateur, param_nom_espece_choisie, especes, "");

            // Retour au menu précédent
            if (reponse == 0) {
                goto menu_affichage_selection;
            } else { // Sélection de l'espèce ou de l'action
                if (type_recherche == "espèce") {
                    nom_item_choisi = liste_items_triees[reponse-1];
                } else if (type_recherche == "action") {
                    nom_item_choisi = liste_items_triees[reponse-1];
                }
            }
        }

    } else if (reponse == 2) { // Recherche par nom

        cout << "\n\n-------------------------------------------------------------------" + string(menu.size(), '-') << endl;
        cout <<     "| InvasiTrack -- " + menu + " -- SELECTION D'UNE " + type_recherche_maj + " -- RECHERCHE PAR NOM |" << endl;
        cout <<     "-------------------------------------------------------------------" + string(menu.size(), '-') << endl;

        cout << "\n# Conservatoire sélectionné : " << conservatoire << endl;
        cout << "# Utilisateur connecté : " << utilisateur << endl;
        cout << "# Type d'utilisateur : " << type_utilisateur << endl;

        // Sélection de l'espèce/l'action avec vérification de la saisie
        int cpt = 1;
        nom_espece_valide_2:

        cin.sync();

        cout << "\nVous avez sélectionné la recherche par nom : il est nécessaire de connaître le nom complet de l'" + type_recherche + " et l'écrire en majuscules, sans accent.\nSi vous voulez revenir au menu précédent, veuillez entrer 'ANNULER'." << endl;
        
        if (nom_valide(nom_item_choisi, type_recherche, true, verbe_menu) == false && cpt==3){
            cout << "Vous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
            return ("NULL");
        }

        if (type_recherche == "espèce") { // Vérification que l'espèce existe
            if (verifier_espece(nom_item_choisi, especes) == false && nom_item_choisi != "ANNULER" && cpt<3){
                cout << "\n\n ERREUR : CETTE ESPECE N'EXISTE PAS.\nVeuillez entrer un nom d'espèce existant." << endl;
                cpt++;
                goto nom_espece_valide_2;
                
            } else if (verifier_espece(nom_item_choisi, especes) == false && nom_item_choisi == "ANNULER") {
                if (menu == "MENU DE MODIFICATION D'UNE ESPECE") {
                    cout << "\nModification de l'espèce annulée. Retour au menu précédent." << endl;
                } else if (menu == "MENU DE SUPPRESSION D'UNE ESPECE") {
                    cout << "\nSuppression de l'espèce annulée. Retour au menu précédent." << endl;
                } else if (menu == "MENU DE CONSULTATION D'UNE ESPECE") {
                    cout << "\nConsultation de l'espèce annulée. Retour au menu précédent." << endl;
                }
            
                return ("NULL");

            } else if (verifier_espece(nom_item_choisi, especes) == false && cpt==3){
                cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
                return ("NULL");
            }

        } else if (type_recherche == "action") { // Vérification que l'action existe
            unordered_map<string, Action> actions = especes[nom_espece_choisie].get_Actions();

            if (verifier_action(nom_item_choisi, actions) == false && nom_item_choisi != "ANNULER" && cpt<3){
                cout << "\n\n ERREUR : CETTE ACTION N'EXISTE PAS.\nVeuillez entrer un nom d'action existant." << endl;
                cpt++;
                goto nom_espece_valide_2;
                
            } else if (verifier_action(nom_item_choisi, actions) == false && nom_item_choisi == "ANNULER") {
                if (menu == "MENU DE MODIFICATION D'UNE ACTION") {
                    cout << "\nModification de l'action annulée. Retour au menu précédent." << endl;
                } else if (menu == "MENU DE SUPPRESSION D'UNE ACTION") {
                    cout << "\nSuppression de l'action annulée. Retour au menu précédent." << endl;
                } else if (menu == "MENU DE CONSULTATION D'UNE ACTION") {
                    cout << "\nConsultation de l'action annulée. Retour au menu précédent." << endl;
                }
            
                return ("NULL");

            } else if (verifier_action(nom_item_choisi, actions) == false && cpt==3){
                cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
                return ("NULL");
            }   
        }
    }

    return (nom_item_choisi);
};

unique_ptr<Espece> Reporter::ajouter_espece(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes){
    string nom, taxonomie, categorieListe, priorite, cycleBiologique, modeReproduction, repartitionGeo, voieIntroduction, potentielDispersion, impacts, potentielInvasif, phaseInvasion, commentaires;

    int nbIndividusRecenses;

    cout << "\n\n------------------------------------------------" << endl;
    cout <<     "| InvasiTrack -- MENU DE CREATION D'UNE ESPECE |" << endl;
    cout <<     "------------------------------------------------" << endl;
    cout << "\n# Conservatoire sélectionné : " << conservatoire << endl;
    cout << "# Utilisateur connecté : " << utilisateur << endl;
    cout << "# Type d'utilisateur : " << type_utilisateur << endl;
   
    cout << "\nMerci de remplir le formulaire suivant pour créer une espèce." << endl;

    // Vérification que le nom de l'espèce est en majuscules
    int cpt = 1;
    nom_espece_valide:
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
    if (nom_valide(nom, "espèce", false, "") == false){
        cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
        return (make_unique<Espece>("NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", 0, "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", false));
    }

    // Vérification que l'espèce n'existe pas déjà
    if (verifier_espece(nom, especes) == true && nom != "ANNULER" && cpt<3){
        cout << "\n\nERREUR : CETTE ESPÈCE EXISTE DÉJÀ.\n" << endl;
        cout << "Veuillez entrer une autre espèce.\nSi vous souhaitez annuler la création de l'espèce, veuillez entrer 'ANNULER'." << endl;
        cpt++;
        goto nom_espece_valide;

    } else if (verifier_espece(nom, especes) == false && nom == "ANNULER") {
        cout << "\nCréation de l'espèce annulée. Retour au menu précédent." << endl;
        return (make_unique<Espece>("NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", 0, "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", false));

    } else if (verifier_espece(nom, especes) == true && cpt==3){
        cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
        return (make_unique<Espece>("NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", 0, "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", false));
    }

    cout << "\nTaxonomie de l'espèce ? " << endl;
    cin.sync(); // supprime le buffer
    getline(cin, taxonomie);
    
    int reponse;
    string choix_categorie = "Catégorie de la liste de l'espèce ?\n1. Alerte    2. Intérêt moindre    3. Observation    4. Espèces invasives";
    verification_saisie_nombre_utilisateur(reponse, choix_categorie, 1, 4, "", false, "", "", "", "", "", especes, "");

    if (reponse == 1) {
        categorieListe = "Alerte";
    } else if (reponse == 2) {
        categorieListe = "Intérêt moindre";
    } else if (reponse == 3) {
        categorieListe = "Observation";
    } else if (reponse == 4) {
        categorieListe = "Espèces invasives";
    }

    reponse = 0;
    string choix_priorite = "Priorité de l'espèce ?\n1. Non-prioritaire    2. À surveiller    3. Prioritaire";
    verification_saisie_nombre_utilisateur(reponse, choix_priorite, 1, 3, "", false, "", "", "", "", "", especes, "");

    if (reponse == 1) {
        priorite = "Non-prioritaire";
    } else if (reponse == 2) {
        priorite = "À surveiller";
    } else if (reponse == 3) {
        priorite = "Prioritaire";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
    cout << "\nCycle biologique de l'espèce ? " << endl;
    getline(cin, cycleBiologique);

    cout << "\nMode de reproduction de l'espèce ? " << endl;
    getline(cin, modeReproduction);

    cout << "\nRépartition géographique de l'espèce ? " << endl;
    getline(cin, repartitionGeo);

    bool est_entier = false;
    while (!est_entier) {
        cout << "\nNombre d'individus recensés de l'espèce ? " << endl;
        cin >> nbIndividusRecenses; 

        if (cin.fail()) { // si une lettre est entrée, saisie = 0 et cin est en erreur car saisie est de type int
            cout << "\n\nERREUR DE SAISIE : CECI N'EST PAS UN NOMBRE.\n" << endl;
            cin.clear(); // supprime le code d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
        } else if (nbIndividusRecenses >= 1) {
            est_entier = true;
        } else if (nbIndividusRecenses == 0) {
            cout << "\n\nERREUR DE SAISIE : LE NOMBRE D'INDIVIDUS RECENSÉS DOIT ÊTRE SUPÉRIEUR À 0.\n" << endl;
        
        }
    }
    
    cout << "\nVoie d'introduction de l'espèce ? " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
    getline(cin, voieIntroduction);

    reponse = 0;
    string choix_potentiel = "Potentiel de dispersion de l'espèce ?\n1. Faible    2. Moyen    3. Important";
    verification_saisie_nombre_utilisateur(reponse, choix_potentiel, 1, 3, "", false, "", "", "", "", "", especes, "");

    if (reponse == 1) {
        potentielDispersion = "Faible";
    } else if (reponse == 2) {
        potentielDispersion = "Moyen";
    } else if (reponse == 3) {
        potentielDispersion = "Important";
    }

    cout << "\nImpacts de l'espèce ? " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
    getline(cin, impacts);

    cout << "\nPotentiel invasif de l'espèce ? " << endl;
    getline(cin, potentielInvasif);

    reponse = 0;
    string choix_phase_invasion = "Phase d'invasion de l'espèce ?\n1. Introduction    2. Installation    3. Expansion    4. Latence    5. Prolifération";
    verification_saisie_nombre_utilisateur(reponse, choix_phase_invasion, 1, 5, "", false, "", "", "", "", "", especes, "");

    if (reponse == 1) {
        phaseInvasion = "Introduction";
    } else if (reponse == 2) {
        phaseInvasion = "Installation";
    } else if (reponse == 3) {
        phaseInvasion = "Expansion";
    } else if (reponse == 4) {
        phaseInvasion = "Latence";
    } else if (reponse == 5) {
        phaseInvasion = "Prolifération";
    }

    cout << "\nCommentaires sur l'espèce ? " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
    getline(cin, commentaires); cout << endl;

    // Création d'un objet de type unique_ptr vers un type espèce et retour au menu principal
    
    cout << "\nL'espèce " << nom << " a été créée avec succès." << endl;
    return (make_unique<Espece>(nom, taxonomie, categorieListe, priorite, cycleBiologique, modeReproduction, repartitionGeo, nbIndividusRecenses, voieIntroduction, potentielDispersion, impacts, potentielInvasif, phaseInvasion, commentaires, false));
};

int Reporter::modifier_espece(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes){   

    // Sélection de l'espèce à modifier
    string nom_espece_choisie = selection_recherche(conservatoire, utilisateur, type_utilisateur, especes, "", "MENU DE MODIFICATION D'UNE ESPECE");

    if (nom_espece_choisie == "RETOUR") {
        return 0;
    } else if (nom_espece_choisie == "NULL") {
        return 1;
    }

    // Menu des options de modification
    menu_options_modif:
    int reponse;
    string affichage_liste = "0. Retour    1. Modification des champs de l'espèce    2. Ajout d'une action    3. Modification d'une action    4. Suppression d'une action";

    verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 4, "", true, "MENU DE MODIFICATION D'UNE ESPECE", conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes, "");

    if (reponse == 0) { // Retour au menu principal
        return 0;
    } else if (reponse == 1) { // Modification des champs de l'espèce
   
        string nouveau_nom, taxonomie, categorieListe, priorite, cycleBiologique, modeReproduction, repartitionGeo, voieIntroduction, potentielDispersion, impacts, potentielInvasif, phaseInvasion, commentaires, affichage_liste;

        int nbIndividusRecenses, reponse;

        affichage_liste = "0. Retour    1. Nom    2. Taxonomie    3. Catégorie de la liste    4. Priorité    5. Cycle biologique    6. Mode de reproduction    7. Répartition géographique    \n8.Nombre d'individus recensés    9. Voie d'introduction    10. Potentiel de dispersion    11. Impacts    12. Potentiel invasif    13. Phase d'invasion    14. Commentaires";

        // Vérification de la saisie de l'utilisateur
        choix_modif_champs:
        verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 14, "" , true, "MENU DE MODIFICATION D'UNE ESPECE -- MODIFICATION DES CHAMPS", conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes, "");

        // Retour au menu précédent
        if (reponse == 0) {
            goto menu_options_modif;
        } else if (reponse == 1) { // Modification du nom
            // Vérification que le nom de l'espèce est en majuscules
            int cpt = 1;
            nom_espece_valide_3:
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
            if (nom_valide(nouveau_nom, "espèce", false, "") == false){
                cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu principal." << endl;
                return (1);
            }

            // Vérification que le nouveau nom de l'espèce n'existe pas déjà
            if (verifier_espece(nouveau_nom, especes) == true && nouveau_nom != "ANNULER" && cpt<3){
                cout << "Ce nom existe déjà, veuillez entrer un autre nom.\nSi vous souhaitez annuler la modification de l'espèce, veuillez entrer 'ANNULER'." << endl;
                cpt++;
                goto nom_espece_valide_3;
            
            } else if (verifier_espece(nouveau_nom, especes) == false && nouveau_nom == "ANNULER") {
                cout << "\nModification de l'espèce annulée. Retour au menu précédent." << endl;
                goto choix_modif_champs;

            } else if (verifier_espece(nouveau_nom, especes) == false && cpt==3){
                cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
                goto choix_modif_champs;
            }

            especes[nouveau_nom] = especes[nom_espece_choisie];
            especes[nouveau_nom].set_Nom(nouveau_nom);
            especes.erase(nom_espece_choisie);
            nom_espece_choisie = nouveau_nom;
            cout << "\nLe nom de l'espèce a été modifié avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 2) { // Modification de la taxonomie
            cout << "\nTaxonomie de l'espèce ? " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, taxonomie,'\n'); cout << endl;

            especes[nom_espece_choisie].set_Taxonomie(taxonomie);
            cout << "\nLa taxonomie de l'espèce a été modifiée avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 3) { // Modification de la catégorie de la liste
            reponse = 0;
            string choix_categorie = "Catégorie de la liste de l'espèce ?\n1. Alerte    2. Intérêt moindre    3. Observation    4. Espèces invasives";
            verification_saisie_nombre_utilisateur(reponse, choix_categorie, 1, 4, "", false, "", "", "", "", "", especes, "");

            if (reponse == 1) {
                categorieListe = "Alerte";
            } else if (reponse == 2) {
                categorieListe = "Intérêt moindre";
            } else if (reponse == 3) {
                categorieListe = "Observation";
            } else if (reponse == 4) {
                categorieListe = "Espèces invasives";
            }

            especes[nom_espece_choisie].set_CategorieListe(categorieListe);
            cout << "\nLa catégorie de la liste de l'espèce a été modifiée avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 4) { // Modification de la priorité
            reponse = 0;
            string choix_priorite = "Priorité de l'espèce ?\n1. Non-prioritaire    2. À surveiller    3. Prioritaire";
            verification_saisie_nombre_utilisateur(reponse, choix_priorite, 1, 3, "", false, "", "", "", "", "", especes, "");

            if (reponse == 1) {
                priorite = "Non-prioritaire";
            } else if (reponse == 2) {
                priorite = "À surveiller";
            } else if (reponse == 3) {
                priorite = "Prioritaire";
            }

            especes[nom_espece_choisie].set_Priorite(priorite);
            cout << "\nLa priorité de l'espèce a été modifiée avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 5) { // Modification du cycle biologique
            cout << "\nCycle biologique de l'espèce ? " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, cycleBiologique,'\n'); cout << endl;

            especes[nom_espece_choisie].set_CycleBiologique(cycleBiologique);
            cout << "\nLe cycle biologique de l'espèce a été modifié avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 6) { // Modification du mode de reproduction
            cout << "\nMode de reproduction de l'espèce ? " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, modeReproduction,'\n'); cout << endl;

            especes[nom_espece_choisie].set_ModeReproduction(modeReproduction);
            cout << "\nLe mode de reproduction de l'espèce a été modifié avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 7) {// Modification de la répartition géographique
            cout << "\nRépartition géographique de l'espèce ? " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, repartitionGeo,'\n'); cout << endl;

            especes[nom_espece_choisie].set_RepartitionGeo(repartitionGeo);
            cout << "\nLa répartition géographique de l'espèce a été modifiée avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 8) { // Modification du nombre d'individus recensés
            bool est_entier = false;
            while (!est_entier) {
                cout << "\nNombre d'individus recensés de l'espèce ? " << endl;
                cin >> nbIndividusRecenses; 

                if (cin.fail()) { // si une lettre est entrée, saisie = 0 et cin est en erreur car saisie est de type int
                    cout << "\n\nERREUR DE SAISIE : CECI N'EST PAS UN NOMBRE.\n" << endl;
                    cin.clear(); // supprime le code d'erreur
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
                } else if (nbIndividusRecenses >= 1) {
                    est_entier = true;
                } else if (nbIndividusRecenses == 0) {
                    cout << "\n\nERREUR DE SAISIE : LE NOMBRE D'INDIVIDUS RECENSÉS DOIT ÊTRE SUPÉRIEUR À 0.\n" << endl;
                
                }
            }

            especes[nom_espece_choisie].set_NbIndividusRecenses(nbIndividusRecenses);
            cout << "\nLe nombre d'individus recensés de l'espèce a été modifié avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 9) { // Modification de la voie d'introduction
            cout << "\nVoie d'introduction de l'espèce ? " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, voieIntroduction,'\n'); cout << endl;

            especes[nom_espece_choisie].set_VoieIntroduction(voieIntroduction);
            cout << "\nLa voie d'introduction de l'espèce a été modifiée avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 10) { // Modification du potentiel de dispersion
            reponse = 0;
            string choix_potentiel = "Potentiel de dispersion de l'espèce ?\n1. Faible    2. Moyen    3. Important";
            verification_saisie_nombre_utilisateur(reponse, choix_potentiel, 1, 3, "", false, "", "", "", "", "", especes, "");

            if (reponse == 1) {
                potentielDispersion = "Faible";
            } else if (reponse == 2) {
                potentielDispersion = "Moyen";
            } else if (reponse == 3) {
                potentielDispersion = "Important";
            }

            especes[nom_espece_choisie].set_PotentielDispersion(potentielDispersion);
            cout << "\nLe potentiel de dispersion de l'espèce a été modifié avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 11) { // Modification des impacts
            cout << "\nImpacts de l'espèce ? " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, impacts,'\n'); cout << endl;

            especes[nom_espece_choisie].set_Impacts(impacts);
            cout << "\nLes impacts de l'espèce ont été modifiés avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 12) { // Modification du potentiel invasif
            cout << "\nPotentiel invasif de l'espèce ? " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, potentielInvasif,'\n'); cout << endl;

            especes[nom_espece_choisie].set_PotentielInvasif(potentielInvasif);
            cout << "\nLe potentiel invasif de l'espèce a été modifié avec succès." << endl;
            goto choix_modif_champs;

        } else if (reponse == 13) { // Modification de la phase d'invasion  
            reponse = 0;
            string choix_phase_invasion = "Potentiel invasif de l'espèce ?\n1. Introduction    2. Installation    3. Expansion    4. Latence    5. Prolifération";

            verification_saisie_nombre_utilisateur(reponse, choix_phase_invasion, 1, 5, "", false, "", "", "", "", "", especes, "");

            if (reponse == 1) {
                phaseInvasion = "Introduction";
            } else if (reponse == 2) {
                phaseInvasion = "Installation";
            } else if (reponse == 3) {
                phaseInvasion = "Expansion";
            } else if (reponse == 4) {
                phaseInvasion = "Latence";
            } else if (reponse == 5) {
                phaseInvasion = "Prolifération";
            }

            especes[nom_espece_choisie].set_PhaseInvasion(phaseInvasion);
            cout << "\nLe potentiel invasif de l'espèce a été modifié avec succès." << endl;
            goto choix_modif_champs;
        
        } else if (reponse == 14) { // Modification des commentaires
            cout << "\nCommentaires sur l'espèce ? " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, commentaires,'\n'); cout << endl;

            especes[nom_espece_choisie].set_Commentaires(commentaires);
            cout << "\nLes commentaires sur l'espèce ont été modifiés avec succès." << endl;
            goto choix_modif_champs;
        }

    } else if (reponse == 2) { // Ajout d'une action

        unique_ptr<Action> nouvelleAction = ajouter_action(conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes);

        // Retour au menu pincipal
        if (nouvelleAction->get_Intitule() == "NULL") {
            nouvelleAction.reset(); // Suppression de l'objet nouvelleAction
            goto menu_options_modif;
        }

        //Ajout de la nouvelle action dans la liste des actions de l'espèce
        unordered_map<string, Action> actions = especes[nom_espece_choisie].get_Actions();
        actions[nouvelleAction->get_Intitule()] = *nouvelleAction;
        especes[nom_espece_choisie].set_Actions(actions);

        return 0; // Retour au menu principal pour sauvegarder les modifications

    } else if (reponse == 3) { // Modification d'une action
 
        int code_retour_modif_action = modifier_action(conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes);

        if (code_retour_modif_action == 1) {
            goto menu_options_modif;
        }

        return 0; // Retour au menu principal pour sauvegarder les modifications

    } else if (reponse == 4) { // Suppression d'une action

        int code_retour_modif_suppr = supprimer_action(conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes);
        
        // Retour au menu principal
        if (code_retour_modif_suppr == 1) {
            goto menu_options_modif;
        }

        return 0; // Retour au menu principal pour sauvegarder les modifications
        
    }

    return 0;
};

int Reporter::supprimer_espece(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes){
    
    // Sélection de l'espèce à supprimer
    string nom_espece_choisie = selection_recherche(conservatoire, utilisateur, type_utilisateur, especes, "", "MENU DE SUPPRESSION D'UNE ESPECE");

    if (nom_espece_choisie == "RETOUR") {
        return 0;
    } else if (nom_espece_choisie == "NULL") {
        return 1;
    }

    // Confirmation de la suppression
    int reponse;
    string affichage_liste = "0. Retour    1. Confirmer la suppression";

    verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 1, "", true, "MENU DE SUPPRESSION D'UNE ESPECE", conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes, "");

    if (reponse == 0) { // Retour au menu principal
        return 0;
    } else if (reponse == 1) { // Suppression de l'espèce
        especes.erase(nom_espece_choisie);
        cout << "\nL'espèce " << nom_espece_choisie << " a été supprimée avec succès." << endl;
    }

    return 0;
};

FicheSuivi Reporter::creer_ficheSuivi(string intituleAction, string typeAction, string idAuteur, vector<int> date, string lieu){
    
    string descriptif,  acteurs, materiel, financement;
    float coutAction;

    cout << "\nActeurs de l'action ? " << endl;
    cin.sync();
    getline(cin, acteurs);

    bool est_reel = false;
    while (!est_reel) {
        cout << "\nCoût de l'action (en €) ? Merci d'utiliser le point comme séparateur décimal." << endl;
        cin >> coutAction; 

        if (cin.fail()) { // si une lettre est entrée, saisie = 0 et cin est en erreur car saisie est de type int
            cout << "\n\nERREUR DE SAISIE : CECI N'EST PAS UN NOMBRE RÉEL.\n" << endl;
            cin.clear(); // supprime le code d'erreur
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
        } else if (coutAction >= 1) {
            est_reel = true;
        } else if (coutAction == 0) {
            cout << "\n\nERREUR DE SAISIE : LE COÛT DOIT ÊTRE SUPÉRIEUR À 0.\n" << endl;
        
        }
    }

    cout << "\nFinancement de l'action ? " << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, financement);

    cout << "\nMatériel utilisé pour l'action ? " << endl;
    getline(cin, materiel);

    cout << "\nDescriptif de l'action ? " << endl;
    getline(cin, descriptif);
    
    FicheSuivi fiche(intituleAction, typeAction, idAuteur, descriptif, date, lieu, acteurs, materiel, coutAction, financement);

    return fiche;
};

int Reporter::modifier_ficheSuivi(string conservatoire, string utilisateur, string type_utilisateur, string nom_espece_choisie, unordered_map<string, Espece> &especes, string nom_action_choisie, unique_ptr<FicheSuivi> &fiche) {

    unordered_map<string, Action> actions = especes[nom_espece_choisie].get_Actions();

    // Modification des champs de la fiche de suivi
    string acteurs, materiel, financement, descriptif,affichage_liste;
    float coutAction;

    affichage_liste = "0. Retour    1. Acteurs    2. Coût    3. Financement    4. Matériel    5. Descriptif";

    // Vérification de la saisie de l'utilisateur
    choix_modif_champs_fiche:
    int reponse;

    verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 5, "" , true, "MENU DE MODIFICATION D'UNE FICHE DE SUIVI -- MODIFICATION DES CHAMPS", conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes, nom_action_choisie);

    // Retour au menu précédent
    if (reponse == 0) {
        return 0;
    } else if (reponse == 1) { // Modification des acteurs
        cout << "\nActeurs de l'action ? " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, acteurs);

        fiche->set_Acteurs(acteurs);
        actions[nom_action_choisie].set_FicheSuivi(*fiche);
        especes[nom_espece_choisie].set_Actions(actions);

        cout << "\nLes acteurs de l'action ont été modifiés avec succès." << endl;
        goto choix_modif_champs_fiche;

    } else if (reponse == 2) { // Modification du coût
        bool est_reel = false;
        while (!est_reel) {
            cout << "\nCoût de l'action (en €) ? Merci d'utiliser le point comme séparateur décimal." << endl;
            cin >> coutAction; 

            if (cin.fail()) { // si une lettre est entrée, saisie = 0 et cin est en erreur car saisie est de type int
                cout << "\n\nERREUR DE SAISIE : CECI N'EST PAS UN NOMBRE RÉEL.\n" << endl;
                cin.clear(); // supprime le code d'erreur
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
            } else if (coutAction >= 1) {
                est_reel = true;
            } else if (coutAction == 0) {
                cout << "\n\nERREUR DE SAISIE : LE COÛT DOIT ÊTRE SUPÉRIEUR À 0.\n" << endl;
            
            }
        }

        fiche->set_CoutAction(coutAction);
        actions[nom_action_choisie].set_FicheSuivi(*fiche);
        especes[nom_espece_choisie].set_Actions(actions);

        cout << "\nLe coût de l'action a été modifié avec succès." << endl;
        goto choix_modif_champs_fiche;

    } else if (reponse == 3) { // Modification du financement
        cout << "\nFinancement de l'action ? " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, financement);

        fiche->set_Financement(financement);
        actions[nom_action_choisie].set_FicheSuivi(*fiche);
        especes[nom_espece_choisie].set_Actions(actions);

        cout << "\nLe financement de l'action a été modifié avec succès." << endl;
        goto choix_modif_champs_fiche;
    
    } else if (reponse == 4) { // Modification du matériel
        cout << "\nMatériel utilisé pour l'action ? " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, materiel);

        fiche->set_Materiel(materiel);
        actions[nom_action_choisie].set_FicheSuivi(*fiche);
        especes[nom_espece_choisie].set_Actions(actions);

        cout << "\nLe matériel utilisé pour l'action a été modifié avec succès." << endl;
        goto choix_modif_champs_fiche;

    } else if (reponse == 5) { // Modification du descriptif
        cout << "\nDescriptif de l'action ? " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, descriptif);

        fiche->set_Descriptif(descriptif);
        actions[nom_action_choisie].set_FicheSuivi(*fiche);
        especes[nom_espece_choisie].set_Actions(actions);

        cout << "\nLe descriptif de l'action a été modifié avec succès." << endl;
        goto choix_modif_champs_fiche;
    }

    return 0;
};

unique_ptr<Action> Reporter::ajouter_action(string conservatoire, string utilisateur, string type_utilisateur, string &espece_choisie, unordered_map<string, Espece> &especes){

    cout << "\n\n------------------------------------------------" << endl;
    cout <<     "| InvasiTrack -- MENU DE CREATION D'UNE ACTION |" << endl;
    cout <<     "------------------------------------------------" << endl;
    cout << "\n# Conservatoire sélectionné : " << conservatoire << endl;
    cout << "# Utilisateur connecté : " << utilisateur << endl;
    cout << "# Type d'utilisateur : " << type_utilisateur << endl;

    unordered_map<string, Action> actions = especes[espece_choisie].get_Actions();

    string intitule, type, lieu, idAuteur, statut, commentaires, affichage_liste;

    vector<int> date;
    int jour, mois, annee;

    cout << "\nMerci de remplir le formulaire suivant pour créer une action." << endl;

    // Vérification que l'intitulé de l'action est en majuscules
    int cpt = 1;
    intitule_action_valide:
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
    if (nom_valide(intitule, "action", false, "") == false){
        cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
        return (make_unique<Action>("NULL", "NULL","NULL", vector<int>{0,0,0}, "NULL", "NULL", "NULL", "NULL", false));
    }

    // Vérification que l'action n'existe pas déjà
    if (verifier_action(intitule, actions) == true && intitule != "ANNULER" && cpt<3){
        cout << "\nCette action existe déjà, veuillez entrer un autre intitulé.\nSi vous souhaitez annuler la création de l'action, veuillez entrer 'ANNULER' lorsque qu'il vous sera demandé d'entrer un intitulé." << endl;
        cpt++;
        goto intitule_action_valide;

    } else if (verifier_action(intitule, actions) == false && intitule == "ANNULER") {
        cout << "\nCréation de l'action annulée. Retour au menu précédent." << endl;
        return (make_unique<Action>("NULL", "NULL","NULL", vector<int>{0,0,0}, "NULL", "NULL", "NULL", "NULL", false));

    } else if (verifier_action(intitule, actions) == true && cpt==3){
        cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
        return (make_unique<Action>("NULL", "NULL","NULL", vector<int>{0,0,0}, "NULL", "NULL", "NULL", "NULL", false));
    }

    int reponse = 0;
    string choix_type = "Type d'action ?\n1. Prévention    2. Surveillance    3. Intervention";
    verification_saisie_nombre_utilisateur(reponse, choix_type, 1, 3, "", false, "", "", "", "", "", especes, "");

    if (reponse == 1) {
        type = "Prévention";
    } else if (reponse == 2) {
        type = "Surveillance";
    } else if (reponse == 3) {
        type = "Intervention";
    }

    // Vérification que la date est valide
    verifier_date(jour, mois, annee, "de l'action");

    date = {annee, mois, jour};

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
    cout << "\nLieu de l'action ? " << endl;
    getline(cin, lieu);

    idAuteur = this->get_Id();

    cout << "\nStatut de l'action ? " << endl;
    getline(cin, statut);

    cout << "\nCommentaires sur l'action ? " << endl;
    getline(cin, commentaires);

    // Création de l'objet de type unique_ptr vers un type action
    unique_ptr<Action> action = make_unique<Action>(intitule, type, espece_choisie, date, lieu, idAuteur, statut, commentaires, false);

    // Création de la fiche suivi associée à l'action

    cout << "\n\n------------------------------------------------------------------------------------------" << endl;
    cout <<     "| InvasiTrack -- MENU DE CREATION D'UNE ACTION -- CREATION DE LA FICHE DE SUIVI ASSOCIEE |" << endl;
    cout <<     "------------------------------------------------------------------------------------------" << endl;
    cout << "\n# Conservatoire sélectionné : " << conservatoire << endl;
    cout << "# Utilisateur connecté : " << utilisateur << endl;
    cout << "# Type d'utilisateur : " << type_utilisateur << endl;

    cout << "\n# Espèce sélectionnée : " << espece_choisie << endl;
    cout << "# Action sélectionnée : " << intitule << endl;

    cout << "\nMerci de remplir le formulaire suivant pour créer la fiche de suivi." << endl;
    FicheSuivi fiche = creer_ficheSuivi(intitule, type, idAuteur,  date, lieu);
    action->set_FicheSuivi(fiche);

    cout << "\n\nL'action " << intitule << " a été créée avec succès." << endl;

    return action;
};

int Reporter::modifier_action(string conservatoire, string utilisateur, string type_utilisateur, string &espece_choisie, unordered_map<string, Espece> &especes){

    // Sélection de l'action
    unordered_map<string, Action> actions = especes[espece_choisie].get_Actions();

    string nom_action_choisie = selection_recherche(conservatoire, utilisateur, type_utilisateur, especes, espece_choisie, "MENU DE MODIFICATION D'UNE ACTION");

    if (nom_action_choisie == "RETOUR") {
        return 0;
    } else if (nom_action_choisie == "NULL") {
        return 1;
    }

    // Modification des champs de l'action
    string nouvel_intitule, type, lieu, idAuteur, statut, commentaires, affichage_liste;
    vector<int> date;
    int jour, mois, annee;

    choix_modif_champs_action:
    affichage_liste = "0. Retour    1. Intitulé    2. Type    3. Date    4. Lieu    5. Statut    6. Commentaires    7. Fiche suivi";

    // Vérification de la saisie de l'utilisateur
    int reponse;    
    verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 7, "" , true, "MENU DE MODIFICATION D'UNE ACTION -- MODIFICATION DES CHAMPS", conservatoire, utilisateur, type_utilisateur, espece_choisie, especes, nom_action_choisie);

    // Retour au menu précédent
    if (reponse == 0) {
        return 0;
        
    } else if (reponse == 1) { // Modification de l'intitulé
        // Vérification que l'intitulé de l'action est en majuscules
        int cpt = 1;
        intitule_action_valide_2:
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
        if (nom_valide(nouvel_intitule, "action", false, "") == false){
            cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
            return 1;
        }

        // Vérification que l'action n'existe pas déjà
        if (verifier_action(nouvel_intitule, actions) == true && nouvel_intitule != "ANNULER" && cpt<3){
            cout << "\nCette action existe déjà, veuillez entrer un autre intitulé.\nSi vous souhaitez annuler la modification de l'action, veuillez entrer 'ANNULER' lorsque qu'il vous sera demandé d'entrer un intitulé." << endl;
            cpt++;
            goto intitule_action_valide_2;

        } else if (verifier_action(nouvel_intitule, actions) == false && nouvel_intitule == "ANNULER") {
            cout << "\nModification de l'action annulée. Retour au menu précédent." << endl;
            goto choix_modif_champs_action;

        } else if (verifier_action(nouvel_intitule, actions) == true && cpt==3){
            cout << "\nVous avez atteint le nombre maximal de tentatives. Retour au menu précédent." << endl;
            goto choix_modif_champs_action;
        }

        // Création d'une action avec le nouvel intitulé, copie des attributs et des méthodes de l'ancienne action, puis suppression de l'ancienne action
        actions[nouvel_intitule] = actions[nom_action_choisie];
        actions[nouvel_intitule].set_Intitule(nouvel_intitule);
        actions.erase(nom_action_choisie);

        // Modification de l'intitulé de l'action dans la fiche de suivi
        FicheSuivi fiche = actions[nom_action_choisie].get_FicheSuivi();
        fiche.set_IntituleAction(nouvel_intitule);
        actions[nouvel_intitule].set_FicheSuivi(fiche);
        
        
        nom_action_choisie = nouvel_intitule; // Le nom est changé pour éviter l'affichage de l'ancien nom dans les menus

        // Sauvegarde dans l'espèce et retour au menu précédent
        especes[espece_choisie].set_Actions(actions);
        cout << "\nL'intitulé de l'action a été modifié avec succès." << endl;

        goto choix_modif_champs_action;

    } else if (reponse == 2) { // Modification du type
        reponse = 0;
        string choix_type = "Type d'action ?\n1. Prévention    2. Surveillance    3. Intervention";
        verification_saisie_nombre_utilisateur(reponse, choix_type, 1, 3, "", false, "", "", "", "", "", especes, "");

        if (reponse == 1) {
            type = "Prévention";
        } else if (reponse == 2) {
            type = "Surveillance";
        } else if (reponse == 3) {
            type = "Intervention";
        }

        // Modification du type de l'action et dans l'objet et dans la fiche de suivi
        actions[nom_action_choisie].set_Type(type);
        
        FicheSuivi fiche = actions[nom_action_choisie].get_FicheSuivi();
        fiche.set_TypeAction(type);
        actions[nom_action_choisie].set_FicheSuivi(fiche);
    
        // Sauvegarde dans l'espèce et retour au menu précédent
        especes[espece_choisie].set_Actions(actions);
        cout << "\nLe type de l'action a été modifié avec succès." << endl;

        goto choix_modif_champs_action;

    } else if (reponse == 3) { // Modification de la date
        // Vérification que la date est valide
        verifier_date(jour, mois, annee, "de l'action");
        date = {annee, mois, jour};

        // Modification de la date de l'action et dans la fiche de suivi
        actions[nom_action_choisie].set_Date(date);
        FicheSuivi fiche = actions[nom_action_choisie].get_FicheSuivi();
        fiche.set_Date(date);
        actions[nom_action_choisie].set_FicheSuivi(fiche);

        // Sauvegarde dans l'espèce et retour au menu précédent        
        especes[espece_choisie].set_Actions(actions);
        cout << "\nLa date de l'action a été modifiée avec succès." << endl;

        goto choix_modif_champs_action;
    
    } else if (reponse == 4) { // Modification du lieu
    
        cout << "\nLieu de l'action ? " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, lieu,'\n'); cout << endl;

        // Modification du lieu de l'action et sauvegarde dans l'espèce, puis retour au menu précédent
        actions[nom_action_choisie].set_Lieu(lieu);
        especes[espece_choisie].set_Actions(actions);
        cout << "\nLe lieu de l'action a été modifié avec succès." << endl;

        goto choix_modif_champs_action;

    } else if (reponse == 5) { // Modification du statut
        cout << "\nStatut de l'action ? " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, statut,'\n'); cout << endl;

        // Modification du statut de l'action et sauvegarde dans l'espèce, puis retour au menu précédent
        actions[nom_action_choisie].set_Statut(statut);
        especes[espece_choisie].set_Actions(actions);
        cout << "\nLe statut de l'action a été modifié avec succès." << endl;

        goto choix_modif_champs_action;

    } else if (reponse == 6) { // Modification des commentaires
        cout << "\nCommentaires sur l'action ? " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, commentaires,'\n'); cout << endl;

        // Modification des commentaires de l'action et sauvegarde dans l'espèce, puis retour au menu précédent
        actions[nom_action_choisie].set_Commentaires(commentaires);
        especes[espece_choisie].set_Actions(actions);        
        cout << "\nLes commentaires sur l'action ont été modifiés avec succès." << endl;

        goto choix_modif_champs_action;

    } else if (reponse == 7) { // Modification de la fiche suivi
        unique_ptr ficheSuivi = make_unique<FicheSuivi>(actions[nom_action_choisie].get_FicheSuivi());

        int code_retour_modif_fiche = modifier_ficheSuivi(conservatoire, utilisateur, type_utilisateur, espece_choisie, especes, nom_action_choisie, ficheSuivi);

        if (code_retour_modif_fiche == 0) {
            cout << "\nLa fiche de suivi de l'action a été modifiée avec succès." << endl;
            goto choix_modif_champs_action;
        }
    }

    return 0;
};


int Reporter::supprimer_action(string conservatoire, string utilisateur, string type_utilisateur, string &espece_choisie, unordered_map<string, Espece> &especes){

    // Sélection de l'action à supprimer
    unordered_map<string, Action> actions = especes[espece_choisie].get_Actions();

    string nom_action_choisie = selection_recherche(conservatoire, utilisateur, type_utilisateur, especes, espece_choisie, "MENU DE SUPPRESSION D'UNE ACTION");

    if (nom_action_choisie == "RETOUR") {
        return 0;
    } else if (nom_action_choisie == "NULL") {
        return 1;
    }
    
    // Confirmation de la suppression
    int reponse;
    string affichage_liste = "0. Retour    1. Confirmer la suppression";

    verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 1, "" , true, "MENU DE SUPPRESSION D'UNE ACTION -- CONFIRMATION DE LA SUPPRESSION", conservatoire, utilisateur, type_utilisateur, espece_choisie, especes, nom_action_choisie);

    if (reponse == 0) { // Retour au menu précédent
        return 0; 
    } else if (reponse == 1) { // Suppression de l'action
        
        actions.erase(nom_action_choisie);
        especes[espece_choisie].set_Actions(actions);

        cout << "\nL'action " << nom_action_choisie << " a été supprimée avec succès." << endl;
    }

    return 0;
};

bool Consultant::verifier_intervalle_temps(vector<int> &date_debut, vector<int> &date_cible, vector<int> &date_fin){
    // ne reçoit que des dates avec des valeurs correctes pour les mois et les jours et des années comprises entre 1900 et 2200

    if (date_cible[0] < date_debut[0] || date_cible[0] > date_fin[0]) {
        return false;
    } else if (date_cible[0] == date_debut[0] && date_cible[1] < date_debut[1]) {
        return false;
    } else if (date_cible[0] == date_debut[0] && date_cible[1] == date_debut[1] && date_cible[2] < date_debut[2]) {
        return false;
    } else if (date_cible[0] == date_fin[0] && date_cible[1] > date_fin[1]) {
        return false;
    } else if (date_cible[0] == date_fin[0] && date_cible[1] == date_fin[1] && date_cible[2] > date_fin[2]) {
        return false;
    } else {
        return true;
    }
};

void Utilisateur::verifier_date(int &jour, int &mois, int &annee, string type_date){
    bool date_valide = false;

    while (!date_valide) {
            cout << "\nDate " + type_date + "? \nJour (jj) : ";
            cin >> jour;
            cout << "\nMois (mm) : ";
            cin >> mois;
            cout << "\nAnnée (aaaa) : ";
            cin >> annee;

            if (cin.fail()) { // si une lettre est entrée, saisie = 0 et cin est en erreur car saisie est de type int
                cout << "\n\nERREUR DE SAISIE : CECI N'EST PAS UNE DATE.\n" << endl;
                cin.clear(); // supprime le code d'erreur
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // enlève ce qu'il y a dans le cin
            } else if (jour >= 1 && jour <= 31 && mois >= 1 && mois <= 12 && annee >= 1900 && annee <= 2200) {
                date_valide = true;
            } else {
                cout << "\n\nERREUR DE SAISIE : LA DATE EST INCORRECTE.\n" << endl;
            }
        }
};

int Consultant::cout_actions(string conservatoire, string utilisateur, string type_utilisateur, string nom_espece_choisie, unordered_map<string, Espece> &especes){
    
    unordered_map<string, Action> actions = especes[nom_espece_choisie].get_Actions();

    // Sélection de la période
    int reponse;
    string affichage_liste = "0. Retour    1. Depuis le début    2. Depuis une date précise    3. Entre deux dates";

    verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 3, "" , true, "MENU DE CONSULTATION D'UNE ESPECE -- CALCUL DU COUT DES ACTIONS", conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes, "");
    
    if (reponse == 0) { // Retour au menu précédent
        return 0;
    } else if (reponse == 1) { // Depuis le début
        float cout_total = 0;
        int cpt_actions = 0;
        for (auto action : actions) {
            cout_total += action.second.get_FicheSuivi().get_CoutAction();
            cpt_actions++;
        }
        
        if (cpt_actions == 0) {
            cout << "\nAucune action n'a été réalisée pour l'espèce " << nom_espece_choisie << "." << endl;
        } else if (cpt_actions == 1) {
            cout << "\nLe coût de l'unique action de l'espèce " << nom_espece_choisie << " est de " << cout_total << " €." << endl;
        } else if (cpt_actions > 1) {
            cout << "\nLe coût total des " + to_string(cpt_actions) + " actions de l'espèce " << nom_espece_choisie << " est de " << cout_total << " €." << endl;
        }

        cout << "\n\nAPPUYER SUR 'ENTRÉE' POUR CONTINUER" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(); 

    } else if (reponse == 2) { // Depuis une date précise
        int jour, mois, annee;
        
        verifier_date(jour, mois, annee, "de début");        

        vector<int> date_debut = {annee, mois, jour};

        float cout_total = 0;
        int cpt_actions =0;
        for (auto action : actions) { 
            if (action.second.get_Date() >= date_debut) {
                cout_total += action.second.get_FicheSuivi().get_CoutAction();
                cpt_actions++;
            }
        }

        if (cpt_actions == 0) {
            cout << "\nAucune action n'a été réalisée depuis le " << jour << "/" << mois << "/" << annee << "." << endl;
        } else if (cpt_actions == 1) {
            cout << "\nLe coût de l'unique action de l'espèce " << nom_espece_choisie << " depuis le " << jour << "/" << mois << "/" << annee << " est de " << cout_total << " €." << endl;
        } else if (cpt_actions > 1) {
            cout << "\nLe coût des " + to_string(cpt_actions) + " actions de l'espèce " << nom_espece_choisie << " depuis le " << jour << "/" << mois << "/" << annee << " est de " << cout_total << " €." << endl;
        }

        cout << "\n\nAPPUYER SUR 'ENTRÉE' POUR CONTINUER" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(); 

    } else if (reponse == 3) { // Entre deux dates
        int jj1, mm1, aaaa1, jj2, mm2, aaaa2;
 
        verifier_date(jj1, mm1, aaaa1, "de début");
        vector<int> date_debut = {aaaa1, mm1, jj1};

        verifier_date(jj2, mm2, aaaa2, "de fin");
        vector<int> date_fin = {aaaa2, mm2, jj2};

        float cout_total = 0;
        int cpt_actions = 0;

        for (auto action : actions) {
            
            vector<int> date_cible = action.second.get_Date();
            
            if (verifier_intervalle_temps(date_debut, date_cible, date_fin)) {
                
                cout_total += action.second.get_FicheSuivi().get_CoutAction();
                cpt_actions++;
            }
        }

        if (cpt_actions == 0) {
            cout << "\nAucune action n'a été réalisée entre le " << jj1 << "/" << mm1 << "/" << aaaa1 << " et le " << jj2 << "/" << mm2 << "/" << aaaa2 << "." << endl;
        } else if (cpt_actions == 1) {
            cout << "\nLe coût de l'unique action de l'espèce " << nom_espece_choisie << " entre le " << jj1 << "/" << mm1 << "/" << aaaa1 << " et le " << jj2 << "/" << mm2 << "/" << aaaa2 << " est de " << cout_total << " €." << endl;
        } else if (cpt_actions > 1) {
            cout << "\nLe coût des " + to_string(cpt_actions) + " actions de l'espèce " << nom_espece_choisie << " entre le " << jj1 << "/" << mm1 << "/" << aaaa1 << " et le " << jj2 << "/" << mm2 << "/" << aaaa2 << " est de " << cout_total << " €." << endl;
        }

        cout << "\n\nAPPUYER SUR 'ENTRÉE' POUR CONTINUER" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(); 
    }
    
    return 0;
};

int Consultant::consulter_action(string conservatoire, string utilisateur, string type_utilisateur, string nom_espece_choisie, unordered_map<string, Espece> &especes){
    // Sélection de l'action à consulter
    string nom_action_choisie = selection_recherche(conservatoire, utilisateur, type_utilisateur, especes, nom_espece_choisie, "MENU DE CONSULTATION D'UNE ESPECE");

    if (nom_action_choisie == "RETOUR") {
        return 0;
    } else if (nom_action_choisie == "NULL") {
        return 1;
    }

    // Affichage des informations de l'action
    choix_consultation_espece_2:
    string affichage_liste = "0. Retour   1. Consulter la fiche de suivi";

    // Vérification de la saisie de l'utilisateur
    int reponse;
    verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 1, "" , true, "MENU DE CONSULTATION D'UNE ESPECE -- CONSULTATION D'UNE ACTION", conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes, nom_action_choisie);
    
    if (reponse == 0) {
        return 0; // Retour au menu de l'action
    } else if (reponse == 1) { // Consultation de la fiche de suivi

        // Affichage des informations de la fiche de suivi
        affichage_liste = "0. Retour";

        // Vérification de la saisie de l'utilisateur
        
        verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 0, "" , true, "MENU DE CONSULTATION D'UNE ESPECE -- CONSULTATION D'UNE ACTION -- FICHE DE SUIVI", conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes, nom_action_choisie );
        
        if (reponse == 0) {
            goto choix_consultation_espece_2; // Retour au menu de l'action
        }
    }

    return 0;
}; 

int Consultant::consulter_espece(string conservatoire, string utilisateur, string type_utilisateur, unordered_map<string, Espece> &especes){

    // Sélection de l'espèce à consulter
    string nom_espece_choisie = selection_recherche(conservatoire, utilisateur, type_utilisateur, especes, "", "MENU DE CONSULTATION D'UNE ESPECE");

    // Retour au menu principal Consultant
    if (nom_espece_choisie == "RETOUR") { 
        return 0; 
    } else if (nom_espece_choisie == "NULL") {
        return 1;
    }

    // Affichage des informations de l'espèce et menu des options
    choix_consultation_espece:
    string affichage_liste;

    affichage_liste = "0. Retour    1. Consulter les actions    2. Calculer le coût des actions";

    // Vérification de la saisie de l'utilisateur
    int reponse;
    verification_saisie_nombre_utilisateur(reponse, affichage_liste, 0, 3, "" , true, "MENU DE CONSULTATION D'UNE ESPECE", conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes, "");
 
    if (reponse == 0) {
        return 0; // Retour au menu principal Consultant
    } else if (reponse == 1) { // Consultation de la liste des actions
        int code_retour_consulter_action = consulter_action(conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes);

       if (code_retour_consulter_action == 0) {
           goto choix_consultation_espece;
       }

    } else if (reponse == 2) { // Calcul du coût des actions
        int code_retour_cout_actions = cout_actions(conservatoire, utilisateur, type_utilisateur, nom_espece_choisie, especes);

        if (code_retour_cout_actions == 0) {
            goto choix_consultation_espece;
        }
    }
    return 0;
};