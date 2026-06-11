using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

void sleep_seconds(double seconds) {
    clock_t start = clock(); // retorna o número de ticks do processador desde que o programa iniciou
    while ((clock() - start) / CLOCKS_PER_SEC < seconds); // CLOCKS_PER_SEC converte ticks para SEGUNDOS
}  

class Presentes{
    private:
        vector<string> presente = {"Flores", "Chocolate", "Livro", "Cafe", "Pizza", "Videogame", "Joia", "Musica", "Planta", "Roupa", "Pelucia", "Perfume"};
        vector<int> preco = {-30, -20, -72, -20, -80, -120, -280, -12, -6, -100, -26, -200};
    public:
        void getItens(){
            for (int i = 0; i < 12; i++){
                cout << i << ". " << presente[i] << " - " << preco[i] << "R$" << endl;
            }
        }

        string getPresente(int index){
            return presente[index];
        }

        int getPreco(int index){
            return preco[index];
        }
};

class Pessoas{
    protected:
        string nome;
        int idade;
        string presente;
        vector<string> inventario;
    public:
        Presentes p;
        void setInfo(string nome, int idade, int index){
            this->nome = nome;
            this->idade = idade;
            this->presente = p.getPresente(index);
        }
    
};

//========================== CLASSE NPC ===========================//

class NPC : public Pessoas{
    private:
        double coracao = 0;
    public:
        NPC(string nome, int idade, int presente){
            setInfo(nome, idade, presente);
        }

        string getName(){
            return nome;
        }

        string getfavPresent(){
            return presente;
        }

        void flertar(string tipo, double qtd){
            if (tipo == "Contar Piada"){
                coracao += 0.5;
            }else if (tipo == "presente"){
                coracao += qtd;
            }
        }
};

void exibirNPCS(){
    cout << "\n---------------------- SOLTEIROS ----------------------\n";
    cout << "0. Maria - 19 Anos - Solteira " << endl;
    cout << "1. Abigail - 21 Anos - Solteira " << endl;
    cout << "2. Alex - 22 Anos - Solteiro " << endl;
    cout << "3. Elliot - 31 Anos - Solteiro " << endl;
    cout << "4. Emily - 28 Anos - Solteira " << endl;
    cout << "5. Haley - 21 Anos - Solteira " << endl;
    cout << "6. Harvey - 33 Anos - Solteiro "<< endl;
    cout << "7. Leah - 27 Anos - Solteira " << endl;
    cout << "8. Maru - 20 Anos - Solteira " << endl;
    cout << "9. Penny - 23 Anos - Solteira " << endl;
    cout << "10. Sam - 21 Anos - Solteiro " << endl;
    cout << "11. Sebastian - 26 Anos - Solteiro " << endl;
    cout << "12. Shane - 31 Anos - Solteiro " << endl;
};

class Jogador : public Pessoas{
    private:
        double dinheiro;
    public:
        Jogador(string n, int i, int pre){
            setInfo(n, i, 0); //voltar aqui
        }

        void addItem(string item){
            inventario.push_back(item);
            cout << "Você comprou: " << item << endl;
        }

        void Presentear(NPC* npc, int itemIdx){
            cout << "Selecione a pessoa que você deseja presentear: ";
            if (itemIdx < 0 || itemIdx >= inventario.size()) {
                cout << "Item invalido!\n"; return;
            }

            cout << "Você presenteou " << npc->getName() << " com " << inventario[itemIdx] << "!\n";
            if (inventario[itemIdx] == npc->getfavPresent()){
                npc->flertar("presente", 1);
                }else{
                    npc->flertar("presente", 0.5);
                }
            inventario.erase(inventario.begin() + itemIdx);
            // aqui você também pode chamar npc->receberPresente(item) futuramente
        }

        void seeItems(){
            for(int i = 0; i < inventario.size(); i++){
                cout << i << " - " << inventario[i];
            }
        }

        void setMoney(int price){
            dinheiro += price;
        }

        double getMoney(){
            return dinheiro;
        }
}; 

