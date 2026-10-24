public class Cubo extends FormaTridimensional {
    int lado;

    public Cubo(int lado) {
        this.lado = lado;
    }

    @Override
    public void obterArea() {
        int area = 6 * lado * lado;
        System.out.println("Área do Cubo: " + area);
    }

    @Override
    public void obterVolume() {
        int volume = lado * lado * lado;
        System.out.println("Volume do Cubo: " + volume);
    }

    @Override
    public void descricao() {
        System.out.println("Eu sou uma figura tridimensional com todos os lados de mesmo tamanho!");
    }
}
