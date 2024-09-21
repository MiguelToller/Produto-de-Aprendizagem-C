#include<stdio.h>
#include <string.h>

typedef struct {
    int anos;
    int meses;
    int dias;
} Idade;

typedef struct {
    char dataUltimaConsulta[11];
    char prescricao[100];
    float peso, altura, valorPago;
} Consulta;

typedef struct {
    int codigo;
    char dataNascimento[11];
    char nomePaciente[100], nomeMae[100], nomePai[100];
    Consulta ultimaConsulta;
    Idade idade;
} Paciente;

int buscarPacienteCodigo(Paciente p[], int totalPaciente, int codigo) {
    for(int i = 0; i < totalPaciente; i++) {
        if(p[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscarPacienteNome(Paciente p[], int totalPaciente, char nome[]) {
    for(int i = 0; i < totalPaciente; i++) {
        if (strcmp(p[i].nomePaciente, nome) == 0) {
            return i;
        }
    }
    return -1;
}

//Calculo da idade baseado na data da ultima consulta
Idade calculaIdade (const char *dataNasc, const char *dataConsulta) {
    int diaNasc, mesNasc, anoNasc;
    int diaConsulta, mesConsulta, anoConsulta;

    sscanf(dataNasc, "%d/%d/%d", &diaNasc, &mesNasc, &anoNasc);
    sscanf(dataConsulta, "%d/%d/%d", &diaConsulta, &mesConsulta, &anoConsulta);

    Idade idade;
    idade.anos = anoConsulta - anoNasc;
    idade.meses = mesConsulta - mesNasc;
    idade.dias = diaConsulta - diaNasc;

    // Ajuste se o dia ou o mês ainda nao ocorreram
    if (idade.dias < 0) {
        idade.meses -= 1;
        idade.dias += 30;
    }
    if (idade.meses < 0) {
        idade.anos -= 1;
        idade.meses += 12;
    }
    return idade;
}

int main() {
    char opcao;
    int contador = 0;
    Consulta c[10];
    Paciente p[10];

    do {
        printf("\nEscolha uma acao a ser executada:\n");
        printf("\na)Cadastrar Paciente\nb)Registrar Consulta\nc)Visualizar Prescricao\nd)Listar Pacientes\ne)Valor total recebido no mes\nf)Finalizar\n");
        scanf("%c", &opcao);
        getchar();

        switch (opcao) {

            //Cadastrar Paciente
            case 'a':
                do {
                    //Codigo do paciente
                    printf("Insira o codigo do paciente:");
                    scanf("%d", &p[contador].codigo);
                    getchar();

                    //Nome do paciente
                    printf("Insira o nome do paciente:");
                    fflush(stdin);
                    fgets(p[contador].nomePaciente, sizeof(p[contador].nomePaciente), stdin);
                    p[contador].nomePaciente[strcspn(p[contador].nomePaciente, "\n")] = '\0';

                    //Data de nascimento
                    printf("Insira a data de nascimento:");
                    fflush(stdin);
                    fgets(p[contador].dataNascimento, sizeof(p[contador].dataNascimento), stdin);
                    p[contador].dataNascimento[strcspn(p[contador].dataNascimento, "\n")] = '\0';

                    //Nome da mãe
                    printf("Insira o nome da mae:");
                    fflush(stdin);
                    fgets(p[contador].nomeMae, sizeof(p[contador].nomeMae), stdin);
                    p[contador].nomeMae[strcspn(p[contador].nomeMae, "\n")] = '\0';

                    //Nome do pai
                    printf("Insira o nome do pai:");
                    fflush(stdin);
                    fgets(p[contador].nomePai, sizeof(p[contador].nomePai), stdin);
                    p[contador].nomePai[strcspn(p[contador].nomePai, "\n")] = '\0';

                    // Inicializando campos da última consulta
                    strcpy(p[contador].ultimaConsulta.dataUltimaConsulta, "");
                    strcpy(p[contador].ultimaConsulta.prescricao, "");
                    p[contador].ultimaConsulta.peso = 0.0;
                    p[contador].ultimaConsulta.altura = 0.0;
                    p[contador].ultimaConsulta.valorPago = 0.0;

                    contador++;

                    //Cadastrar outro paciente
                    printf("Deseja cadastrar outro paciente? (S/N):");
                    scanf("%c", &opcao);
                    getchar();
                } while (opcao == 'S' || opcao == 's');
                break;

            //Registrar Consulta
            case 'b':
                int escolha, codigoPaciente, indicePaciente = -1;
                char nomePaciente[100];

                //Verifica se existe pacientes cadastrados
                if (contador == 0) {
                    printf("Nenhum paciente cadastrado.\n");
                    break;
                }

                //Cadastro por codigo ou nome
                printf("Registro da consulta\n");
                printf("1)Buscar por codigo\n2)Buscar por nome\n");
                scanf("%d", &escolha);

                //Cadastro por codigo
                if (escolha == 1) {
                    printf("Insira o codigo do paciente:");
                    scanf("%d",&codigoPaciente);
                    indicePaciente = buscarPacienteCodigo(p, contador, codigoPaciente);

                //Cadastro por nome
                } else if (escolha == 2) {
                    printf("Insira o nome do paciente:");
                    fflush(stdin);
                    fgets(nomePaciente, sizeof(nomePaciente), stdin);
                    nomePaciente[strcspn(nomePaciente, "\n")] = '\0';
                    indicePaciente = buscarPacienteNome(p, contador, nomePaciente);
                } else {
                    printf("opcao invalida.\n");
                    break;
                }
                if (indicePaciente == -1) {
                    printf("Paciente invalido.\n");
                } else {
                    //Registrar a consulta
                    printf("Registro de consulta do paciente %d\n", indicePaciente + 1);

                    //Data ultima consulta
                    printf("Insira a data da ultima consulta:");
                    fflush(stdin);
                    fgets(p[indicePaciente].ultimaConsulta.dataUltimaConsulta, sizeof(p[indicePaciente].ultimaConsulta.dataUltimaConsulta), stdin);
                    p[indicePaciente].ultimaConsulta.dataUltimaConsulta[strcspn(p[indicePaciente].ultimaConsulta.dataUltimaConsulta, "\n")] = '\0';

                    //Peso
                    getchar();
                    printf("Insira o peso do paciente (KG):");
                    scanf("%f", &p[indicePaciente].ultimaConsulta.peso);

                    //Altura
                    getchar();
                    printf("Insira a altura do paciente (cm):");
                    scanf("%f", &p[indicePaciente].ultimaConsulta.altura);

                    //Valor pago
                    getchar();
                    printf("Insira o valor pago:");
                    scanf("%f", &p[indicePaciente].ultimaConsulta.valorPago);

                    //Prescricao
                    printf("Insira a prescricao:");
                    fflush(stdin);
                    fgets(p[indicePaciente].ultimaConsulta.prescricao, sizeof(p[indicePaciente].ultimaConsulta.prescricao), stdin);
                    p[indicePaciente].ultimaConsulta.prescricao[strcspn(p[indicePaciente].ultimaConsulta.prescricao, "\n")] = '\0';
                }
                break;

            //Vizualizar Prescricao
            case 'c':
                //Verifica se existe pacientes cadastrados
                if (contador == 0) {
                    printf("Nenhum paciente cadastrado.\n");
                    break;
                }

                //Cadastro por codigo ou nome
                printf("Vizualizar Prescricao:\n");
                printf("1)Buscar por codigo\n2)Buscar por nome\n");
                scanf("%d", &escolha);

                //Cadastro por codigo
                if (escolha == 1) {
                    printf("Insira o codigo do paciente:");
                    scanf("%d",&codigoPaciente);
                    getchar();
                    indicePaciente = buscarPacienteCodigo(p, contador, codigoPaciente);

                //Cadastro por nome
                } else if (escolha == 2) {
                    printf("Insira o nome do paciente:");
                    fflush(stdin);
                    fgets(nomePaciente, sizeof(nomePaciente), stdin);
                    nomePaciente[strcspn(nomePaciente, "\n")] = '\0';
                    indicePaciente = buscarPacienteNome(p, contador, nomePaciente);
                } else {
                    printf("opcao invalida.");
                    break;
                }
                if (indicePaciente == -1) {
                    printf("Paciente invalido.");
                } else {
                    // Verifica se o paciente já realizou uma consulta
                    if (p[indicePaciente].ultimaConsulta.dataUltimaConsulta[0] == '\0') {
                        printf("O paciente %s nao realizou nenhuma consulta ainda.\n", p[indicePaciente].nomePaciente);
                    } else {
                        //Chamada da funcao para calcular idade
                        p[indicePaciente].idade = calculaIdade(p[indicePaciente].dataNascimento, p[indicePaciente].ultimaConsulta.dataUltimaConsulta);

                        //Mostrar as informacoes
                        printf("Codigo do paciente: %d\n", p[indicePaciente].codigo);
                        printf("Nome do paciente: %s\n", p[indicePaciente].nomePaciente);
                        printf("Data da ultima consulta: %s\n", p[indicePaciente].ultimaConsulta.dataUltimaConsulta);
                        printf("Idade: %d anos, %d meses e %d dias.\n", p[indicePaciente].idade.anos, p[indicePaciente].idade.meses, p[indicePaciente].idade.dias);
                        printf("Peso: %.2f\n", p[indicePaciente].ultimaConsulta.peso);
                        printf("Altura: %.2f\n", p[indicePaciente].ultimaConsulta.altura);
                        printf("Prescricao: %s\n", p[indicePaciente].ultimaConsulta.prescricao);
                    }
                }
                break;

            //Listar Pacientes
            case 'd':
                //Verifica se existe pacientes cadastrados
                if (contador == 0) {
                    printf("Nenhum paciente cadastrado.\n");
                    break;
                }
                for (int i = 0; i < contador; i++) {
                    //Mostrar as informacoes
                    printf("\nPaciente %d\n", i + 1);
                    printf("Codigo do paciente: %d\n", p[i].codigo);
                    printf("Nome do paciente: %s\n", p[i].nomePaciente);
                    printf("Data de Nascimento: %s\n", p[i].dataNascimento);
                    printf("Nome da mae: %s\n", p[i].nomeMae);
                    printf("Nome do pai: %s\n", p[i].nomePai);
                }
                break;

            //Valor total recebido no mes
            case 'e':
                int mes, ano;
                float valorTotal = 0.0;

                printf("Insira o mes desejado:");
                scanf("%d", &mes);
                printf("Insira o ano desejado:");
                scanf("%d", &ano);

                for (int i=0; i<contador; i++) {
                    int mesConsulta, anoConsulta;
                    sscanf(p[i].ultimaConsulta.dataUltimaConsulta, "%*d/%d/%d", &mesConsulta, &anoConsulta );
                    if (mesConsulta == mes && anoConsulta == ano) {
                        valorTotal += p[i].ultimaConsulta.valorPago;
                    }
                }
                printf("Valor total recebido no mes %d/%d: %.2f\n", mes, ano, valorTotal);
                getchar();
                break;
        } //switch end
    } while (opcao != 'f');
    return 0;
}