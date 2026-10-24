/*Matricula:12311BCC003
  Codigo:003
  Municipio: Abre Campo, MG. 3100302
 */
public class Main {
    public static void main(String[] args) {
        Candidato a = new Candidato("Albidon", "26/12/1952",
                "Masculino", 3620000, "Nao", 13, "Vereador");

        Candidato b = new Candidato("Silas Da Saude", "24/08/1990",
                "Masculino", 210000, "Nao", 45, "Vereador");

        Candidato c = new Candidato("Mamae Noel Do Granada", "26/03/1955",
                "Feminino", 0, "Nao", 10, "Vereador");

        a.mostrar();
        b.mostrar();
        c.mostrar();
    }
}