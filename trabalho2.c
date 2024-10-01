#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// struct com as informações do carro
typedef struct{
	int e; // número de vezes que entrou na garagem
	int s; // número de vezes que saiu da garagem
	char placa[8];
}carro;

// struct de cada elemento da pilha
typedef struct no{
	carro c;
	struct no *proximo;
}No;

// função para definir as informações do carro
carro registrar_carro(char placa[8]){
	carro c;
	strcpy(c.placa, placa);
	c.e = 1; // como o carro está sendo inserido pela primeira vez na garagem, recebe entrada como sendo igual a 1
	c.s = 0;
	return c;
}

// função para imprimir as informações de cada carro
void imprimir_carro(carro c){
	printf("\nPlaca: %s", c.placa);
}

// função para adicionar um novo carro à garagem
No* adicionar_carro(No **topo, char placa[8]){
	No *novo = malloc(sizeof(No)); // cria um novo no
	int n_carros = 0;
	No *aux = *topo; // cria um ponteiro auxiliar para manter o conteúdo da pilha
	
	// condicional para contabilizar o número de carros na garagem até o momento
	while(aux){
		aux = aux->proximo;
		n_carros++;
	}
	
	// caso o número de carros seja 5 (limite suportado), a função retorna a mesma pilha
	if(n_carros >= 5){
		printf("\nA garagem já atingiu o limite de vagas. Carro %s não entrou.\n", placa);
		return *topo;
	}
	
	// condicional para verificar se o novo no foi criado com sucesso
	if(novo){
		novo->c = registrar_carro(placa);
		novo->proximo = *topo;
		printf("\nCarro %s entrou na garagem.\n", placa);
		return novo;
	}
	else{
		printf("\nNão foi possível adicionar o carro\n");
		return NULL;
	}
}

// função para remover um carro da garagem, escolhido pelo usuário
No* remover_carro(No **topo, char placa_a_remover[8]){
	No *remover = NULL; // ponteiro onde ficará alocado o elemento a ser removido
	No *aux = *topo; // cria um ponteiro auxiliar para manter o conteúdo da pilha
	
	// condicional para verificar se a pilha possui algum elemento
	if(*topo){
		// condicional para caso o carro a ser excluido seja o primeiro da pilha
		if(strcmp((*topo)->c.placa, placa_a_remover) == 0){ 
			remover = *topo;
			*topo = remover->proximo;
			printf("\nCarro %s saiu da garagem.\n", remover->c.placa);
		} else {
			// condicional para percorrer todos os elementos da pilha em busca da placa inserida pelo usuário
			while(aux->proximo && strcmp(aux->proximo->c.placa, placa_a_remover) != 0){  
				aux = aux->proximo;
			}
			
			// quando a placa for encontrada, atribui ao ponteiro remover o elemento que será excluído
			if(aux->proximo){
				remover = aux->proximo; 
				aux->proximo = remover->proximo; 
				printf("\nCarro %s saiu da garagem.\n", remover->c.placa);
			}
		}
	}
	
	if(remover) {
		remover->c.s++;
	}
	
	return remover;
}

// função para visualizar todos os carros/placas até o momento
void visualizar_garagem(No *topo){
	while(topo){
		printf("\n\n==========================");
		imprimir_carro(topo->c);
		printf("\n==========================");
		topo = topo->proximo;
	}
}

// função para contar quantos carros precisaram de manobras para retirar o carro selecionado
void contagem_manobras(No **topo, No *remover){
	int n_manobras = 0;	
	No *aux = *topo;
	
	while(aux && aux != remover->proximo){
		aux = aux->proximo;
		n_manobras++;
	}
	
	printf("\nNúmero de carros que precisaram fazer manobras: %d\n", n_manobras);
}

int main(void){
	setlocale(LC_ALL, "Portuguese");
	
	No *remover, *topo = NULL; 	// ponteiro onde a função a ser excluída será alocada | cria a Lista
	
	// Listagem das placas de "E" - Entrada e "S" - Saída
	char placas_e_movimentos[][2][18] = {
		{"E", "JOV4340"},
		{"E", "NFB4125"},
		{"E", "HTJ8438"},
		{"S", "NFB4125"},
		{"E", "MXC8514"},
		{"S", "JOV4340"},
		{"E", "MPE3615"},
		{"E", "MMD9657"},
		{"S", "HTJ8438"},
		{"E", "LWP6813"},
		{"E", "NAV2363"},
		{"S", "LWP6813"},
		{"E", "MYG5410"},
		{"S", "MXC8514"},
		{"E", "BHB3282"},
		{"E", "KIM2792"},
		{"S", "MYG5410"},
		{"E", "EGI6357"},
	};
	
	// armazena o número total de placas/movimentos da Lista
	int n_movimentos = sizeof(placas_e_movimentos) / sizeof(placas_e_movimentos[0]); // tamanho total da matriz divido pelo tamanho de um elemento
	
	// condicional para passar por todas as placas/movimentos da lista
	for(int i = 0; i < n_movimentos; i++){
		// Se o movimento for de 'Entrada', o carro é adicionado à garagem
		if(strcmp(placas_e_movimentos[i][0], "E") == 0){
			topo = adicionar_carro(&topo, placas_e_movimentos[i][1]);
		} 
		
		// Se o movimento for de 'Saída', o carro será removido da garagem e será contado o número de manobras necessárias
		else if(strcmp(placas_e_movimentos[i][0], "S") == 0){
			remover = remover_carro(&topo, placas_e_movimentos[i][1]);
			if(remover){
				contagem_manobras(&topo, remover);
				free(remover);
				printf("\n");
			}
		}
	}
	
	printf("\n\nCarros na garagem:\n");
	visualizar_garagem(topo);
	
	printf("\n\n\n");
	
	system("PAUSE");
	
	return 0;
}
