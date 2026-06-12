using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>

void sleep_seconds(double seconds) {
    clock_t start = clock(); // retorna o número de ticks do processador desde que o programa iniciou
    while ((clock() - start) / CLOCKS_PER_SEC < seconds); // CLOCKS_PER_SEC converte ticks para SEGUNDOS
}  

// Função para ler um inteiro com validação
int lerInt(string mensagem){
    int valor;
    cout << mensagem;
    cin >> valor;
    while(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida! Digite um numero: ";
        cin >> valor;
    }
    return valor;
}

//========================== CLASSE PRESENTES ===========================//
class Presentes{
    private:
        vector<string> presente = {"Flores", "Chocolate", "Livro", "Cafe", "Pizza", "Videogame", "Joia", "Musica", "Planta", "Roupa", "Pelucia", "Perfume"};
        vector<int> preco = {-30, -20, -72, -20, -80, -120, -280, -12, -6, -100, -26, -200};
    public:
        void getItens(){
            for (int i = 0; i < 12; i++){
                cout << "[" << i << "] " << presente[i] << " - " << preco[i] << "R$" << endl;
            }
        }

        string getPresente(int index){
            return presente[index];
        }

        int getPreco(int index){
            return preco[index];
        }
};

// Classe base que representa qualquer pessoa do jogo(NPC ou Jogador)
class Pessoas{
    protected:
        string nome;
        int idade;
        string presente; //Presente favorito da pessoa
        vector<string> inventario;
    public:
        Presentes p; //Composição: cada pessoa tem acesso ao catálogo de presentes
        void setInfo(string nome, int idade, int index){
            this->nome = nome;
            this->idade = idade;
            this->presente = p.getPresente(index);
        }
    
};

//NPC: pretendente que pode evoluir relacionamento com o jogador
class NPC : public Pessoas{
    private:
        double coracao = 0; // representa o nível de relacionamento do NPC com o jogador, varia de 0 a 100
        bool namorando = false;
        bool casado = false;
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
        double getCoracao(){
            return coracao;
        }

        bool getNamorando(){
            return namorando;
        }

        bool getCasado(){
            return casado;
        }

        void setRelacionamento(bool namoro, bool casando){
            namorando = namoro;
            casado = casando;
        }

        void flertar(string tipo, double qtd){
            if (tipo == "Contar Piada"){
                coracao += 0.5;
            }else if (tipo == "presente"){
                coracao += qtd;
            }
        }

        void exibirInformacoes(int index){
            cout << "[" << index << "] " << nome << " - " << idade << " Anos - " << "Nivel de Relacionamento: " << coracao << endl;
        }
};

class Jogador : public Pessoas{
    protected:
        double dinheiro = 0;
    public:
        Jogador(string n, int i, int pre){
            setInfo(n, i, 0);
        }

        void addItem(string item){
            inventario.push_back(item);
            cout << "Você comprou: " << item << endl;
        }

        void pedirNamoro(NPC* npc){
            if (npc->getNamorando() == true){
                cout << "\nVocê já está namorando!!\n";
                sleep_seconds(1);
                return;
            }
            if (npc->getCoracao() < 50){
                cout << "\nVocês ainda não são chegados o suficiente!\n";
                sleep_seconds(1);
                return;
            }
            cout << "\nParabens!! Agora vocês estão namorando!!\n";
            npc->setRelacionamento(true, false);
            sleep_seconds(1);
        }
        //Regra: só pode se casar se já estiver namorando, e o nível de relacionamento tem que ser 100 ou mais
        void pedirCasamento(NPC* npc){
            if (npc->getCasado() == true){
                cout << "\nVocê já está casado!!\n";
                sleep_seconds(1);
                return;
            }
            if (npc->getNamorando() == false){
                cout << "\nVocês ainda não estão namorando!\n";
                sleep_seconds(1);
                return; // faltava esse return!
            }
            if (npc->getCoracao() < 100){
                cout << "\nVocês ainda não são chegados o suficiente!\n";
                sleep_seconds(1);
                return;
            }
            cout << "\nParabens!! Agora vocês estão casados!!\n";
            npc->setRelacionamento(true, true);

            // Tela de fim de jogo
            sleep_seconds(1);
            system("cls");
            cout << "\033[33m";
            cout << "\nOBRIGADO POR JOGAR\n";
            cout << "\033[0m";
            cout << "\nParabéns!! Você zerou o jogo!\n";
            cout << "O jogo fechará em 4 segundos...\n";
            sleep_seconds(4);
            exit(0); // fecha o programa
        }

