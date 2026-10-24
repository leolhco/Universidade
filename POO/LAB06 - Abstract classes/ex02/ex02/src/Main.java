public class Main {
    public static void main(String[] args) {
           ContaEspecial ce = new ContaEspecial(10000, 0, 1234, 4321);
           ContaCorrente cc = null;
           if(ce.getLimite() == 0){
               cc = ce.paraContaComum();
           }
           if (cc != null)
           System.out.println(cc.toString());
    }
}