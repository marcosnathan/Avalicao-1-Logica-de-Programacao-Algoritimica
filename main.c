/**
 *
 *
 *                      UNINASSAU - Curso Análise e Desenvolvimento de Sistemas
 *                        Avaliação 1 - Lógica de Programação Algorítimica
 *
 *  Proposta de Algoritmo:
 *          Cálculo de gastos e orçamento pessoal com foco em realizar um objetivo familiar
 *
 * @author Marcos Nathan
 * @date 09/07/2024
 */
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#define LIMITE_ITENS 20

//atual taxa de selic anual
const float TAXA_JUROS_ANO = 10.4f;

//conversão para meses
const float TAXA_JUROS_MES = (TAXA_JUROS_ANO / 12.f);

//valor padrão para porcentagem de investimento referente aos rendimentos de líquidos
float porcentagem_investimento = 10.0f;

// estrutura que descreve uma movimentação no orçamento: Receita ou Despesa.
typedef struct {
    char descricao[255];
    double valor;
} Movimentacao;

//estrutura que define um objetivo familiar
typedef struct {
    bool cadastrado;
    char descricao[255];
    double valor;
} Objetivo;

//estrutura que descreve o orçamento familiar
typedef struct {
    Movimentacao despesas[LIMITE_ITENS];
    Movimentacao receitas[LIMITE_ITENS];
} Orcamento;

//inicialização de variáveis global
Objetivo objetivo;
Orcamento orcamento;
int despesas = 0, receitas = 0;


/**
 * Menu com opçoes
 */
 void mostrar_menu() {
    printf("1 - Cadastrar objetivo\n");
    printf("2 - Cadastrar receita\n");
    printf("3 - Remover receita\n");
    printf("4 - Cadastrar despesa\n");
    printf("5 - Remover despesa\n");
    printf("6 - Listar receitas\n");
    printf("7 - Listar despesas\n");
    printf("8 - Alterar porcentagem de aportes mensal\n");
    printf("9 - Gerar relatorio\n");
 }



/**
 * Adiciona uma nova receita ao orçamento
 */
void adicionar_receita();

/**
 * Remove uma receita do orçamento
 */
void remover_receita();

/**
 * Lista as receitas do orçamento
 */
void listar_receitas();

/**
 * Adiciona uma nova despesa ao orçamento
 */
void adicionar_despesa();

/**
 * Lista as receitas do orçamento
 */
void listar_despesas();

/**
 * Remove uma despesa do orçamento
 */
 void remover_despesa();

 /**
  * Cadastrar um objetivo
  */
 void cadastrar_objetivo();

 /**
  * Alterar porcentagem de investimento
  * padrão: 10%
  * esse valor reflete na porcentagem que será aportado mensalmente
  * da receita líquida, ou seja, quando descontadas as despesas.
  */
void alterar_porcentagem_aporte_mensal();

/**
 * Função utilitária
 * @param movimentacoes  Receitas ou Despesas para serem exibidas
 */
void print_movimentacoes(Movimentacao * movimentacoes, int tamanho);

/**
 * Função utilitária para exibir dados de uma movimentação
 * @param movimentacoes  Receitas ou Despesas para serem exibidas
 * @param indice         Posicao da movimentacao no array
 */
void print_movimentacao(Movimentacao  movimentacao, int indice);

/**
 * função utilitária para realocar o array de despesas ou receitas quando um item for removido.
 * Ao remover um item do array será necessário realocar os itenns para esquerda para que não
 * tenha espaços vazios no array. Exemplo:
 * Suponha o seguinte array: [*,*,*,*]
 * Caso seja necessário remover o índice 2, o array ficaria assim: [*,*,NULL,*]
 * para isso resolver isso será necessário realocar o indice 3 para o 2: [*,*,*,NULL]
 * @param movimentacoes     Array de movimentacoes que precisa ser realocado
 * @param tamanho           Tamanho do array preenchido
 * @param posicao           Posicao do array que deve ser removido
 */
 void remover_e_realocar_array(Movimentacao * movimentacoes, int *tamanho, int posicao);

 /**
  * função para gerar o relatório final com dados do tempo necessário
  * para acumular o montante desejado para alcançar o objetivo
  */
 void gerar_relatorio();

void adicionar_receita() {
    if(receitas == 20){
        printf("Limite de receitas atingido\n");
        return;
    }
    printf("ADICIONAR RECEITA\n");
    printf("Informe a receita: \n");
    Movimentacao receita;
    scanf("%s", receita.descricao);
    printf("Informe o valor: \n");
    char tmp[255];
    scanf("%s", tmp);
    char *endPtr;
    receita.valor = strtod(tmp, &endPtr);
    orcamento.receitas[receitas] = receita;
    receitas++;
    printf("RECEITA ADICIONADA COM SUCESSO: %d\n", receitas);
    printf("##########################################\n\n");
}

