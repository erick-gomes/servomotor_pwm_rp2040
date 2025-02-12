# Projeto PWM: Controle de Servomotor e LED no Raspberry Pi Pico

Este projeto demonstra como controlar um servomotor e um LED de forma sincronizada utilizando PWM (Pulse Width Modulation) no Raspberry Pi Pico. A implementação permite posicionar o servomotor em ângulos pré-definidos, além de realizar transições suaves entre os extremos, com o LED acompanhando a posição para fornecer um feedback visual.

---

## Índice

- [Visão Geral](#visão-geral)
- [Características](#características)
- [Arquitetura e Funcionamento](#arquitetura-e-funcionamento)
- [Exemplo de Código](#exemplo-de-código)
- [Configuração e Compilação](#configuração-e-compilação)
- [Contribuição](#contribuição)
- [Licença](#licença)
- [Contato](#contato)

---

## Visão Geral

O objetivo deste projeto é ilustrar como implementar e sincronizar dois canais de PWM para:
- **Servomotor:** Controla ângulos específicos (0°, 90° e 180°).
- **LED:** Ajusta o brilho de acordo com a posição do servomotor.

Ao iniciar, o servomotor assume três posições fixas, cada uma exibida por 5 segundos. Em seguida, o sistema realiza uma transição suave entre os ângulos extremos (0° e 180°), proporcionando um movimento contínuo e gradual.

---

## Características

- **Precisão no Controle:** Utiliza configurações de PWM para manter uma frequência de ~50Hz, ideal para servomotores.
- **Feedback Visual Integrado:** O LED acompanha o movimento do servomotor, ajudando na visualização das posições.
- **Transição Suave:** Incrementos/decrementos de 5µs garantem uma movimentação gradual e sem solavancos.
- **Código Modular:** Fácil de adaptar e expandir para outras aplicações envolvendo PWM no Raspberry Pi Pico.

---

## Arquitetura e Funcionamento

1. **Inicialização:**  
   O código inicia com a configuração padrão do Pico (stdio_init_all), preparando os canais de PWM para o servomotor e o LED.

2. **Configuração do PWM:**  
   - **Clock e Wrap:** Utiliza um divisor de clock de 100.0 e wrap de 25000, ajustando a frequência para cerca de 50Hz.
   - **Posições Pré-definidas:** São definidas três posições:
     - 0° → 2400µs
     - 90° → 1470µs
     - 180° → 500µs  
   Cada posição é aplicada por 5 segundos.

3. **Movimentação Suave:**  
   Após exibir as posições fixas, o programa entra em um loop contínuo onde o servomotor (e o LED) realizam transições suaves entre 0° e 180°, invertendo o sentido de movimento ao atingir os limites.

---
