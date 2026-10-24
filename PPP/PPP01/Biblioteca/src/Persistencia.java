import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

public class Persistencia {
    private String caminho;

    public Persistencia(String caminho){
        this.caminho = caminho;
    }

    public void escreverArq1(Item a){
        ItemLivro aux = (ItemLivro) a;

        try ( BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.caminho, true))) {

            bufferedWriter.write(aux.salvar());
            bufferedWriter.write("\n");

        } catch (IOException e) {
            System.out.println("Erro ao gravar os dados: " + e.getMessage());
        }
    }

    public void escreverArq2(Item a){
        ItemRevista aux = (ItemRevista) a;

        try ( BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.caminho, true))) {

            bufferedWriter.write(aux.salvar());
            bufferedWriter.write("\n");

        } catch (IOException e) {
            System.out.println("Erro ao gravar os dados: " + e.getMessage());
        }
    }

    public void escreverArq3(Item a){
        ItemVideo aux = (ItemVideo) a;

        try ( BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(this.caminho, true))) {

            bufferedWriter.write(aux.salvar());
            bufferedWriter.write("\n");

        } catch (IOException e) {
            System.out.println("Erro ao gravar os dados: " + e.getMessage());
        }
    }
}
