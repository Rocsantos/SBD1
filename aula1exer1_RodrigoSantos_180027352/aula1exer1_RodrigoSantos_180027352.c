/**
 * @file aula1exer1_RodrigoSantos_180027352.c
 * @author Rodrigo Carvalho dos Santos (https://github.com/Rocsantos)
 * @brief Um pequeno projeto para a aula de Sistemas de Bancos de Dados 1
 * a qual tem o intuito de cadastrar um número indeterminado de pessoas e
 * um número indeterminado de carros, associados a esta pessoa.
 * Diferente da versão anterior, este código salva fisicamente as pessoas
 * por ordem de CPF, e os carros pela placa.
 * @version 1.0
 * @date 29/03/2023
 * @copyright Copyright (c) 2022
**/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __WIN32
#define LIMPATELA system("cls")
#else
#define LIMPATELA system("clear")
#endif
#define SEPARADOR puts("-------------------------------------------------------------------------------------");

// Definição de nome de Arquivos
#define FILE_PESSOAS "pessoas.bin"
#define FILE_VEICULOS "veiculos.bin"

// Declaração de tipos
typedef struct PESSOA
{
  char cpf_ou_rne[12];
  char cnh[12];
  char nome[81];
} PESSOA;

typedef struct VEICULO
{
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
unsigned qtd_pessoas_alocadas = 2;
unsigned qtd_pessoas_cadastradas = 0;
VEICULO *veiculos_cadastrados;
unsigned qtd_veiculos_alocados = 2;
unsigned qtd_veiculos_cadastrados = 0;

// Declaração de Funções
FILE *ReadFile(char *file_name, char *read_type);
void CadastrarPessoa();
PESSOA *ListarPessoas();
PESSOA EncontrarPessoa(char *cpf_ou_rne);
void CadastrarVeiculo(char *cpf_ou_rne);
VEICULO *ListarVeiculos();

int main () {
  pessoas_cadastradas = ListarPessoas();
  veiculos_cadastrados = ListarVeiculos();
  char opcao;
  do {
    LIMPATELA;
		puts("1) Cadastrar Pessoa");
		puts("2) Cadastrar Veiculo");
		puts("3) Listar Pessoas");
		puts("4) Listar Veiculos");
		puts("5) Sair");
		puts("Selecione uma opção");
		scanf(" %c", &opcao);
		switch (opcao)
		{
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
      	for(int i = 0; i < qtd_pessoas_cadastradas; i++)
				{
					printf("Nome: %s | CPF ou RNE: %s | CNH: %s\n",
            pessoas_cadastradas[i].nome,
            pessoas_cadastradas[i].cpf_ou_rne,
            pessoas_cadastradas[i].cnh);
					SEPARADOR;
				}
				puts("Voltar para Menu?(s/n)");
				while(opcao!='s')
          scanf(" %c", &opcao);
				break;
			case '4':
				LIMPATELA;
        veiculos_cadastrados = ListarVeiculos();
        SEPARADOR;
				for(int i = 0; i < qtd_veiculos_cadastrados; i++)
				{
          PESSOA proprietario = EncontrarPessoa(veiculos_cadastrados[i].cpf_ou_rne_proprietario);
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
  FILE *f = ReadFile(FILE_PESSOAS, "ab");
  PESSOA nova_pessoa;
  LIMPATELA;
  puts("Nome:"); scanf(" %80[^\n]", nova_pessoa.nome);
  puts("CPF ou RNE:"); scanf(" %11s", nova_pessoa.cpf_ou_rne);
  puts("CNH: (se não possuir digite 0)"); scanf(" %11s", nova_pessoa.cnh);
  fwrite(&nova_pessoa, sizeof(PESSOA), 1, f);
  fclose(f);

  puts("Deseja Cadastrar um Veiculo para esta pessoa?(s/n)");
  char opcao;
  scanf(" %c", &opcao);
  if(opcao == 's')
    CadastrarVeiculo(nova_pessoa.cpf_ou_rne);
}

PESSOA *ListarPessoas() {
  FILE *f = ReadFile(FILE_PESSOAS, "r+b");
  PESSOA tmp, *listatmp = malloc(sizeof(PESSOA)*qtd_pessoas_alocadas);
  unsigned i;
  for(i = 0; fread(&tmp, sizeof(PESSOA), 1, f) == 1; i++) {
    if(i >= qtd_pessoas_alocadas) {
      qtd_pessoas_alocadas *=2;
      listatmp = realloc(listatmp, qtd_pessoas_alocadas);
    }
    listatmp[i] = tmp;
  }
  qtd_pessoas_cadastradas = i;
  fclose(f);
  return listatmp;
}

PESSOA EncontrarPessoa(char *cpf_ou_rne) {
  for(unsigned i = 0; i < qtd_pessoas_cadastradas; i++)
    if(!strcmp(pessoas_cadastradas[i].cpf_ou_rne, cpf_ou_rne))
      return pessoas_cadastradas[i];
  return (PESSOA) { .nome = "Não Encontrado"};
}

void CadastrarVeiculo(char *cpf_ou_rne) {
  FILE *f = ReadFile(FILE_VEICULOS, "ab");
  VEICULO novo_veiculo;
  if(!strcmp(cpf_ou_rne, "")) {
    puts("CPF ou RNE do Proprietário");
    scanf(" %11s", novo_veiculo.cpf_ou_rne_proprietario);
  }
  else {
    strcpy(novo_veiculo.cpf_ou_rne_proprietario, cpf_ou_rne);
    LIMPATELA;
  }

  char opcao;
  do {
	  puts("Modelo:"); scanf(" %30[^\n]", novo_veiculo.modelo);
    puts("Marca:"); scanf(" %30[^\n]", novo_veiculo.marca);
	  puts("Ano de Fabricação:"); scanf("%u", &novo_veiculo.ano_fabricacao);
	  puts("Cor:"); scanf(" %30[^\n]", novo_veiculo.cor);
	  puts("Placa:"); scanf(" %8s", novo_veiculo.placa);
	  puts("Chassi:"); scanf(" %17s", novo_veiculo.chassi);
    puts("Cadastrar outro Veiculo para esta pessoa?(s/n)");
    scanf("%c", &opcao);
    fwrite(&novo_veiculo, sizeof(VEICULO), 1, f);
  } while(opcao == 's');
  fclose(f);
}

VEICULO *ListarVeiculos() {
  FILE *f = ReadFile(FILE_VEICULOS, "r+b");
  VEICULO tmp, *listatmp = malloc(sizeof(VEICULO)*qtd_veiculos_alocados);
  unsigned i;
  for(i = 0; fread(&tmp, sizeof(VEICULO), 1, f) == 1; i++) {
    if(i >= qtd_veiculos_alocados) {
      qtd_veiculos_alocados *= 2;
      listatmp = realloc(listatmp, qtd_veiculos_alocados);
    }
    listatmp[i] = tmp;
  }
  qtd_veiculos_cadastrados = i;
  fclose(f);
  return listatmp;
}
