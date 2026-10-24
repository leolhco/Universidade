public class candidato {

    String nome;
    String data;
    String genero;
    double bens;
    String reeleicao;
    int partido;
    String cargo;


    public candidato(String nomeCandidato, String dataNascimento, String generoCandidato, double totalBens,
                     String reeleicaoStatus, int numeroPartido, String cargoPretendido) {
        this.nome = nomeCandidato;
        this.data = dataNascimento;
        this.genero = generoCandidato;
        this.bens = totalBens;
        this.reeleicao = reeleicaoStatus;
        this.partido = numeroPartido;
        this.cargo = cargoPretendido;
    }


    public void mostrar() {
        System.out.println("Nome: " + this.nome);
        System.out.println("Data de Nascimento: " + this.data);
        System.out.println("Gênero: " + this.genero);
        System.out.println("Total de Bens: " + this.bens);
        System.out.println("Reeleição: " + this.reeleicao);
        System.out.println("Partido: " + this.partido);
        System.out.println("Cargo: " + this.cargo);
        System.out.println();
    }

}

