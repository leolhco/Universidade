import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Revista extends Janela implements ActionListener{

    private JLabel revistas = new JLabel("REVISTAS");
    private JLabel titulo = new JLabel("TITULO:");
    private JLabel org = new JLabel("ORG.:");
    private JLabel vol = new JLabel("VOL.:");
    private JLabel nro = new JLabel("NRO.:");
    private JLabel ano = new JLabel("ANO:");
    private JTextField c1 = new JTextField(10);
    private JTextField c2 = new JTextField(10);
    private JTextField c3 = new JTextField(5);
    private JTextField c4 = new JTextField(5);
    private JTextField c5 = new JTextField(5);
    private JButton incluir = new JButton("INCLUIR");
    private JButton livros = new JButton("LIVROS");
    private JButton listagem = new JButton("LISTAGEM");
    private JButton videos = new JButton("VIDEOS");
    private JPanel p1 = new JPanel();
    private JPanel p2 = new JPanel();
    private JPanel p3 = new JPanel();
    private Font fonte1 = new Font("Arial", Font.BOLD, 50);
    private Font fonte2 = new Font("Arial", Font.BOLD, 30);

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == videos) new Video();
        if(e.getSource() == listagem) new Lista();
        if(e.getSource() == livros) new Livro();

        if(e.getSource() == incluir){
            try {

                String str1 = c1.getText().trim();
                String str2 = c2.getText().trim();
                String str3 = c3.getText().trim();
                String str4 = c4.getText().trim();
                String str5 = c5.getText().trim();

                if (str1.isEmpty() || str2.isEmpty() || str3.isEmpty() || str4.isEmpty() || str5.isEmpty()) {
                    throw new IllegalArgumentException();
                }


                Item aux = new ItemRevista(str1, str5, str2, str3, str4);
                Persistencia p = new Persistencia("src/Catalogo");
                p.escreverArq2(aux);

                JOptionPane.showMessageDialog(null, "Cadastro concluido com sucesso!", "Sucesso", JOptionPane.INFORMATION_MESSAGE);

                c1.setText("");
                c2.setText("");
                c3.setText("");
                c4.setText("");
                c5.setText("");

            } catch (IllegalArgumentException ex) {

                JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos!", "Erro de entrada", JOptionPane.ERROR_MESSAGE);

            }
        }
    }

    public Revista() {
        incluir.addActionListener(this::actionPerformed);
        listagem.addActionListener(this::actionPerformed);
        livros.addActionListener(this::actionPerformed);
        videos.addActionListener(this::actionPerformed);

        super.def();
        setTitle("REVISTAS");

        add(p1, BorderLayout.NORTH);
        this.p1.setBackground(Color.GRAY);

        this.revistas.setOpaque(true);
        this.revistas.setBackground(Color.GRAY);
        this.revistas.setForeground(Color.BLACK);
        this.revistas.setFont(fonte1);
        p1.add(revistas);

        add(p2, BorderLayout.CENTER);
        this.p2.setLayout(new GridLayout(5,2,10,10));
        this.p2.setBackground(Color.GRAY);

        this.titulo.setOpaque(true);
        this.titulo.setForeground(Color.BLACK);
        this.titulo.setBackground(Color.GRAY);
        this.titulo.setFont(fonte2);

        this.org.setOpaque(true);
        this.org.setForeground(Color.BLACK);
        this.org.setBackground(Color.GRAY);
        this.org.setFont(fonte2);

        this.vol.setOpaque(true);
        this.vol.setForeground(Color.BLACK);
        this.vol.setBackground(Color.GRAY);
        this.vol.setFont(fonte2);

        this.nro.setOpaque(true);
        this.nro.setForeground(Color.BLACK);
        this.nro.setBackground(Color.GRAY);
        this.nro.setFont(fonte2);

        this.ano.setOpaque(true);
        this.ano.setForeground(Color.BLACK);
        this.ano.setBackground(Color.GRAY);
        this.ano.setFont(fonte2);

        this.p2.add(titulo);
        this.p2.add(c1);
        this.p2.add(org);
        this.p2.add(c2);
        this.p2.add(vol);
        this.p2.add(c3);
        this.p2.add(nro);
        this.p2.add(c4);
        this.p2.add(ano);
        this.p2.add(c5);

        add(p3, BorderLayout.SOUTH);
        this.p3.setLayout(new FlowLayout(FlowLayout.CENTER,10,3));
        this.p3.setBackground(Color.GRAY);

        this.p3.add(incluir);
        this.p3.add(livros);
        this.p3.add(videos);
        this.p3.add(listagem);

    }

}


