// Inclui as bibliotecas necessárias para o programa.
#include <iostream> // Para entrada e saída padrão (std::cout, std::cin).
#include <string>   // Para usar a classe std::string para textos.
#include <memory>   // Para usar std::unique_ptr para gerenciamento inteligente de memória (evita vazamentos de memória).

// Enumeração (enum) para representar os possíveis personagens que o Akinator pode adivinhar.
enum CharacterGuess {
    UNKNOWN_GUESS,        // Representa um palpite desconhecido ou um estado inicial.
    HARRY_POTTER,
    VOLDEMORT,
    HERMIONE_GRANGER,
    DRACO_MALFOY,
    SNAPE,
    RON_WEASLEY,
    GINNY_WEASLEY,
    LUNA_LOVEGOOD,
    MINERVA_MCGONAGALL,
    ALBUS_DUMBLEDORE,
    BELLATRIX_LESTRANGE
};

// Enumeração para representar os diferentes atributos sobre os quais o Akinator fará perguntas.
// Cada membro representa uma pergunta específica.
enum QuestionAttribute {
    IS_MALE,                  // O personagem é do sexo masculino?
    IS_STUDENT_AT_HOGWARTS,   // O personagem é/foi estudante em Hogwarts?
    IS_VILLAIN_ARCHETYPE,     // O personagem é um vilão ou usa magia das trevas?
    IS_GRYFFINDOR_HOUSE,      // O personagem pertence à casa Grifinória?
    IS_WEASLEY,               // O personagem é da família Weasley?
    IS_DEATH_EATER,           // O personagem é um Comensal da Morte?
    IS_HOGWARTS_PROFESSOR,    // O personagem é/foi professor em Hogwarts?
    IS_RAVENCLAW_HOUSE,       // O personagem pertence à casa Corvinal?
    NONE_QUESTION             // Valor especial para indicar que este nó é uma folha (um palpite final) e não uma pergunta.
};

// Estrutura para representar um nó na árvore de decisão do Akinator.
// Um nó pode ser uma pergunta (nó interno) ou um palpite final (nó folha).
struct Node {
    QuestionAttribute question; // Armazena o atributo da pergunta que este nó representa.
                                // Se for NONE_QUESTION, significa que este nó é um palpite.
    CharacterGuess guess;       // Se este nó for uma folha (um palpite), armazena qual personagem é.
                                // Caso contrário, geralmente é UNKNOWN_GUESS.

    std::unique_ptr<Node> yesBranch; // Ponteiro inteligente para o nó filho se a resposta à pergunta for "sim".
    std::unique_ptr<Node> noBranch;  // Ponteiro inteligente para o nó filho se a resposta à pergunta for "não".

    // Construtor para um nó que representa uma pergunta.
    // Inicializa o nó com uma pergunta e define o palpite como desconhecido.
    Node(QuestionAttribute q) : question(q), guess(UNKNOWN_GUESS) {}

    // Construtor para um nó que representa um palpite final (nó folha).
    // Inicializa o nó com um palpite e define a pergunta como NONE_QUESTION.
    Node(CharacterGuess g) : question(NONE_QUESTION), guess(g) {}

    // Método para verificar se este nó é um nó folha (ou seja, um palpite).
    // Retorna true se o campo 'guess' não for UNKNOWN_GUESS, indicando que é um palpite.
    bool isGuess() const {
        return guess != UNKNOWN_GUESS;
    }
};

// Função para fazer uma pergunta ao usuário e obter uma resposta binária (sim/não).
// Recebe o texto da pergunta como argumento.
// Retorna true para "sim" (s/S) e false para "não" (n/N).
bool askQuestion(const std::string& questionText) {
    std::cout << questionText << " (s/n): "; // Exibe a pergunta.
    char response;
    std::cin >> response; // Lê a resposta do usuário.

    // Loop para garantir que a entrada do usuário seja válida ('s', 'S', 'n', ou 'N').
    while (response != 's' && response != 'S' && response != 'n' && response != 'N') {
        std::cout << "Resposta inválida. Por favor, digite 's' para sim ou 'n' para não: ";
        std::cin >> response; // Pede novamente a entrada se for inválida.
    }
    // Retorna true se a resposta for 's' ou 'S', caso contrário, false.
    return (response == 's' || response == 'S');
}

