#!/usr/bin/env python3
"""
Script de visualisation des performances
Génère des graphiques pour comparer les algorithmes
"""

import matplotlib.pyplot as plt
import sys

def lire_fichier(nom_fichier):
    """Lit le fichier CSV et retourne les données"""
    # Dictionnaires pour stocker les données de chaque algo
    donnees = {1: [], 2: [], 3: []}
    
    fichier = open(nom_fichier, 'r')
    lignes = fichier.readlines()
    fichier.close()
    
    # Ignorer la première ligne (en-tête)
    for ligne in lignes[1:]:
        valeurs = ligne.strip().split(',')
        algo = int(valeurs[0])
        nb_mots_total = int(valeurs[1])
        nb_mots_diff = int(valeurs[2])
        temps = float(valeurs[3])
        mem_max = int(valeurs[4])
        
        donnees[algo].append({
            'nb_mots': nb_mots_total,
            'nb_diff': nb_mots_diff,
            'temps': temps,
            'memoire': mem_max
        })
    
    return donnees

def graphique_temps(donnees):
    """Graphique du temps d'exécution"""
    plt.figure(figsize=(10, 6))
    
    noms = {1: "Tableau", 2: "Liste", 3: "Hachage"}
    couleurs = {1: 'blue', 2: 'green', 3: 'red'}
    
    for algo in [1, 2, 3]:
        if donnees[algo]:
            # Trier par nombre de mots
            donnees[algo].sort(key=lambda x: x['nb_mots'])
            
            mots = [d['nb_mots'] for d in donnees[algo]]
            temps = [d['temps'] for d in donnees[algo]]
            
            plt.plot(mots, temps, marker='o', label=noms[algo], 
                    color=couleurs[algo], linewidth=2)
    
    plt.xlabel('Nombre de mots')
    plt.ylabel('Temps (secondes)')
    plt.title('Temps d\'exécution des algorithmes')
    plt.legend()
    plt.grid(True)
    plt.savefig('temps.png')
    print("✓ Graphique sauvegardé : temps.png")
    plt.close()

def graphique_memoire(donnees):
    """Graphique de l'utilisation mémoire"""
    plt.figure(figsize=(10, 6))
    
    noms = {1: "Tableau", 2: "Liste", 3: "Hachage"}
    couleurs = {1: 'blue', 2: 'green', 3: 'red'}
    
    for algo in [1, 2, 3]:
        if donnees[algo]:
            donnees[algo].sort(key=lambda x: x['nb_mots'])
            
            mots = [d['nb_mots'] for d in donnees[algo]]
            memoire = [d['memoire'] / 1024 for d in donnees[algo]]  # En Ko
            
            plt.plot(mots, memoire, marker='s', label=noms[algo],
                    color=couleurs[algo], linewidth=2)
    
    plt.xlabel('Nombre de mots')
    plt.ylabel('Mémoire (Ko)')
    plt.title('Utilisation mémoire des algorithmes')
    plt.legend()
    plt.grid(True)
    plt.savefig('memoire.png')
    print("✓ Graphique sauvegardé : memoire.png")
    plt.close()

def graphique_comparaison(donnees):
    """Graphique en barres pour comparer les algos"""
    plt.figure(figsize=(10, 6))
    
    noms = {1: "Tableau", 2: "Liste", 3: "Hachage"}
    
    # Calculer le temps moyen pour chaque algo
    temps_moyens = []
    noms_algos = []
    
    for algo in [1, 2, 3]:
        if donnees[algo]:
            temps = [d['temps'] for d in donnees[algo]]
            temps_moyen = sum(temps) / len(temps)
            temps_moyens.append(temps_moyen)
            noms_algos.append(noms[algo])
    
    couleurs = ['blue', 'green', 'red']
    plt.bar(noms_algos, temps_moyens, color=couleurs)
    plt.ylabel('Temps moyen (secondes)')
    plt.title('Comparaison des temps moyens')
    plt.grid(True, axis='y')
    plt.savefig('comparaison.png')
    print("✓ Graphique sauvegardé : comparaison.png")
    plt.close()

# Programme principal
if len(sys.argv) < 2:
    print("Usage: python visualisation.py performances.csv")
else:
    fichier = sys.argv[1]
    print(f"Lecture de {fichier}...")
    
    donnees = lire_fichier(fichier)
    
    print("Génération des graphiques...")
    graphique_temps(donnees)
    graphique_memoire(donnees)
    graphique_comparaison(donnees)
    
    print("\n✓ Terminé !")