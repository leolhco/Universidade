import javax.swing.*;
import java.awt.*;

public class Janela extends JFrame {

    public void def(){
        setLayout(new BorderLayout());
        def2();
    }

    public void def1(){
        setLayout(null);
        def2();
    }

    public void def2(){
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }
}
