public class Time {
    private String nome;
    private Jogador[] jogadores = new Jogador[3];


    public Time(String nome, String nomeTitular1, int idadeTitular1, double alturaTitular1, double pesoTitular1,
                String nomeTitular2, int idadeTitular2, double alturaTitular2, double pesoTitular2,
                String nomeSubstituto, int idadeSubstituto, double alturaSubstituto, double pesoSubstituto) {
        this.nome = nome;
        jogadores[0] = new Jogador(nomeTitular1, idadeTitular1, alturaTitular1, pesoTitular1);
        jogadores[1] = new Jogador(nomeTitular2, idadeTitular2, alturaTitular2, pesoTitular2);
        jogadores[2] = new Jogador(nomeSubstituto, idadeSubstituto, alturaSubstituto, pesoSubstituto);
    }


    public Time(String nome, String nomeTitular1, int idadeTitular1, double alturaTitular1, double pesoTitular1,
                String nomeTitular2, int idadeTitular2, double alturaTitular2, double pesoTitular2) {
        this.nome = nome;
        jogadores[0] = new Jogador(nomeTitular1, idadeTitular1, alturaTitular1, pesoTitular1);
        jogadores[1] = new Jogador(nomeTitular2, idadeTitular2, alturaTitular2, pesoTitular2);
        jogadores[2] = null;
    }


    public String toString() {
        String infoTitulares = "Titular 1: " + jogadores[0] + "\nTitular 2: " + jogadores[1];
        String infoSubstituto = (jogadores[2] != null) ? jogadores[2].toString() : "Nenhum substituto";
        return "Nome do Time: " + nome + "\n" + infoTitulares + "\nSubstituto: " + infoSubstituto;
    }


    public double calcularMediaIdade() {
        int somaIdades = 0;
        int contadorJogadores = 0;


        for (int i = 0; i < jogadores.length; i++) {
            if (jogadores[i] != null) {
                somaIdades += jogadores[i].getIdade();
                contadorJogadores++;
            }
        }


        return (double) somaIdades / contadorJogadores;
    }
}
