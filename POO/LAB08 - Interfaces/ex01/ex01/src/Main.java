public class Main {
    public static void main(String[] args)  {
        
        Produto produtoA = new Produto(003);
        Produto produtoB = new Produto(002);
        Produto produtoC = new Produto(001);

        Produto[] vetProdutos = {produtoA, produtoB, produtoC};

        Cliente clienteA = new Cliente("Leonardo");
        Cliente clienteB = new Cliente("Filipe");
        Cliente clienteC = new Cliente("Arthur");

        Cliente[] vetClientes = {clienteA, clienteB, clienteC};

        Servico servicoA = new Servico(500);
        Servico servicoB = new Servico(400);
        Servico servicoC = new Servico(300);

        Servico[] vetServicos = {servicoA, servicoB, servicoC};

        Classificador classificador = new Classificador();

        System.out.println("Vetor produtos antes da ordenaçao");
        for(Produto produto : vetProdutos){
            produto.mostrar();
        }
        classificador.ordena(vetProdutos);
        System.out.println("Vetor produtos apos a ordenaçao");
        for(Produto produto : vetProdutos){
            produto.mostrar();
        }

        System.out.println("\n=========================================================");

        System.out.println("Vetor clientes antes da ordenaçao");
        for(Cliente cliente : vetClientes){
            cliente.mostrar();
        }
        classificador.ordena(vetClientes);
        System.out.println("Vetor clientes apos a ordenaçao");
        for(Cliente cliente : vetClientes){
            cliente.mostrar();
        }

        System.out.println("\n==========================================================");

        System.out.println("Vetor serviços antes da ordenaçao");
        for(Servico servico : vetServicos){
            servico.mostrar();
        }
        classificador.ordena(vetServicos);
        System.out.println("Vetor serviços apos a ordenaçao");
        for(Servico servico : vetServicos){
            servico.mostrar();
        }

        System.out.println("\n===========================================================");

    }
}
