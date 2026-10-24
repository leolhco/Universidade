public class FormaBidimensional extends Forma {
    public void bidimensional() {
        System.out.println("Sou uma forma Bidimensional!");
    }

    public FormaBidimensional() {
        this.setDimensao(true);  // Dimensao é bidimensional
    }


    @Override
    public void obterArea() {
        System.out.println("Cálculo de área bidimensional!\n");
    }
}
