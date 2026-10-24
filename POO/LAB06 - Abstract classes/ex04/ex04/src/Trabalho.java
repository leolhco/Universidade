public class Trabalho extends Contato{
    String tipo;

    public Trabalho(String nome, String apelido, String email,
                    String aniversario, String tipo) {
        super(nome, apelido, email, aniversario);
        this.tipo = tipo;
    }

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    @Override
    boolean imprimirContato() {
        System.out.println(super.imprimirBasico() + "\nTipo do Contato no Trabalho: "
                + this.tipo
                + "----------------------------------");
        return false;
    }
}
