public class Universidade {
    private String nome;
    private String dataFundacao;
    private Estudante[] alunos;
    private int quantidadeAlunos;

    public Universidade(String nome, String dataFundacao) {
        this.nome = nome;
        this.dataFundacao = dataFundacao;
        this.alunos = new Estudante[100];
        this.quantidadeAlunos = 0;
    }

    public void adicionarAluno(Estudante aluno) {
        if (quantidadeAlunos < 100) {
            alunos[quantidadeAlunos++] = aluno;
        }
    }


    public void contarTiposEstudantes() {
        int graduacao = 0, mestrado = 0, doutorado = 0;
        for (Estudante aluno : alunos) {
            if (aluno instanceof EstudanteGraduacao) {
                graduacao++;
            } else if (aluno instanceof EstudanteMestrado) {
                mestrado++;
            } else if (aluno instanceof EstudanteDoutorado) {
                doutorado++;
            }
        }
        System.out.println("Graduandos: " + graduacao);
        System.out.println("Mestrandos: " + mestrado);
        System.out.println("Doutorandos: " + doutorado);
    }


    public void mostrarInformacoesAlunos() {
        for (Estudante aluno : alunos) {
            if (aluno != null) {
                aluno.print();
                if (aluno instanceof EstudanteDoutorado) {
                    System.out.println("Título da Tese: " + ((EstudanteDoutorado) aluno).getTituloTese());
                    System.out.println("Linha de Pesquisa: " + ((EstudanteDoutorado) aluno).getLinhaDePesquisa());
                }
            }
        }
    }


    public EstudantePosGrad[] copiarAlunosPosGraduacao() {
        EstudantePosGrad[] posGraduacao = new EstudantePosGrad[quantidadeAlunos];
        int index = 0;
        for (Estudante aluno : alunos) {
            if (aluno instanceof EstudantePosGrad) {
                posGraduacao[index++] = (EstudantePosGrad) aluno;
            }
        }
        return posGraduacao;
    }

    public void mostrarPosGraduacao(EstudantePosGrad[] posGraduacao) {
        for (EstudantePosGrad aluno : posGraduacao) {
            if (aluno != null) {
                aluno.print();
            }
        }
    }
}
