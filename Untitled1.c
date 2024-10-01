#include <stdio.h>
#include <string.h>
#include <ctype.h> // Para usar a função isdigit

#define MAX_VENDAS 100
#define MAX_NOME_PRODUTO 50

typedef struct {
    char nome[MAX_NOME_PRODUTO];
    int quantidade;
    float valor_unitario;
} Venda;

void exibir_tabela(Venda vendas[], int num_vendas) {
    printf("\nLista de vendas realizadas no dia, em ordem decrescente:\n");
    printf("+-------------------+------------+-------------------+\n");
    printf("|      Produto      | Quantidade |   Valor Unitario   |\n");
    printf("+-------------------+------------+-------------------+\n");
    int i; // Declare a variável i antes do loop
    for (i = 0; i < num_vendas; i++) {
        printf("| %-17s | %10d | R$ %14.2f |\n",
               vendas[i].nome, vendas[i].quantidade, vendas[i].valor_unitario);
    }
    printf("+-------------------+------------+-------------------+\n");
}

int main() {
    Venda vendas[MAX_VENDAS];
    int num_vendas = 0;
    float faturamento_total = 0;
    int total_itens_vendidos = 0;
    int total_clientes = 0;
    char produto_mais_vendido[MAX_NOME_PRODUTO];
    char produto_menos_vendido[MAX_NOME_PRODUTO];
    int max_vendido = 0;
    int min_vendido = 0;
    char comando[50];

    while (1) {
        printf("Digite o nome do produto (ou 'fim' para encerrar): ");
        scanf("%s", vendas[num_vendas].nome);

        if (strcmp(vendas[num_vendas].nome, "fim") == 0) {
            break;
        }

        while (1) {
            printf("Digite a quantidade vendida: ");
            if (scanf("%d", &vendas[num_vendas].quantidade) != 1) {
                printf("Erro: quantidade invalida. Por favor, digite um numero.\n");
                // Limpar o buffer de entrada
                while (getchar() != '\n');
            } else {
                break;
            }
        }

        while (1) {
            printf("Digite o valor unitario: ");
            if (scanf("%f", &vendas[num_vendas].valor_unitario) != 1) {
                printf("Erro: valor unitario invalido. Por favor, digite um numero.\n");
                // Limpar o buffer de entrada
                while (getchar() != '\n');
            } else {
                break;
            }
        }

        faturamento_total += vendas[num_vendas].quantidade * vendas[num_vendas].valor_unitario;
        total_itens_vendidos += vendas[num_vendas].quantidade;
        total_clientes++;

        if (vendas[num_vendas].quantidade > max_vendido) {
            max_vendido = vendas[num_vendas].quantidade;
            strcpy(produto_mais_vendido, vendas[num_vendas].nome);
        }

        if (min_vendido == 0 || vendas[num_vendas].quantidade < min_vendido) {
            min_vendido = vendas[num_vendas].quantidade;
            strcpy(produto_menos_vendido, vendas[num_vendas].nome);
        }

        num_vendas++;
    }

    printf("\n----- Relatorio Diario -----\n");
    printf("Quantidade total de itens vendidos: %d\n", total_itens_vendidos);
    printf("Faturamento bruto diario: %.2f\n", faturamento_total);
    printf("Quantidade de clientes que realizaram compras: %d\n", total_clientes);
    printf("Item mais vendido: %s\n", produto_mais_vendido);
    printf("Item menos vendido: %s\n", produto_menos_vendido);

    printf("\nPara finalizar, Digite qualquer tecla: ");
    getch();

    if (strcmp(comando, "tabela") == 0) {
        exibir_tabela(vendas, num_vendas);
    }

    return 0;
}
