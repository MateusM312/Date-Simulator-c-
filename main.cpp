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
            cout << index << ". " << nome << " - " << idade << " Anos - " << "Nivel de Relacionamento: " << coracao << endl;
        }
};

class Jogador : public Pessoas{
    protected:
        double dinheiro = 0;
    public:
        Jogador(string n, int i, int pre){
            setInfo(n, i, 0); //voltar aqui
        }

        void addItem(string item){
            inventario.push_back(item);
            cout << "Você comprou: " << item << endl;
        }

        void pedirNamoro(NPC* npc){
            if (npc->getNamorando() == true){
                cout << "\nVocê já está namorando!!\n";
                return;
            }
            if (npc->getCoracao() < 50){
                cout << "\nVocês ainda não são chegados o suficiente!\n";
                return;
            }
            cout << "\nParabens!! Agora vocês estão namorando!!\n";
            npc->setRelacionamento(true, false);
        }

        void pedirCasamento(NPC* npc){
            if (npc->getCasado() == true){
                cout << "\nVocê já está casado!!\n";
                return;
            }
            if (npc->getCoracao() < 100){
                cout << "\nVocês ainda não são chegados o suficiente!\n";
                return;
            }
            if (npc->getNamorando() == false){
                cout << "\nVocês ainda não estão namorando!\n";
                return; // faltava esse return!
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
                npc->flertar("presente", 1);
                cout << "\033[32m";
                cout << "Bonus de +1 pois esse é o predente favorito de " << npc->getName() << endl;
                cout << "\033[0m";
                }else{
                    npc->flertar("presente", 0.5);
                }
            inventario.erase(inventario.begin() + itemIdx);
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
        cout << "7. Exibir pretendentes" << endl;
        cout << "9. Debug" << endl;
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
                    Presentes loja;
                    loja.getItens();
                    cout << "99. Sair da loja\nEscolha: ";
                    cin >> v;
                    if (v != 99){
                        try {
                            if (v < 0 || v > 11)
                                throw runtime_error("Item inexistente na loja!");
                            
                            player->setMoney(loja.getPreco(v));
                            player->addItem(loja.getPresente(v));
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
                    cout << "\n---------------------- FLERTAR ----------------------\n";
                    cout << "\033[0m";
                    cout << "Com quem você deseja flertar: ";
                    cin >> flerte;

                    try {
                        if (flerte < 0 || flerte >= npcs.size()){
                            throw out_of_range("NPC não encontrado!");
                        }

                        cout << "1. Contar piada\n";
                        cout << "2. Presentear\n";
                        cout << "0. Sair\n";
                        cin >> tipoFlerte;

                        if (tipoFlerte == 1){
                            npcs[flerte]->flertar("Contar Piada", 0.5);
                            npcs[flerte]->exibirInformacoes(flerte);
                            sleep_seconds(0.1);
                        } else if (tipoFlerte == 2){
                            system("cls");
                            int giveGift = 0;
                            player->seeItems();
                            cout << "\nEscolha que presente deseja dar: ";
                            cin >> giveGift;
                            player->Presentear(npcs[flerte], giveGift);
                            npcs[flerte]->exibirInformacoes(flerte);
                            sleep_seconds(2);
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
                for (int i = 0; i < npcs.size(); i++){
                    npcs[i]->exibirInformacoes(i);
                }
                cout << "Quem você deseja pedir em namoro?\n-> ";
                cin >> indexNamoro;
                player->pedirNamoro(npcs[indexNamoro]);
                break;
            case 5:
                system("cls");
                int indexCasamento;
                for (int i = 0; i < npcs.size(); i++){
                    npcs[i]->exibirInformacoes(i);
                }
                cout << "Quem você deseja pedir em casamento?\n-> ";
                cin >> indexCasamento;
                player->pedirCasamento(npcs[indexCasamento]);
                break;
                break;
            case 6:
                int s;
                do{
                    system("cls");
                    cout << "\n---------------------- INVENTARIO ----------------------\n";
                    player->seeItems();
                    cout << "\n0. Sair\n->";
                    cin >> s;
                } while (s != 0);
                break;
            case 7:
                int u;
                do{
                    system("cls");
                    cout << "\n---------------------- SOLTEIROS ----------------------\n";
                    for (int i = 0; i < npcs.size(); i++){
                        npcs[i]->exibirInformacoes(i);
                    }
                    cout << "0 Para sair!\n->";
                    cin >> u;
                    cout << endl;
                }while (u != 0);
                break;
            case 9:
                int debug;
                do{
                    system("cls");
                    cout << "\n---------------------- DEBUG MENU ----------------------\n";
                    cout << "1. Adicionar NPC\n2. Deletar NPC\n3. Adicionar Dinheiro\n0. Sair\n->";
                    cin >> debug;
                    switch(debug){
                        case 1:{
                            string nomeNPC; 
                            int idadeNPC, presenteNPC;

                            system("cls");
                            cout << "\n---------------------- CRIAR NPC ----------------------\n";

                            cout << "Nome do novo pretendente: ";
                            cin >> nomeNPC;

                            cout << "Idade: ";
                            cin >> idadeNPC;

                            cout << "\nPresentes: 0.Flores 1.Chocolate 2.Livro 3.Cafe 4.Pizza 5.Videogame 6.Joia 7.Musica 8.Planta 9.Roupa 10.Pelucia 11.Perfume";
                            cout << "\nQual o seu presente favorito: ";
                            cin >> presenteNPC;

                            NPC* novoNPC = new NPC(nomeNPC, idadeNPC, presenteNPC);
                            npcs.push_back(novoNPC);

                            cout << "\nNPC " << nomeNPC << " criado com sucesso!\n";
                            sleep_seconds(1.5);
                            break;
                        }
                        case 2:{
                            system("cls");
                            int total = -1;
                            for (int i = 0; i < npcs.size(); i++){
                                npcs[i]->exibirInformacoes(i);
                                total++;
                            }
                            int excluir;
                            cout << "\nDe 0 - " << total << " selecione quem você quer excluir\n-> ";
                            cin >> excluir;

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
                        case 3:
                            double money;
                            system("cls");
                            cout << "\nQuanto de dinheiro deseja adicionar\n-> ";
                            cin >> money;
                            player->setMoney(money);
                            break;
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
