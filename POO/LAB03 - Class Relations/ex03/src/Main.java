public class Main {
    public static void main(String[] args) {
        Carro carro = new Carro("Ferrari", "V8");

        System.out.println(carro);

        // Se o objeto Carro for removido, o Motor também é removido,
        // pois o motor é parte do carro, ou seja, nao sao independentes.
    }
}