// Função recursiva para "jogar" o Akinator, percorrendo a árvore de decisão.
// Recebe um ponteiro constante para o nó atual da árvore.
void playAkinator(const Node* node) {
    // Caso base da recursão: se o nó atual é um palpite (nó folha).
    if (node->isGuess()) {
        std::cout << "\n------------------------------------" << std::endl;
        std::cout << "Seu personagem é... ";
        // Usa um switch para imprimir o nome do personagem correspondente ao palpite.
        switch (node->guess) {
            case HARRY_POTTER: std::cout << "Harry Potter!"; break;
            case VOLDEMORT: std::cout << "Lord Voldemort!"; break;
            case HERMIONE_GRANGER: std::cout << "Hermione Granger!"; break;
            case DRACO_MALFOY: std::cout << "Draco Malfoy!"; break;
            case SNAPE: std::cout << "Severus Snape!"; break;
            case RON_WEASLEY: std::cout << "Rony Weasley!"; break;
            case GINNY_WEASLEY: std::cout << "Ginny Weasley!"; break;
            case LUNA_LOVEGOOD: std::cout << "Luna Lovegood!"; break;
            case MINERVA_MCGONAGALL: std::cout << "Minerva McGonagall!"; break;
            case ALBUS_DUMBLEDORE: std::cout << "Alvo Dumbledore!"; break;
            case BELLATRIX_LESTRANGE: std::cout << "Bellatrix Lestrange!"; break;
            default: std::cout << "um personagem desconhecido para mim! (Minha base de dados é limitada.)"; break;
        }
        std::cout << "\n------------------------------------" << std::endl;
        return; // Termina a função, pois o palpite foi dado.
    }

    // Se não é um nó de palpite, então é um nó de pergunta.
    bool response; // Variável para armazenar a resposta do usuário (true para sim, false para não).
    // Usa um switch para determinar qual pergunta fazer com base no atributo do nó atual.
    switch (node->question) {
        case IS_MALE:
            response = askQuestion("Seu personagem é do sexo masculino?");
            break;
        case IS_STUDENT_AT_HOGWARTS:
            response = askQuestion("Seu personagem é um estudante em Hogwarts (durante os livros)?");
            break;
        case IS_VILLAIN_ARCHETYPE:
            response = askQuestion("Seu personagem é um vilão principal ou usa magia negra com frequência?");
            break;
        case IS_GRYFFINDOR_HOUSE:
            response = askQuestion("Seu personagem é da casa Grifinória?");
            break;
        case IS_WEASLEY:
            response = askQuestion("Seu personagem faz parte da família Weasley?");
            break;
        case IS_DEATH_EATER:
            response = askQuestion("Seu personagem é um Comensal da Morte (oficialmente ou leal)?");
            break;
        case IS_HOGWARTS_PROFESSOR:
            response = askQuestion("Seu personagem é/foi professor em Hogwarts?");
            break;
        case IS_RAVENCLAW_HOUSE:
            response = askQuestion("Seu personagem é da casa Corvinal?");
            break;
        default:
            // Caso um atributo de pergunta desconhecido seja encontrado (erro na lógica da árvore).
            std::cout << "Desculpe, não consigo adivinhar. Algo deu errado na minha lógica." << std::endl;
            return;
    }

    // Com base na resposta do usuário, decide para qual ramo da árvore seguir.
    if (response) { //   Se a resposta foi "sim".
        if (node->yesBranch) { // Verifica se existe um ramo "sim".
            playAkinator(node->yesBranch.get()); // Chama recursivamente a função para o ramo "sim".
                                                 // .get() obtém o ponteiro bruto do unique_ptr.
        } else {
            // Se não houver um ramo "sim" (a árvore está incompleta para este caminho).
            std::cout << "\n------------------------------------" << std::endl;
            std::cout << "Hmm, não consigo adivinhar com base nas suas respostas. Minha base de dados é limitada. Tente outro personagem!" << std::endl;
            std::cout << "------------------------------------" << std::endl;
        }
    } else { // Se a resposta foi "não".
        if (node->noBranch) { // Verifica se existe um ramo "não".
            playAkinator(node->noBranch.get()); // Chama recursivamente a função para o ramo "não".
        } else {
            // Se não houver um ramo "não" (a árvore está incompleta para este caminho).
            std::cout << "\n------------------------------------" << std::endl;
            std::cout << "Hmm, não consigo adivinhar com base nas suas respostas. Minha base de dados é limitada. Tente outro personagem!" << std::endl;
            std::cout << "------------------------------------" << std::endl;
        }
    }
}

