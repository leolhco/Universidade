**Exercício 2**

**E. O que acontece quando usamos o valor de k=1 e quando escolhemos um valor de k muito grande?**

Com k=1, o algoritmo considera só o vizinho mais próximo. Por isso, ele fica mais sensível a ruídos e pode acabar classificando errado alguns casos. Já com um k muito grande, ele considera muitos vizinhos e pode acabar generalizando demais, deixando de perceber algumas diferenças entre as classes.

**G. A classe muda em relação à execução com normalização?**

Na base Iris, normalmente as classes não mudam. Isso acontece porque os atributos estão todos na mesma unidade e possuem valores parecidos. Em outras bases, onde os atributos têm escalas muito diferentes, a normalização pode fazer bastante diferença no resultado.

**Exercício 3**

**B. Os três vizinhos mais próximos foram os mesmos?**

Não necessariamente. Como as medidas de distância são diferentes, os três vizinhos mais próximos podem mudar de uma execução para outra.

**C. A classe atribuída foi a mesma?**

Sim, na maioria dos casos. Mesmo que alguns vizinhos mudem, eles geralmente ainda pertencem à mesma classe, principalmente porque as classes da Iris são relativamente bem separadas.

**D. Por que duas medidas de distância podem produzir diferentes conjuntos de vizinhos para uma mesma instância?**

Porque cada medida calcula a distância de uma forma diferente. A Euclidiana considera a distância em linha reta entre os pontos, enquanto a Manhattan soma as diferenças de cada atributo. Por isso, um ponto pode ser considerado mais próximo usando uma medida e não usando a outra.
