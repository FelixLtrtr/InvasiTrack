/*
################################################
Projet : Outil de gestion des espèces exotiques envahissantes
Version 1.8
Date : 10/01/2024

Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
Affiliation : Master 2 Bioinformatique, Nantes Université

Programme développé C++ et compilé en C++20

Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

Définitions des méthodes de la classe Conservatoire et code de test
################################################
*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <limits> // pour utiliser numeric_limits
#include <memory> // pour utiliser les pointeurs intelligents


#include "conservatoire.hpp"

using namespace std;

unique_ptr<Consultant> Conservatoire::get_utilisateurConnecteConsultant(){
    unique_ptr<Consultant> consultant = make_unique<Consultant>();

    consultant->set_Id(this->get_Utilisateurs()[this->get_utilisateurConnecteId()].get_Id());
    
    consultant->set_Mdp(this->get_Utilisateurs()[this->get_utilisateurConnecteId()].get_Mdp());

    consultant->set_Email(this->get_Utilisateurs()[this->get_utilisateurConnecteId()].get_Email());

    consultant->set_Type(this->get_Utilisateurs()[this->get_utilisateurConnecteId()].get_Type());

    return consultant;
};

unique_ptr<Reporter> Conservatoire::get_utilisateurConnecteReporter(){
    unique_ptr<Reporter> reporter = make_unique<Reporter>();

    reporter->set_Id(this->get_Utilisateurs()[this->get_utilisateurConnecteId()].get_Id());
    
    reporter->set_Mdp(this->get_Utilisateurs()[this->get_utilisateurConnecteId()].get_Mdp());

    reporter->set_Email(this->get_Utilisateurs()[this->get_utilisateurConnecteId()].get_Email());

    reporter->set_Type(this->get_Utilisateurs()[this->get_utilisateurConnecteId()].get_Type());

    return reporter;
};

unique_ptr<Utilisateur> Conservatoire::get_utilisateurConnecte() {
    return make_unique<Utilisateur>(this->get_Utilisateurs()[this->get_utilisateurConnecteId()]);
};


bool Conservatoire::verifier_utilisateur(string id){
    unordered_map<string, Utilisateur> utilisateurs = this->get_Utilisateurs();
    if (utilisateurs.find(id) == utilisateurs.end()){
        return 0;
    } else {
        return 1;
    }
};

void verification_saisie_nombre(auto &saisie, string affichage_liste, int index_choix_min, int index_choix_max, string phrase_selection, bool afficher_menu, string menu, string conservatoire, string utilisateur, string type_utilisateur){
    if (afficher_menu) {
        cout << "\n\n------------------" + string(menu.size(), '-') + "-" << endl;
            cout << "| InvasiTrack -- " << menu << " |" << endl;
            cout << "------------------" + string(menu.size(), '-') + "-" << endl;

        if (conservatoire != "") {cout << "\n# Conservatoire sélectionné : " << conservatoire << endl;}

        if (utilisateur != "") {cout << "# Utilisateur connecté : " << utilisateur << endl;}

        if (type_utilisateur != "") {cout << "# Type : " << type_utilisateur << endl;}

        if (phrase_selection == "") {phrase_selection = "Veuillez choisir une option (merci de sélectionner le numéro correspondant).";}
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

int Conservatoire::creer_utilisateur(){
    string tmp_id;
    string tmp_mdp;
    string tmp_confirm_mdp;
    string tmp_mail;
    string tmp_type;
    int cpt = 1;

    cout << "\n\n---------------------------------------------" << endl;
    cout <<     "| InvasiTrack -- MENU DE CREATION DE COMPTE |" << endl;
    cout <<     "---------------------------------------------" << endl;
    cout << "\n# Conservatoire sélectionné : " << this->get_Nom() << endl;
    cout << "\nMerci de remplir le formulaire suivant pour créer votre compte." << endl;
    cout << "\nEntrez votre identifiant." << endl;
    cin >> tmp_id; cout << endl; 

    unordered_map<string, Utilisateur> utilisateurs = this->get_Utilisateurs();
    
    // Vérification de l'existence de l'identifiant dans la liste des utilisateurs
    while (this->verifier_utilisateur(tmp_id)!=0 && cpt<3){
        cout << "\nCet identifiant est déjà utilisé. Veuillez en choisir un autre." << endl;
        cin >> tmp_id; cout << endl;
        cpt++;
    }

    if (this->verifier_utilisateur(tmp_id)!=0 && cpt==3){
        cout << "\nTrop de tentatives. Retour au menu de connexion" << endl;
        return(1); 
    }

    cout << "\nQuel type de compte souhaiteriez-vous créer ? (Entrer le numéro correspondant)" << endl;
    cout << "1. Reporter\t2. Consultant" << endl;
    cin >> tmp_type; cout << endl;
    
    while(tmp_type != "1" && tmp_type != "2"){
        cout << "\nErreur de saisie. Veuillez entrer 1 ou 2." << endl;
        cin >> tmp_type; cout << endl;
    }
    
    if (tmp_type == "1"){tmp_type = "reporter";} 
    else if (tmp_type == "2"){tmp_type = "consultant";}

    mot_de_passe:
    cout << "\nEntrez votre mot de passe." << endl;
    cin >> tmp_mdp; cout << endl;

    cout << "\nConfirmez votre mot de passe." << endl;
    cin >> tmp_confirm_mdp; cout << endl;

    cpt = 1;
    while (tmp_mdp != tmp_confirm_mdp && cpt<3){
        cout << "\nLes mots de passe ne correspondent pas. Veuillez réessayer." << endl;
        cin >> tmp_confirm_mdp; cout << endl;
        cpt++;
    }

    if (tmp_mdp != tmp_confirm_mdp && cpt==3){
        cout << "\nTrop de tentatives de mots de passe non-correspondants.\nSouhaitez-vous entrer un nouveau mot de passe (1) ou retourner au menu de connexion (2) ?" << endl;

        string reponse;
        cin >> reponse; cout << endl;

        while (reponse != "1" && reponse != "2"){
            cout << "\nErreur de saisie. Veuillez entrer 1 ou 2." << endl;
            cin >> reponse; cout << endl;
        }

        if (reponse == "1"){goto mot_de_passe;}
        else if (reponse == "2"){
            cout << "\nRetour au menu de connexion." << endl;
            return(1);
        }
    }

    cout << "Entrez votre adresse mail." << endl;
    cin >> tmp_mail; cout << endl;

    // Création de l'objet Utilisateur
    if (tmp_type == "reporter"){
        Reporter utilisateur(tmp_id, tmp_mdp, tmp_mail);
        utilisateurs[utilisateur.get_Id()] = utilisateur;
    } else if (tmp_type == "consultant"){
        Consultant utilisateur(tmp_id, tmp_mdp, tmp_mail);
        utilisateurs[utilisateur.get_Id()] = utilisateur;
    }

    //Enregistrement de l'utilisateur dans le conservatoire
    this->set_Utilisateurs(utilisateurs);

    cout << "Votre compte a bien été créé." << endl;
    cout << "Vous pouvez désormais vous connecter." << endl;

    return(0);
};

int Conservatoire::suppr_utilisateur(){
    string tmp_id;
    string tmp_mdp;
    int cpt = 1;

    cout << "\n\n------------------------------------------------" << endl;
    cout <<     "| InvasiTrack -- MENU DE SUPPRESSION DE COMPTE |" << endl;
    cout <<     "------------------------------------------------" << endl;
    cout << "\n# Conservatoire sélectionné : " << this->get_Nom() << endl;

    cout << "\nEntrez l'identifiant de l'utilisateur à supprimer." << endl;
    cin >> tmp_id; cout << endl;

    // Vérification de l'existence de l'identifiant dans la liste des utilisateurs
    while (this->verifier_utilisateur(tmp_id)==0 && cpt<3){
        cout << "\nCet identifiant n'existe pas. Veuillez entrez un identifiant qui existe." << endl;
        cin >> tmp_id; cout << endl;
        cpt++;
    }

    if (this->verifier_utilisateur(tmp_id)==0 && cpt==3){
        cout << "\nTrop de tentatives. Retour au menu de connexion" << endl;
        return(1); 
    }

    // Verification de l'identité de l'utilisateur
    cpt = 1;
    cout << "\nEntrez le mot de passe de l'utilisateur à supprimer." << endl;
    cin >> tmp_mdp; cout << endl;
    
    while (tmp_mdp != utilisateurs[tmp_id].get_Mdp() && cpt<3){
        cout << "\nMot de passe incorrect. Veuillez réessayer." << endl;
        cin >> tmp_mdp; cout << endl;
        cpt++;
    }
    
    if (tmp_mdp != utilisateurs[tmp_id].get_Mdp() && cpt==3){
        cout << "\nTrop de tentatives. Retour au menu de connexion" << endl;
        return(1); 
    }
    
    unordered_map<string, Utilisateur> utilisateurs = this->get_Utilisateurs();
    utilisateurs.erase(tmp_id);
    this->set_Utilisateurs(utilisateurs);

    cout << "L'utilisateur " << tmp_id << " a bien été supprimé." << endl;

    return(0);
};

int Conservatoire::menu_connexion(){
    // Affichage et sélection des options
    affichage_liste: // Ancre pour le goto
    string affichage_liste = "0. Retour au choix du conservatoire    1. Connexion    2. Créer un compte    3. Supprimer un compte    4. Quitter le programme";

    unordered_map<string, Utilisateur> utilisateurs = this->get_Utilisateurs();
    
    // Vérification de la saisie (uniquement des nombres)
    int reponse;
    verification_saisie_nombre(reponse, affichage_liste, 0, 4, "", true, "MENU DE CONNEXION & CREATION DE COMPTE", this->get_Nom(), "", "");

    
    if (reponse == 0) {return(2);} // Retour au menu de sélection du conservatoire

    if (reponse == 1) { // Connexion
        string tmp_id;
        string tmp_mdp;
        int cpt = 1;

        cout << "\n\n------------------------------------" << endl;
        cout <<     "| InvasiTrack -- MENU DE CONNEXION |" << endl;
        cout <<     "------------------------------------" << endl;
        cout << "\n# Conservatoire : " << this->get_Nom() << endl;

        cout << "\nEntrez votre identifiant." << endl;
        cin >> tmp_id; cout << endl;

        // Vérification de l'existence de l'identifiant dans la liste des utilisateurs
        while (this->verifier_utilisateur(tmp_id)==0 && cpt<3){
            cout << "\nCet identifiant n'existe pas. Veuillez entrez un identifiant qui existe." << endl;
            cin >> tmp_id; cout << endl;
            cpt++;
        }

        if (this->verifier_utilisateur(tmp_id)==0 && cpt==3){return(1);} // Sortie du programme si 3 tentatives échouées

        cout << "\nEntrez votre mot de passe." << endl;
        cin >> tmp_mdp; cout << endl;
        cpt = 1;

        // Vérification du mot de passe
        while (tmp_mdp != utilisateurs[tmp_id].get_Mdp() && cpt<3){
            cout << "Mot de passe incorrect. Veuillez réessayer." << endl;
            cin >> tmp_mdp; cout << endl;
            cpt++;
        }

        if (tmp_mdp != utilisateurs[tmp_id].get_Mdp() && cpt==3){return(1);} // Sortie du programme si 3 tentatives échouées

        // Affectation de l'utilisateur connecté dans le conservatoire
        this->utilisateurConnecteId = utilisateurs[tmp_id].get_Id();
        cout << "Connexion réussie." << endl;
        return (0);

    
    } else if (reponse == 2) {  // Création d'un compte
        this->creer_utilisateur();
        goto affichage_liste; //Retour au menu de connexion

    
    } else if (reponse == 3) { // Suppression d'un compte
        this -> suppr_utilisateur();
        goto affichage_liste; //Retour au menu de connexion
    } else if (reponse == 4) { // Quitter le programme
        this -> deconnexion();
        return (3);
    }

    return(0);
};

int Conservatoire::deconnexion(){
    cout << "\n\nVous avez été déconnecté de votre session." << endl;
    this->set_utilisateurConnecteId("NULL");
    return (0);
};

int Conservatoire::menu_principal(){
    unordered_map<string, Espece> especes = this->get_Especes();

    string affichage_liste;
    
    if (this->get_utilisateurConnecte()->get_Type() == "reporter") {
        // Récupération d'une copie de l'utilisateur connecté (reporter)
        unique_ptr<Reporter> utilisateurConnecteReporter = this->get_utilisateurConnecteReporter();

        menu_principal_reporter: // Ancre pour le goto
        // Affichage des options
        affichage_liste = "0. Déconnexion    1. Ajouter une espèce    2. Modifier une espèce    3. Supprimer une espèce    4. Quitter le programme";

        // Vérification de la saisie utilisateur
        int reponse;
        verification_saisie_nombre(reponse, affichage_liste, 0, 4, "", true, "MENU PRINCIPAL", this->get_Nom(), this->get_utilisateurConnecte()->get_Id(), "reporter");

        if (reponse == 0) { // Déconnexion
            this->deconnexion();
            return (2);

        } else if (reponse == 1) { // Ajouter une espèce
            unique_ptr<Espece> nouvelleEspece = utilisateurConnecteReporter->ajouter_espece(this->get_Nom(), this->get_utilisateurConnecteId(), "reporter", especes);

            if (nouvelleEspece->get_Nom() == "NULL") {
                nouvelleEspece.reset(); // Suppression de l'objet nouvelleEspece
                goto menu_principal_reporter;
            } 

            //Ajout de l'espèce dans la liste des espèces du conservatoire
            especes[nouvelleEspece->get_Nom()] = *nouvelleEspece;
            this->set_Especes(especes);

        } else if (reponse == 2) { // Modifier une espèce
            int code_retour_modif_espece = utilisateurConnecteReporter->modifier_espece(this->get_Nom(), this->get_utilisateurConnecteId(), "reporter", especes);

            if (code_retour_modif_espece == 1) {
                goto menu_principal_reporter;
            } 

            this->set_Especes(especes);
            
        } else if (reponse == 3) { // Supprimer une espèce
            int code_retour_suppr_espece = utilisateurConnecteReporter->supprimer_espece(this->get_Nom(), this->get_utilisateurConnecteId(), "reporter", especes);

            if (code_retour_suppr_espece == 1) {
                goto menu_principal_reporter;
            } 

            this->set_Especes(especes);

        } else if (reponse == 4) {
            this -> deconnexion();
            return (3);
        }

        return(0); // Retour au main pour la sauvegarde dans les fichiers json

    } else if (this->get_utilisateurConnecte()->get_Type() == "consultant") {

        // Récupération d'une copie de l'utilisateur connecté (consultant)
        unique_ptr<Consultant> utilisateurConnecteConsultant = this->get_utilisateurConnecteConsultant();

        // Affichage des options
        affichage_liste = "0. Déconnexion   1. Consulter une espèce   2. Quitter le programme";

        menu_principal_consultant: // Ancre pour le goto
        // Vérification de la saisie utilisateur
        int reponse;
        verification_saisie_nombre(reponse, affichage_liste, 0, 2, "", true, "MENU PRINCIPAL", this->get_Nom(), this->get_utilisateurConnecte()->get_Id(), "consultant");

        if (reponse == 0) { // Déconnexion
            this->deconnexion();
            return (2);

        } else if (reponse == 1) { // Consulter une espèce
            utilisateurConnecteConsultant->consulter_espece(this->get_Nom(), this->get_utilisateurConnecteId(), "consultant", especes);

            goto menu_principal_consultant;

        } else if (reponse == 2) {
            this -> deconnexion();
            return (3);
        }
    }

    return(0);

};