import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Candidato[] candidatos = new Candidato[3];

        for(int i = 0; i < candidatos.length; i++){
            candidatos[i] = new Candidato();
        }
        /*for(Candidato candidato : candidatos){
            candidato = new Candidato();
        }*/

        for(int i = 0; i < candidatos.length; i++){
            System.out.printf("Entre com o nome do candidato:");
            candidatos[i].nome = sc.nextLine();

            System.out.printf("Entre com a data de nascimento do candidato:");
            candidatos[i].data = sc.nextLine();

            System.out.printf("Entre com o genero do candidato:");
            candidatos[i].genero = sc.nextLine();

            System.out.printf("Entre com os bens em reais do candidato:");
            candidatos[i].bens = sc.nextDouble();

            sc.nextLine();

            System.out.printf("O candidato esta tentando a reeleicao?");
            candidatos[i].reeleicao = sc.nextLine();

            System.out.printf("Entre com o numero do partido do candidato:");
            candidatos[i].numPartido = sc.nextInt();

            sc.nextLine();

            System.out.printf("Entre com o cargo pleitado pelo candidato:");
            candidatos[i].cargo = sc.nextLine();
            System.out.println();
        }
        for(Candidato candidato: candidatos){
            candidato.mostrar();
        }

        sc.close();
    }
}