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

struct tb_inscricoes
{
  int inscricao_id;
  int inscricao_id_aluno;
  int inscricao_id_turma;
};

// protótipos de suas funções
int exibir_menu();
void cadastrar_turma();
void exibir_turmas();
void remover_turma();
void cadastrar_professor();
void cadastrar_inscricao();
void cancelar_inscricao();
void cancelar_turmas();
void exibir_inscricoes();
void confirmar_turmas();
int obter_numero_alunos_inscritos(int turma_id);
int obter_max_alunos_turma(int turma_id);
int obter_numero_inscricoes_por_turma(int turma_id);


// Programa Principal, ela executa difentes ações com base na opcao do usuario
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
      cadastrar_aluno(); // chama a funcao para cadastrar um aluno
      break;
    case 2:
      cadastrar_professor();// Chama a função para cadastrar um professor
      break;
    case 3:
      cadastrar_turma();// Chama a função para cadastrar uma turma
      break;
    case 4:
      cadastrar_inscricao();// Chama a função para cadastrar uma inscrição
      break;
    case 5:
      cancelar_inscricao();// Chama a função para cancelar uma inscrição
      break;
    case 6:
      confirmar_turmas();
      break;
    case 7:
      cancelar_turmas();
      break;
    case 8:
      exibir_turmas();// Chama a função para exibir as turmas cadastradas
      break;
    case 9:
      remover_turma();// Chama a função para remover uma turma
      break;
		case 10:
  		exibir_professores();// Chama a função para exibir os professores cadastrados
  		break;
		case 11:
 			remover_professor();// Chama a função para remover um professor
  		break;
		case 12:
			exibir_inscricoes();// Chama a função para exibir as inscrições realizadas
			break;
    case 0:
      printf("Saindo do programa...\n");
      // espera por 3 segundos
      sleep(3);// Aguarda 3 segundos antes de encerrar o programa
      exit(0); // Encerra o programa
      break;
    default:
      printf("Opção inválida. Tente novamente.\n");
      break;
    }

  } while (opcao != 0);

  return 0;
}

// A função a seguir cria o menu de opcoes para o usuario digitar o valor desejado
int exibir_menu()
{
  int opcao;
  printf("\n----- MENU DE GERENCIAMENTO -----\n");
  puts("Academia Depressão\nDigite a opção: ");
  printf("01. Cadastrar aluno\n");
  printf("02. Cadastrar professor\n");
  printf("03. Cadastrar turma\n");
  printf("04. Inscrever alunos\n");
  printf("05. Cancelar inscrição\n");
  printf("06. Confirmar turmas\n");
  printf("07. Fechar turmas\n");
  printf("08. Exibir turmas\n");
  printf("09. Remover turma\n");
	printf("10. Exibir professores\n");
	printf("11. Remover professor\n");
	printf("12. Exibir inscrições\n");
  printf("0. Sair\n");
  printf("Escolha uma opção: ");
  scanf("%d", &opcao);
  printf("-----------------------");
  printf("\nCarregando opção...\n");
      // espera por 3 segundos
  sleep(1);

return opcao;
}

void cancelar_turmas()
{
	// pegar dados dos arquivos
	// remover turma no arquivo de turma
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para obter o nome do professor com base no ID
char* obter_nome_professor(int professor_id) {
    FILE* arquivos_professores = fopen("professores.csv", "r");
    if (arquivos_professores == NULL) {
        printf("Erro ao abrir o arquivo de professores.\n");
        return NULL;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivos_professores)) {
        int id;
        char nome[100];

        sscanf(linha, "%d,%[^,]", &id, nome);

        if (id == professor_id) {
            fclose(arquivos_professores);
            return strdup(nome); // Retorna uma cópia alocada dinamicamente do nome do professor
        }
    }

    fclose(arquivos_professores);
    return NULL; // Caso o professor não seja encontrado
}

