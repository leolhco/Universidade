<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <title>${empty param.titulo ? "Sistema Biblioteca" : param.titulo}</title>
    <style>
        /* Variáveis de cor para facilitar a manutenção */
        :root {
            --cor-primaria: #1f3a5f;
            --cor-secundaria: #3a639c;
            --cor-fundo: #f4f7f6;
            --cor-texto: #333;
            --cor-branco: #ffffff;
        }
        
        body { 
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
            margin: 0; 
            color: var(--cor-texto);
            background-color: var(--cor-fundo);
            padding-bottom: 70px; /* Garante que o footer fixo não cubra o conteúdo */
        }

        /* Estilo do Topo (Header) */
        header.topo { 
            background: linear-gradient(135deg, var(--cor-primaria) 0%, var(--cor-secundaria) 100%);
            color: var(--cor-branco); 
            padding: 20px 30px; 
            box-shadow: 0 4px 10px rgba(0,0,0,0.15);
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        header.topo h1 { margin: 0; font-size: 24px; font-weight: 600; letter-spacing: 0.5px; }
        header.topo p  { margin: 0; font-size: 14px; opacity: 0.9; font-weight: 300; background: rgba(255,255,255,0.1); padding: 5px 12px; border-radius: 20px; }
        
        /* Container Principal */
        main { 
            padding: 30px; 
            max-width: 1200px; /* Centraliza e limita a largura em telas muito grandes */
            margin: 0 auto; 
            min-height: calc(100vh - 200px); 
        }
        
        /* Formulários e Fieldsets */
        fieldset { 
            margin-bottom: 20px; 
            max-width: 100%; 
            border: 1px solid #dcdcdc; 
            border-radius: 8px; 
            padding: 20px; 
            background: var(--cor-branco); 
            box-shadow: 0 2px 5px rgba(0,0,0,0.02);
        }
        legend { font-weight: bold; color: var(--cor-primaria); padding: 0 10px; font-size: 16px; }
        
        /* Mensagens de Feedback */
        .msg-ok  { color: #1a7f37; font-weight: bold; background: #e6f4ea; padding: 12px; border-radius: 6px; border-left: 4px solid #1a7f37; }
        .msg-erro{ color: #c0392b; font-weight: bold; background: #fce8e6; padding: 12px; border-radius: 6px; border-left: 4px solid #c0392b; }
    </style>
</head>
<body>
    <header class="topo">
        <div>
            <h1>📚 Sistema Gerenciador de Biblioteca</h1>
        </div>
        <div>
            <p>${empty param.titulo ? "Bem-vindo" : param.titulo}</p>
        </div>
    </header>
    <main>