#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Plant.h"
#include "Zombie.h"
using namespace std;

void limparTela(){
    system("cls");
}

int main(){
    srand(time(nullptr));
    Game pvz;
    int opcao = 0;
    int turno = 1;
    bool jogoAtivo = true;

    while(opcao != 14 && jogoAtivo){
        limparTela();
        pvz.displayBoard(turno);
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if(opcao >= 1 && opcao <= 7){
            int lin, col;
            cout << "Digite a linha (1-5) e coluna (1-9): ";
            cin >> lin >> col;

            lin--;
            col--;

            switch(opcao){
                case 1:
                    pvz.placePlant(new Sunflower(lin, col), lin, col);
                    break;
                case 2:
                    pvz.placePlant(new Peashooter(lin, col), lin, col);
                    break;
                case 3:
                    pvz.placePlant(new Repeater(lin, col), lin, col);
                    break;
                case 4:
                    pvz.placePlant(new FirePeashooter(lin, col), lin, col);
                    break;
                case 5:
                    pvz.placePlant(new PotatoMine(lin, col), lin, col);
                    break;
                case 6:
                    pvz.placePlant(new BonkChoy(lin, col), lin, col);
                    break;
                case 7:
                    pvz.placePlant(new WallNut(lin, col), lin, col);
                    break;
            }

            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else if(opcao == 8){
            jogoAtivo = pvz.updateEntities();
            
            if(jogoAtivo && rand() % 100 < 75){ 
                pvz.spawnNextZombieFromQueue();
            }

            turno++;
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else if(opcao == 9){
            string nome;
            cout << "Digite o nome do zumbi (ex: Buckethead Zombie): ";
            cin.ignore();
            getline(cin, nome);
            pvz.searchZombieByName(nome);
            cout << "\nPressione Enter para continuar...";
            cin.get();
        }
        else if(opcao == 10){
            pvz.sortZombiesBubble();
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else if(opcao == 11){
            pvz.sortZombiesInsertion();
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else if(opcao == 12){
            pvz.showHistory();
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else if(opcao == 13){
            string planta;
            cout << "Digite o nome da planta (ex: Sunflower, Peashooter, Repeater, Fire Peashooter, Potato Mine, Bonk Choy, WallNut): ";
            cin.ignore();
            getline(cin, planta);
            pvz.consultAlmanaque(planta);
            cout << "\nPressione Enter para continuar...";
            cin.get();
        }
    }

    if(!jogoAtivo){
        cout << "\nVOCE PERDEU! Os zumbis invadiram seu jardim.\n";
    }else{
        cout << "\nJogo encerrado pelo jogador!\n";
    }

return 0;
}