-- --------     << aula4exer5Evolucao4 >>     ------------
--
--                    SCRIPT DE POPULA (DML)
--
-- Data Criacao ...........: 10/05/2023
-- Autor(es) ..............: Rodrigo Carvalho dos Santos
-- Banco de Dados .........: MySQL
-- Banco de Dados(nome) ...: aula4exer5Evolucao4
--
-- PROJETO => 01 Base de Dados
--         => 10 Tabelas
-- -----------------------------------------------------------------

use aula4exer5Evolucao4;

INSERT INTO PESSOA (idPessoa, nomeCompleto) VALUES
(1, 'João Silva'),
(2, 'Maria Souza'),
(3, 'Pedro Santos'),
(4, 'Ana Oliveira'),
(5, 'Lucas Pereira'),
(6, 'Alex Silva');

INSERT INTO PACIENTE (idPaciente, sexo, cep, estado, cidade, rua, numero, complemento, dtNascimento) VALUES
(1, 'M', 1234567, 'SP', 'São Paulo', 'Avenida Paulista', 100, 'Apto 501', '1980-05-10'),
(2, 'F', 9876543, 'RJ', 'Rio de Janeiro', 'Copacabana', 200, NULL, '1992-08-25'),
(3, 'M', 4567891, 'MG', 'Belo Horizonte', 'Rua da Consolação', 300, 'Sala 102', '1975-11-15');

INSERT INTO MEDICO (ufCrm, numeroCrm, idPessoa) VALUES
('SP', 12345, 4),
('RJ', 54321, 5),
('MG', 98765, 6);

INSERT INTO ESPECIALIDADE (idEspecialidade, nomeEspecialidade) VALUES
(1, 'Cardiologia'),
(2, 'Dermatologia'),
(3, 'Pediatria');

INSERT INTO RECEITA (idReceita, descricao, idConsulta) VALUES
(1, 'Prescrição para tratamento de hipertensão', 1),
(2, 'Receita para tratamento de acne', 2),
(3, 'Prescrição de medicamentos para criança com febre', 3);

INSERT INTO MEDICAMENTO (idMedicamento, nomeMedicamento) VALUES
(1, 'Aspirina'),
(2, 'Hidroclorotiazida'),
(3, 'Ibuprofeno');

INSERT INTO CONSULTA (idConsulta, ufCrm, numeroCrm, idPaciente, dataHora) VALUES
(1, 'SP', 12345, 1, '2023-01-10 09:00:00'),
(2, 'RJ', 54321, 2, '2023-02-15 14:30:00'),
(3, 'MG', 98765, 3, '2023-03-20 10:15:00');

INSERT INTO possui (idEspecialidade, ufCrm, numeroCrm) VALUES
(1, 'SP', 12345),
(2, 'RJ', 54321),
(3, 'MG', 98765);

INSERT INTO preescreve (idMedicamento, idReceita) VALUES
(1, 1),
(2, 1),
(3, 2);
