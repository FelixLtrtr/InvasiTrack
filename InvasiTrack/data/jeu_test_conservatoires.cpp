#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstring>
#include <filesystem>


#include "../src/.nlohmann_3.11.3/json.hpp"

#include "../src/main.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
    /// CONSERVATOIRE LOIRE-BRETAGNE
    Conservatoire LoireBretagne("Loire_Bretagne", false);
    
    // Création des utilisateurs
    Reporter steven("steven", "mdp","steven.pichon@etu.univ-nantes.fr", false);
    Reporter felix("felix", "mdp","felix.letertre@etu.univ-nantes.fr", false);
    Consultant basma("basma", "mdp","basma.baqqali@etu.univ-nantes.fr", false);
    Consultant demoC("demoC", "mdp","demoC@univ-nantes.fr", false);
    Reporter demoR("demoR", "mdp","demoR@univ-nantes.fr", false);
    
    // Création de la liste des utilisateurs
    unordered_map<string, Utilisateur> utilisateurs_LB;
    utilisateurs_LB[steven.get_Id()] = steven;
    utilisateurs_LB[felix.get_Id()] = felix;
    utilisateurs_LB[basma.get_Id()] = basma;
    utilisateurs_LB[demoC.get_Id()] = demoC;
    utilisateurs_LB[demoR.get_Id()] = demoR;

    LoireBretagne.set_Utilisateurs(utilisateurs_LB);

    // Création des espèces
    Espece acerNegundo("ERABLE NEGUNDO", "Acer negundo L.", "Observation", "Non-prioritaire", "N/A", "Sexuée", "Saint-Sébastien-sur-Loire", 12, "Naturelle", "Faible", "Peu importants", "N/A", "Introduction", "Aucun", false);

    Action prevention1("SENSIBILISATION AUX POPULATIONS LOCALES", "Prévention", "ERABLE NEGUNDO", {2021,01,15}, "Saint-Sébastien-sur-Loire", "steven", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi1("SENSIBILISATION AUX POPULATIONS LOCALES", "Prévention", "steven", "Sensibilisation des populations locales à l'espèce", {2021,01,15}, "Saint-Sébastien-sur-Loire", "N/A", "N/A", 50, "N/A", false);
    prevention1.set_FicheSuivi(ficheSuivi1);

    unordered_map<string, Action> acerNegundo_actions;
    acerNegundo_actions[prevention1.get_Intitule()] = prevention1;
    acerNegundo.set_Actions(acerNegundo_actions);



    Espece bidensFrondosa("BIDENT FEUILLE", "Bidens frondosa L.", "Alerte", "À surveiller", "N/A", "Sexuée", "Carquefou", 51, "Naturelle", "Moyen", "Aucun", "N/A", "Installation", "Aucun", false);
    
    Action surveillance1("DENOMBREMENT", "Surveillance", "BIDENT FEUILLE", {2018,06,24}, "Carquefou", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi2("DENOMBREMENT", "Surveillance", "felix", "Dénombrement des individus", {2018,06,24}, "Carquefou", "N/A", "N/A", 60, "N/A", false);
    surveillance1.set_FicheSuivi(ficheSuivi2);

    Action surveillance2("DEPLACEMENT", "Surveillance", "BIDENT FEUILLE", {2019,01,14}, "Carquefou", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi3("DEPLACEMENT", "Surveillance", "felix", "Déplacement des individus", {2019,01,14}, "Carquefou", "N/A", "N/A", 60, "N/A", false);
    surveillance2.set_FicheSuivi(ficheSuivi3);

    Action intervention1("ARRACHAGE", "Intervention", "BIDENT FEUILLE", {2020,10,02}, "Carquefou", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi4("ARRACHAGE", "Intervention", "felix", "Arrachage des individus", {2020,10,02}, "Carquefou", "N/A", "N/A", 40, "N/A", false);
    intervention1.set_FicheSuivi(ficheSuivi4);

    unordered_map<string, Action> bidensFrondosa_actions;
    bidensFrondosa_actions[surveillance1.get_Intitule()] = surveillance1;
    bidensFrondosa_actions[surveillance2.get_Intitule()] = surveillance2;
    bidensFrondosa_actions[intervention1.get_Intitule()] = intervention1;
    bidensFrondosa.set_Actions(bidensFrondosa_actions);

    

    Espece celtisAustralis("MICOCOULIER DE PROVENCE", "Celtis australis L.", "Intérêt moindre", "Non-prioritaire", "N/A", "Sexuée", "Nantes", 2, "Naturelle", "Faible", "Aucun", "N/A", "Introduction", "Aucun", false);

    Action surveillance3("DENOMBREMENT", "Surveillance", "MICOCOULIER DE PROVENCE", {2022,05,04}, "Nantes", "steven", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi5("DENOMBREMENT", "Surveillance", "steven", "Dénombrement des individus", {2022,05,04}, "Nantes", "N/A", "N/A", 60, "N/A", false);
    surveillance3.set_FicheSuivi(ficheSuivi5);

    Action prevention2("SENSIBILISATION AUX POPULATIONS LOCALES", "Prévention", "MICOCOULIER DE PROVENCE", {2021,04,17}, "Nantes", "steven", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi6("SENSIBILISATION AUX POPULATIONS LOCALES", "Prévention", "steven", "Sensibilisation des populations locales à l'espèce", {2021,04,17}, "Nantes", "N/A", "N/A", 50, "N/A", false);
    prevention2.set_FicheSuivi(ficheSuivi6);

    unordered_map<string, Action> celtisAustralis_actions;
    celtisAustralis_actions[surveillance3.get_Intitule()] = surveillance3;
    celtisAustralis_actions[prevention2.get_Intitule()] = prevention2;
    celtisAustralis.set_Actions(celtisAustralis_actions);



    Espece dioscoreaPolystachya("DIOSCOREE A LARGES FEUILLES", "Dioscorea polystachya Turcz.", "Espèce invasives", "Prioritaire", "N/A", "Sexuée", "Nantes", 116, "Naturelle", "Faible", "Aucun", "N/A", "Latence", "Aucun", false);

    Action surveillance4("DENOMBREMENT", "Surveillance", "DIOSCOREE A LARGES FEUILLES", {2023,11,04}, "Nantes", "steven", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi7("DENOMBREMENT", "Surveillance", "steven", "Dénombrement des individus", {2023,11,04}, "Nantes", "N/A", "N/A", 60, "N/A", false);
    surveillance4.set_FicheSuivi(ficheSuivi7);

    Action intervention2("ARRACHAGE", "Intervention", "DIOSCOREE A LARGES FEUILLES", {2024,01,04}, "Nantes", "steven", "En cours", "Aucun", false);
    FicheSuivi ficheSuivi8("ARRACHAGE", "Intervention", "steven", "Arrachage des individus", {2024,01,04}, "Nantes", "N/A", "N/A", 80, "N/A", false);
    intervention2.set_FicheSuivi(ficheSuivi8);

    unordered_map<string, Action> dioscoreaPolystachya_actions;
    dioscoreaPolystachya_actions[surveillance4.get_Intitule()] = surveillance4;
    dioscoreaPolystachya_actions[intervention2.get_Intitule()] = intervention2;
    dioscoreaPolystachya.set_Actions(dioscoreaPolystachya_actions);



    Espece elaeagnusAngustifolia("OLIVIER DE BOHEME", "Elaeagnus angustifolia L.", "Intérêt moindre", "Non-prioritaire", "N/A", "Sexuée", "Vertou", 2, "Humaine", "Faible", "Aucun", "N/A", "Introduction", "Aucun", false);

    Action surveillance5("DENOMBREMENT", "Surveillance", "OLIVIER DE BOHEME", {2017,8,12}, "Vertou", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi9("DENOMBREMENT", "Surveillance", "felix", "Dénombrement des individus", {2017,8,12}, "Vertou", "N/A", "N/A", 60, "N/A", false);
    surveillance5.set_FicheSuivi(ficheSuivi9);

    Action prevention3("SENSIBILISATION AUX POPULATIONS LOCALES", "Prévention", "OLIVIER DE BOHEME", {2023,01,23}, "Vertou", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi10("SENSIBILISATION AUX POPULATIONS LOCALES", "Prévention", "felix", "Sensibilisation des populations locales à l'espèce", {2023,01,23}, "Vertou", "N/A", "N/A", 50, "N/A", false);
    prevention3.set_FicheSuivi(ficheSuivi10);

    unordered_map<string, Action> elaeagnusAngustifolia_actions;
    elaeagnusAngustifolia_actions[surveillance5.get_Intitule()] = surveillance5;
    elaeagnusAngustifolia_actions[prevention3.get_Intitule()] = prevention3;
    elaeagnusAngustifolia.set_Actions(elaeagnusAngustifolia_actions);



    Espece fallopiaJaponica("RENOUEE DU JAPON", "Fallopia japonica (Houtt.) Ronse Decr.", "Espèce invasives", "Prioritaire", "N/A", "Sexuée", "Rezé", 86, "Humaine", "Faible", "Aucun", "N/A", "Latence", "Aucun", false);

    Action surveillance6("DENOMBREMENT", "Surveillance", "RENOUEE DU JAPON", {2015,02,28}, "Rezé", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi11("DENOMBREMENT", "Surveillance", "felix", "Dénombrement des individus", {2015,02,28}, "Rezé", "N/A", "N/A", 60, "N/A", false);
    surveillance6.set_FicheSuivi(ficheSuivi11);

    Action intervention3("ARRACHAGE", "Intervention", "RENOUEE DU JAPON", {2016,03,28}, "Rezé", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi12("ARRACHAGE", "Intervention", "felix", "Arrachage des individus", {2016,03,28}, "Rezé", "N/A", "N/A", 80, "N/A", false);
    intervention3.set_FicheSuivi(ficheSuivi12);

    unordered_map<string, Action> fallopiaJaponica_actions;
    fallopiaJaponica_actions[surveillance6.get_Intitule()] = surveillance6;
    fallopiaJaponica_actions[intervention3.get_Intitule()] = intervention3;
    fallopiaJaponica.set_Actions(fallopiaJaponica_actions);



    Espece gleditsiaTriacanthos("FEVIER D'AMERIQUE", "Gleditsia triacanthos L.", "Intérêt moindre", "Non-prioritaire", "N/A", "Sexuée", "Saint-Herblain", 2, "Humaine", "Faible", "Aucun", "N/A", "Introduction", "Aucun", false);

    Action surveillance7("DENOMBREMENT", "Surveillance", "FEVIER D'AMERIQUE", {2019,04,12}, "Saint-Herblain", "steven", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi13("DENOMBREMENT", "Surveillance", "steven", "Dénombrement des individus", {2019,04,12}, "Saint-Herblain", "N/A", "N/A", 60, "N/A", false);
    surveillance7.set_FicheSuivi(ficheSuivi13);

    Action prevention4("SENSIBILISATION AUX POPULATIONS LOCALES", "Prévention", "FEVIER D'AMERIQUE", {2020,01,12}, "Saint-Herblain", "steven", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi14("SENSIBILISATION AUX POPULATIONS LOCALES", "Prévention", "steven", "Sensibilisation des populations locales à l'espèce", {2020,01,12}, "Saint-Herblain", "N/A", "N/A", 50, "N/A", false);
    prevention4.set_FicheSuivi(ficheSuivi14);

    unordered_map<string, Action> gleditsiaTriacanthos_actions;
    gleditsiaTriacanthos_actions[surveillance7.get_Intitule()] = surveillance7;
    gleditsiaTriacanthos_actions[prevention4.get_Intitule()] = prevention4;
    gleditsiaTriacanthos.set_Actions(gleditsiaTriacanthos_actions);

    // Affectation des espèces au conservatoire
    unordered_map<string, Espece> especes_LB;
    especes_LB[acerNegundo.get_Nom()] = acerNegundo;
    especes_LB[bidensFrondosa.get_Nom()] = bidensFrondosa;
    especes_LB[celtisAustralis.get_Nom()] = celtisAustralis;
    especes_LB[dioscoreaPolystachya.get_Nom()] = dioscoreaPolystachya;
    especes_LB[elaeagnusAngustifolia.get_Nom()] = elaeagnusAngustifolia;
    especes_LB[fallopiaJaponica.get_Nom()] = fallopiaJaponica;
    especes_LB[gleditsiaTriacanthos.get_Nom()] = gleditsiaTriacanthos;

    LoireBretagne.set_Especes(especes_LB);


    /// CONSERVATOIRE GRAND EST
    Conservatoire GrandEst("Grand_Est", false);

    // Création des utilisateurs
    unordered_map<string, Utilisateur> utilisateurs_GE;
    utilisateurs_GE[steven.get_Id()] = steven;
    utilisateurs_GE[felix.get_Id()] = felix;
    utilisateurs_GE[basma.get_Id()] = basma;
    utilisateurs_GE[demoC.get_Id()] = demoC;
    utilisateurs_GE[demoR.get_Id()] = demoR;

    GrandEst.set_Utilisateurs(utilisateurs_GE);

    // Création des espèces
    Espece crassulaHelmsii("CRASSULE DE HELMS", "Crassula helmsii (Kirk) Cockayne", "Espèce invasive", "Prioritaire", "N/A", "Sexuée", "Nancy", 2, "Humaine", "Faible", "Aucun", "N/A", "Introduction", "Aucun", false);

    Action surveillance8("DENOMBREMENT", "Surveillance", "CRASSULE DE HELMS", {2019,9,15}, "Nancy", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi15("DENOMBREMENT", "Surveillance", "felix", "Dénombrement des individus", {2019,9,15}, "Nancy", "N/A", "N/A", 60, "N/A", false);
    surveillance8.set_FicheSuivi(ficheSuivi15);

    Action intervention4("ARRACHAGE", "Intervention", "CRASSULE DE HELMS", {2020,06,25}, "Nancy", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi16("ARRACHAGE", "Intervention", "felix", "Arrachage des individus", {2020,06,25}, "Nancy", "N/A", "N/A", 80, "N/A", false);
    intervention4.set_FicheSuivi(ficheSuivi16);

    unordered_map<string, Action> crassulaHelmsii_actions;
    crassulaHelmsii_actions[surveillance8.get_Intitule()] = surveillance8;
    crassulaHelmsii_actions[intervention4.get_Intitule()] = intervention4;
    crassulaHelmsii.set_Actions(crassulaHelmsii_actions);



    Espece elodeaCanadensis("ELODEE DU CANADA", "Elodea canadensis Michx.", "Espèce invasive", "Prioritaire", "N/A", "Sexuée", "Nancy", 2, "Humaine", "Faible", "Aucun", "N/A", "Introduction", "Aucun", false);

    Action surveillance9("DENOMBREMENT", "Surveillance", "ELODEE DU CANADA", {2020,8,06}, "Nancy", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi17("DENOMBREMENT", "Surveillance", "felix", "Dénombrement des individus", {2020,8,06}, "Nancy", "N/A", "N/A", 60, "N/A", false);
    surveillance9.set_FicheSuivi(ficheSuivi17);

    Action intervention5("ARRACHAGE", "Intervention", "ELODEE DU CANADA", {2021,01,06}, "Nancy", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi18("ARRACHAGE", "Intervention", "felix", "Arrachage des individus", {2021,01,06}, "Nancy", "N/A", "N/A", 80, "N/A", false);
    intervention5.set_FicheSuivi(ficheSuivi18);

    Action intervention6("ARRACHAGE", "Intervention", "ELODEE DU CANADA", {2022,04,29}, "Nancy", "felix", "Terminé", "Aucun", false);
    FicheSuivi ficheSuivi19("ARRACHAGE", "Intervention", "felix", "Arrachage des individus", {2022,04,29}, "Nancy", "N/A", "N/A", 80, "N/A", false);
    intervention6.set_FicheSuivi(ficheSuivi19);

    unordered_map<string, Action> elodeaCanadensis_actions;
    elodeaCanadensis_actions[surveillance9.get_Intitule()] = surveillance9;
    elodeaCanadensis_actions[intervention5.get_Intitule()] = intervention5;
    elodeaCanadensis_actions[intervention6.get_Intitule()] = intervention6;
    elodeaCanadensis.set_Actions(elodeaCanadensis_actions);

    // Affectation des espèces au conservatoire
    unordered_map<string, Espece> especes_GE;
    especes_GE[crassulaHelmsii.get_Nom()] = crassulaHelmsii;
    especes_GE[elodeaCanadensis.get_Nom()] = elodeaCanadensis;

    GrandEst.set_Especes(especes_GE);




    /// CRÉATION DES CONSERVATOIRES ET ÉCRITURE DANS LE FICHIER JSON
    unordered_map<string, Conservatoire> conservatoires;
    conservatoires[LoireBretagne.get_Nom()] = LoireBretagne;
    conservatoires[GrandEst.get_Nom()] = GrandEst;

    json default_conservatoires = to_json_umap_conservatoires(conservatoires);
    // cout << default_conservatoires.dump(4, ' ', false, json::error_handler_t::replace) << endl;

    ecrire_json("conservatoires.json", default_conservatoires);
}