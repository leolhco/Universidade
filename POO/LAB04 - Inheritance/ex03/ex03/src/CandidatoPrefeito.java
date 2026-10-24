public class CandidatoPrefeito extends Candidato {
    private String nomeVice;
    private String partidoVice;

    public CandidatoPrefeito(String nome, String dataNascimento, String genero, float bens, boolean reeleicao, int numPartido, String nomeVice, String partidoVice) {
        super(nome, dataNascimento, genero, bens, reeleicao, numPartido);
        this.nomeVice = nomeVice;
        this.partidoVice = partidoVice;
    }

    @Override
    public String toString() {
        return super.toString() + "\nVice: " + nomeVice + ", Partido do Vice: " + partidoVice;
    }
}