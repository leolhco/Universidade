public class Esfera extends FormaTridimensional {
    float raio;

    public Esfera(float raio) {
        this.raio = raio;
    }

    @Override
    public void obterArea() {
        float area = 4 * (float)Math.PI * raio * raio;
        System.out.println("Área da Esfera: " + area);
    }

    @Override
    public void obterVolume() {
        float volume = (4 / 3) * (float)Math.PI * raio * raio * raio;
        System.out.println("Volume da Esfera: " + volume);
    }

    @Override
    public void descricao() {
        System.out.println("Eu sou uma figura tridimensional com raio e diâmetro!");
    }
}
