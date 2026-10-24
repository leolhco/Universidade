public class CandidatoVereador extends Candidato {
    private String numVereador;
    private String bairro;

    public CandidatoVereador(String nome, String dataNascimento, String genero, float bens, boolean reeleicao, int numPartido, String numVereador, String bairro) {
        super(nome, dataNascimento, genero, bens, reeleicao, numPartido);
        this.numVereador = numVereador;
        this.bairro = bairro;
    }


    public CandidatoVereador(Candidato candidato, String numVereador, String bairro) {
        super(candidato.getNome(), candidato.getDataNascimento(), candidato.getGenero(), candidato.getBens(), candidato.isReeleicao(), candidato.getNumPartido());
        this.numVereador = numVereador;
        this.bairro = bairro;
    }

    @Override
    public String toString() {
        return super.toString() + "\nNúmero de Vereador: " + numVereador + "\nBairro: " + bairro;
    }
}
