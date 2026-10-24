public class Triangulo extends FormaBidimensional {
    int base;
    int altura;

    public Triangulo(int base, int altura) {
        this.base = base;
        this.altura = altura;
    }

    @Override
    public void obterArea() {
        int area = (base * altura) / 2;
        System.out.println("Área do Triângulo: " + area);
    }

    @Override
    public void descricao() {
        System.out.println("Figura bidimensional com 3 lados. A área é calculada pela base vezes a altura.\n");
    }
}