void confirmar_turmas() {
    FILE* arquivo;
    FILE* arquivo_confirmadas;
    FILE* arquivos_professores;
    char linha[100];
    int turma_id;

    printf("\n----- CONFIRMAR TURMAS -----\n");

    printf("ID da turma a ser confirmada: ");
    scanf("%d", &turma_id);

    arquivo = fopen("turmas.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de turmas.\n");
        return;
    }

    int encontrada = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        int tur_id;
        sscanf(linha, "%d", &tur_id);

        if (tur_id == turma_id) {
            encontrada = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrada) {
        printf("Turma com ID %d não encontrada. Nenhuma alteração realizada.\n", turma_id);
        return;
    }

    arquivo_confirmadas = fopen("turmas_confirmadas.csv", "a");
    if (arquivo_confirmadas == NULL) {
        printf("Erro ao abrir o arquivo de turmas confirmadas.\n");
        return;
    }

    FILE* temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(arquivo_confirmadas);
        return;
    }

    arquivo = fopen("turmas.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de turmas.\n");
        fclose(arquivo_confirmadas);
        fclose(temp);
        return;
    }

    arquivos_professores = fopen("professores.csv", "r");
    if (arquivos_professores == NULL) {
        printf("Erro ao abrir o arquivo de professores.\n");
        fclose(arquivo_confirmadas);
        fclose(temp);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        int tur_id;
        char tur_tipo_aula[100];
        int tur_dia_da_semana;
        int tur_faixa_etaria;
        int tur_horario_de_aula;
        int tur_numero_alunos_min;
        int tur_numero_alunos_max;
        int tur_id_professores;
        
        int qtd = obter_numero_alunos_inscritos(turma_id);

        sscanf(linha, "%d,%[^,],%d,%d,%d,%d,%d,%d", &tur_id, tur_tipo_aula, &tur_dia_da_semana, &tur_faixa_etaria, &tur_horario_de_aula, &tur_numero_alunos_min, &tur_numero_alunos_max, &tur_id_professores);

        char* nome_professor = obter_nome_professor(tur_id_professores);
        
        if (tur_id == turma_id) {
            fprintf(arquivo_confirmadas, "%s,%d,%d,%s,%d\n", tur_tipo_aula, tur_dia_da_semana, tur_horario_de_aula, nome_professor, qtd);
        } else {
            fprintf(temp, "%s", linha);
        }

        free(nome_professor); // Liberar a memória alocada dinamicamente
    }

    fclose(arquivo);
    fclose(arquivo_confirmadas);
    fclose(temp);

    if (remove("turmas.csv") != 0) {
        printf("Erro ao remover o arquivo de turmas.");
        remove("temp.csv");
        return;
    }

    if (rename("temp.csv", "turmas.csv") != 0) {
        printf("Erro ao renomear o arquivo temporário.");
        return;
    }

    printf("Turma confirmada e removida do arquivo de turmas com sucesso.");
}



// Funcao que pegao numero de inscritos na turma para armazenar em turmas_confirmadas.csv
int obter_numero_alunos_inscritos(int turma_id) {
    FILE *arquivo;
    char linha[100];
    int qtd_alunos = 0;

    arquivo = fopen("inscricoes.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de inscrições.\n");
        return -1;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        int tur_id,id,alun_id;
        sscanf(linha, "%d,%d,%d", &id,&alun_id,&tur_id);

        if (tur_id == turma_id) {
            qtd_alunos++;
        }
    }

    fclose(arquivo);

    return qtd_alunos;
}


