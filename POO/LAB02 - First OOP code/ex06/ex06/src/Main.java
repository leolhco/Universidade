public class Main {
    public static void main(String[] args) {


                Candidato candidato1 = new Candidato("João Silva", "15/08/1975",
                        "Masculino", 500000.0, "Sim", 45, "Vereador");

                Candidato candidato2 = new Candidato("Maria Souza", "20/12/1980",
                        "Feminino", 750000.0, "Não", 20, "Prefeita");

                Candidato candidato3 = new Candidato("Pedro Oliveira", "10/03/1965",
                        "Masculino", 300000.0, "Sim", 13, "Vereador");

                Candidato candidato4 = new Candidato("Ana Costa", "05/06/1990",
                        "Feminino", 250000.0, "Não", 30, "Prefeita");

                Candidato candidato5 = new Candidato("Carlos Mendes", "25/11/1985",
                        "Masculino", 900000.0, "Sim", 50, "Vereador");

                Candidato[] candidatos = {candidato1, candidato2, candidato3, candidato4, candidato5};

                Eleicao eleicao = new Eleicao("São Paulo", "São Paulo", "Sudeste",
                8500000, 5);

                eleicao.candidato = candidatos;

                eleicao.candidatoMaisRico(candidatos);



    }
}