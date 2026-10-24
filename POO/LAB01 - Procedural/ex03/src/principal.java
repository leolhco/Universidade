import java.util.Scanner;

public class principal {

    public static void ex01(){
        Scanner sc = new Scanner(System.in);
        int val1,val2,val3,val4,val5,val6;

        System.out.println("<< Listando um vetor >>");
        System.out.println("Entre com o número 1:");
        val1 = sc.nextInt();

        System.out.println("Entre com o número 2:");
        val2 = sc.nextInt();

        System.out.println("Entre com o número 3:");
        val3 = sc.nextInt();

        System.out.println("Entre com o número 4:");
        val4 = sc.nextInt();

        System.out.println("Entre com o número 5:");
        val5 = sc.nextInt();

        System.out.println("Entre com o número 6:");
        val6 = sc.nextInt();

        System.out.println("Os valores lidos são:");
        System.out.printf("%d %d %d %d %d %d ", val1, val2, val3, val4, val5, val6);
    }

    public static void ex02(){
        Scanner sc = new Scanner(System.in);
        int[] vet = new int[6];
        System.out.println("<< Listando um vetor >>");

        for (int i = 0; i < 6; i++){
            System.out.printf("Entre com o número %d:\n",i+1);
            vet[i] = sc.nextInt();
        }

        System.out.println("Os valores lidos são:");
        for (int i = 0; i < 6; i++){
            System.out.printf("%d ",vet[i]);
        }
    }

    public static void ex03() {
        Scanner sc = new Scanner(System.in);
        int[] vet = new int[6];
        int val;


        for (int i = 0; i < 6; i++) {
            System.out.print("Entre com um valor: ");
            val = sc.nextInt();
            vet[i] = val;
        }


        System.out.print("Os valores lidos em ordem inversa são: ");
        for (int i = 5; i >= 0; i--) {
            System.out.print(vet[i] + " ");
        }

    }

     public static void ex04() {
        Scanner sc = new Scanner(System.in);
        int[] vet = new int[6];
        int val;
        int i = 0;


        while (i != 6) {
            System.out.print("Entre com um valor par: ");
            val = sc.nextInt();
            if (val % 2 == 0) {
                vet[i++] = val;
            }
        }


        i = 0;
        System.out.print("Os valores lidos são: ");
        while (i != 6) {
            System.out.print(vet[i] + " ");
            i++;
        }

    }

     public static void ex05() {
        Scanner sc = new Scanner(System.in);
        int[] vet = new int[5];
        int val;
        int amaior = 0;
        int amenor = 0;
        int media = 0;


        for (int i = 0; i < 5; i++) {
            System.out.print("Entre com um número: ");
            val = sc.nextInt();
            vet[i] = val;
            media += val;


            if (i == 0) {
                amaior = amenor = vet[i];
            }


            if (vet[i] > amaior) {
                amaior = vet[i];
            }


            if (vet[i] < amenor) {
                amenor = vet[i];
            }
        }


        System.out.println("Os números digitados são: ");
        for (int i = 0; i < 5; i++) {
            System.out.print(vet[i] + " ");
        }



        System.out.printf("O maior valor, o menor valor e a média são: %d %d %d%n",
                amaior, amenor, media / 5);
    }

    public static void ex06() {
        Scanner sc = new Scanner(System.in);
        int[] vet = new int[5];
        int val;
        int maior = 0, menor = 0, media = 0;
        int idmaior = 0, idmenor = 0;


        for (int i = 0; i < 5; i++) {
            System.out.print("Entre com um número: ");
            val = sc.nextInt();
            vet[i] = val;
            media += val;


            if (i == 0) {
                maior = menor = vet[i];
            }


            if (vet[i] > maior) {
                maior = vet[i];
                idmaior = i;
            }


            if (vet[i] <menor) {
                menor = vet[i];
                idmenor = i;
            }
        }


        System.out.println("Os números digitados são: ");
        for (int i = 0; i < 5; i++) {
            System.out.print(vet[i] + " ");
        }



        System.out.printf("O maior valor, o menor valor e a média são: %d(%d), %d(%d), %d%n",
                maior, idmaior, menor, idmenor, media / 5);
    }

    public static void ex07() {
        Scanner sc = new Scanner(System.in);
        int[] vet = new int[5];
        int val;


        for (int i = 0; i < 5; i++) {
            System.out.print("Entre com um número: ");
            val = sc.nextInt();
            if (i == 4) {
                vet[i] = 100;
            } else {
                vet[i] = 2 * val;
            }
        }


        System.out.println("Os números digitados são: ");
        for (int i = 0; i < 5; i++) {
            System.out.print(vet[i] + " ");
        }

    }

