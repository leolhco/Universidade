public class Quadrado extends FormaBidimensional {
    int lado;

    public Quadrado(int lado) {
        this.lado = lado;
    }

    @Override
    public void obterArea() {
        int area = lado * lado;
        System.out.println("Área do Quadrado: " + area);
    }

    @Override
    public void descricao() {
        System.out.println("Figura bidimensional com 4 lados iguais.\n");
    }
}
