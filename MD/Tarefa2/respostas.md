# Respostas

## Questão 1

### Item 9

O Naive Bayes considera que as características do carro, como preço, manutenção, número de portas e segurança, são independentes. A partir dessas informações, ele calcula a probabilidade de o carro pertencer a cada classe e escolhe a mais provável.

### Item 10

A principal diferença está no tipo de dado que cada um trabalha:

- **CategoricalNB:** é usado para dados categóricos, ou seja, valores que representam categorias. Por isso, é o mais adequado para a base CarEvaluation.

- **GaussianNB:** é usado para dados numéricos contínuos e considera que esses valores seguem uma distribuição normal.

## Questão 2

### Item 12

O primeiro atributo da árvore é `persons`.

### Item 13

Um dos caminhos é: se `persons` for menor ou igual a 0.5, o carro é classificado como inaceitável.

### Item 14

Não. Os dois algoritmos podem produzir previsões diferentes. Isso acontece porque a Árvore de Decisão usa regras de divisão dos dados, enquanto o Naive Bayes calcula probabilidades e considera os atributos independentes. Por isso, dependendo do exemplo, eles podem chegar a classificações diferentes.