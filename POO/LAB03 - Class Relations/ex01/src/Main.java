public class Main {
    public static void main(String[] args) {
        Aluno aluno = new Aluno("Leonardo", 12311);

        Professor professor = new Professor("Bruno");
        Curso curso = new Curso("POO", professor);

        System.out.println(aluno);
        System.out.println(curso);

        /* Aqui os objetos Aluno e Curso são independentes, ou seja, o curso pode existir sem o aluno inscrito e vice-versa */
    }
}