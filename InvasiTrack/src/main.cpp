/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Programme principal du projet
################################################
*/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstring>
#include <filesystem>
#include <exception> // pour utiliser les exceptions (try catch)
#include <limits> // pour utiliser numeric_limits
#include <memory> // pour utiliser les pointeurs intelligents

#include ".nlohmann_3.11.3/json.hpp"

#include "main.hpp"

using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

int main() {

    // Instanciation de l'accueil
    Accueil accueil;

    //Vérification des bases de données disponibles et création si nécessaire d'un conservatoire par défaut
    
    if (!fs::is_regular_file("conservatoires.json")) {
        
        Conservatoire defaut("ConservatoireDefaut", false);

        // Création du fichier conservatoires.json avec un conservatoire par défaut dans la liste des conservatoires
        unordered_map<string, Conservatoire> conservatoires;
        conservatoires["ConservatoireDefaut"] = defaut;
        
        json default_conservatoires = to_json_umap_conservatoires(conservatoires);

        ecrire_json("conservatoires_defaut.json", default_conservatoires);
        accueil.set_Conservatoires({{"ConservatoireDefaut", defaut}});

        accueil.set_ConservatoireSelectionneNom(defaut.get_Nom());

        // Menu principal avec le conservatoire par défaut
        cout << "\n---------------------------------------------------" << endl;
        cout <<   "| InvasiTrack -- MENU DU CONSERVATOIRE PAR DÉFAUT |" << endl;
        cout <<   "---------------------------------------------------\n" << endl;
        cout << "Conservatoire sélectionné : " << accueil.get_ConservatoireSelectionne()->get_Nom() << endl;
        cout << "Ceci est un conservatoire par défaut, vous ne pouvez pas aller plus loin, merci d'ajouter un fichier 'conservatoires.json' contenant un véritable conservatoire pour utiliser ce logiciel.\n" << endl;

        return 0;

    } else if (fs::is_empty("conservatoires.json")) {
        cout << "\n\nInvasiTrack -- ERREUR\n" << endl;
        cout << "Le fichier 'conservatoires.json' est vide, merci d'ajouter un conservatoire pour utiliser ce logiciel.\n" << endl;
        return 1;

    } else if (fs::is_regular_file("conservatoires.json")) {
        // Récupération des conservatoires dans le fichier conservatoires.json
        json liste_conservatoires = lire_json("conservatoires.json");
      
        unordered_map<string, Conservatoire> conservatoires;
        
        for (auto item=liste_conservatoires.begin(); item != liste_conservatoires.end();++item) {
            Conservatoire conservatoire = json_to_conservatoire(item.value());

            conservatoires[item.key()] = conservatoire;
        }

        // Création des dossiers des conservatoires
        for (auto item=conservatoires.begin(); item != conservatoires.end();++item) {
            if (!fs::is_directory(item->second.get_Nom())) {
                fs::create_directory(item->second.get_Nom());

                // Création des fichiers utilisateurs.json et especes.json pour chaque conservatoire
                json utilisateurs = to_json_umap_utilisateurs(item->second.get_Utilisateurs());
                ecrire_json(item->second.get_Nom() + "/utilisateurs.json", utilisateurs);

                json especes = to_json_umap_especes(item->second.get_Especes());
                ecrire_json(item->second.get_Nom() + "/especes.json", especes);
            } else {
                // Récupération des utilisateurs et des espèces dans les fichiers utilisateurs.json et especes.json pour chaque conservatoire
                json utilisateurs = lire_json(item->second.get_Nom() + "/utilisateurs.json");
                json especes = lire_json(item->second.get_Nom() + "/especes.json");

                unordered_map<string, Utilisateur> utilisateurs_map = json_to_umap_utilisateurs(utilisateurs);
                
                unordered_map<string, Espece> especes_map = json_to_umap_especes(especes);

                item->second.set_Utilisateurs(utilisateurs_map);
                item->second.set_Especes(especes_map);
            }
        }
        accueil.set_Conservatoires(conservatoires);

    } else if (fs::is_regular_file("conservatoires_defaut.json")) {
        // Menu principal avec le conservatoire par défaut
        cout << "\n\nInvasiTrack -- MENU PRINCIPAL\n" << endl;
        cout << "Conservatoire sélectionné : " << accueil.get_ConservatoireSelectionne()->get_Nom() << endl;
        cout << "Ceci est un conservatoire par défaut, vous ne pouvez pas aller plus loin, merci d'ajouter un fichier 'conservatoires.json' contenant un véritable conservatoire pour utiliser ce logiciel.\n" << endl;

        return 0;
    } 
    
    // Menu de sélection du conservatoire
    accueil.choix_conservatoire();

    // Récupération du conservatoire sélectionné
    unique_ptr<Conservatoire> conservatoireCourant = accueil.get_ConservatoireSelectionne();
    auto taille_utilisateurs = conservatoireCourant->get_Utilisateurs().size();
    
    // Menu de connexion/création de compte
    menu_connexion: // Ancre pour le goto
    try {
        int code_retour_connexion = conservatoireCourant->menu_connexion();

        if (taille_utilisateurs != conservatoireCourant->get_Utilisateurs().size()) { // Si un utilisateur a été ajouté, le fichier utilisateurs.json du conservatoire associé est réécrit et la taille de la map utilisateurs est mise à jour
            json utilisateurs = to_json_umap_utilisateurs(conservatoireCourant->get_Utilisateurs());
            ecrire_json(conservatoireCourant->get_Nom()+"/utilisateurs.json", utilisateurs);

            taille_utilisateurs = conservatoireCourant->get_Utilisateurs().size();

            // Mise à jour de la liste des conservatoires
            sauvegarde_conservatoires(accueil, conservatoireCourant);
        }
                
        if(code_retour_connexion == 1){ 
            throw too_much_connection_try();
        } else if (code_retour_connexion == 2) { // Déconnexion
            accueil.choix_conservatoire();
            goto menu_connexion;
        } else if (code_retour_connexion == 3) { // Quitter le programme
            cout << "\n\nInvasiTrack a été fermé." << endl;
            return 0;
        }
    } catch (exception& connexion_exception) {
        cout << connexion_exception.what() << endl;
        cout << "\nInvasiTrack a été fermé." << endl;
        return 1;
    }

    // Menu principal du conservatoire
    menu_principal: // Ancre pour le goto
    {
        int code_retour_menu_principal = conservatoireCourant->menu_principal();
        // Mise à jour des espèces dans le conservatoire et mise à jour du fichier conservatoires.json
        json especes = to_json_umap_especes(conservatoireCourant->get_Especes());
        ecrire_json(conservatoireCourant->get_Nom()+"/especes.json", especes);
        sauvegarde_conservatoires(accueil, conservatoireCourant);

        if (code_retour_menu_principal == 2) { // Déconnexion
            goto menu_connexion; 

        } else if (code_retour_menu_principal == 3) { // Quitter le programme

            cout << "InvasiTrack a été fermé." << endl;
            return 0;
        }

        goto menu_principal;
    }
}