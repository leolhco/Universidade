public class Main {
    public static void main(String[] args) {
        CandidatoPrefeito prefeito = new CandidatoPrefeito("Paulo Sergio", "17/10/2000", "Masculino", 350000f, false,
                11, "Pelizer", "22");

        CandidatoVereador vereador = new CandidatoVereador("Fabao", "09/11/2001", "Masculino", 100000f, true,
                43, 123, "Santa Monica");

        System.out.println(prefeito);
        System.out.println(vereador);
    }
}