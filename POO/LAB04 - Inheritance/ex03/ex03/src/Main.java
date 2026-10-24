public class Main {
    public static void main(String[] args) {
        CandidatoPrefeito prefeito = new CandidatoPrefeito("João Silva", "10/03/1970", "Masculino", 1500000.75f, true, 45, "Carlos Souza", "40");
        CandidatoVereador vereador = new CandidatoVereador("Maria Lima", "15/05/1985", "Feminino", 500000.00f, false, 33, "123", "Centro");

        System.out.println(prefeito);
        System.out.println();
        System.out.println(vereador);


        CandidatoVereador vereadorCopia = new CandidatoVereador(prefeito, "456", "Jardim das Flores");
        System.out.println();
        System.out.println(vereadorCopia);
    }
}