public class Tetraedro extends FormaTridimensional {
    double lado;

    public Tetraedro(double lado) {
        this.lado = lado;
    }

    @Override
    public void obterArea() {
        double area = lado * lado * Math.sqrt(3);
        System.out.println("Área do Tetraedro: " + area);
    }

    @Override
    public void obterVolume() {
        double volume = (lado * lado * lado) / (6 * Math.sqrt(2));
        System.out.println("Volume do Tetraedro: " + volume);
    }

    @Override
    public void descricao() {
        System.out.println("Eu sou uma pirâmide de base quadrangular.");
    }
}
