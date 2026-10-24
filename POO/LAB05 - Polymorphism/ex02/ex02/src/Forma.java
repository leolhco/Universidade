public class Forma {
    boolean dimensao;

    public void obterArea() {
        System.out.println("Cálculo genérico da área!\n");
    }

    public void obterVolume() {
        System.out.println("Cálculo genérico do volume (somente para formas 3D)!\n");
    }

    public void descricao() {
        System.out.println("Descrição da forma.\n");
    }

    public boolean isDimensao() {
        return dimensao;
    }

    public void setDimensao(boolean dimensao) {
        this.dimensao = dimensao;
    }
}
