import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Queue;
import java.util.Stack;


public class Main {
    public static void main(String[] args)  {
     ArrayList<Estudante> estudantes1 = new ArrayList<Estudante>();
      
     estudantes1.add(new EstudanteDoutorado("Bruno", "Sala 1B-123",
      "BCC", "Processamento de Imagens",  "Processamento Digital de Imagens"));

      estudantes1.add(new EstudanteDoutorado("Augusto", "Sala 1B-123",
      "BCC", "Processamento de Imagens",  "Processamento Digital de Imagens"));

      estudantes1.add(new EstudanteDoutorado("Nassif", "Sala 1B-123",
      "BCC", "Processamento de Imagens",  "Processamento Digital de Imagens"));

      estudantes1.add(new EstudanteDoutorado("Travençolo", "Sala 1B-123",
      "BCC", "Processamento de Imagens",  "Processamento Digital de Imagens"));


      System.out.println("ArrayList antes da Ordenaçao por nome");

      for(Estudante estudante : estudantes1){
        if (estudante instanceof EstudanteDoutorado){
            ((EstudanteDoutorado) estudante).print();
        }
      }

      Collections.sort(estudantes1);

      System.out.println("\n" + "ArrayList apos a Ordenaçao por nome");

      for(Estudante estudante : estudantes1){
        if (estudante instanceof EstudanteDoutorado){
            ((EstudanteDoutorado) estudante).print();
        }
      }

     
    
      estudantes1.clear();

     System.out.println("================================================================================");

     Stack<Estudante> estudantes3 = new Stack<Estudante>(); 

     estudantes3.push(new EstudanteDoutorado("Bruno", "Sala 1B-123",
      "BCC", "Processamento de Imagens",  "Processamento Digital de Imagens"));

      estudantes3.push(new EstudanteDoutorado("Augusto", "Sala 1B-123",
      "BCC", "Processamento de Imagens",  "Processamento Digital de Imagens"));

      estudantes3.push(new EstudanteDoutorado("Nassif", "Sala 1B-123",
      "BCC", "Processamento de Imagens",  "Processamento Digital de Imagens"));

      estudantes3.push(new EstudanteDoutorado("Travençolo", "Sala 1B-123",
      "BCC", "Processamento de Imagens",  "Processamento Digital de Imagens"));

      for(Estudante estudante : estudantes3){
        if (estudante instanceof EstudanteDoutorado){
            ((EstudanteDoutorado) estudante).print();
        }
      }

      estudantes3.clear();

    
   } 
}
