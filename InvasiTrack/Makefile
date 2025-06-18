################################################
# Projet : Outil de gestion des espèces exotiques envahissantes
# Version 1.8
# Date : 10/01/2024

# Auteurs : Basma BAQQALI, Félix LETERTRE, Steven PICHON
# Affiliation : Master 2 Bionforamtics, Nantes Université

# Programme développé C++ et compilé en C++20

# Ce programme fait partie d'un projet pour le module X3BI020 - Programmation objet pour les biologistes en 2023-2024.

# Makefile pour compiler le programme
################################################

### ALIAS POUR LES DOSSIERS
SRC_DIR := ./src
BUILD_DIR := ./build
DATA_DIR := ./data

INC_DIRS := $(shell find $(SRC_DIR) -type d)
# récupère tous les dossiers dans ./src

### DÉFINITION DES VARIABLES POUR LES FICHIERS
SRCS := $(shell find $(SRC_DIR) -name '*.cpp') # récupère tous les fichiers .cpp
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o) # préfixe tous les fichiers .cpp avec ./build/ et suffixe avec .o
DEPS := $(OBJS:.o=.d) # remplace .o par .d

### DÉFINITION DES VARIABLES POUR LA COMPILATION
TARGET_EXEC := InvasiTrack
GCC := g++
CPPFLAGS := $(addprefix -I,$(INC_DIRS)) -MMD -MP -Wall -std=c++20 
# -I permet de passer les dossiers à GCC
# -MMD et -MP génèrent des fichiers Makefile pour chaque fichier .cpp

sCPPFLAGS := -Wall -std=c++20

### DÉFINITION DES VARIABLES POUR LA VERSION
NEXT_VERSION := 1.8
VERSION_FILES := $(shell find $(SRC_DIR) -name '*.[c,h]pp')
MAKE_FILES := $(shell find -name 'Makefile')
DATE := $(shell date +"%d\/%m\/%Y")


### DÉFINITION DES CIBLES

## Compilation de l'exécutable
$(TARGET_EXEC): $(OBJS)
	@$(GCC) -o $@ $(OBJS)
	@echo
	@echo Compilation du programme $(TARGET_EXEC) terminée

## Compilation des fichiers .cpp et génération du jeu de données
$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo Compilation de $<
	@mkdir -p $(dir $@)
	@$(GCC) $(CPPFLAGS) -c $< -o $@

## Compilation du jeu de données et génération du fichier .json
$(DATA_DIR)/jeu_test_conservatoires: $(DATA_DIR)/jeu_test_conservatoires.cpp
	@if [ ! -e "conservatoires.json" ]; then \
		$(CXX) -Wall -std=c++20 -o $(DATA_DIR)/jeu_test_conservatoires $(DATA_DIR)/jeu_test_conservatoires.cpp; \
		$(DATA_DIR)/jeu_test_conservatoires; \
		rm -f $(DATA_DIR)/jeu_test_conservatoires; \
		echo "Jeu de données initialisé"; \
	else \
		echo "Le fichier conservatoires.json existe déjà"; \
	fi

.PHONY: clean launch test version update data demo
# .PHONY indique que ces cibles ne sont pas des fichiers et seront toujours exécutées

update: $(TARGET_EXEC) version

launch:
	@./$(TARGET_EXEC)

data: $(DATA_DIR)/jeu_test_conservatoires

clean:
	@rm -f $(TARGET_EXEC)
	@rm -f data/jeu_test_conservatoires
	@rm -f *.json
	@rm -rf $(filter-out src/ $(DATA_DIR:./%=%)/, $(basename $(wildcard */))) # supprime tous les dossiers sauf src/ et data/
	@echo Netttoyage terminé

test:
	@echo Sources : $(SRCS)
	@echo
	@echo Objects :  $(OBJS)
	@echo
	@echo Dossiers : $(INC_DIRS)
	@echo
	@echo Date : $(DATE)

	# g++ -Wall -std=c++20 -c action.cpp accueil.cpp conservatoire.cpp espece.cpp ficheSuivi.cpp utilisateur.cpp && g++ -Wall -std=c++20 -o main main.cpp *.o

version:
	@sed -i 's/\(Version\s*\)[^\s]*$$/\1$(NEXT_VERSION)/' $(VERSION_FILES)
	@echo BEFORE
	@sed -i 's/\(Date :\s*\)[^\s]*$$/\1$(DATE)/' $(VERSION_FILES)
	@echo AFTER

	@$(eval NEW_VERSION=$(shell echo $(NEXT_VERSION) | awk -F. '{if (($$2+1) == 10) print $$1+1 "." 0; else print $$1 "." $$2+1}'))

	@sed -i 's/\(# Version\s*\)[^\s]*$$/\1$(NEXT_VERSION)/' $(MAKE_FILES)
	@sed -i 's/\(NEXT_VERSION := \s*\s*\)[^\s]*$$/\1$(NEW_VERSION)/' $(MAKE_FILES)
	@sed -i 's/\(# Date :\s*\)[^\s]*$$/\1$(DATE)/' $(MAKE_FILES)
	
	@echo "Mise à jour de la version $(NEXT_VERSION) effectuée dans les fichiers"

demo: data $(TARGET_EXEC)

-include $(DEPS)
# Inclusion des fichiers .d générés par GCC, - au début pour ne pas afficher les erreurs de fichiers manquants