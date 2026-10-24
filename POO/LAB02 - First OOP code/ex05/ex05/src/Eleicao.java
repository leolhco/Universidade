public class Eleicao {
    String nomeDaCidade;
    int numEleitores;
    int numCandidatos;
    String estadoDaCidade;
    String regiaoDaCidade;

          public Eleicao(String nomeDaCidade, String estadoDaCidade,
                         String regiaoDaCidade, int numEleitores, int numCandidatos){

              this.nomeDaCidade = nomeDaCidade;
              this.estadoDaCidade = estadoDaCidade;
              this.regiaoDaCidade = regiaoDaCidade;
              this.numEleitores = numEleitores;
              this.numCandidatos = numCandidatos;
          }

          public void mostrar(){
              System.out.println("Nome Da Cidade: "+this.nomeDaCidade);
              System.out.println("Estado Da Cidade: "+this.estadoDaCidade);
              System.out.println("Regiao Da Cidade: "+this.regiaoDaCidade);
              System.out.println("Numero De Eleitores Na Cidade: "+this.numEleitores);
              System.out.println("Numero De Candidatos Na Cidade: "+this.numCandidatos);
              System.out.println();
          }
}
