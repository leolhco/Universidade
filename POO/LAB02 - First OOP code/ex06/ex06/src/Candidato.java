public class Candidato {

        private String nome;
        private String data;
        private String genero;
        private double bens;
        private String reeleicao;
        private int partido;
        private String cargo;


        public Candidato(String nomeCandidato, String dataNascimento, String generoCandidato, double totalBens,
                         String reeleicaoStatus, int numeroPartido, String cargoPretendido) {
            nome = nomeCandidato;
            data = dataNascimento;
            genero = generoCandidato;
            bens = totalBens;
            reeleicao = reeleicaoStatus;
            partido = numeroPartido;
            cargo = cargoPretendido;
        }


        public void mostrar() {
            System.out.println("Nome: " + nome);
            System.out.println("Data de Nascimento: " + data);
            System.out.println("Gênero: " + genero);
            System.out.println("Total de Bens: " + bens);
            System.out.println("Reeleição: " + reeleicao);
            System.out.println("Partido: " + partido);
            System.out.println("Cargo: " + cargo);
            System.out.println();
        }

        public double getBens(){
            return this.bens;
        }




}