    public static void ex08() {
        Scanner sc = new Scanner(System.in);
        float[] vet = new float[5];
        float media = 0;
        float desvio = 0;


        for (int i = 0; i < 5; i++) {
            System.out.print("Entre com um número: ");
            vet[i] = sc.nextFloat();
            media += vet[i];
        }


        media = media / 5;


        for (int i = 0; i < 5; i++) {
            desvio += Math.pow(vet[i] - media, 2);
        }
        desvio = (float) Math.sqrt(desvio / 5);


        System.out.printf("Média e Desvio Padrão: %.2f %.2f%n", media, desvio);
    }

    public static void ex09() {
        Scanner sc = new Scanner(System.in);


        System.out.print("Digite o número de alunos na turma: ");
        int numAlunos = sc.nextInt();


        if (numAlunos <= 0 || numAlunos > 100) {
            System.out.println("Número de alunos inválido. Digite um número entre 1 e 100.");
            return;
        }


        double[] notas = new double[numAlunos];


        for (int i = 0; i < numAlunos; i++) {
            System.out.printf("Digite a nota do aluno %d: ", i + 1);
            notas[i] = sc.nextDouble();
        }



        double soma = 0;
        for (int i = 0; i < numAlunos; i++) {
            soma += notas[i];
        }
        double media = soma / numAlunos;



        System.out.println("\nNotas dos alunos:");
        for (int i = 0; i < numAlunos; i++) {
            System.out.printf("Aluno %d: %.2f\n", i + 1, notas[i]);
        }


        System.out.printf("\nMédia da turma: %.2f\n", media);
    }

    public static void ex10() {
        Scanner sc = new Scanner(System.in);

        int[] A = new int[3];
        int[] B = new int[3];
        int[] C = new int[3];


        System.out.println("Digite os 3 números do array A:");
        for (int i = 0; i < 3; i++) {
            System.out.printf("A[%d]: ", i);
            A[i] = sc.nextInt();
        }


        System.out.println("Digite os 3 números do array B:");
        for (int i = 0; i < 3; i++) {
            System.out.printf("B[%d]: ", i);
            B[i] = sc.nextInt();
        }


        for (int i = 0; i < 3; i++) {
            C[i] = A[i] - B[i];
        }


        System.out.println("Os valores do array C (A - B) são:");
        for (int i = 0; i < 3; i++) {
            System.out.printf("C[%d]: %d\n", i + 1, C[i]);
        }
    }

    public static void ex11() {
        Scanner sc = new Scanner(System.in);

        int[] v = new int[5];
        int[] v1 = new int[5];
        int[] v2 = new int[5];

        int v1Index = 0;
        int v2Index = 0;


        System.out.println("Digite 5 números inteiros:");
        for (int i = 0; i < 5; i++) {
            System.out.printf("v[%d]: ", i);
            v[i] = sc.nextInt();


            if (v[i] % 2 == 0) {
                v2[v2Index] = v[i];
                v2Index++;
            } else {
                v1[v1Index] = v[i];
                v1Index++;
            }
        }


        System.out.println("\nElementos utilizados em v1 (ímpares):");
        for (int i = 0; i < v1Index; i++) {
            System.out.printf("v1[%d]: %d\n", i, v1[i]);
        }


        System.out.println("\nElementos utilizados em v2 (pares):");
        for (int i = 0; i < v2Index; i++) {
            System.out.printf("v2[%d]: %d\n", i, v2[i]);
        }
    }

    public static void ex12() {
        Scanner sc = new Scanner(System.in);


        System.out.print("Digite a quantidade de bolinhas azuis: ");
        int azul = sc.nextInt();

        System.out.print("Digite a quantidade de bolinhas verdes: ");
        int verde = sc.nextInt();

        System.out.print("Digite a quantidade de bolinhas amarelas: ");
        int amarelo = sc.nextInt();

        System.out.print("Digite a quantidade de bolinhas vermelhas: ");
        int vermelho = sc.nextInt();


        int total = azul + verde + amarelo + vermelho;


        double probAzul = (double) azul / total;
        double probVerde = (double) verde / total;
        double probAmarelo = (double) amarelo / total;
        double probVermelho = (double) vermelho / total;


        System.out.printf("Probabilidade de bolinhas azuis: %.2f%%\n", probAzul * 100);
        System.out.printf("Probabilidade de bolinhas verdes: %.2f%%\n", probVerde * 100);
        System.out.printf("Probabilidade de bolinhas amarelas: %.2f%%\n", probAmarelo * 100);
        System.out.printf("Probabilidade de bolinhas vermelhas: %.2f%%\n", probVermelho * 100);


        double maxProb = Math.max(Math.max(probAzul, probVerde), Math.max(probAmarelo, probVermelho));
        System.out.print("A cor com a maior probabilidade é: ");

        if (maxProb == probAzul) {
            System.out.println("Azul");
        } else if (maxProb == probVerde) {
            System.out.println("Verde");
        } else if (maxProb == probAmarelo) {
            System.out.println("Amarelo");
        } else {
            System.out.println("Vermelho");
        }
    }

