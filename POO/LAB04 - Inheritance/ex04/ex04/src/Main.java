public class Main {
    public static void main(String[] args) {

        C1 candidato1 = new C1("Carlos Silva", "Masculino", "123.456.789-00");
        candidato1.mostrarAtributos();
        System.out.println();


        C2 candidato2 = new C2("Maria Oliveira", "Feminino", "987.654.321-00", "Rua A, 123", "555-1234", "maria@email.com");
        candidato2.mostrarAtributos();
        System.out.println();


        C3 candidato3 = new C3("Ana Costa", "Feminino", "456.789.123-45", "Avenida B, 456", "555-5678", "ana@email.com",
                "Engenheira", "Brasileira", "ID-789456");
        candidato3.mostrarAtributos();
        System.out.println();


        candidato3.mostrarAtributosSuper();
    }
}
