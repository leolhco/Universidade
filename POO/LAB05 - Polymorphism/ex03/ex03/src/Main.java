public class Main {
    public static void main(String[] args) {

        Universidade universidade = new Universidade("Universidade ABC", "01/01/1950");


        EstudanteGraduacao estudante1 = new EstudanteGraduacao("Carlos", "Rua A", "TCC sobre Inteligência Artificial");
        EstudanteMestrado estudante2 = new EstudanteMestrado("Ana", "Rua B", "Engenharia de Software", "Sistemas Distribuídos", "Acadêmico", "Dissertação sobre Cloud Computing");
        EstudanteDoutorado estudante3 = new EstudanteDoutorado("João", "Rua C", "Engenharia de Computação", "Machine Learning", "Tese sobre Redes Neurais");


        universidade.adicionarAluno(estudante1);
        universidade.adicionarAluno(estudante2);
        universidade.adicionarAluno(estudante3);


        System.out.println("Contagem de estudantes por nível:");
        universidade.contarTiposEstudantes();


        System.out.println("\nInformações dos alunos:");
        universidade.mostrarInformacoesAlunos();


        EstudantePosGrad[] posGraduacao = universidade.copiarAlunosPosGraduacao();
        System.out.println("\nInformações dos alunos de pós-graduação:");
        universidade.mostrarPosGraduacao(posGraduacao);
    }
}