void exibir_inscricoes()
{
    FILE *arquivo;
    char linha[100];

    printf("\n----- EXIBIR INSCRIÇÕES -----\n");

    arquivo = fopen("inscricoes.csv", "r"); // Abre o arquivo "inscricoes.csv" em modo de leitura
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de inscrições.\n"); // Caso haja um erro ao abrir o arquivo, exibe uma mensagem de erro e retorna da função
        return;
    }

    printf("ID Inscricao | ID Aluno | ID Turma\n");


    // Loop para percorrer o arquivo e exibir as inscrições
    while (fgets(linha, sizeof(linha), arquivo)) 
    {
        int inscricao_id, aluno_id, turma_id;
        sscanf(linha, "%d,%d,%d", &inscricao_id, &aluno_id, &turma_id);// Lê os valores da linha do arquivo e armazena nas variáveis correspondentes
        printf("%12d | %8d | %7d\n", inscricao_id, aluno_id, turma_id); // Exibe as informações da inscrição formatadas
        // Se o número não ocupar todos os 12 caracteres, espaços em branco serão adicionados à esquerda para preencher o espaço.
    }

    fclose(arquivo);
}

// funcao responsavel para cadastrar os professores
void cadastrar_professor()
{
  struct tb_professores professor;
  FILE *arquivo;
  printf("\n----- CADASTRAR PROFESSOR -----\n");

  printf("ID do professor: ");
  scanf("%d", &professor.prof_id);

  // Verificar se o ID do professor já existe, para nao ter id's duplicados
  arquivo = fopen("professores.csv", "r");
  if (arquivo != NULL)
  {
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo))
    {
			int prof_id;
        // Extrai o ID do professor da linha, ignorando os outros campos usando "*[^,]"
      sscanf(linha, "%d,%*[^,]", &prof_id);
        // Verifica se o ID do professor extraído é igual ao ID fornecido
      if (prof_id == professor.prof_id)
      {
        // Se o ID já existe, exibe uma mensagem de erro e encerra o cadastro
        printf("O ID do professor já existe. Cadastro não realizado.\n");
        fclose(arquivo);
        return;
      }
    }
    fclose(arquivo);
  }

  printf("Nome do professor(ex: Carlos): ");
  scanf("%s", professor.prof_nome);

  printf("CPF do professor(xxx.xxx.xxx-xx): ");
  scanf("%s", professor.prof_cpf);

  printf("Telefone do professor((xx)xxxx-xxxx): ");
  scanf("%s", professor.prof_telefone);

  printf("Email do professor(xxxxx@): ");
  scanf("%s", professor.prof_email);

  arquivo = fopen("professores.csv", "a");

  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  // escrevendo no arquivo
  fprintf(arquivo, "%d,%s,%s,%s,%s\n", professor.prof_id, professor.prof_nome, professor.prof_cpf, professor.prof_telefone, professor.prof_email);

  fclose(arquivo);

  printf("Professor cadastrado com sucesso.\n");
}

// função para pegar o numero maximo de alunos que a turma permite, ela retorna o valor para a funcao de cadastrar inscrição
int obter_max_alunos_turma(int turma_id)
{
  FILE *arquivo;
  char linha[100];

  arquivo = fopen("turmas.csv", "r");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de turmas.\n");
    return -1; // Valor inválido para indicar erro
  }
  // Percorre o arquivo de turmas linha por linha
  while (fgets(linha, sizeof(linha), arquivo))
  {
   int tur_id, tur_dia_da_semana, tur_faixa_etaria, tur_horario_de_aula, tur_numero_alunos_min, tur_numero_alunos_max;
    char tur_tipo_aula[100];

    // Extrai os campos da linha
    sscanf(linha, "%d,%[^,],%d,%d,%d,%d,%d", &tur_id, tur_tipo_aula, &tur_dia_da_semana, &tur_faixa_etaria, &tur_horario_de_aula, &tur_numero_alunos_min, &tur_numero_alunos_max);

    // Verifica se o ID da turma corresponde ao ID fornecido
    if (tur_id == turma_id)
    {
      fclose(arquivo);
      printf("Limite de inscrições: %d\n",tur_numero_alunos_max);
      return tur_numero_alunos_max;// Retorna o limite máximo de alunos da turma
    }
  }

  fclose(arquivo);
  return -1; // Retorna um valor inválido para indicar que a turma não foi encontrada
}

