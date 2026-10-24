import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws Exception {
        int opt;
        Scanner sc = new Scanner(System.in);
        Map<String, Turma> turmas = populate();

        System.out.println("Bem vindo.");
        while (true) {
            System.out.println("Escolha uma opcao:\n1- Estudante\n2- Professor\n3- Turma\n4- Sair");
            opt = sc.nextInt();
            switch (opt) {
                case 1:
                    
                    System.out.println("\n\n\n");
                    studentMenu(turmas);
                    break;
                
                case 2:
                    
                    System.out.println("\n\n\n");
                    teacherMenu(turmas);
                    break;
                
                case 3:
                    
                    System.out.println("\n\n\n");               
                    classMenu(turmas);
                    break;
                
                case 4:
                    
                    System.out.println("\n\n\n");
                    System.out.println("buh-bye!");
                    sc.close();
                    System.exit(0);
                
                default:
                    System.out.println("\n\n\n");
                    System.out.println("Opcao invalida.");
                    break;
            }
        }

    }

    // cria entradas estaticas para turmas
    private static Map<String, Turma> populate() {

        Map<String, Turma> turmas = new HashMap<>();

        String arq1 = "C:\\TrabFinalPOO\\TrabFinal\\college-management-system-main\\build\\src\\estudante1.txt";
        ArrayList<Estudante> alunosArray1 = new ArrayList<Estudante>();

        try(BufferedReader leitor = new BufferedReader(new FileReader(arq1))){
        
            String linha;
            while((linha = leitor.readLine()) != null){
              
                String[] separa = linha.split(",");
              
                if(separa.length == 6){
                Grad aluno = new Grad(separa[0].trim(), separa[1].trim(), separa[2].trim(),
                 Float.parseFloat(separa[3].trim()), separa[4].trim(), separa[5].trim());
                alunosArray1.add(aluno);
               
              }

            }
         } catch(IOException e) {
            System.out.println("Erro ao ler arquivo");
            System.out.println(e.getMessage());
         }


        String arq2 = "C:\\TrabFinalPOO\\TrabFinal\\college-management-system-main\\build\\src\\estudante2.txt";
        ArrayList<Estudante> alunosArray2 = new ArrayList<Estudante>();

        try(BufferedReader leitor = new BufferedReader(new FileReader(arq2))){
        
            String linha;
            while((linha = leitor.readLine()) != null){
              
                String[] separa = linha.split(",");
              
                if(separa.length == 6){
                 Grad aluno = new Grad(separa[0].trim(), separa[1].trim(), separa[2].trim(),
                  Float.parseFloat(separa[3].trim()), separa[4].trim(), separa[5].trim());
                 alunosArray2.add(aluno);
                 
              }

            }
         } catch(IOException e) {
            System.out.println("Erro ao ler arquivo");
            System.out.println(e.getMessage());
         }


        String arq3 = "C:\\TrabFinalPOO\\TrabFinal\\college-management-system-main\\build\\src\\estudante3.txt";
        ArrayList<Estudante> alunosArray3 = new ArrayList<Estudante>();

        try(BufferedReader leitor = new BufferedReader(new FileReader(arq3))){
        
            String linha;
            while((linha = leitor.readLine()) != null){
              
                String[] separa = linha.split(",");
              
                if(separa.length == 6){
                 PostGrad aluno = new PostGrad(separa[0].trim(), separa[1].trim(), separa[2].trim(),
                  Float.parseFloat(separa[3].trim()), separa[4].trim(), separa[5].trim());
                 alunosArray3.add(aluno);
                 
              }

            }
         } catch(IOException e) {
            System.out.println("Erro ao ler arquivo");
            System.out.println(e.getMessage());
         }
          

        String arq4 = "C:\\TrabFinalPOO\\TrabFinal\\college-management-system-main\\build\\src\\professor.txt";
        ArrayList<Professor> professorArray = new ArrayList<Professor>();

        try(BufferedReader leitor = new BufferedReader(new FileReader(arq4))){
        
            String linha;
            while((linha = leitor.readLine()) != null){
              
                String[] separa = linha.split(",");
              
                if(separa.length == 5){
                 Professor professor = new Professor(separa[0].trim(), separa[1].trim(), separa[2].trim(),
                  separa[3].trim(), separa[4].trim());
                 professorArray.add(professor);
                }

            }
         } catch(IOException e) {
            System.out.println("Erro ao ler arquivo");
            System.out.println(e.getMessage());
         }
         
         
        Turma turma1 = new Turma(alunosArray1, professorArray.get(0), 2021, 1, "POO", "123", "60");
        Turma turma2 = new Turma(alunosArray2, professorArray.get(1), 2021, 1, "IA", "456", "60");
        Turma turma3 = new Turma(alunosArray3, professorArray.get(2), 2021, 1, "BD", "789", "60");
        

        turmas.put("COMP69", turma1);
        turmas.put("COMP70", turma2);
        turmas.put("COMP71", turma3);

        return turmas;

    }



    private static void studentMenu(Map<String, Turma> turmas) {

        Scanner sc = new Scanner(System.in);

        while (true) {
            System.out.println("\n\n\n");
            
            try {
                System.out.println("Escolha uma opcao:\n1- Adicionar estudante da graduaçao\n2- Adicionar estudante da pos graduaçao\n3- Remover estudante\n4- Visualizar informacoes de estudante\n5- Sair");
                int opt = sc.nextInt();
                sc.nextLine();
                String turma;
                Estudante temp;
                Persistencia p;
                switch (opt) {
                    case 1:
                        
                        System.out.println("\n\n\n");
                        temp = getStudentDataGraduacao();
                        if (temp == null) {
                            System.out.println("Erro no cadastro do estudante.");
                            break;
                        }

                        System.out.println("Digite o codigo da turma que deseja adicionar o estudante:");
                        turma = sc.nextLine();
                        if (!turmas.containsKey(turma)) {
                            throw new TurmaNaoEncontrada("Turma " + turma + " nao encontrada.");
                        }
                        
                        if (turma.compareTo("COMP69") == 0 || turma.compareTo("COMP70") == 0){
                            if (turmas.get(turma).adicionarEstudante(temp))
                                 System.out.println("Estudante adicionado com sucesso.");
                            else
                                 System.out.println("Erro ao adicionar estudante.");
                        } else {
                            System.out.println("Turma Indisponivel.");
                        }

                        if (turma.compareTo("COMP69") == 0) {
                            p = new Persistencia("C:\\TrabFinalPOO\\TrabFinal\\college-management-system-main\\build\\src\\estudante1.txt");
                            p.escreverArq1(temp);
                        } else {
                            p = new Persistencia("C:\\TrabFinalPOO\\TrabFinal\\college-management-system-main\\build\\src\\estudante2.txt");
                            p.escreverArq2(temp);
                        }

                        System.out.println("\n\n\n");

                        break;

                    case 2:
                          
                        System.out.println("\n\n\n");
                        temp = getStudentDataPostGrad();
                        if (temp == null) {
                            System.out.println("Erro no cadastro do estudante.");
                            System.out.println("\n\n\n");
                            break;
                        }

                        System.out.println("Digite o codigo da turma que deseja adicionar o estudante:");
                        turma = sc.nextLine();
                        if (!turmas.containsKey(turma)) {
                            throw new TurmaNaoEncontrada("Turma " + turma + " nao encontrada.");
                        }
                        if (turma.compareTo("COMP71") == 0){
                            if (turmas.get(turma).adicionarEstudante(temp))
                                System.out.println("Estudante adicionado com sucesso.");
                            else
                                System.out.println("Erro ao adicionar estudante.");
                        } else {
                            System.out.println("Turma Indisponivel.");
                        }      

                        if (turma.compareTo("COMP71") == 0){
                            p = new Persistencia("C:\\TrabFinalPOO\\TrabFinal\\college-management-system-main\\build\\src\\estudante3.txt");
                            p.escreverArq3(temp);
                        }

                        System.out.println("\n\n\n");

                        break;

                    case 3:
                         
                        System.out.println("\n\n\n");
                        System.out.println("Digite o codigo da turma do estudante que deseja remover:");
                        turma = sc.nextLine();
                        if (!turmas.containsKey(turma)) {
                            throw new TurmaNaoEncontrada("Turma " + turma + " nao encontrada.");
                        }
                        System.out.println("Digite o CPF do estudante que deseja remover:");
                        String CPF = sc.nextLine();

                        if (turmas.get(turma).removerEstudante(CPF))
                            System.out.println("Estudante removido com sucesso.");
                        else
                            System.out.println("Erro ao remover estudante.");


                            System.out.println("\n\n\n");

                        break;

                    case 4:
                                
                        System.out.println("\n\n\n");
                        System.out.println("Voce deseja:\n1- Visualizar lista de estudantes\n2- Visualizar informacoes de um estudante especifico\n3- Voltar");
                        int opt2 = sc.nextInt();
                        sc.nextLine();

                        if (opt2 == 1) {
                            System.out.println("Digite o codigo da turma:");
                            turma = sc.nextLine();
                            if (turmas.containsKey(turma))
                                turmas.get(turma).showStudentList();
                            else
                                throw new TurmaNaoEncontrada("Turma " + turma + " nao encontrada.");
                        } else if (opt2 == 2) {
                            System.out.println("Digite o codigo da turma:");
                            turma = sc.nextLine();
                            if (turmas.containsKey(turma)) {
                                System.out.println("Digite o CPF do estudante:");
                                CPF = sc.nextLine();
                                temp = turmas.get(turma).searchStudent(CPF);
                                if (temp == null)
                                    System.out.println("Estudante nao encontrado.");
                                else
                                    System.out.println(temp);
                            } else
                                throw new TurmaNaoEncontrada("Turma " + turma + " nao encontrada.");
                        }

                        System.out.println("\n\n\n");

                        break;

                    case 5:
                        // volta para o menu principal;
                        System.out.println("\n\n\n");
                        System.out.println("Voltando para o Menu Principal.");
                        System.out.println("\n\n\n");
                         return; 

                    default:
                        
                        System.out.println("\n\n\n");
                        System.out.println("Opcao invalida.");
                        System.out.println("\n\n\n");
                }
            } catch (TurmaNaoEncontrada e) {
                System.out.println(e.getMessage());
                System.out.println("\n\n\n");
            }
           // sc.close();
        }
    }

    private static void teacherMenu(Map<String, Turma> turmas) {
        Scanner sc = new Scanner(System.in);
        
        while (true) {
            System.out.println("\n\n\n"); 
            try {
                
                System.out.println("Você deseja:\n1- Adicionar professor\n2- Remover professor\n3- Visualizar informações de professor\n4- Voltar");
                int opt = sc.nextInt();
                sc.nextLine(); 
                
                
                switch (opt) {
                    case 1:
                        
                        System.out.println("\n\n\n");
                        Professor temp = getProfessorData();
                        System.out.println("Digite o código da turma que deseja adicionar o professor:");
                        String turma = sc.nextLine();
                        if (turmas.containsKey(turma)) {
                            turmas.get(turma).setProfessor(temp);
                            Persistencia p = new Persistencia("C:\\TrabFinalPOO\\TrabFinal\\college-management-system-main\\build\\src\\professor.txt");
                            p.escreverArq4(temp);
                            System.out.println("Professor adicionado com sucesso!");
                        } else {
                            throw new TurmaNaoEncontrada("Turma " + turma + " não encontrada.");
                        }
                        System.out.println("\n\n\n");
                        break;
    
                    case 2:
                        
                        System.out.println("\n\n\n");
                        System.out.println("Digite o código da turma do professor que deseja remover:");
                        turma = sc.nextLine();
                        if (turmas.containsKey(turma)) {
                            turmas.get(turma).setProfessor(null);
                            System.out.println("Professor removido com sucesso!");
                        } else {
                            throw new TurmaNaoEncontrada("Turma " + turma + " não encontrada.");
                        }
                        System.out.println("\n\n\n");
                        break;
    
                    case 3:
                        System.out.println("\n\n\n");
                        System.out.println("Você deseja:\n1- Visualizar informações de um professor específico\n2- Visualizar professores de todas as turmas\n3- Voltar");
                        int opt2 = sc.nextInt();
                        sc.nextLine(); 
                        if (opt2 == 1) {
                            System.out.println("Digite o código da turma:");
                            turma = sc.nextLine();
                            if (turmas.containsKey(turma)) {
                                Professor prof = turmas.get(turma).getProfessor();
                                if (prof != null) {
                                    System.out.println(prof.mostrarDados());
                                } else {
                                    System.out.println("Nenhum professor atribuído a esta turma.");
                                }
                            } else {
                                throw new TurmaNaoEncontrada("Turma " + turma + " não encontrada.");
                            }
                        } else if (opt2 == 2) {
                            for (Map.Entry<String, Turma> entry : turmas.entrySet()) {
                                System.out.println("Turma: " + entry.getKey());
                                Professor prof = entry.getValue().getProfessor();
                                System.out.println(prof != null ? "Professor: " + prof.mostrarDados() : "Professor: Nenhum professor atribuído.");
                            }
                        } else {
                            System.out.println("Voltando...");
                        }
                        System.out.println("\n\n\n");
                        break;
    
                    case 4:
                        
                        System.out.println("\n\n\n");
                        System.out.println("Voltando ao menu principal...");
                        System.out.println("\n\n\n");
                        return;
    
                    default:
                        
                        System.out.println("\n\n\n");
                        System.out.println("Opção inválida.");
                        System.out.println("\n\n\n");
                }
            } catch (TurmaNaoEncontrada e) {
                
                System.out.println(e.getMessage());
                System.out.println("\n\n\n");
            }
       //  sc.close();
        }
    }
    
    private static void classMenu(Map<String, Turma> turmas) {
        Scanner sc = new Scanner(System.in);
        
        while (true) {
          System.out.println("\n\n\n"); 
        
        try {
            System.out.println("Voce deseja:\n1- Adicionar uma turma\n2- Visualizar as informacoes de uma turma\n3- Remover uma turma\n4- Voltar");
            int opt = sc.nextInt();
            sc.nextLine();
            String turma;

            switch (opt) {
                case 1:
                    
                    System.out.println("\n\n\n");
                    System.out.println("Digite o codigo da turma:");
                    String codigo = sc.nextLine();
                    if (turmas.containsKey(codigo)) {
                        System.out.println("Turma ja existente.");
                        break;
                    }
                    System.out.println("Digite o ano da turma:");
                    int ano = sc.nextInt();
                    System.out.println("Digite o semestre da turma:");
                    int semestre = sc.nextInt();
                    System.out.println("Digite o nome da disciplina:");
                    String disNome = sc.nextLine();
                    System.out.println("Digite o codigo da disciplina:");
                    String disCodigo = sc.nextLine();
                    System.out.println("Digite a carga horaria da disciplina:");
                    String disCargaHoraria = sc.nextLine();
                    Professor prof = getProfessorData();
                    turmas.put(codigo, new Turma(new ArrayList<Estudante>(100), prof, ano, semestre, disNome, disCodigo, disCargaHoraria));
                    System.out.println("\n\n\n");

                    break;

                case 2:
                    
                    System.out.println("\n\n\n");
                    System.out.println("Digite o codigo da turma:");
                    turma = sc.nextLine();
                    if (turmas.containsKey(turma))
                        System.out.println(turmas.get(turma).mostrarDados());
                    else
                        throw new TurmaNaoEncontrada("Turma " + turma + " nao encontrada.");
                    
                    System.out.println("\n\n\n");

                    break;

                case 3:
                     
                    System.out.println("\n\n\n");
                    System.out.println("Digite o codigo da turma:");
                    turma = sc.nextLine();
                    if (turmas.containsKey(turma))
                        turmas.remove(turma);
                    else
                        throw new TurmaNaoEncontrada("Turma " + turma + " nao encontrada.");
                       
                    System.out.println("Turma removida com sucesso.");
                    System.out.println("\n\n\n");
                    
                    break;

                case 4:

                    System.out.println("\n\n\n");
                    System.out.println("Voltando ao Menu Anterior.");
                    System.out.println("\n\n\n");
                    return;
                
                default:
                    
                    System.out.println("\n\n\n");
                    System.out.println("Opçao Invalida.");
                    System.out.println("\n\n\n");
            }
        }catch (TurmaNaoEncontrada e)
        {
            System.out.println(e.getMessage());
            System.out.println("\n\n\n");
        }
      //sc.close();
    } 
} 

    private static Professor getProfessorData() {
        System.out.println("\n\n\n");
        Scanner sc = new Scanner(System.in);
        System.out.println("Digite o nome do professor:");
        String nome = sc.nextLine();
        System.out.println("\n");
        System.out.println("Digite a data de nascimento do professor:");
        String dataNascimento = sc.nextLine();
        System.out.println("\n");
        System.out.println("Digite o CPF do professor:");
        String CPF = sc.nextLine();
        System.out.println("\n");
        System.out.println("Digite a data de inicio do contrato do professor:");
        String inicioContrato = sc.nextLine();
        System.out.println("\n");
        System.out.println("Digite o departamento do professor:");
        String departamento = sc.nextLine();
       // sc.close();
        System.out.println("\n\n\n");
        return new Professor(nome, dataNascimento, CPF, inicioContrato, departamento);
    }


    private static Estudante getStudentDataGraduacao() {
        
        System.out.println("\n\n\n");
        Scanner sc = new Scanner(System.in);
        System.out.println("Voce deseja:\n1- Continuar\n2- Voltar");
        int opt = sc.nextInt();
        sc.nextLine();
        System.out.println("\n\n\n");

        switch (opt) {
       
            case 1:
                // pega dados do usuario
                System.out.println("Digite o nome do estudante:");
                String nome = sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite a data de nascimento do estudante:");
                String dataNascimento = sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite o CPF do estudante:");
                String CPF = sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite o CRA do estudante:");
                Float CRA = sc.nextFloat();
                sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite o nome da empresa de estagio do estudante:");
                String estagio = sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite a data de inicio do estagio do estudante:");
                String dataInicioEstagio = sc.nextLine();

                //sc.close();
                // cria um objeto do tipo grad temporario
                System.out.println("\n\n\n");
                return new Grad(nome, dataNascimento, CPF, CRA, estagio, dataInicioEstagio);
            
            case 2:
                System.out.println("Voltando ao Menu Anterior.");
                //sc.close();
                System.out.println("\n\n\n");
                return null;
            default:
                System.out.println("Opcao invalida.");
                System.out.println("\n\n\n");
                //sc.close();
                return null;
        }

    }

    private static Estudante getStudentDataPostGrad(){
        
        System.out.println("\n\n\n");
        Scanner sc = new Scanner(System.in);
        System.out.println("Voce deseja:\n1- Continuar\n2- Voltar");
        int opt = sc.nextInt();
        sc.nextLine();
        System.out.println("\n\n\n");

        switch (opt){
            case 1:
                // pega dados do usuario
                System.out.println("Digite o nome do estudante:");
                String nome = sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite a data de nascimento do estudante:");
                String dataNascimento = sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite o CPF do estudante:");
                String CPF = sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite o CRA do estudante:");
                float CRA = sc.nextFloat();
                sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite o tema da dissertacao do estudante:");
                String tema = sc.nextLine();
                System.out.println("\n");
                System.out.println("Digite a data de defesa da dissertacao do estudante:");
                String dataDefesa = sc.nextLine();

                //sc.close();
                System.out.println("\n\n\n");
                // cria um objeto do tipo postGrad temporario
                return new PostGrad(nome, dataNascimento, CPF, CRA, tema, dataDefesa);

            case 2:
                System.out.println("Voltando ao Menu Anterior.");
               // sc.close();
                System.out.println("\n\n\n");
                return null;

            default:
                System.out.println("Opcao invalida.");
                //sc.close();
                return null;
            
        }
        
                
    }

}
