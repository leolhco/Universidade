import java.util.List;


public class Pedido {

    private String cliente;

    private List<Double> itens;


    public Pedido(String cliente, List<Double> itens) {

        this.cliente = cliente;

        this.itens = itens;

    }


    public void processarPedido() {

        System.out.println("Processando pedido para o cliente: " + cliente);


// Cálculo do subtotal

        double subtotal = 0;

        for (double item : itens) {

            subtotal += item;

        }


// Cálculo do desconto

        double desconto = 0;

        if (subtotal > 100) {

            desconto = subtotal * 0.1;

        }


// Cálculo do imposto

        double imposto = (subtotal - desconto) * 0.08;


// Cálculo do total final

        double total = subtotal - desconto + imposto;


// Exibição do recibo

        System.out.println("Subtotal: R$" + subtotal);

        System.out.println("Desconto: R$" + desconto);

        System.out.println("Imposto: R$" + imposto);

        System.out.println("Total: R$" + total);

    }

}