public class Familia extends Contato{
    protected String parentesco;

    public Familia(String nome, String apelido, String email, String aniversario, String parentesco){
        super(nome, apelido, email, aniversario);
        this.parentesco = parentesco;
    }

    @Override
    boolean imprimirContato(){
        System.out.println(super.imprimirBasico() + "\nParentesco: " + this.parentesco
        + "----------------------------------");
        return false;
    }

    public String getParentesco() {
        return parentesco;
    }

    public void setParentesco(String parentesco) {
        this.parentesco = parentesco;
    }
}