void remover_receita(){
    listar_receitas();
    int opcao;
    printf("Escolha qual receita remover: \n");
    scanf("%d", &opcao);
    remover_e_realocar_array(orcamento.receitas, &receitas, opcao-1);
    printf("RECEITA REMOVIDA COM SUCESSO: %d\n", receitas);
}

void adicionar_despesa() {
    if(despesas == 20){
        printf("Limite de despesas atingido\n");
        return;
    }
    printf("ADICIONAR DESPESA\n");
    printf("Informe a despesa: \n");
    Movimentacao despesa;
    scanf("%s", despesa.descricao);
    printf("Informe o valor: \n");
    char tmp[255];
    scanf("%s", tmp);
    char *endPtr;
    despesa.valor = strtod(tmp, &endPtr);
    orcamento.despesas[despesas] = despesa;
    despesas++;
    printf("DESPESA ADICIONADA COM SUCESSO: %d\n", despesas);
    printf("##########################################\n\n");
}

void remover_despesa(){
    listar_despesas();
    int opcao;
    printf("Escolha qual despesa remover: \n");
    scanf("%d", &opcao);
    remover_e_realocar_array(orcamento.despesas, &despesas, opcao-1);
    printf("DESPESA REMOVIDA COM SUCESSO: %d\n", despesas);
    printf("##########################################\n\n");
}

void cadastrar_objetivo() {
    if(objetivo.cadastrado){
        printf("Objetivo ja cadastrado\n");
        return;
    }
    printf("CADASTRAR OBJETIVO\n");
    printf("Qual objetivo deseja alancar?\n");

    char str[100];

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    if (fgets(objetivo.descricao, sizeof(objetivo.descricao), stdin) != NULL) {
        size_t length = strlen(str);
        if (length > 0 && str[length - 1] == '\n') {
            str[length - 1] = '\0';
        }
    } else {
        printf("Erro ao ler a entrada.\n");
        return;
    }

    printf("Quanto sera necessario para realiza-lo? \n");
    char tmp[255];
    scanf("%s", tmp);
    char *endPtr;
    objetivo.valor = strtod(tmp, &endPtr);
    objetivo.cadastrado = true;
    printf("OBJETIVO CADASTRADO COM SUCESSO\n");
    printf("##########################################\n\n");
}

void listar_despesas() {
    if(despesas <= 0)
        return;
    printf("LISTA DE DESPESAS:\n");
    print_movimentacoes(orcamento.despesas, despesas);
    printf("##########################################\n\n");
}

void listar_receitas() {
    if(receitas <= 0)
        return;
    printf("LISTA DE RECEITAS:\n");
    print_movimentacoes(orcamento.receitas, receitas);

    printf("##########################################\n\n");

}

void print_movimentacoes(Movimentacao * movimentacoes, int tamanho){
    for (int i = 0; i < tamanho; ++i) {
        print_movimentacao(movimentacoes[i], i);
    }
}

void print_movimentacao(Movimentacao  movimentacao, int indice){
    printf("%d - ", indice + 1);
    printf("Descricao: %s | ", movimentacao.descricao);
    printf("Valor: %.2f\n", movimentacao.valor);
}

void remover_e_realocar_array(Movimentacao * movimentacoes, int *tamanho, int posicao){
    movimentacoes[posicao] = movimentacoes[(*tamanho)+1];
    (*tamanho)--;
}

void alterar_porcentagem_aporte_mensal() {
    printf("Insira quantos porcentos da receita liquida deve ser aportado mensalmente: ");
    scanf("%f", &porcentagem_investimento);
    printf("PORCENTAGEM ALTERADA PARADA %.2f\n", porcentagem_investimento);
}

double soma_movimentacoes(Movimentacao * movimentacoes, int tamanho){
    double total = 0;
    for (int i = 0; i < tamanho; ++i) {
        total += movimentacoes[i].valor;
    }
    return total;
}

void exibir_calculo(int tempo, double aporte_mensal){
    double total_investido = 0;
    double total_juros = 0;
    double total_acumulado;
    printf("mes\tjuros\t\ttotal investido\t\ttotal de juros\t\ttotal acumulado\n");
    for (int i = 1; i <= tempo; ++i) {
        total_investido += aporte_mensal;
        total_acumulado =  total_investido + total_juros;
        double juros = total_acumulado*(TAXA_JUROS_MES/100);
        total_juros += juros;
        if(i < 4){
            printf("%d\t", i);
            printf("%.2f\t\t", juros);
            printf("%.2f\t\t\t", total_investido);
            printf("%.2f\t\t\t", total_juros);
            printf("%.2f\n", total_acumulado);
        } else if(i == 4){
            printf(".\n.\n.\n");
        }
        if(tempo - 4 < i){
            printf("%d\t", i);
            printf("%.2f\t\t", juros);
            printf("%.2f\t\t", total_investido);
            printf("%.2f\t\t", total_juros);
            printf("%.2f\n", total_acumulado);
        }

    }
}


