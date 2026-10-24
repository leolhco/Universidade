public class UsaBanco {
    public static void main(String[] args) {
           ContaEspecial ce1 = new ContaEspecial(10000, 100, 1234, 4321);
           ContaEspecial ce2 = new ContaEspecial(10000, 200, 1234, 4321);
           ContaEspecial ce3 = new ContaEspecial(10000, 300, 1234, 4321);
           ContaEspecial ce4 = new ContaEspecial(10000, 400, 1234, 4321);

           System.out.println(ce1.toString() +"\n\n\n"+ ce2.toString() +"\n\n\n"+ ce3.toString() +"\n\n\n"+ ce4.toString());

           ce1.debitaValor(5000);
           ce2.debitaValor(4000);
           ce3.debitaValor(3000);
           ce4.debitaValor(2000);

        System.out.println(ce1.toString() +"\n\n\n"+ ce2.toString() +"\n\n\n"+ ce3.toString() +"\n\n\n"+ ce4.toString());

    }
}