// Permite ao usuário cancelar uma inscrição fornecendo o ID do aluno e o ID da turma. As inscrições são armazenadas em um arquivo chamado "inscricoes.csv" 
void cancelar_inscricao()
{
  FILE *arquivo;
  FILE *arquivoCanceladas;
  FILE *arquivos_alunos;
  FILE *arquivos_turmas;
  char linha[100];

  int aluno_id, turma_id;
  printf("\n----- REMOVER INSCRIÇÃO -----\n");
  printf("Digite o ID do aluno: ");
  scanf("%d", &aluno_id);
  printf("Digite o ID da turma: ");
  scanf("%d", &turma_id);

  // Abrir o arquivo de inscrições para leitura
  arquivo = fopen("inscricoes.csv", "r");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de inscrições.\n");
    return;
  }

  arquivos_alunos = fopen("alunos.csv", "r");
  if (arquivos_alunos == NULL)
  {
     printf("Erro ao abrir o arquivo de alunos.\n");
    fclose(arquivo);
    return;
  }

  arquivos_turmas = fopen("turmas.csv", "r");
  if (arquivos_turmas == NULL)
  {
     printf("Erro ao abrir o arquivo de turmas.\n");
    fclose(arquivo);
    fclose(arquivos_alunos);
    return;
  }

  // Abrir o arquivo de inscrições canceladas para adicionar as inscrições removidas
  arquivoCanceladas = fopen("inscricoes_canceladas.csv", "a");
  if (arquivoCanceladas == NULL)
  {
    printf("Erro ao abrir o arquivo de inscrições canceladas.\n");
    fclose(arquivo);
    fclose(arquivos_alunos);
    fclose(arquivos_turmas);
    return;
  }

  // Criar um arquivo temporário para armazenar as inscrições não removidas
  FILE *arquivoTemp = fopen("temp.csv", "w");
  if (arquivoTemp == NULL)
  {
    printf("Erro ao criar o arquivo temporário.\n");
    fclose(arquivo);
    fclose(arquivoCanceladas);
    fclose(arquivos_alunos);
    fclose(arquivos_turmas);
    return;
  }

  // Ler as linhas do arquivo de inscrições
  while (fgets(linha, sizeof(linha), arquivo))
  {
    int inscricao_id, inscricao_id_aluno, inscricao_id_turma;
    sscanf(linha, "%d,%d,%d", &inscricao_id, &inscricao_id_aluno, &inscricao_id_turma);

    // Verificar se o aluno e a turma estão inscritos nessa inscrição
    if (inscricao_id_aluno == aluno_id && inscricao_id_turma == turma_id)
    {
      // Ler os dados da turma e do aluno correspondentes
      char tur_tipo_aula[100];
      int tur_dia_da_semana;
      int tur_horario_de_aula;
      char aluno_nome[300];
      char aluno_telefone[50];
      char aluno_email[100];

      // Buscar as informações da turma
      char linha_turma[100];
      while (fgets(linha_turma, sizeof(linha_turma), arquivos_turmas))
      {
        int id_turma, tur_faixa_etaria;
        sscanf(linha_turma, "%d,%[^,],%d,%d,%d", &id_turma, tur_tipo_aula, &tur_dia_da_semana,&tur_faixa_etaria, &tur_horario_de_aula);
        if (id_turma == turma_id)
          break;
      }

      // Buscar as informações do aluno
      char linha_aluno[400];
      while (fgets(linha_aluno, sizeof(linha_aluno), arquivos_alunos))
      {
        int id_aluno;
        char aluno_cpf[15];
        sscanf(linha_aluno, "%d,%[^,],%[^,],%[^,],%[^,]", &id_aluno, aluno_nome, aluno_cpf, aluno_telefone, aluno_email);
        if (id_aluno == aluno_id)
          break;
      }

      fprintf(arquivoCanceladas, "%s,%d,%d,%s,%s,%s",tur_tipo_aula,tur_dia_da_semana,tur_horario_de_aula,aluno_nome,aluno_telefone,aluno_email);
    }

  }

  // Fechar os arquivos
  fclose(arquivo);
  fclose(arquivoCanceladas);
  fclose(arquivoTemp);
  fclose(arquivos_alunos);
  fclose(arquivos_turmas);

  // Remover o arquivo original
  remove("inscricoes.csv");

  // Renomear o arquivo temporário para o nome original
  rename("temp.csv", "inscricoes.csv");

  printf("____________________________________________");
  printf("\nInscrições do aluno removidas com sucesso.");
  printf("____________________________________________\n");
}

