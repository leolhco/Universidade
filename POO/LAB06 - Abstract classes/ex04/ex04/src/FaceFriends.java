import java.util.Scanner;

public class FaceFriends {
    public static void main(String[] args) {
        int tam = 4, escolha = 0, escolhaNova = 0, grau, tamVet = 0, cont, indice = 0;
        Contato[] contatos = new Contato[tam];
        Scanner sc = new Scanner(System.in);
        String nome, email, apelido, aniversario, parentesco, tipo;

        do {
            System.out.println("========MENU=======");
            System.out.println("1-> Inserir contato");
            System.out.println("2-> Imprimir todos os contatos");
            System.out.println("3-> Imprimir somente os familiares");
            System.out.println("4-> Imprimir somente os amigos");
            System.out.println("5-> Imprimir somente o pessoal do trabalho");
            System.out.println("6-> Imprimir com filtro os contatos");
            System.out.println("7-> Imprimir um contato baseado em índice");
            System.out.println("8-> Sair do Programa");
            System.out.print("Escolha uma opção: ");
            escolha = sc.nextInt();
            sc.nextLine();

            switch (escolha) {
                case 1:
                    System.out.printf("\nDigite o nome do contato: ");
                    nome = sc.nextLine();
                    System.out.printf("\nDigite o apelido do contato: ");
                    apelido = sc.nextLine();
                    System.out.printf("\nDigite o email do contato: ");
                    email = sc.nextLine();
                    System.out.printf("\nDigite o aniversario do contato: ");
                    aniversario = sc.nextLine();
                    System.out.println("Escolha o tipo de contato:\n 1-> Familia\n 2-> Amigos\n 3-> Trabalho");
                    escolhaNova = sc.nextInt();
                    sc.nextLine();

                    if (tamVet >= tam) {
                        System.out.println("Capacidade máxima de contatos atingida!");
                        break;
                    }

                    switch (escolhaNova) {
                        case 1:
                            System.out.printf("\nDigite o parentesco do contato: ");
                            parentesco = sc.nextLine();
                            contatos[tamVet] = new Familia(nome, apelido, email, aniversario, parentesco);
                            tamVet++;
                            break;

                        case 2:
                            System.out.printf("\nDigite o grau de amizade do contato: ");
                            grau = sc.nextInt();
                            sc.nextLine();  // Consumir nova linha
                            contatos[tamVet] = new Amigos(nome, apelido, email, aniversario, grau);
                            tamVet++;
                            break;

                        case 3:
                            System.out.printf("\nDigite o tipo de relação no trabalho do contato: ");
                            tipo = sc.nextLine();
                            contatos[tamVet] = new Trabalho(nome, apelido, email, aniversario, tipo);
                            tamVet++;
                            break;

                        default:
                            System.out.println("Opção inválida!");
                            break;
                    }
                    break;

                case 2:
                    System.out.println("Imprimindo todos os contatos!");
                    for (Contato contato : contatos) {
                        if (contato instanceof Familia) {
                            ((Familia) contato).imprimirContato();
                        }

                        if (contato instanceof Amigos) {
                            ((Amigos) contato).imprimirContato();
                        }

                        if (contato instanceof Trabalho) {
                            ((Trabalho) contato).imprimirContato();
                        }
                    }
                    break;

                case 3:
                    System.out.println("Imprimindo somente os familiares!");
                    cont = 0;
                    for (Contato contato : contatos) {
                        if (contato instanceof Familia) {
                            cont++;
                            ((Familia) contato).imprimirContato();
                        }
                    }
                    if (cont == 0) {
                        System.out.println("Sem contato do tipo Familia cadastrado!");
                    }
                    break;

                case 4:
                    System.out.println("Imprimindo somente os amigos!");
                    cont = 0;
                    for (Contato contato : contatos) {
                        if (contato instanceof Amigos) {
                            cont++;
                            ((Amigos) contato).imprimirContato();
                        }
                    }
                    if (cont == 0) {
                        System.out.println("Sem contato do tipo Amigos cadastrado!");
                    }
                    break;

                case 5:
                    System.out.println("Imprimindo somente o pessoal do trabalho!");
                    cont = 0;
                    for (Contato contato : contatos) {
                        if (contato instanceof Trabalho) {
                            cont++;
                            ((Trabalho) contato).imprimirContato();
                        }
                    }
                    if (cont == 0) {
                        System.out.println("Sem contato do tipo Trabalho cadastrado!");
                    }
                    break;

                case 6:
                    System.out.println("Imprimindo os contatos com filtro!");
                    cont = 0;
                    for (Contato contato : contatos) {
                        if (contato instanceof Familia) {
                            if ((((Familia) contato).parentesco).equals("irmao")) {
                                ((Familia) contato).imprimirContato();
                                cont++;
                            }
                        }
                        if (contato instanceof Amigos) {
                            if (((Amigos) contato).grau == 1) {
                                ((Amigos) contato).imprimirContato();
                                cont++;
                            }
                        }
                        if (contato instanceof Trabalho) {
                            if ((((Trabalho) contato).tipo).equals("colega")) {
                                ((Trabalho) contato).imprimirContato();
                                cont++;
                            }
                        }
                    }
                    if (cont == 0) {
                        System.out.println("Sem contato com esses filtros!");
                    }
                    break;

                case 7:
                    System.out.printf("\nDigite o índice do contato que deseja imprimir: ");
                    indice = sc.nextInt();
                    sc.nextLine();

                    if (indice < 0 || indice >= tamVet) {
                        System.out.println("ERRO! Índice inválido.");
                    } else {
                        if (contatos[indice] instanceof Familia) {
                            Familia familia = (Familia) contatos[indice];
                            familia.imprimirContato();
                        } else if (contatos[indice] instanceof Amigos) {
                            Amigos amigos = (Amigos) contatos[indice];
                            amigos.imprimirContato();
                        } else if (contatos[indice] instanceof Trabalho) {
                            Trabalho trabalho = (Trabalho) contatos[indice];
                            trabalho.imprimirContato();
                        }
                    }
                    break;

                case 8:
                    System.out.println("Saindo do Programa...");
                    break;

                default:
                    System.out.println("ERRO! Opção inválida.");
            }
        } while (escolha != 8);
        sc.close();
    }
}
