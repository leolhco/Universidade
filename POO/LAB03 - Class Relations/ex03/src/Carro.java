public class Carro {
    private String modelo;
    private Motor motor;


    public Carro(String modelo, String tipoMotor) {
        this.modelo = modelo;
        this.motor = new Motor(tipoMotor);
    }


    public String getModelo() {
        return modelo;
    }

    public void setModelo(String modelo) {
        this.modelo = modelo;
    }

    public Motor getMotor() {
        return motor;
    }


    public String toString() {
        return "Carro{" + "modelo='" + modelo + '\'' + ", motor=" + motor + '}';
    }
}