// Função para construir a árvore de decisão do Akinator.
// Define a estrutura de perguntas e respostas que leva aos palpites.
// Retorna um unique_ptr para o nó raiz da árvore construída.
std::unique_ptr<Node> buildAkinatorTree() {
    // Nível 1: Raiz - A primeira pergunta é sobre o sexo do personagem.
    auto root = std::make_unique<Node>(IS_MALE); // Cria o nó raiz com a pergunta IS_MALE.

    // --- RAMO MASCULINO (Resposta "SIM" para IS_MALE) ---
    // Se for masculino, a próxima pergunta é: É estudante em Hogwarts?
    root->yesBranch = std::make_unique<Node>(IS_STUDENT_AT_HOGWARTS);

    // Se é masculino E estudante:
    // Próxima pergunta: É da Grifinória?
    root->yesBranch->yesBranch = std::make_unique<Node>(IS_GRYFFINDOR_HOUSE);
    Node* maleStudentBranch = root->yesBranch->yesBranch.get(); // Ponteiro auxiliar para facilitar a adição de nós.

    // Se é masculino, estudante E da Grifinória:
    // Próxima pergunta: É um Weasley?
    maleStudentBranch->yesBranch = std::make_unique<Node>(IS_WEASLEY);
    maleStudentBranch->yesBranch->yesBranch = std::make_unique<Node>(RON_WEASLEY); // Sim (Weasley) -> Rony Weasley
    maleStudentBranch->yesBranch->noBranch = std::make_unique<Node>(HARRY_POTTER);  // Não (não Weasley, mas Grifinória) -> Harry Potter

    // Se é masculino, estudante E NÃO da Grifinória:
    // Assume-se que é Draco Malfoy (principal estudante masculino não-Grifinória, Sonserina).
    maleStudentBranch->noBranch = std::make_unique<Node>(DRACO_MALFOY);

    // Se é masculino E NÃO estudante (adulto, pós-Hogwarts ou nunca foi estudante):
    // Próxima pergunta: É/foi professor em Hogwarts?
    root->yesBranch->noBranch = std::make_unique<Node>(IS_HOGWARTS_PROFESSOR);
    Node* maleNonStudentBranch = root->yesBranch->noBranch.get(); // Ponteiro auxiliar.

    // Se é masculino, não estudante E professor:
    maleNonStudentBranch->yesBranch = std::make_unique<Node>(ALBUS_DUMBLEDORE); // Sim (professor) -> Alvo Dumbledore
                                                                             
    // Se é masculino, não estudante E NÃO professor:
    // Próxima pergunta: É um vilão?
    maleNonStudentBranch->noBranch = std::make_unique<Node>(IS_VILLAIN_ARCHETYPE);
    maleNonStudentBranch->noBranch->yesBranch = std::make_unique<Node>(VOLDEMORT); // Sim (vilão) -> Voldemort
    maleNonStudentBranch->noBranch->noBranch = std::make_unique<Node>(SNAPE);      // Não (vilão, mas não professor) -> Snape (complexo, mas essa lógica simplifica)

    // --- RAMO FEMININO (Resposta "NÃO" para IS_MALE) ---
    // Se for feminino, a próxima pergunta é: É estudante em Hogwarts?
    root->noBranch = std::make_unique<Node>(IS_STUDENT_AT_HOGWARTS);

    // Se é feminino E estudante:
    // Próxima pergunta: É da Grifinória?
    root->noBranch->yesBranch = std::make_unique<Node>(IS_GRYFFINDOR_HOUSE);
    Node* femaleStudentBranch = root->noBranch->yesBranch.get(); // Ponteiro auxiliar.

    // Se é feminino, estudante E da Grifinória:
    // Próxima pergunta: É uma Weasley?
    femaleStudentBranch->yesBranch = std::make_unique<Node>(IS_WEASLEY);
    femaleStudentBranch->yesBranch->yesBranch = std::make_unique<Node>(GINNY_WEASLEY);    // Sim (Weasley) -> Ginny Weasley
    femaleStudentBranch->yesBranch->noBranch = std::make_unique<Node>(HERMIONE_GRANGER); // Não (Weasley, mas Grifinória) -> Hermione Granger

    // Se é feminino, estudante E NÃO da Grifinória:
    // Próxima pergunta: É da Corvinal?
    femaleStudentBranch->noBranch = std::make_unique<Node>(IS_RAVENCLAW_HOUSE);
    femaleStudentBranch->noBranch->yesBranch = std::make_unique<Node>(LUNA_LOVEGOOD); // Sim (Corvinal) -> Luna Lovegood
    femaleStudentBranch->noBranch->noBranch = std::make_unique<Node>(UNKNOWN_GUESS); // Não (Corvinal, nem Grifinória) -> Palpite desconhecido                

    // Se é feminino E NÃO estudante:
    // Próxima pergunta: É/foi professora em Hogwarts?
    root->noBranch->noBranch = std::make_unique<Node>(IS_HOGWARTS_PROFESSOR);
    Node* femaleNonStudentBranch = root->noBranch->noBranch.get(); // Ponteiro auxiliar.

    // Se é feminino, não estudante E professora:
    femaleNonStudentBranch->yesBranch = std::make_unique<Node>(MINERVA_MCGONAGALL); // Sim (professora) -> Minerva McGonagall

    // Se é feminino, não estudante E NÃO professora:
    // Próxima pergunta: É uma Comensal da Morte?
    femaleNonStudentBranch->noBranch = std::make_unique<Node>(IS_DEATH_EATER);
    femaleNonStudentBranch->noBranch->yesBranch = std::make_unique<Node>(BELLATRIX_LESTRANGE); // Sim (Comensal da Morte) -> Bellatrix Lestrange
    femaleNonStudentBranch->noBranch->noBranch = std::make_unique<Node>(UNKNOWN_GUESS);       // Não (Comensal da Morte) -> Palpite desconhecido
    return root; // Retorna o ponteiro para o nó raiz da árvore montada.
}

// Função principal do programa.
int main() {
    // Mensagens de boas-vindas para o usuário.
    std::cout << "Bem-vindo ao Akinator de Harry Potter Ampliado!" << std::endl;
    std::cout << "Pense em um personagem e eu tentarei adivinhar!" << std::endl;
    std::cout << "Responda com 's' para sim ou 'n' para não." << std::endl;

    // Constrói a árvore de decisão do Akinator.
    // 'auto' deduz o tipo de akinatorTree como std::unique_ptr<Node>.
    auto akinatorTree = buildAkinatorTree();

    // Inicia o jogo, começando pelo nó raiz da árvore.
    // .get() é usado para passar o ponteiro bruto gerenciado pelo unique_ptr para a função.
    playAkinator(akinatorTree.get());

    return 0; // Indica que o programa terminou com sucesso.
}