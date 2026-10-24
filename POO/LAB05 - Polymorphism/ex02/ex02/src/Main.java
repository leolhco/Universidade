public class Main {
    public static void main(String[] args) {
        Forma[] forma = new Forma[6];
        forma[0] = new Circulo(3);
        forma[1] = new Triangulo(4, 5);
        forma[2] = new Quadrado(4);
        forma[3] = new Esfera(5);
        forma[4] = new Cubo(6);
        forma[5] = new Tetraedro(7);

        forma[0].obterArea();
        forma[1].obterArea();
        forma[2].obterArea();
        forma[3].obterVolume();
        forma[4].obterVolume();
        forma[5].obterVolume();

    }
}