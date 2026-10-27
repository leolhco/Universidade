# Snake 3D

Snake em 3D construído sobre a engine de rasterização por software (C + SDL2).
A engine não foi modificada — o jogo vive em módulos próprios que só consomem
sua API pública.

## Compilar e jogar

Requer SDL2 (`libsdl2-dev`).

```
make
make run      # ou ./snake3d
```

## Controles

- Setas ou `WASD` — mover a cobra
- `R` — reiniciar
- `ESC` — sair

O placar aparece no título da janela.

## Como funciona

- **Um único mesh de cubo** (`cube.obj`) é carregado uma vez e reutilizado por
  todos os segmentos da cobra, pela maçã, pelo chão e pelas paredes — muda só a
  matriz de transformação.
- **Câmera fixa** top-down levemente inclinada. A `view` é calculada uma vez e
  nunca mais muda.
- **Iluminação Phong** (ambient + diffuse + specular), reaproveitando o
  `shader_phong` da engine.
- **Movimento em grade** discreto, um passo por tick.
- **Animação de "tombo"**: em vez de deslizar, cada cubo rola 90° em torno da
  aresta de contato com o chão até a próxima célula. Numa curva, cada segmento
  tomba na direção do seu próprio deslocamento. É puramente visual — a lógica
  continua discreta.

## Módulos

| Arquivo         | Responsabilidade                                             |
|-----------------|--------------------------------------------------------------|
| `arena.{h,c}`   | grade, conversão célula↔mundo, limites (parede)              |
| `snake.{h,c}`   | estado e lógica da cobra (passo, crescer, colisões)          |
| `game.{h,c}`    | estado do jogo, maçã, tick, e desenho da cena                |
| `render_util.{h,c}` | projeção/viewport, matriz de tombo, draw de cubo (Phong) |
| `main.c`        | SDL, câmera, loop, input, placar                             |

Os demais arquivos (`vec`, `mat`, `canvas`, `camera`, `mesh`, `obj`, `raster`,
`shader`, `program`) são a engine original, intactos.
