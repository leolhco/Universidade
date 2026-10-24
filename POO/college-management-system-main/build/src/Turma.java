import java.util.ArrayList;
import java.util.List;

public class Turma extends Disciplina implements Exibivel{
    private List<Estudante> alunos;
    private Professor professor;
    private int ano;
    private int semestre;

    public Turma(List<Estudante> alunos, Professor professor, int ano, int semestre, String disNome, String disCodigo, String disCargaHoraria) {
        super(disNome, disCodigo, disCargaHoraria);
        this.alunos = new ArrayList<Estudante>(alunos);
        this.professor = professor;
        this.ano = ano;
        this.semestre = semestre;
    }

    public void setAlunos(List<Estudante> alunos) {
        this.alunos = alunos;
    }

    public void setProfessor(Professor professor) {
        this.professor = professor;
    }

    public void setDisciplina(String disNome, String disCodigo, String disCargaHoraria) {
        super.setNome(disNome);
        super.setCodigo(disCodigo);
        super.setCargaHoraria(disCargaHoraria);
    }

    public void setAno(int ano) {
        this.ano = ano;
    }

    public void setSemestre(int semestre) {
        this.semestre = semestre;
    }

    public List<Estudante> getAlunos() {
        return alunos;
    }

    public Professor getProfessor() {
        return professor;
    }


    public int getAno() {
        return ano;
    }

    public int getSemestre() {
        return semestre;
    }

    // metodos lista
    public boolean adicionarEstudante(Estudante aluno) {
        return alunos.add(aluno);
    }

    public boolean removerEstudante(String CPF) {

        for (Estudante aluno : alunos) {
            if (aluno.getCPF().equals(CPF)) {
                alunos.remove(aluno);
                return true;
            }
        }
        return false;
    }

    public void showStudentList() {
        for (Estudante aluno : alunos) {
            System.out.println(aluno.mostrarDados());
            System.out.println("\n\n\n");
        }
    }

    public Estudante searchStudent(String CPF) {
        for (Estudante aluno : alunos) {
            if (aluno.getCPF().equals(CPF)) {
                return aluno;
            }
        }
        return null;
    }

    // metodo abstrato
    @Override
    public String mostrarDados() {
        return "Nome: " + super.getNome() + "\nCodigo: " + super.getCodigo() + "\nCarga Horaria: " + super.getCargaHoraria() + "\nAno: " + ano + "\nSemestre: " + semestre + "\n\n\n";
    }

}
