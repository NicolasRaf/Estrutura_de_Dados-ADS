#include <iostream>
#include <string>
#include <memory> 
#include <vector> 

// Enum para representar as classificações (o palpite final do Akinator)
enum CharacterGuess {
    UNKNOWN_GUESS,
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

// Enum para representar os atributos que o Akinator vai perguntar
enum QuestionAttribute {
    IS_MALE,
    IS_STUDENT_AT_HOGWARTS,
    IS_VILLAIN_ARCHETYPE,
    IS_GRYFFINDOR_HOUSE,
    IS_WEASLEY,            // Nova pergunta
    IS_DEATH_EATER,        // Nova pergunta
    IS_HOGWARTS_PROFESSOR, // Nova pergunta
    IS_RAVENCLAW_HOUSE,    // Nova pergunta
    NONE_QUESTION // Para nós folha (o palpite)
};

// Estrutura para um nó da árvore (uma pergunta ou um palpite final)
struct Node {
    QuestionAttribute question; // A pergunta que este nó irá fazer
    CharacterGuess guess;      // Se for um nó folha, este é o palpite

    std::unique_ptr<Node> yesBranch; // Filho para a resposta "sim"
    std::unique_ptr<Node> noBranch;  // Filho para a resposta "não"

    // Construtor para nó de pergunta
    Node(QuestionAttribute q) : question(q), guess(UNKNOWN_GUESS) {}

    // Construtor para nó folha (palpite)
    Node(CharacterGuess g) : question(NONE_QUESTION), guess(g) {}

    // Verifica se é um nó folha (ou seja, um palpite)
    bool isGuess() const {
        return guess != UNKNOWN_GUESS;
    }
};

// Função para fazer uma pergunta ao usuário e obter a resposta binária
bool askQuestion(const std::string& questionText) {
    std::cout << questionText << " (s/n): ";
    char response;
    std::cin >> response;
    // Garante que a entrada seja um 's' ou 'n' válido
    while (response != 's' && response != 'S' && response != 'n' && response != 'N') {
        std::cout << "Resposta inválida. Por favor, digite 's' para sim ou 'n' para não: ";
        std::cin >> response;
    }
    return (response == 's' || response == 'S');
}

// Função para "jogar" o Akinator percorrendo a árvore
void playAkinator(const Node* node) {
    if (node->isGuess()) {
        std::cout << "\n------------------------------------" << std::endl;
        std::cout << "Seu personagem é... ";
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
        return;
    }

    // Se não é um palpite, faz a pergunta correspondente ao nó
    bool response;
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
            std::cout << "Desculpe, não consigo adivinhar. Algo deu errado na minha lógica." << std::endl;
            return;
    }

    // Baseado na resposta, segue para o ramo "sim" ou "não"
    if (response) {
        if (node->yesBranch) {
            playAkinator(node->yesBranch.get());
        } else {
            std::cout << "\n------------------------------------" << std::endl;
            std::cout << "Hmm, não consigo adivinhar com base nas suas respostas. Minha base de dados é limitada. Tente outro personagem!" << std::endl;
            std::cout << "------------------------------------" << std::endl;
        }
    } else {
        if (node->noBranch) {
            playAkinator(node->noBranch.get());
        } else {
            std::cout << "\n------------------------------------" << std::endl;
            std::cout << "Hmm, não consigo adivinhar com base nas suas respostas. Minha base de dados é limitada. Tente outro personagem!" << std::endl;
            std::cout << "------------------------------------" << std::endl;
        }
    }
}

