public class Estudante{
    private String nome;
    private String matricula;
    private String turma;
    
    
    public Estudante(String nome, String matricula, String turma) {
        this.nome = nome;
        this.matricula = matricula;
        this.turma = turma;
    }

    public String getNome() {
        return nome;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
    public String getMatricula() {
        return matricula;
    }
    public void setMatricula(String matricula) {
        this.matricula = matricula;
    }
    public String getTurma() {
        return turma;
    }
    public void setTurma(String turma) {
        this.turma = turma;
    }

    @Override
    public String toString() {
        return "Estudante [nome = " + nome + ", matricula = " + matricula + ", turma = " + turma + "]" + "\n======================================================\n";
    }

   public void show(){
    System.out.println(this.toString());
   }

    
}