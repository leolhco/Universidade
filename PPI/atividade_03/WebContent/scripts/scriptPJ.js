function gerarRelatorio() {
  // Captura os valores dos campos
  const nome = document.getElementById("nome").value.trim();
  const responsavel = document.getElementById("responsavel").value.trim();
  const inicio = document.getElementById("inicio").value.trim();
  const entrega = document.getElementById("entrega").value.trim();
  const categoria = document.getElementById("categoria").value;

  // alerta de validação
  if (!nome || !responsavel || !inicio || !entrega || !categoria) {
    alert("Preencha todos os campos!");
    return;
  }

  // relatório
  let relatorioHTML = `
    <h3>Relatório do Cadastro</h3>
    <p><strong>Nome do Projeto:</strong> ${nome}</p>
    <p><strong>Responsável:</strong> ${responsavel}</p>
    <p><strong>Data de Início:</strong> ${inicio}</p>
    <p><strong>Data de Entrega:</strong> ${entrega}</p>
    <p><strong>Categoria:</strong> ${categoria}</p>
  `;

  // Escolhe imagem conforme categoria
  let imgSrc = "";
  switch (categoria) {
    case "Web":
      imgSrc = "./img/web.png";
      break;
    case "Mobile":
      imgSrc = "./img/mobile.png";
      break;
    case "IA":
      imgSrc = "./img/ia.png";
      break;
  }

  relatorioHTML += `<img src="${imgSrc}" alt="${categoria}" style="width:150px;margin-top:10px;">`;

  // Exibe relatório
  document.getElementById("relatorio").innerHTML = relatorioHTML;
}
