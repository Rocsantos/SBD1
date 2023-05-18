-- -----------< aula4exer5Evolucao3 > -----------
--
--               SCRIPT DE CRIAÇÃO (DDL)
-- Data criacao..........: 10/05/2023
-- Autor(es).............: Igor e Silva Penha
-- Revisor(es)...........: Rodrigo Carvalho dos Santos
-- Baco de Dados.........: MySQL 8.0
-- Base de Dados.........: aula4exer5Evolucao4
--
-- Data Ultima Alteracao ..: 17/05/2023
--   => Criação Especialização e correção de endereço
--
-- PROJETO => 01 Base de Dados
--            10 Tabelas
--
-- -------------------------------------------------

CREATE DATABASE IF NOT EXISTS aula4exer5Evolucao4;

USE aula4exer5Evolucao4;

CREATE TABLE PESSOA (
    idPessoa INT NOT NULL,
    nomeCompleto VARCHAR(80),
    CONSTRAINT PESSOA_PK PRIMARY KEY (idPessoa)
)ENGINE innoDB;

CREATE TABLE MEDICO (
    ufCrm VARCHAR(2) NOT NULL,
    numeroCrm INT NOT NULL,
    idPessoa INT NOT NULL,
    CONSTRAINT MEDICO_PK PRIMARY KEY (numeroCrm, estadoCrm),
    CONSTRAINT PACIENTE_FK FOREIGN KEY (idPaciente) REFERENCES PESSOA (idPessoa)
)ENGINE innoDB;

CREATE TABLE PACIENTE (
    idPaciente INT NOT NULL,
    sexo ENUM('F','M') NOT NULL,
    cep INT NOT NULL,
    estado VARCHAR(2) NOT NULL,
    cidade VARCHAR(30) NOT NULL,
    rua VARCHAR(30) NOT NULL,
    numero INT NOT NULL,
    complemento VARCHAR(30),
    dtNascimento DATE NOT NULL,
    CONSTRAINT PACIENTE_PK PRIMARY KEY (idPaciente),
    CONSTRAINT PACIENTE_FK FOREIGN KEY (idPaciente) REFERENCES PESSOA (idPessoa)
)ENGINE innoDB;

CREATE TABLE ESPECIALIDADE (
    nomeEspecialidade VARCHAR(30) NOT NULL,
    idEspecialidade INT NOT NULL,
    CONSTRAINT ESPECIALIDADE_PK PRIMARY KEY (idEspecialidade)
)ENGINE innoDB;

CREATE TABLE RECEITA (
    idReceita INT NOT NULL,
    descricao VARCHAR(100),
    idConsulta INT,
    CONSTRAINT RECEITA_PK PRIMARY KEY (idReceita),
    CONSTRAINT RECEITA_CONSULTA_FK FOREIGN KEY (idConsulta)  REFERENCES CONSULTA (idConsulta)
)ENGINE innoDB;

CREATE TABLE MEDICAMENTO (
    idMedicamento INT NOT NULL,
    nomeMedicamento VARCHAR(30) NOT NULL,
    CONSTRAINT MEDICAMENTO_PK PRIMARY KEY (idMedicamento)
)ENGINE innoDB;

CREATE TABLE CONSULTA (
    idConsulta INT NOT NULL,
    ufCrm VARCHAR(2),
    numeroCrm INT,
    idPaciente INT,
    dataHora DATETIME
)ENGINE innoDB;

CREATE TABLE telefone (
    idPaciente INT NOT NULL,
    telefone BIGINT NOT NULL,
    CONSTRAINT telefone_PESSOA_FK FOREIGN KEY (idPessoa) REFERENCES PACIENTE (idPaciente)
)ENGINE innoDB;

CREATE TABLE possui (
    idEspecialidade INT NOT NULL,
    ufCrm VARCHAR(2) NOT NULL,
    numeroCrm INT NOT NULL,
    CONSTRAINT possui_ESPECIALIDADE_FK FOREIGN KEY (idEspecialidade) REFERENCES ESPECIALIDADE (idEspecialidade) ON DELETE RESTRICT,
    CONSTRAINT possui_MEDICO_FK FOREIGN KEY (numeroCrm, estadoCrm) REFERENCES MEDICO (numeroCrm, estadoCrm) ON DELETE RESTRICT
)ENGINE innoDB;

CREATE TABLE preescreve (
    idMedicamento INT NOT NULL,
    idReceita INT NOT NULL,
    CONSTRAINT preescreve_RECEITA_FK FOREIGN KEY (idReceita) REFERENCES RECEITA (idReceita) ON DELETE RESTRICT,
    CONSTRAINT preescreve_MEDICAMENTO_FK FOREIGN KEY (idMedicamento) REFERENCES MEDICAMENTO (idMedicamento) ON DELETE RESTRICT
)ENGINE innoDB;