// Solicita ao usuário informações sobre um aluno e as armazena em um arquivo chamado "alunos.csv".
void cadastrar_aluno()
{
  struct tb_alunos aluno;
  FILE *arquivo;
  char linha[100];

  printf("\n----- CADASTRAR ALUNO -----\n");

  printf("ID do aluno: ");
  scanf("%d", &aluno.aluno_id);

  printf("Nome do aluno: ");
  scanf(" %[^\n]s", aluno.aluno_nome);

  printf("CPF do aluno: ");
  scanf(" %[^\n]s", aluno.aluno_cpf);

  printf("Telefone do aluno: ");
  scanf(" %[^\n]s", aluno.aluno_telefone);

  printf("Email do aluno: ");
  scanf(" %[^\n]s", aluno.aluno_email);

  // Verificar se o aluno já está cadastrado no arquivo "alunos.csv"
  arquivo = fopen("alunos.csv", "r");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de alunos.\n");
    return;
  }

  while (fgets(linha, sizeof(linha), arquivo))
  {
    int aluno_id;
    sscanf(linha, "%d", &aluno_id);
    if (aluno_id == aluno.aluno_id)
    {
      fclose(arquivo);
      printf("O aluno com o ID %d já está cadastrado.\n", aluno.aluno_id);
      return;
    }
  }

  fclose(arquivo);

  // Adicionar o aluno ao arquivo "alunos.csv"
  arquivo = fopen("alunos.csv", "a");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de alunos.\n");
    return;
  }

  fprintf(arquivo, "%d,%s,%s,%s,%s\n", aluno.aluno_id, aluno.aluno_nome, aluno.aluno_cpf, aluno.aluno_telefone, aluno.aluno_email);
  fclose(arquivo);

  printf("Aluno cadastrado com sucesso.\n");
}

int obter_numero_inscricoes_por_turma(int turma_id) {
    FILE *arquivo;
    char linha[100];

    arquivo = fopen("inscricoes.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de inscrições.\n");
        return -1; // Valor inválido para indicar erro
    }

    int numInscricoes = 0;
    int inscricao_id, inscricao_id_aluno, inscricao_id_turma;

    // Percorre o arquivo de inscrições linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d,%d,%d", &inscricao_id,&inscricao_id_aluno, &inscricao_id_turma);
        // Verifica se o ID da turma corresponde ao ID fornecido
        if (inscricao_id_turma == turma_id) {
            numInscricoes++;// Incrementa o contador de inscrições
        }
    }

    fclose(arquivo);

    return numInscricoes;// Retorna o número de inscrições para a turma
}