int main(){
    int escolha, idade, presenteFav;
    string nome;

    system("cls");
    system("chcp 65001 > nul");

    cout << "\n---------------------- DATE SIMULATOR (Crie seu personagem) ----------------------\n";
    cout << "Qual o seu nome: ";
    cin  >> nome;
    cout << "\nQual sua idade: ";
    cin >> idade;
    cout << "\nPresentes: 0.Flores 1.Chocolate 2.Livro 3.Cafe 4.Pizza 5.Videogame 6.Joia 7.Musica 8.Planta 9.Roupa 10.Pelucia 11.Perfume";
    cout << "\nQual o seu presente favorito: ";
    cin >> presenteFav;

    Jogador* player = new Jogador(nome, idade, presenteFav);

    vector<NPC*> npcs = {
        new NPC("Maria", 19, 0), // Ama Flores
        new NPC("Abigail", 21, 5), //Ama Videogame
        new NPC("Alex", 22, 9), //Ama Roupa
        new NPC("Elliot", 31, 10), //Ama Pelucia
        new NPC("Emily", 28, 6), //Ama joia
        new NPC("Haley", 21, 11), // Ama Perfume
        new NPC("Harvey", 33, 3), //Ama cafe
        new NPC("Leah", 27, 8), //Ama Planta
        new NPC("Maru", 20, 5), //Ama Videogame
        new NPC("Penny", 23, 2), //Ama Livro
        new NPC("Sam", 21, 7), //Ama Musica
        new NPC("Sebastian", 26, 1), //Ama Chocolate
        new NPC("Shane", 31, 4), //Ama Pizza
    };
    

    do{
        system("cls");
        cout << "\n---------------------- DATE SIMULATOR ----------------------\n";

        cout << "1. Ir trabalhar" << endl;
        cout << "2. Ir para a loja" << endl;
        cout << "3. Flertar" << endl;
        cout << "4. Pedir em namoro" << endl;
        cout << "5. Pedir em casamento" << endl;
        cout << "6. Verificar o inventário" << endl;
        cout << "0. Sair" << endl;

        cout << "O que voce deseja fazer? "; 
        cin >> escolha;
        cout << endl;

        switch (escolha) {
            case 1:
                int i;
                do{
                    system("cls");
                    double oldMoney = player->getMoney();
                    cout << "\033[32m";
                    cout << "\n---------------------- TRABALHAR ----------------------\n";
                    cout << "\033[0m";
                    cout << "1. Vender bolo de pote\n";
                    cout << "2. Cultivar plantas\n";
                    cout << "3. Trabalhar em um escritório\n";
                    cout << "0. Voltar pra casa\n";
                    cin >> i;
                    switch (i)
                    {
                    case 1:
                        player->setMoney(+50);
                        cout << "Saldo anterior: " << oldMoney << " - Saldo atual: " << player->getMoney() << endl;
                        sleep_seconds(0.1);
                        break;
                    case 2:
                        player->setMoney(+20);
                        cout << "Saldo anterior: " << oldMoney << " - Saldo atual: " << player->getMoney() << endl;
                        sleep_seconds(0.1);
                        break;
                    case 3:
                        player->setMoney(+150);
                        cout << "Saldo anterior: " << oldMoney << " - Saldo atual: " << player->getMoney() << endl;
                        sleep_seconds(0.1);
                        break;
                    case 0:
                        cout << "\nVoltando!\n";
                        sleep_seconds(0.1);
                        break;
                    default:
                        cout << "\nNão encontrado!\n";
                        sleep_seconds(0.1);
                        break;
                    }
                }while (i != 0);
                
                break;
            case 2:
                int v;
                do{
                    system("cls");
                    cout << "\n---------------------- LOJA ----------------------\n";
                    Presentes loja;
                    loja.getItens();
                    cout << "-1. Sair da loja\nEscolha: ";
                    cin >> v;
                    if (v != 0){
                        player->setMoney(loja.getPreco(v));
                        cout << "O Item " << loja.getPresente(v) << " foi comprador por " << loja.getPreco(v) << "R$\n";
                        cout << "Seu saldo agora é " << player->getMoney();
                    }
                }while (v != -1);
                break;
            case 3:
                int m;
                do{
                    system("cls");
                    cout << "\033[31m";
                    int flerte, tipoFlerte;
                    cout << "\n---------------------- FLERTAR ----------------------\n";
                    cout << "\033[0m";
                    cout << "Com quem você deseja flertar: ";
                    cin >> flerte;

                    cout << "1. Contar piada\n";
                    cout << "2. Presentear\n";
                    cin >> tipoFlerte;

                    if (tipoFlerte == 1){
                        npcs[flerte]->flertar("Contar Piada", 0.5);
                    } else if (tipoFlerte == 2){
                        player->Presentear(npcs[flerte], 1);
                    }
                } while (m != 0);
                break;
            case 4:
            
                break;
            case 5:
            
                break;
            case 6:
                int s;
                do{
                    system("cls");
                    cout << "\n---------------------- INVENTARIO ----------------------\n";
                    player->seeItems();
                    cout << "\n1. Sair\n2. Continuar\n";
                    cin >> s;
                } while (s != 0);
                break;
            case 0:
                system("cls");
                cout << "\033[31m"; 
                cout << "Saindo";

                sleep_seconds(0.1);
                system("cls");
                cout << "Saindo.";

                sleep_seconds(0.1);
                system("cls");
                cout << "Saindo..";

                sleep_seconds(0.1);
                system("cls");
                cout << "Saindo...";
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    } while(escolha != 0);

    return 0;
}
