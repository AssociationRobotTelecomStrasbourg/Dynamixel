# Dynamixel
Bibliothèque de fonctions et classes pour l'utilisation des moteurs dynamixels XM430-W210.

## Contenu
### dynamixel_sdk_c
Code source en C utilisé pour le développement de la bibliothèque.
Source originale : [Robotis](https://github.com/ROBOTIS-GIT/DynamixelSDK)
### XM_class et Control_Table
Code en C++ permettant de contrôler un moteur plus aisément :
- Control_Table contient les variables de contrôle des dynamixels (adresse mémoire, valeurs limites, taille, etc...)
- XM_class comprend une classe qui gère l'initialisation et le contrôle d'un unique moteur

## Utilisation
Pour utiliser cette bibliothèque, il faut d'abord installer ncurses : sudo apt-get install libncurses5-dev libncursesw5-dev

Pour l'installer :
- git clone https://github.com/AssociationRobotTelecomStrasbourg/Dynamixel.git
- cd ARTS_Dynamixel
- mkdir bin build lib && cd build
- cmake ..
- make
