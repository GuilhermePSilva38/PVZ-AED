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

void exibirMenu(){
    cout << "========================================\n";
    cout << "      PLANTS VS ZOMBIES 2 - AED C++     \n";
    cout << "========================================\n";
    cout << " 1. Girassol (Sunflower - $50)\n";
    cout << " 2. Ervilha Simples (Peashooter - $100)\n";
    cout << " 3. Disparervilha Dupla (Repeater - $200)\n";
    cout << " 4. Ervilha de Fogo (Fire Peashooter - $175)\n";
    cout << " 5. Mina Batata (Potato Mine - $25)\n";
    cout << " 6. Repolho Boxeador (Bonk Choy - $150)\n";
    cout << " 7. Nos Escudo (Wall-nut - $50)\n";
    cout << " 8. Passar Turno (Atualizar Acoes e Inimigos)\n";
    cout << " 9. Buscar Zumbi por Nome (LDE)\n";
    cout << " 10. Ordenar Zumbis por HP (LDE)\n";
    cout << " 11. Sair\n";
    cout << "========================================\n";
    cout << "Escolha uma opcao: ";
}

int main(){
    srand(time(nullptr));
    Game pvz;
    int opcao = 0;
    int turno = 1;
    bool jogoAtivo = true;

    while(opcao != 11 && jogoAtivo){
        limparTela();
        cout << "Turno Atual: " << turno << " | Sois Disponiveis: $" << pvz.getSuns() << endl;
        
        pvz.displayBoard();
        exibirMenu();
        cin >> opcao;

        if(opcao >= 1 && opcao <= 7){
            int lin, col;
            cout << "Digite a linha (0-4) e coluna (0-8): ";
            cin >> lin >> col;

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
            
            if(jogoAtivo && rand() % 100 < 70){ 
                int linha = rand() % 5;
                int sorteio = rand() % 4;

                if(sorteio == 0) pvz.spawnZombie(new BasicZombie(linha, 8));
                else if(sorteio == 1) pvz.spawnZombie(new ConeheadZombie(linha, 8));
                else if(sorteio == 2) pvz.spawnZombie(new BucketheadZombie(linha, 8));
                else if(sorteio == 3) pvz.spawnZombie(new NewspaperZombie(linha, 8));
            }

            turno++;
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        else if(opcao == 9){
            string nome;
            cout << "Digite o nome do zumbi a buscar (ex: Buckethead Zombie): ";
            cin.ignore();
            getline(cin, nome);
            pvz.searchZombieByName(nome);
            cout << "\nPressione Enter para continuar...";
            cin.get();
        }
        else if(opcao == 10){
            pvz.sortZombiesByHp();
            cout << "\nPressione Enter para continuar...";
            cin.ignore();
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