void cadastrar_inscricao()
{
  struct tb_inscricoes inscricao;
  FILE *arquivo;
  char linha[100];

  printf("\n----- CADASTRAR INSCRIÇÃO -----\n");

  printf("ID da inscrição: ");
  scanf("%d", &inscricao.inscricao_id);

  printf("ID do aluno: ");
  scanf("%d", &inscricao.inscricao_id_aluno);

  printf("ID da turma: ");
  scanf("%d", &inscricao.inscricao_id_turma);

  int teste = inscricao.inscricao_id_turma;
  // Verificar se o aluno existe no arquivo "alunos.csv"
  arquivo = fopen("alunos.csv", "r");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de alunos.\n");
    return;
  }

  int alunoEncontrado = 0;

  while (fgets(linha, sizeof(linha), arquivo))
  {
    int aluno_id;
    sscanf(linha, "%d", &aluno_id);

    if (aluno_id == inscricao.inscricao_id_aluno)
    {
      alunoEncontrado = 1;
      break;
    }
  }

  fclose(arquivo);

  if (!alunoEncontrado)
  {
    printf("O aluno com o ID %d não existe. Não é possível realizar a inscrição.\n", inscricao.inscricao_id_aluno);
    return;
  }

  // Verificar se a turma existe no arquivo "turmas.csv"
  arquivo = fopen("turmas.csv", "r");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de turmas.\n");
    return;
  }

  int turmaEncontrada = 0;
  int tur_numero_alunos_max = 0;

  while (fgets(linha, sizeof(linha), arquivo))
  {
    int tur_id;
    sscanf(linha, "%d", &tur_id);

    if (tur_id == inscricao.inscricao_id_turma)
    {
      turmaEncontrada = 1;
      tur_numero_alunos_max = obter_max_alunos_turma(tur_id);
      break;
    }
  }

  fclose(arquivo);

  if (!turmaEncontrada)
  {
    printf("A turma com o ID %d não existe. Não é possível realizar a inscrição.\n", inscricao.inscricao_id_turma);
    return;
  }

  // Verificar o número máximo de inscrições permitido
  arquivo = fopen("inscricoes.csv", "r");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de inscrições.\n");
    return;
  }

// essa parte deve percorrer o arquivo inscricoes e retornar o numero de inscricoes

  int numInscricoes = obter_numero_inscricoes_por_turma(teste);


  fclose(arquivo);

  int numMaxInscricoes = tur_numero_alunos_max;
  int numVagasDisponiveis = numMaxInscricoes - numInscricoes;

  if (numVagasDisponiveis <= 0)
  {
    printf("O número máximo de inscrições foi atingido. Não é possível realizar mais inscrições.\n");
    return;
  }

  
    // Adicionar a inscrição ao arquivo "inscricoes.csv"
  arquivo = fopen("inscricoes.csv", "a");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de inscrições.\n");
    return;
  }

  fprintf(arquivo, "%d,%d,%d\n", inscricao.inscricao_id, inscricao.inscricao_id_aluno, inscricao.inscricao_id_turma);
  fclose(arquivo);

  printf("Inscrição cadastrada com sucesso.\n");
  printf("Número de vagas disponíveis: %d\n", numVagasDisponiveis - 1);
}

void exibir_professores()
{
  FILE *arquivo;
  char linha[100];
  char campos[5][20] = {"ID", "Nome", "CPF", "Telefone", "Email"};

  printf("\n----- PROFESSORES CADASTRADOS -----\n");

  arquivo = fopen("professores.csv", "r");

  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  // Exibir os nomes dos campos
  for (int i = 0; i < 5; i++)
  {
    printf("%-15s", campos[i]);
  }
  printf("\n");
  // Percorre o arquivo de professores linha por linha
  while (fgets(linha, sizeof(linha), arquivo))
  {
    int prof_id;
    char prof_nome[100];
    char prof_cpf[15];
    char prof_telefone[15];
    char prof_email[100];

    sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^,\n]", &prof_id, prof_nome, prof_cpf, prof_telefone, prof_email);

    // Exibir os dados
    printf("%-15d", prof_id);
    printf("%-15s", prof_nome);
    printf("%-15s", prof_cpf);
    printf("%-15s", prof_telefone);
    printf("%-15s", prof_email);
    printf("\n");
    // O -15  garante que o campo do ID tenha uma largura fixa de 15 caracteres, preenchendo espaços em branco à direita, se necessário.
  }

  fclose(arquivo);
}

