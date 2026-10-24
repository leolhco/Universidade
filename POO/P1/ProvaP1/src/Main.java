import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Quantos times você quer criar? ");
        int n = sc.nextInt();
        sc.nextLine();

        Time[] times = new Time[n];


        for (int i = 0; i < n; i++) {
            System.out.print("\nNome do time " + (i + 1) + ": ");
            String nomeTime = sc.nextLine();

            System.out.print("Nome do titular 1: ");
            String nomeTitular1 = sc.nextLine();
            System.out.print("Idade do titular 1: ");
            int idadeTitular1 = sc.nextInt();
            System.out.print("Altura do titular 1 (em metros): ");
            double alturaTitular1 = sc.nextDouble();
            System.out.print("Peso do titular 1 (em kg): ");
            double pesoTitular1 = sc.nextDouble();
            sc.nextLine();

            System.out.print("Nome do titular 2: ");
            String nomeTitular2 = sc.nextLine();
            System.out.print("Idade do titular 2: ");
            int idadeTitular2 = sc.nextInt();
            System.out.print("Altura do titular 2 (em metros): ");
            double alturaTitular2 = sc.nextDouble();
            System.out.print("Peso do titular 2 (em kg): ");
            double pesoTitular2 = sc.nextDouble();
            sc.nextLine();

            System.out.print("O time tem um substituto? (s/n): ");
            String temSubstituto = sc.nextLine();

            if (temSubstituto.equals("s")) {
                System.out.print("Nome do substituto: ");
                String nomeSubstituto = sc.nextLine();
                System.out.print("Idade do substituto: ");
                int idadeSubstituto = sc.nextInt();
                System.out.print("Altura do substituto (em metros): ");
                double alturaSubstituto = sc.nextDouble();
                System.out.print("Peso do substituto (em kg): ");
                double pesoSubstituto = sc.nextDouble();
                sc.nextLine();

                times[i] = new Time(nomeTime, nomeTitular1, idadeTitular1, alturaTitular1, pesoTitular1,
                        nomeTitular2, idadeTitular2, alturaTitular2, pesoTitular2,
                        nomeSubstituto, idadeSubstituto, alturaSubstituto, pesoSubstituto);
            } else {
                times[i] = new Time(nomeTime, nomeTitular1, idadeTitular1, alturaTitular1, pesoTitular1,
                        nomeTitular2, idadeTitular2, alturaTitular2, pesoTitular2);
            }
        }


        System.out.println("\nInformações dos times:");
        for (Time time : times) {
            System.out.println(time);
        }


        Time timeComMaiorMedia = times[0];
        for (int i = 1; i < times.length; i++) {
            if (times[i].calcularMediaIdade() > timeComMaiorMedia.calcularMediaIdade()) {
                timeComMaiorMedia = times[i];
            }
        }

        System.out.println("\nTime com a maior média de idade: " + timeComMaiorMedia);

        for (int i = 0; i < times.length; i++) {
            times[i] = null;
        }

        sc.close();
    }
}
