public class FormaTridimensional extends Forma{
      public void tridimensional(){
          System.out.println("Sou uma forma Tridimensional!");
      }

      public void obterVolume(){
          System.out.println("Na maioria das vezes, volume e area da base X altura.");
      }

      public FormaTridimensional(){
          this.setDimensao(false);
      }
}
