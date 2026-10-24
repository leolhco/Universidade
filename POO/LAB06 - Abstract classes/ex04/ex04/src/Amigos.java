public class Amigos extends Contato{
     protected int grau;


    public Amigos(String nome, String apelido, String email, String aniversario,
                  int grau) {
        super(nome, apelido, email, aniversario);
        this.grau = grau;

    }

    public int getGrau() {
        return grau;
    }

    public void setGrau(int grau) {
        this.grau = grau;
    }



    @Override
    boolean imprimirContato() {
        System.out.println(super.imprimirBasico() + "\nGrau: " + this.grau +
                "----------------------------------");
        return false;
    }
}
