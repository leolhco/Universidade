public class Grad extends Estudante implements Exibivel, ToTXT{
    String estagio;
    String  dataInicioEstagio;

    public Grad(String nome, String dataNascimento, String CPF, Float CRA, String estagio, String dataInicioEstagio) {
        super(nome, dataNascimento, CPF, CRA);
        this.estagio = estagio;
        this.dataInicioEstagio = dataInicioEstagio;
    }

    public void setEstagio(String estagio) {
        this.estagio = estagio;
    }

    public void setDataInicioEstagio(String dataInicioEstagio) {
        this.dataInicioEstagio = dataInicioEstagio;
    }

    public String getEstagio() {
        return estagio;
    }

    public String getDataInicioEstagio() {
        return dataInicioEstagio;
    }

    @Override
    public String mostrarDados() {
        return super.mostrarDados() + "\nEstágio: " + estagio + "\nData de Início do Estágio: " + dataInicioEstagio;
    }

    @Override
    public String toTXT() {
       return  this.nome + "," + this.dataNascimento + "," + this.CPF + "," + this.CRA + "," + this.estagio + "," + this.dataInicioEstagio;
    }

}
