public class Main {
    public static void main(String[] args) {

        Eleicao cidadea = new Eleicao("Uberlandia", "Minas Gerais",
                "Sudeste", 540000, 544);

        Eleicao cidadeb = new Eleicao("Uberaba", "Minas Gerais",
                "Sudeste", 233000, 386);

        cidadea.mostrar();
        cidadeb.mostrar();
    }
}