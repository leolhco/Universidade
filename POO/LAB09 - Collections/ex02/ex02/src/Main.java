import java.util.ArrayDeque;
import java.util.Deque;
import java.util.NoSuchElementException;

public class Main {
    public static void main(String[] args) {
        
        Deque<Estudante> deque = new ArrayDeque<Estudante>();

        try {
           deque.addFirst(new Estudante("Cleo", "123", "45"));
            deque.offerFirst(new Estudante("Pires", "321", "54"));
           deque.removeFirst();
           deque.removeFirst();
           deque.removeFirst();
        } catch (NoSuchElementException e) {
            System.out.println(" Erro ao tentar remover o primeiro elemento: " + e.getMessage());
        }

        try {
           deque.addLast(new Estudante("Cleo", "123", "45"));
           deque.offerLast(new Estudante("Pires", "321", "54"));
           deque.removeLast();
           deque.removeLast();
           deque.removeLast();
        } catch (NoSuchElementException e) {
            System.out.println(" Erro ao tentar remover o último elemento: " + e.getMessage());
        }
    }
}