void gerar_relatorio() {
    if(!objetivo.cadastrado){
        printf("Nao ha um objetivo cadastrado!");
        return;
    }

    double total_despesas = soma_movimentacoes(orcamento.despesas, despesas);
    double total_receitas = soma_movimentacoes(orcamento.receitas, receitas);
    if(total_despesas >= total_receitas){
        printf("Não há espacos para investir em seu orcamento!");
        return;
    }

    double liquido = total_receitas - total_despesas;
    double valor_investimento = (porcentagem_investimento/100.f) * liquido;
    double M = objetivo.valor;
    double i = TAXA_JUROS_MES/100.f;
    double C = valor_investimento;
    double t = log10((M*i/C) + 1) / log10(1 + i);
    printf("RELATORIO GERADO\n");
    printf("Total de receitas: R$%.2f\n", total_receitas);
    printf("Total de despesas: R$%.2f\n", total_despesas);
    printf("Renda liquida: R$%.2f\n", liquido);
    printf("Objetivo almejado: %s\n", objetivo.descricao);
    printf("Valor necessario para realizar o objetivo: R$%.2f\n", objetivo.valor);
    printf("Taxa de juros: %.2f%% (a.a) / %.6f%% (a.m)\n", TAXA_JUROS_ANO, TAXA_JUROS_MES);
    printf("Aportes mensais %.2f que corresponde a %.1f%% da sua renda liquida\n", valor_investimento, porcentagem_investimento);
    printf("Sera necessario %.1f meses (%.1f anos) para alcancar seu objetivo.\n\n", t, t/12);

    int tempo = (int) ceil(t);
    exibir_calculo(tempo, valor_investimento);

    printf("Aperte enter para continuar...");
    int tmp;
    scanf("%d", &tmp);
}


void inicializar_receitas(){
    strcpy(orcamento.receitas[receitas].descricao, "Salario Homem");
    orcamento.receitas[receitas].valor = 1342.0f;
    receitas++;

    strcpy(orcamento.receitas[receitas].descricao, "Salario Mulher");
    orcamento.receitas[receitas].valor = 5000.0f;
    receitas++;

    strcpy(orcamento.receitas[receitas].descricao, "Aluguel 1");
    orcamento.receitas[receitas].valor = 400.0f;
    receitas++;

    strcpy(orcamento.receitas[receitas].descricao, "Aluguel 2");
    orcamento.receitas[receitas].valor = 1000.0f;
    receitas++;

    strcpy(orcamento.receitas[receitas].descricao, "Aluguel 3");
    orcamento.receitas[receitas].valor = 900.0f;
    receitas++;

    strcpy(orcamento.receitas[receitas].descricao, "Aluguel 4");
    orcamento.receitas[receitas].valor = 800.0f;
    receitas++;
}

void inicializar_despesas(){
    strcpy(orcamento.despesas[despesas].descricao, "Alimentacao");
    orcamento.despesas[despesas].valor = 1500.0f;
    despesas++;

    strcpy(orcamento.despesas[despesas].descricao, "Lazer");
    orcamento.despesas[despesas].valor = 500.0f;
    despesas++;

    strcpy(orcamento.despesas[despesas].descricao, "Escola Filho 1");
    orcamento.despesas[despesas].valor = 200.0f;
    despesas++;

    strcpy(orcamento.despesas[despesas].descricao, "Escola Filho 2");
    orcamento.despesas[despesas].valor = 200.0f;
    despesas++;

    strcpy(orcamento.despesas[despesas].descricao, "Luz e agua");
    orcamento.despesas[despesas].valor = 200.0f;
    despesas++;

    strcpy(orcamento.despesas[despesas].descricao, "Internet");
    orcamento.despesas[despesas].valor = 100.0f;
    despesas++;
}

void inicializar(){
    inicializar_receitas();
    inicializar_despesas();
    strcpy(objetivo.descricao, "Comprar uma casa");
    objetivo.valor = 200000;
    objetivo.cadastrado = true;
}



int main(void) {
    inicializar();
    int opcao;
    do {
        mostrar_menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        switch (opcao) {
            case 1:
                cadastrar_objetivo();
                break;
            case 2:
                adicionar_receita();
                break;
            case 3:
                remover_receita();
                break;
            case 4:
                adicionar_despesa();
                break;
            case 5:
                remover_despesa();
                break;
            case 6:
                listar_receitas();
                break;
            case 7:
                listar_despesas();
                break;
            case 8:
                alterar_porcentagem_aporte_mensal();
                break;
            case 9:
                gerar_relatorio();
                break;
            default:
                printf("Escolha uma opcao valida!\n");
                break;
        }
    } while (opcao != -1);

    return 0;
}
