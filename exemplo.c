#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog2Utils.h" // biblioteca de funções auxiliares. Por exemplo editar informações de arquivos.

#define TAMANHO_MAXIMO 100

struct tb_alunos
{
  int aluno_id;
  char aluno_nome[300];
  char aluno_cpf[15];
  char aluno_telefone[50];
  char aluno_email[100];
};

struct tb_professores
{
  int prof_id;
  char prof_nome[100];
  char prof_cpf[15];
  char prof_telefone[15];
  char prof_email[100];
};

struct tb_turmas
{
  int tur_id;
  char tur_tipo_aula[100];
  int tur_dia_da_semana;
  int tur_faixa_etaria;
  int tur_horario_de_aula;
  int tur_numero_alunos_min;
  int tur_numero_alunos_max;
  int tur_id_professores;
};

// protótipos de suas funções
int exibir_menu();
void cadastrar_turma();
void exibir_turmas();
void remover_turma();

// Programa Principal
int main()
{
  int opcao;
  struct tb_turmas turmas[TAMANHO_MAXIMO];
  int numTurmas = 0;

  do
  {
    opcao = exibir_menu();

    switch (opcao)
    {
    case 1:
      // cadastrar_aluno();
      break;
    case 2:
      // cadastrar_professor();
      break;
    case 3:
      cadastrar_turma();
      break;
    case 4:
      // cadastrar_aluno_turma();
      break;
    case 5:
      // cancelar_inscricao();
      break;
    case 6:
      // confirmar_turmas();
      break;
    case 7:
      // fechar_turmas();
      break;
    case 8:
      exibir_turmas();
      break;
    case 9:
      remover_turma();
      break;
    case 0:
      printf("Saindo...\n");
      // salvar_aula(aulas);
      exit(0);
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }

  } while (opcao != 0);

  return 0;
}

int exibir_menu()
{
  int opcao;
  printf("\n----- MENU DE GERENCIAMENTO -----\n");
  puts("Academia Depressão\nDigite a opção: ");
  printf("1. Cadastrar aluno\n");
  printf("2. Cadastrar professor\n");
  printf("3. Cadastrar turma\n");
  printf("4. Inscrever alunos\n");
  printf("5. Cancelar inscrição\n");
  printf("6. Confirmar turmas\n");
  printf("7. Fechar turmas\n");
  printf("8. Exibir turmas\n");
  printf("9. Remover turma\n");
  printf("0. Sair\n");
  printf("Escolha uma opção: ");
  scanf("%d", &opcao);

  return opcao;
}

void cadastrar_turma()
{
  struct tb_turmas turma;
  FILE *arquivo;

  printf("\n----- CADASTRAR TURMA -----\n");

  printf("ID da turma: ");
  scanf("%d", &turma.tur_id);

  printf("Tipo de aula: ");
  scanf("%s(turma.tur_tipo_aula);

printf("Dia da semana (1-7): ");
scanf("%d", &turma.tur_dia_da_semana);

printf("Faixa etária: ");
scanf("%d", &turma.tur_faixa_etaria);

printf("Horário de aula: ");
scanf("%d", &turma.tur_horario_de_aula);

printf("Número mínimo de alunos: ");
scanf("%d", &turma.tur_numero_alunos_min);

printf("Número máximo de alunos: ");
scanf("%d", &turma.tur_numero_alunos_max);

printf("ID do professor: ");
scanf("%d", &turma.tur_id_professores);

arquivo = fopen("turmas.csv", "a");

if (arquivo == NULL)
{
printf("Erro ao abrir o arquivo.\n");
return;
}

fprintf(arquivo, "%d,%s,%d,%d,%d,%d,%d,%d\n", turma.tur_id, turma.tur_tipo_aula, turma.tur_dia_da_semana, turma.tur_faixa_etaria, turma.tur_horario_de_aula, turma.tur_numero_alunos_min, turma.tur_numero_alunos_max, turma.tur_id_professores);

fclose(arquivo);

printf("Turma cadastrada com sucesso.\n");
}

/*
A função exibir_turmas busca no arquivo csv e exibe os cadastros realizados
*/

void exibir_turmas()
{
FILE *arquivo;
char linha[100];

printf("\n----- TURMAS CADASTRADAS -----\n");

arquivo = fopen("turmas.csv", "r");

if (arquivo == NULL)
{
printf("Erro ao abrir o arquivo.\n");
return;
}

while (fgets(linha, sizeof(linha), arquivo))
{
struct tb_turmas turma;
sscanf(linha, "%d,%[^,],%d,%d,%d,%d,%d,%d", &turma.tur_id, turma.tur_tipo_aula, &turma.tur_dia_da_semana, &turma.tur_faixa_etaria, &turma.tur_horario_de_aula, &turma.tur_numero_alunos_min, &turma.tur_numero_alunos_max, &turma.tur_id_professores);
printf("ID: %d\n", turma.tur_id);
printf("Tipo de Aula: %s\n", turma.tur_tipo_aula);
printf("Dia da Semana: %d\n", turma.tur_dia_da_semana);
printf("Faixa Etária: %d\n", turma.tur_faixa_etaria);
printf("Horário de Aula: %d\n", turma.tur_horario_de_aula);
printf("Número Mínimo de Alunos: %d\n", turma.tur_numero_alunos_min);
printf("Número Máximo de Alunos: %d\n", turma.tur_numero_alunos_max);
printf("ID do Professor: %d\n\n", turma.tur_id_professores);
}

fclose(arquivo);
}

void remover_turma()
{
FILE *arquivo;
FILE *arquivo_temp;
struct tb_turmas turma;
int id;
char linha[100];

printf("\n----- REMOVER TURMA -----\n");

printf("ID da turma aremover: ");
scanf("%d", &id);

arquivo = fopen("turmas.csv", "r");
arquivo_temp = fopen("temp.csv", "w");

if (arquivo == NULL || arquivo_temp == NULL)
{
printf("Erro ao abrir o arquivo.\n");
return;
}

while (fgets(linha, sizeof(linha), arquivo))
{
sscanf(linha, "%d,%[^,],%d,%d,%d,%d,%d,%d", &turma.tur_id, turma.tur_tipo_aula, &turma.tur_dia_da_semana, &turma.tur_faixa_etaria, &turma.tur_horario_de_aula, &turma.tur_numero_alunos_min, &turma.tur_numero_alunos_max, &turma.tur_id_professores);
if (turma.tur_id != id)
{
fprintf(arquivo_temp, "%d,%s,%d,%d,%d,%d,%d,%d\n", turma.tur_id, turma.tur_tipo_aula, turma.tur_dia_da_semana, turma.tur_faixa_etaria, turma.tur_horario_de_aula, turma.tur_numero_alunos_min, turma.tur_numero_alunos_max, turma.tur_id_professores);
}
}

fclose(arquivo);
fclose(arquivo_temp);

if (remove("turmas.csv") != 0)
{
printf("Erro ao remover a turma.\n");
return;
}

if (rename("temp.csv", "turmas.csv") != 0)
{
printf("Erro ao renomear o arquivo.\n");
return;
}

printf("Turma removida com sucesso.\n");
}
