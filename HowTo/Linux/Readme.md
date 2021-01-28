Executer les commandes suivantes depuis Projet_initial
1. make -C irrlicht-1.8.4/source/Irrlicht (opt. -j16)           
2. Attendre un peu
3. mkdir build
4. cd build
5. cmake ..
6. make
7. cd ..
8. ./build/irrlicht_CPE

Il est aussi possible de remplacer les étapes 3 à 8 par l'utilisation de qtcreator. 
Ouvrir le CMakeLists.txt avec qtcreator et mofifier le repertoire d'execution pour Projet_initial.
