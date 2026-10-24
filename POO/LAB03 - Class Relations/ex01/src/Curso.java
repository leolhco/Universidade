public class Curso {
    private String nome;
    private Professor professorResponsavel;


    public Curso(String nome, Professor professorResponsavel) {
        this.nome = nome;
        this.professorResponsavel = professorResponsavel;
    }


    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Professor getProfessorResponsavel() {
        return professorResponsavel;
    }

    public void setProfessorResponsavel(Professor professorResponsavel) {
        this.professorResponsavel = professorResponsavel;
    }


    public String toString() {
        return "Curso{" + "nome='" + nome + '\'' + ", professorResponsavel=" + professorResponsavel + '}';
    }
}
