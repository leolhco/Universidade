/*Matricula:12311BCC003
  Codigo:003
  Municipio: Abre Campo, MG. 3100302
 */
public class Main {
    public static void main(String[] args) {

        candidato a = new candidato();
        candidato b = new candidato();
        candidato c = new candidato();

        a.setNome("Albidon");
        a.setData("26/12/1952");
        a.setGenero("Masculino");
        a.setBens(3620000);
        a.setReeleicao("Nao");
        a.setPartido(13);
        a.setCargo("Vereador");

        b.setNome("Silas Da Saude");
        b.setData("24/08/1990");
        b.setGenero("Masculino");
        b.setBens(210000);
        b.setReeleicao("Nao");
        b.setPartido(45);
        b.setCargo("Vereador");

        c.setNome("Mamae Noel Do Granada");
        c.setData("26/03/1955");
        c.setGenero("Feminino");
        c.setBens(0);
        c.setReeleicao("Nao");
        c.setPartido(10);
        c.setCargo("Vereador");

        a.mostrar();
        b.mostrar();
        c.mostrar();
    }
}