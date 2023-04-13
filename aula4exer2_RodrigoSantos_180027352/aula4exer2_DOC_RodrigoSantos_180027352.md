<style>
    footer {
        text-align: center;
        page-break-after: always;
    }
</style>

<!--
     METODOLOGIA =>   (primeiro) ME-R =>   (depois) DE-R =>   (finaliza) DE

ENUNCIADO

Existe a necessidade de criação de uma agenda pessoal para uma única pessoa contendo os dados de identificação de cada pessoa cadastrada, seu(s) endereço(s) e telefone(s), parentescos primários (somente cônjuge, filhos e pais) identificados com os dados pessoais (nome e data de nascimento) de cada um destes parentes que serão registrados (armazenados na agenda pessoal).

Respeite as regras para elaboração do ME-R e dos diagramas (DE-R e Diagrama de Esquemas), conforme foi estudado nas últimas aulas.

-->

**Aluno:** Rodrigo Carvalho dos Santos<br>
**Matrícula:** 180027352<br>

# AULA 4 EXERCÍCIO 2

## ME-R (Modelo Entidade Relacionamento)

### ENTIDADES:

PESSOA<br>
ENDERECO<br>
TELEFONE<br>

### ATRIBUTOS:

PESSOA(<u>nomeCompleto</u>, dataNascimento)<br>
ENDERECO(<u>nomeDaPessoa</u>, cep, estado, cidade, bairro, rua, numero, complemento)<br>
TELEFONE(<u>nomeDaPessoa</u>, ddd, numero)<br>

### RELACIONAMENTOS:

PESSOA - **possui** - ENDERECO<br>
Uma PESSOA pode possuir um ou mais ENDERECO<br>
Cardinalidade: (**1:n**)<br>

PESSOA - **reside** - TELEFONE<br>
Uma PESSOA pode possuir um ou mais TELEFONE<br>
Cardinalidade: (**1:n**)<br>

<footer></footer>

## DE-R (Diagrama Entidade Relacionamento)

![](Conceitual_RodrigoSantos_180027352.png)

<footer></footer>

## DE

![](Esquema_RodrigoSantos_180027352.png)
