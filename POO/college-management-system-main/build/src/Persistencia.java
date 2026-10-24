import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class Persistencia {
    private String caminho;

    public Persistencia(String caminho){
        this.setCaminho(caminho);
    }

    public void setCaminho(String caminho){
        this.caminho = caminho;
    }

    public void escreverArq1(Estudante a){
       Grad aux = (Grad) a;

          try ( BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.caminho, true))) {
            
            bufferedWriter.write(aux.toTXT());
            bufferedWriter.newLine();
            
            System.out.println("Dados gravados com sucesso no arquivo: estudante1.txt");
          
        } catch (IOException e) {
            System.out.println("Erro ao gravar os dados: " + e.getMessage());
        }
    }

    public void escreverArq2(Estudante a){
        Grad aux = (Grad) a;
 
           try ( BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.caminho, true))) {
             
             bufferedWriter.write(aux.toTXT());
             bufferedWriter.newLine();
             
             System.out.println("Dados gravados com sucesso no arquivo: estudante2.txt");
           
         } catch (IOException e) {
             System.out.println("Erro ao gravar os dados: " + e.getMessage());
         }
     }

     public void escreverArq3(Estudante a){
        PostGrad aux = (PostGrad) a;
 
           try ( BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.caminho, true))) {
             
             bufferedWriter.write(aux.toTXT());
             bufferedWriter.newLine();
             
             System.out.println("Dados gravados com sucesso no arquivo: estudante3.txt");
             
         } catch (IOException e) {
             System.out.println("Erro ao gravar os dados: " + e.getMessage());
         }
     }

     public void escreverArq4(Professor a){
        Professor aux =  a;
 
           try ( BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.caminho, true))) {
             
             bufferedWriter.write(aux.toTXT());
             bufferedWriter.newLine();
             
             System.out.println("Dados gravados com sucesso no arquivo: professor.tx");
             bufferedWriter.close();
         } catch (IOException e) {
             System.out.println("Erro ao gravar os dados: " + e.getMessage());
         }
     }
}
