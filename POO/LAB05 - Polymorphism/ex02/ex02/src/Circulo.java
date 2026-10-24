public class Circulo extends FormaBidimensional {
    private int raio;

    public Circulo(int raio) {
        this.raio = raio;
    }


    @Override
    public void obterArea() {
        double area = Math.PI * raio * raio;
        System.out.println("Área do Círculo: " + area);
    }

    @Override
    public void descricao() {
        System.out.println("Figura bidimensional com um raio.\n");
    }
}
