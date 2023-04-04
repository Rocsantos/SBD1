/**
 * @file aula1exer1_RodrigoSantos_180027352.c
 * @author Rodrigo Carvalho dos Santos (https://github.com/Rocsantos)
 * @brief Um pequeno projeto para a aula de Sistemas de Bancos de Dados 1
 * a qual tem o intuito de cadastrar um número indeterminado de pessoas e
 * um número indeterminado de carros, associados a esta pessoa.
 * Diferente da versão anterior, este código salva fisicamente as pessoas
 * por ordem de nome, e os carros pelo cpf ou rne do proprietario.
 * @version 2.0
 * @date 03/04/2023
**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura Util
#ifdef __WIN32
#define LIMPATELA system("cls")
#else
#define LIMPATELA system("clear")
#endif
#define SEPARADOR puts("-------------------------------------------------------------------------------------");
#define ALOCAVETOR(VETOR, ALOCADO, CADASTRADO, SIZE_T) \
if(CADASTRADO >= ALOCADO) {\
  ALOCADO *= 2;\
  VETOR = realloc(VETOR, SIZE_T*ALOCADO);\
}

// Definição de nome de Arquivos
#define FILE_PESSOAS "pessoas.bin"
#define FILE_VEICULOS "veiculos.bin"

// Declaração de tipos
typedef struct PESSOA {
  char cpf_ou_rne[12];
  char cnh[12];
  char nome[81];
} PESSOA;

typedef struct VEICULO {
  char cpf_ou_rne_proprietario[12];
  char modelo[31];
  char marca[31];
  unsigned ano_fabricacao;
  char cor[31];
  char placa[9];
  char chassi[18];
} VEICULO;

// Controle de Dados;
PESSOA *pessoas_cadastradas;
unsigned qtd_pessoas_alocadas = 32;
unsigned qtd_pessoas_cadastradas = 0;
VEICULO *veiculos_cadastrados;
unsigned qtd_veiculos_alocados = 32;
unsigned qtd_veiculos_cadastrados = 0;

// Declaração de Funções
FILE *ReadFile(char *file_name, char *read_type);
void CadastrarPessoa();
PESSOA *ListarPessoas();
PESSOA EncontrarPessoa(char *cpf_ou_rne, int r);
void CadastrarVeiculo(char *cpf_ou_rne);
VEICULO *ListarVeiculos();

// Ordenação qsort
int comparaNome(const void *a, const void *b) {
  return strcmp(((PESSOA *)a)->nome, ((PESSOA *)b)->nome);
}

int comparaProprietario(const void *a, const void *b) {
  return strcmp(((VEICULO *)a)->cpf_ou_rne_proprietario, ((VEICULO *)b)->cpf_ou_rne_proprietario);
}

int main () {
  pessoas_cadastradas = ListarPessoas();
  veiculos_cadastrados = ListarVeiculos();
  char opcao;
  do {
    LIMPATELA;
		puts("1) Cadastrar Pessoa\n2) Cadastrar Veiculo");
		puts("3) Listar Pessoas\n4) Listar Veiculos");
		puts("5) Sair\nSelecione uma opção"); scanf(" %c", &opcao);
		switch (opcao) {
			case '1':
				CadastrarPessoa();
				break;
			case '2':
				CadastrarVeiculo("");
				break;
			case '3':
				pessoas_cadastradas = ListarPessoas();
        LIMPATELA;
        SEPARADOR;
      	for(int i = 0; i < qtd_pessoas_cadastradas; i++) {
					printf("Nome: %s | CPF ou RNE: %s | CNH: %s\n",
            pessoas_cadastradas[i].nome,
            pessoas_cadastradas[i].cpf_ou_rne,
            pessoas_cadastradas[i].cnh);
					SEPARADOR;
				}
				puts("Voltar para Menu?(s/n)");
				while(opcao=='s')
          scanf(" %c", &opcao);
				break;
			case '4':
				LIMPATELA;
        veiculos_cadastrados = ListarVeiculos();
        SEPARADOR;
				for(int i = 0; i < qtd_veiculos_cadastrados; i++) {
          PESSOA proprietario = EncontrarPessoa(veiculos_cadastrados[i].cpf_ou_rne_proprietario, qtd_pessoas_cadastradas);
					printf("Placa: %s | Marca: %s | Modelo: %s | Cor: %s\n",
            veiculos_cadastrados[i].placa,
            veiculos_cadastrados[i].marca,
            veiculos_cadastrados[i].modelo,
            veiculos_cadastrados[i].cor);
					printf("Chassi: %s | Ano de Fabricação: %u\n",
            veiculos_cadastrados[i].chassi,
            veiculos_cadastrados[i].ano_fabricacao);
          printf("Proprietario: %s\n", proprietario.nome);
					SEPARADOR;
				}
				puts("Voltar para Menu?(s/n)");
				while(opcao!='s') scanf(" %c", &opcao);
				break;
			case '5':
				opcao = 0;
			default:
				break;
		}
	} while (opcao);
  return 0;
}

// Definição de Funções
FILE *ReadFile(char *file_name, char *read_type) {
  FILE *f = fopen(file_name, read_type);
  if(f == NULL) {
    f = fopen(file_name, "w");
  }
  return f;
}

void CadastrarPessoa() {
  ALOCAVETOR(pessoas_cadastradas, qtd_pessoas_alocadas, qtd_pessoas_cadastradas, sizeof(PESSOA));
  PESSOA *nova_pessoa = &pessoas_cadastradas[qtd_pessoas_cadastradas++];
  LIMPATELA;
  puts("Nome:"); scanf(" %80[^\n]", nova_pessoa->nome);
  puts("CPF ou RNE:"); scanf(" %11s", nova_pessoa->cpf_ou_rne);
  puts("CNH: (se não possuir digite 0)"); scanf(" %11s", nova_pessoa->cnh);

  qsort(pessoas_cadastradas, qtd_pessoas_cadastradas, sizeof(PESSOA), comparaNome);

  FILE *f = ReadFile(FILE_PESSOAS, "w+b");
  for(unsigned i = 0; i < qtd_pessoas_cadastradas; i++)
    fwrite(&pessoas_cadastradas[i], sizeof(PESSOA), 1, f);
  fclose(f);

  puts("Deseja Cadastrar um Veiculo para esta pessoa?(s/n)");
  char opcao;
  scanf(" %c", &opcao);
  if(opcao == 's')
    CadastrarVeiculo(nova_pessoa->cpf_ou_rne);
}

PESSOA *ListarPessoas() {
  FILE *f = ReadFile(FILE_PESSOAS, "r+b");
  PESSOA tmp, *listatmp = malloc(sizeof(PESSOA)*qtd_pessoas_alocadas);
  unsigned i;
  for(i = 0; fread(&tmp, sizeof(PESSOA), 1, f) == 1; i++) {
    ALOCAVETOR(pessoas_cadastradas, qtd_pessoas_alocadas, i, sizeof(PESSOA));
    listatmp[i] = tmp;
  }
  qtd_pessoas_cadastradas = i;
  printf("Pessoas Cadastradas: %d\n", i);
  fclose(f);
  return listatmp;
}

PESSOA EncontrarPessoa(char *cpf_ou_rne, int r) {
  unsigned l = 0;
  while (l < r) {
    int m = (l+r)/2;
    int search = strcmp(pessoas_cadastradas[m].cpf_ou_rne, cpf_ou_rne);
    if(search < 0)
      l=m;
    else if(search > 0)
      r=m;
    else
      return pessoas_cadastradas[m];
  }
  return (PESSOA) { .nome = "Não Cadastrado"};
}

void CadastrarVeiculo(char *cpf_ou_rne) {
  if(!strcmp(cpf_ou_rne, "")) {
    puts("CPF ou RNE do Proprietário");
    cpf_ou_rne = malloc(sizeof(char)*12);
    scanf(" %11s", cpf_ou_rne);
  }
  else
    LIMPATELA;

  char opcao = 'n';
  do {
    ALOCAVETOR(veiculos_cadastrados, qtd_veiculos_alocados, qtd_veiculos_cadastrados, sizeof(VEICULO));
    VEICULO *novo_veiculo = &veiculos_cadastrados[qtd_veiculos_cadastrados++];
    strcpy(novo_veiculo->cpf_ou_rne_proprietario, cpf_ou_rne);
	  puts("Modelo:"); scanf(" %30[^\n]", novo_veiculo->modelo);
    puts("Marca:"); scanf(" %30[^\n]", novo_veiculo->marca);
	  puts("Ano de Fabricação:"); scanf("%u", &novo_veiculo->ano_fabricacao);
	  puts("Cor:"); scanf(" %30[^\n]", novo_veiculo->cor);
	  puts("Placa:"); scanf(" %8s", novo_veiculo->placa);
	  puts("Chassi:"); scanf(" %17s", novo_veiculo->chassi);
    puts("Cadastrar outro Veiculo para esta pessoa?(s/n)");
    scanf(" %c", &opcao);
  } while(opcao == 's');
  qsort(veiculos_cadastrados, qtd_veiculos_cadastrados, sizeof(VEICULO), comparaProprietario);
  FILE *f = ReadFile(FILE_VEICULOS, "w+b");
  for(unsigned i = 0; i < qtd_veiculos_cadastrados; i++)
    fwrite(&veiculos_cadastrados[i], sizeof(VEICULO), 1, f);
  fclose(f);
}

VEICULO *ListarVeiculos() {
  FILE *f = ReadFile(FILE_VEICULOS, "r+b");
  VEICULO tmp, *listatmp = malloc(sizeof(VEICULO)*qtd_veiculos_alocados);
  unsigned i;
  for(i = 0; fread(&tmp, sizeof(VEICULO), 1, f) == 1; i++) {
    ALOCAVETOR(veiculos_cadastrados, qtd_veiculos_alocados, i, sizeof(VEICULO));
    listatmp[i] = tmp;
  }
  qtd_veiculos_cadastrados = i;
  fclose(f);
  printf("Veiculos Cadastrados: %d\n", i);
  return listatmp;
}