    public static void ex13() {
        Scanner sc = new Scanner(System.in);
        int[] vetor = new int[5];


        System.out.println("Digite 5 números inteiros:");
        for (int i = 0; i < 5; i++) {
            System.out.printf("vetor[%d]: ", i);
            vetor[i] = sc.nextInt();
        }


        for (int i = 0; i < 5; i++) {
            if (vetor[i] < 0) {
                vetor[i] = 0;
            }
        }


        System.out.println("Vetor final com valores negativos substituídos por 0:");
        for (int i = 0; i < 5; i++) {
            System.out.printf("vetor[%d]: %d\n", i, vetor[i]);
        }
    }

    public static void ex14() {
        Scanner sc = new Scanner(System.in);


        int maxAlunos = 10000;


        System.out.println("<< Universidade Federal de Uberlândia >>");
        System.out.print("Quantos alunos serão cadastrados: ");
        int numAlunos = sc.nextInt();


        if (numAlunos > maxAlunos) {
            System.out.println("Erro: O número máximo de alunos permitido é 10.000.");
            return;
        }


        int[] matriculas = new int[numAlunos];
        char[] classesSociais = new char[numAlunos];
        double[] cras = new double[numAlunos];


        for (int i = 0; i < numAlunos; i++) {
            System.out.printf("Entre com o número do aluno %d: ", i + 1);
            matriculas[i] = sc.nextInt();

            System.out.printf("Entre com a classe social do aluno %d: ", matriculas[i]);
            classesSociais[i] = sc.next().charAt(0);

            System.out.printf("Entre com o CRA do aluno %d: ", matriculas[i]);
            cras[i] = sc.nextDouble();
        }


        System.out.println("\n==== Alunos Cadastrados ====");
        for (int i = 0; i < numAlunos; i++) {
            System.out.printf("Número: %d Classe Social: %c CRA: %.2f\n", matriculas[i], classesSociais[i], cras[i]);
        }
    }

    public static void ex15() {
        Scanner sc = new Scanner(System.in);
        int[] vetor = new int[8];
        boolean[] repetido = new boolean[8];


        System.out.println("Digite 8 números inteiros:");
        for (int i = 0; i < 8; i++) {
            System.out.printf("vetor[%d]: ", i);
            vetor[i] = sc.nextInt();
        }


        for (int i = 0; i < 8; i++) {
            for (int j = i + 1; j < 8; j++) {
                if (vetor[i] == vetor[j]) {
                    repetido[j] = true;
                }
            }
        }


        System.out.println("Valores repetidos:");
        boolean encontrouRepetido = false;
        for (int i = 0; i < 8; i++) {
            if (repetido[i]) {
                System.out.println(vetor[i]);
                encontrouRepetido = true;
                repetido[i] = false;
            }
        }

        if (!encontrouRepetido) {
            System.out.println("Não há valores repetidos.");
        }
    }

    public static void ex16() {
        Scanner sc = new Scanner(System.in);
        int[] vetor = new int[8];
        int[] contagem = new int[8];


        System.out.println("Digite 8 números inteiros:");
        for (int i = 0; i < 8; i++) {
            System.out.printf("vetor[%d]: ", i);
            vetor[i] = sc.nextInt();
        }


        for (int i = 0; i < 8; i++) {
            int frequencia = 1;
            for (int j = i + 1; j < 8; j++) {
                if (vetor[i] == vetor[j]) {
                    frequencia++;
                    contagem[j] = -1;
                }
            }
            if (contagem[i] != -1) {
                contagem[i] = frequencia;
            }
        }


        System.out.println("Quantidades de ocorrências:");
        boolean encontrouRepetidos = false;
        for (int i = 0; i < 8; i++) {
            if (contagem[i] > 0) {
                System.out.printf("Valor %d aparece %d vez(es)\n", vetor[i], contagem[i]);
                encontrouRepetidos = true;
            }
        }

        if (!encontrouRepetidos) {
            System.out.println("Não há valores repetidos.");
        }
    }

    public static void main(String[] args) {
<<<<<<< HEAD
        // ex01();
        // ex02();
        // ex03();
        // ex04();
        // ex05();
        // ex06();
        // ex07();
        // ex08();
        // ex09();
        // ex10();
        // ex11();
        // ex12();
        // ex13();
        // ex14();
        // ex15();
        // ex16();
=======
        //ex01();
        ex02();
        //ex03();
>>>>>>> 410c8d194ee74c713f6bc5eb9b4c6d54659a1bed
    }


}
