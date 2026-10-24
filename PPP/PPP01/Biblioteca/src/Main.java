import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Main extends Janela implements ActionListener{
    private JButton livros = new JButton("LIVROS");
    private JButton revistas = new JButton("REVISTAS");
    private JButton lista = new JButton("LISTA");
    private JButton videos = new JButton("VIDEOS");

    @Override
    public  void actionPerformed(ActionEvent e) {
        if(e.getSource() == livros) new Livro();
        if(e.getSource() == revistas) new Revista();
        if(e.getSource() == lista) new Lista();
        if(e.getSource() == videos) new Video();
    }

    public Main(){
        super.def1();
        setTitle("Menu Inicial");

        livros.setBounds(80,100,100,50);
       revistas.setBounds(200,100,100,50);
       lista.setBounds(80, 170, 100, 50);
       videos.setBounds(200, 170, 100, 50);
       add(livros);
       add(revistas);
       add(lista);
       add(videos);

       livros.addActionListener(this::actionPerformed);
       revistas.addActionListener(this::actionPerformed);
       lista.addActionListener(this::actionPerformed);
       videos.addActionListener(this::actionPerformed);

    }


    public static void main(String[] args) {
        new Main();
    }


}