void remover_professor()
{
  FILE *arquivo;
  FILE *arquivo_temp;
  struct tb_professores professor;
  int id;
  char linha[100];

  printf("\n----- REMOVER PROFESSOR -----\n");

  printf("ID do professor a ser removido: ");
  scanf("%d", &id);

  arquivo = fopen("professores.csv", "r");
  arquivo_temp = fopen("temp.csv", "w");

  if (arquivo == NULL || arquivo_temp == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  while (fgets(linha, sizeof(linha), arquivo))
  {
    sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^,]", &professor.prof_id, professor.prof_nome, professor.prof_cpf, professor.prof_telefone, professor.prof_email);
    if (professor.prof_id != id)
    {
      fprintf(arquivo_temp, "%d,%s,%s,%s,%s\n", professor.prof_id, professor.prof_nome, professor.prof_cpf, professor.prof_telefone, professor.prof_email);
    }
  }

  fclose(arquivo);
  fclose(arquivo_temp);

  if (remove("professores.csv") != 0)
  {
    printf("Erro ao remover o professor.\n");
    return;
  }

  if (rename("temp.csv", "professores.csv") != 0)
  {
    printf("Erro ao renomear o arquivo.\n");
    return;
  }
	printf("------------------------------");
  printf("\nProfessor removido com sucesso.\n");
	printf("------------------------------");

}

void cadastrar_turma()
{
  struct tb_turmas turma;
  FILE *arquivo;
  char linha[100];

  printf("\n----- CADASTRAR TURMA -----\n");

  printf("ID da turma: ");
  scanf("%d", &turma.tur_id);

  printf("Tipo de aula: ");
  scanf("%s", turma.tur_tipo_aula);

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

  // Verificar se o professor existe no arquivo "professores.csv"
  arquivo = fopen("professores.csv", "r");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de professores.\n");
    return;
  }

  int professorEncontrado = 0;
  while (fgets(linha, sizeof(linha), arquivo))
  {
    int prof_id;
    sscanf(linha, "%d", &prof_id);
    if (prof_id == turma.tur_id_professores)
    {
      professorEncontrado = 1;
      break;
    }
  }

  fclose(arquivo);

  if (!professorEncontrado)
  {
    printf("O professor com o ID %d não existe. Não é possível cadastrar a turma.\n", turma.tur_id_professores);
    return;
  }

  arquivo = fopen("turmas.csv", "a");

  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo de turmas.\n");
    return;
  }

  fprintf(arquivo, "%d,%s,%d,%d,%d,%d,%d,%d\n", turma.tur_id, turma.tur_tipo_aula, turma.tur_dia_da_semana, turma.tur_faixa_etaria, turma.tur_horario_de_aula, turma.tur_numero_alunos_min, turma.tur_numero_alunos_max, turma.tur_id_professores);

  fclose(arquivo);

  printf("Turma cadastrada com sucesso.\n");
}

//	A função exibir busca no arquivo csv e exibe os cadastros realizados
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
    int tur_id, tur_dia_da_semana, tur_faixa_etaria, tur_horario_de_aula, tur_numero_alunos_min, tur_numero_alunos_max, tur_id_professores;
    char tur_tipo_aula[100];

    sscanf(linha, "%d,%[^,],%d,%d,%d,%d,%d,%d", &tur_id, tur_tipo_aula, &tur_dia_da_semana, &tur_faixa_etaria, &tur_horario_de_aula, &tur_numero_alunos_min, &tur_numero_alunos_max, &tur_id_professores);

    printf("ID: %d\n", tur_id);
    printf("Tipo de Aula: %s\n", tur_tipo_aula);
    printf("Dia da Semana: %d\n", tur_dia_da_semana);
    printf("Faixa Etária: %d\n", tur_faixa_etaria);
    printf("Horário de Aula: %d\n", tur_horario_de_aula);
    printf("Mínimo de Alunos: %d\n", tur_numero_alunos_min);
    printf("Máximo de Alunos: %d\n", tur_numero_alunos_max);
    printf("ID do Professor: %d\n", tur_id_professores);
    printf("----------------------\n");
  }

  fclose(arquivo);
}

//	A função remover no arquivo csv
void remover_turma()
{
FILE *arquivo;
FILE *arquivo_temp;
struct tb_turmas turma;
int id;
char linha[100];

printf("\n----- REMOVER TURMA -----\n");

printf("ID da turma a ser removida: ");
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