// Função para construir a árvore de "perguntas" do Akinator
std::unique_ptr<Node> buildAkinatorTree() {
    // Nível 1: Raiz - É do sexo masculino?
    auto root = std::make_unique<Node>(IS_MALE);

    // --- RAMO MASCULINO (SIM) ---
    root->yesBranch = std::make_unique<Node>(IS_STUDENT_AT_HOGWARTS); // É estudante em Hogwarts?

    // Se é masculino E estudante
    root->yesBranch->yesBranch = std::make_unique<Node>(IS_GRYFFINDOR_HOUSE);
    Node* maleStudentBranch = root->yesBranch->yesBranch.get(); // Pega o ponteiro bruto para este nó

    maleStudentBranch->yesBranch = std::make_unique<Node>(IS_WEASLEY); // Se Sim (Grifinória) -> É Weasley?
    maleStudentBranch->yesBranch->yesBranch = std::make_unique<Node>(RON_WEASLEY); // Se Sim (Weasley) -> Rony Weasley
    maleStudentBranch->yesBranch->noBranch = std::make_unique<Node>(HARRY_POTTER); // Se Não (não Weasley, Grifinória) -> Harry Potter
    maleStudentBranch->noBranch = std::make_unique<Node>(DRACO_MALFOY); // Se Não (Grifinória, mas estudante masculino) -> Draco Malfoy (assumindo Sonserina como principal não-Grifinória estudante masculino)

    // Se é masculino E NÃO estudante (pós-Hogwarts ou nunca estudante)
    root->yesBranch->noBranch = std::make_unique<Node>(IS_HOGWARTS_PROFESSOR);
    Node* maleNonStudentBranch = root->yesBranch->noBranch.get(); // Pega o ponteiro bruto para este nó

    maleNonStudentBranch->yesBranch = std::make_unique<Node>(ALBUS_DUMBLEDORE);
    maleNonStudentBranch->noBranch = std::make_unique<Node>(IS_VILLAIN_ARCHETYPE);
    maleNonStudentBranch->noBranch->yesBranch = std::make_unique<Node>(VOLDEMORT);
    maleNonStudentBranch->noBranch->noBranch = std::make_unique<Node>(SNAPE);

    // --- RAMO FEMININO (NÃO) ---
    root->noBranch = std::make_unique<Node>(IS_STUDENT_AT_HOGWARTS); // É estudante em Hogwarts?

    // Se é feminino E estudante
    root->noBranch->yesBranch = std::make_unique<Node>(IS_GRYFFINDOR_HOUSE);
    Node* femaleStudentBranch = root->noBranch->yesBranch.get(); // Pega o ponteiro bruto para este nó

    femaleStudentBranch->yesBranch = std::make_unique<Node>(IS_WEASLEY);
    femaleStudentBranch->yesBranch->yesBranch = std::make_unique<Node>(GINNY_WEASLEY);
    femaleStudentBranch->yesBranch->noBranch = std::make_unique<Node>(HERMIONE_GRANGER);

    femaleStudentBranch->noBranch = std::make_unique<Node>(IS_RAVENCLAW_HOUSE);
    femaleStudentBranch->noBranch->yesBranch = std::make_unique<Node>(LUNA_LOVEGOOD);
    femaleStudentBranch->noBranch->noBranch = std::make_unique<Node>(UNKNOWN_GUESS);

    // Se é feminino E NÃO estudante
    root->noBranch->noBranch = std::make_unique<Node>(IS_HOGWARTS_PROFESSOR);
    Node* femaleNonStudentBranch = root->noBranch->noBranch.get(); // Pega o ponteiro bruto para este nó

    femaleNonStudentBranch->yesBranch = std::make_unique<Node>(MINERVA_MCGONAGALL);
    femaleNonStudentBranch->noBranch = std::make_unique<Node>(IS_DEATH_EATER);
    femaleNonStudentBranch->noBranch->yesBranch = std::make_unique<Node>(BELLATRIX_LESTRANGE);
    femaleNonStudentBranch->noBranch->noBranch = std::make_unique<Node>(UNKNOWN_GUESS);

    return root;
}

int main() {
    std::cout << "Bem-vindo ao Akinator de Harry Potter Ampliado!" << std::endl;
    std::cout << "Pense em um personagem e eu tentarei adivinhar!" << std::endl;
    std::cout << "Responda com 's' para sim ou 'n' para não." << std::endl;

    auto akinatorTree = buildAkinatorTree();
    playAkinator(akinatorTree.get());

    return 0;
}