        void Presentear(NPC* npc, int itemIdx){
            if (itemIdx < 0 || itemIdx >= inventario.size()) {
                cout << "Item invalido!\n"; return;
            }

            cout << "Você presenteou " << npc->getName() << " com " << inventario[itemIdx] << "!\n";
            if (inventario[itemIdx] == npc->getfavPresent()){
                npc->flertar("presente", 25);
                cout << "\033[32m";
                cout << "Bonus de +25 pois esse é o predente favorito de " << npc->getName() << endl;
                cout << "\033[0m";
                }else{
                    npc->flertar("presente", 6);
                }
            inventario.erase(inventario.begin() + itemIdx);
        }

        void seeItems(){
            for(int i = 0; i < inventario.size(); i++){
                cout << "[" << i << "] - " << inventario[i] << endl;
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

    cout << "\n ======================================================================\n";
    cout << "                           DATE SIMULATOR!\n";
    cout << "                         Crie seu personagem\n";
    cout << " ======================================================================\n\n";
    cout << "Nome: ";
    cin  >> nome;


    //-----------------------------------------------------------------------
    // Validação de idade com try-catch + loop:
    // continua pedindo a idade até que seja valida (entre 16 e 60 anos)
    //-----------------------------------------------------------------------
    while(true){
        idade = lerInt("Idade: ");
        try{
            if(idade < 16 || idade > 60){
                throw invalid_argument("Idade Invalida! O jogo so aceita idades entre 16 e 60 anos.");
            }
            break;
        }catch(invalid_argument& e){
            cout << "\n" << e.what() << "\n\n";
        }
    }
    cout << "\n Presentes disponíveis:\n";
    cout << "---------------------------------------------------------\n";
    cout << " [0] FLores    [1] Chocolate   [2] Livro \n";
    cout << " [3] Cafe      [4] Pizza       [5] Videogame \n";
    cout << " [6] Joia      [7] Musica      [8] Planta \n";
    cout << " [9] Roupa     [10] Pelucia   [11] Perfume \n";
    cout << "---------------------------------------------------------\n";
    cout << "\nDigite o numero do seu presente favorito!!\n";
    while(true){
    presenteFav = lerInt("\nEscolha: ");
    try{
        if(presenteFav < 0 || presenteFav > 11){
            throw invalid_argument("Presente Invalido! Escolha um numero entre 0 e 11.");
        }
        break; // valor válido, sai do loop
    }catch(const exception& e){ //const Exception& é para pegar qualquer tipo de exceção, não só invalid_argument
        cout << "\n" << e.what() << "\n\n";
    }
}
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
        cout << "\n ================================================\n";
        cout << "              DATE SIMULATOR\n";
        cout << " ================================================\n";
        cout << "  Saldo: R$" << player->getMoney() << "\n";
        cout << " ------------------------------------------------\n";
        cout << "  [1] Ir Trabalhar\n";
        cout << "  [2] Ir a Loja\n";
        cout << "  [3] Flertar\n";
        cout << "  [4] Pedir em namoro\n";
        cout << "  [5] Pedir em casamento\n";
        cout << "  [6] Exibir Inventario\n";
        cout << "  [7] Ver pretendentes\n";
        cout << "  [8] Debug\n";
        cout << "  [0] Sair\n";
        cout << " ------------------------------------------------\n";
      
        escolha = lerInt(" Escolha: ");
        cout << endl;

        switch (escolha) {
            case 1:
                int i;
                do{
                    system("cls");
                    double oldMoney = player->getMoney();
                    cout << "\033[32m";
                    cout << "\n=========================================\n";
                    cout << "               TRABALHAR\n";
                    cout << "=========================================\n";
                    cout << "\033[0m";
                    cout << "-----------------------------------------\n";
                    cout << "[1] Vender bolo de pote\n";
                    cout << "[2] Cultivar plantas\n";
                    cout << "[3] Trabalhar em um escritório\n";
                    cout << "[0] Voltar pra casa\n";
                    cout << "-----------------------------------------\n";
                    i = lerInt("O que deseja fazer? n-> ");
                    switch (i)
                    {
                    case 1:
                        player->setMoney(+50);
                        cout << "Saldo anterior: " << oldMoney << " - Saldo atual: R$" << player->getMoney() << endl;
                        sleep_seconds(1);
                        break;
                    case 2:
                        player->setMoney(+20);
                        cout << "Saldo anterior: " << oldMoney << " - Saldo atual: R$" << player->getMoney() << endl;
                        sleep_seconds(1); 
                        break;
                    case 3:
                        player->setMoney(+150);
                        cout << "Saldo anterior: " << oldMoney << " - Saldo atual: R$" << player->getMoney() << endl;
                        sleep_seconds(1);
                        break;
                    case 0:
                        cout << "\nVoltando!\n";
                        sleep_seconds(0.5);
                        break;
                    default:
                        cout << "\nNão encontrado!\n";
                        sleep_seconds(0.3);
                        break;
                    }
                }while (i != 0);
                
                break;
            case 2:
                int v;
                do{
                    system("cls");
                    Presentes loja;
                    cout << "\n=========================================\n";
                    cout << "               LOJA\n";
                    cout << "=========================================\n";
                    cout << "Saldo Atual: R$" << player->getMoney() << endl;
                    cout << "------------------------------------\n";
                    loja.getItens();
                    cout << "[99] Sair da loja\n";
                    cout << "------------------------------------\n";
                    v = lerInt("O que deseja comprar? n-> ");
                    if (v != 99){
                        try {
                            if (v < 0 || v > 11)
                                throw runtime_error("Item inexistente na loja!");
                            
                            player->setMoney(loja.getPreco(v));
                            player->addItem(loja.getPresente(v));
                            sleep_seconds(1.5);
                        } catch (runtime_error& e) {
                            cout << "\nErro: " << e.what() << "\n";
                            sleep_seconds(1.5);
                        }
                    }
                }while (v != 99);
                break;            
            case 3:
                int tipoFlerte;
                do{
                    system("cls");
                    cout << "\033[31m";
                    int flerte;
                    cout << "\n================================================\n";
                    cout << "                   FLERTAR\n";
                    cout << "================================================\n";
                    cout << "\033[0m";
                    cout <<"--------------------------------------------------\n";
                    for (int i = 0; i < npcs.size(); i++){
                        npcs[i]->exibirInformacoes(i);
                    }
                    cout <<"--------------------------------------------------\n";
                    flerte = lerInt("Com quem deseja flertar? n-> ");
                    cout << endl;
                    try {
                        if (flerte < 0 || flerte >= npcs.size()){
                            throw out_of_range("NPC não encontrado!");
                        }

                        cout << "[1] Contar piada\n";
                        cout << "[2] Presentear\n";
                        cout << "[0] Sair\n";
                        cout << endl;
                        tipoFlerte = lerInt("Escolha: ");

                        if (tipoFlerte == 1){
                            npcs[flerte]->flertar("Contar Piada", 12);
                            npcs[flerte]->exibirInformacoes(flerte);
                            sleep_seconds(0.1);
                        } else if (tipoFlerte == 2){
                            system("cls");
                            int giveGift = 0;
                            cout << "\n=================================\n";
                            cout << "        Items para presentear\n";
                            cout << "=================================\n";
                            cout << "---------------------------------\n";
                            player->seeItems();
                            cout << "---------------------------------\n";
                            cout << "\nEscolha que presente deseja dar: ";
                            giveGift = lerInt("n-> ");
                            player->Presentear(npcs[flerte], giveGift);
                            npcs[flerte]->exibirInformacoes(flerte);
                            sleep_seconds(4);
                            tipoFlerte = -1; // para voltar pro menu de flerte
                        } else {
                            continue;
                        }

                    } catch (out_of_range& e) {
                        cout << "\n\033[31mErro: " << e.what() << "\033[0m\n";
                        sleep_seconds(1.5);
                        tipoFlerte = -1;
                    }

                } while (tipoFlerte != 0);
                break;            
            case 4:
                system("cls");
                int indexNamoro;
                cout << "\n  ================================================\n";
                cout << "             PEDIR EM NAMORO\n";
                cout << "  ================================================\n";
                cout << "------------------------------------------------\n";
                try{
                    for (int i = 0; i < npcs.size(); i++){
                        npcs[i]->exibirInformacoes(i);
                     }
                cout << "------------------------------------------------\n";
                     indexNamoro = lerInt("Com quem deseja namorar? n-> ");

                    if (indexNamoro < 0 || indexNamoro >= npcs.size()){
                    throw out_of_range("NPC não encontrado!");
                    }
                     player->pedirNamoro(npcs[indexNamoro]);
                 }catch (out_of_range& e) {
                      cout << "\n\033[31mErro: " << e.what() << "\033[0m\n";
                    sleep_seconds(1.5);
                }
                break;
            case 5:
                system("cls");
                 int indexCasamento;
                cout << "\n  ================================================\n";
                cout << "             PEDIR EM CASAMENTO\n";
                cout << "  ================================================\n";
                cout << "------------------------------------------------\n";
                 try{
                     for (int i = 0; i < npcs.size(); i++){
                         npcs[i]->exibirInformacoes(i);
                    }
                    cout << "------------------------------------------------\n";
                    indexCasamento = lerInt("Com quem deseja casar? n-> ");

                    if(indexCasamento < 0 || indexCasamento >= npcs.size()){
                        throw out_of_range("NPC não encontrado!");
                    }
                    player->pedirCasamento(npcs[indexCasamento]);
                 }catch (out_of_range& e) {
                     cout << "\n\033[31mErro: " << e.what() << "\033[0m\n";
                    sleep_seconds(2);
                }
                break;
            case 6:
                int s;
                do{
                    system("cls");
                    cout << "\n=========================================\n";
                    cout << "               INVENTÁRIO\n";
                    cout << "=========================================\n";
                    cout << "-------------------------------------------\n";
                    player->seeItems();
                    cout << endl;
                    cout <<"\nDigite [0] Para voltar!\n";
                    cout << "-----------------------------------------\n\n";
                    cout << "Digite aqui: ";
                    cin >> s;
                } while (s != 0);
                break;
            case 7:
                int u;
                do{
                    system("cls");
                    cout << "\n=========================================\n";
                    cout << "               SOLTEIROS\n";
                    cout << "=========================================\n";
                    cout << "------------------------------------------------\n";
                    for (int i = 0; i < npcs.size(); i++){
                        npcs[i]->exibirInformacoes(i);
                    }
                    cout << endl;
                    cout << "Digite [0] Para voltar!\n";
                    cout << "------------------------------------------------\n";
                    cout << endl;
                    cout <<"Digite aqui: ";
                    cin >> u;
                    cout << endl;
                }while (u != 0);
                break;
            case 8:
                int debug;
                do{
                    system("cls");
                    cout << "\n=========================================\n";
                    cout << "               DEBUG MENU\n";
                    cout << "=========================================\n";
                    cout << "------------------------------------------\n";
                    cout << "[1] Adicionar NPC\n[2] Deletar NPC\n[3] Adicionar Dinheiro\n[0] Sair" << endl;
                    cout << "------------------------------------------\n";
                    debug = lerInt("Escolha: ");
                    switch(debug){
                        case 1:{
                            string nomeNPC; 
                            int idadeNPC, presenteNPC;

                            system("cls");
                            cout << "\n=========================================\n";
                            cout << "               CRIAR NPC\n";
                            cout << "=========================================\n";

                            cout << "Nome do novo pretendente: ";
                            cin >> nomeNPC;

                            idadeNPC = lerInt("Idade do novo pretendente: ");

                            cout << "\nPresentes disponíveis:\n";
                            cout << "---------------------------------------------------------\n";
                            cout << " [0] FLores    [1] Chocolate   [2] Livro \n";
                            cout << " [3] Cafe      [4] Pizza       [5] Videogame \n";
                            cout << " [6] Joia      [7] Musica      [8] Planta \n";
                            cout << " [9] Roupa     [10] Pelucia   [11] Perfume \n";
                            cout << "---------------------------------------------------------\n";
                            presenteNPC = lerInt("Presente favorito do NPC: ");

                            NPC* novoNPC = new NPC(nomeNPC, idadeNPC, presenteNPC);
                            npcs.push_back(novoNPC);

                            cout << "\nNPC " << nomeNPC << " criado com sucesso!\n";
                            sleep_seconds(1.5);
                            break;
                        }
                        case 2:{
                            system("cls");
                            int total = -1;
                            cout << "----------------------------------------------------\n";
                            for (int i = 0; i < npcs.size(); i++){
                                npcs[i]->exibirInformacoes(i);
                                total++;
                            }
                            cout << "---------------------------------------------------\n";

                            int excluir = lerInt("\nDe 0 a " + to_string(total) + ", qual NPC deseja excluir? n-> ");

                            if (excluir >= 0 && excluir < npcs.size()){
                                cout << "\nNPC " << npcs[excluir]->getName() << " excluido!\n";
                                delete npcs[excluir]; // libera
                                npcs.erase(npcs.begin() + excluir); // remove
                            }else{
                                cout << "\nInvalido!\n";
                            }

                            sleep_seconds(1.5);
                            break;
                        }
                        case 3:{
                            system("cls");
                            int money = lerInt("Quanto dinheiro deseja adicionar? n-> ");
                            player->setMoney(money);
                            cout << " Saldo atual: R$" << player->getMoney() << endl;
                            break;
                        };
                        default:
                            cout << "\nERRO\n";
                            break;
                    }
                }while(debug != 0);
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