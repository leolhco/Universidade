public class Candidato {
    public String nome;
    public String data;
    public String genero;
    public double bens;
    public String reeleicao;
    public int numPartido;
    public String cargo;

           public Candidato(String nome, String data, String genero, double bens, String reeleicao, int numPartido, String Cargo){
               this.nome = nome;
               this.data = data;
               this.genero = genero;
               this.bens = bens;
               this.reeleicao = reeleicao;
               this.numPartido = numPartido;
               this.cargo = cargo;
           }

           public Candidato(){}

           public void mostrar(){
               System.out.println("Nome: "+this.nome);
               System.out.println("Data de Nascimento: "+this.data);
               System.out.println("Genero: "+this.genero);
               System.out.println("Bens: "+this.bens+" R$");
               System.out.println("O(A) Candidato(a) Esta Tentando a Reeleiçao?: "+this.reeleicao);
               System.out.println("Numero do Partido: "+this.numPartido);
               System.out.println("Cargo Pretendido: "+this.cargo);
               System.out.println();
           }
}
