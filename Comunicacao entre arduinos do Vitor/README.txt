Comunicação entre Arduinos
Autor: Vitor Giovani Dellinocente
Esses códigos tem por funcao, comunicar dois arduinos entre si através da Serial
Os arduinos utilizados foram os arduinos pro mini.
O arduino ligado ao PC recebe uma mensagem do terminal via serial e envia uma mensagem ao arduino
ligado a ele, assim, ele, dependendo do valor digitado na tela, liga ou desliga o led.
Lembrando que esse código foi produzido para receber três bytes de uma vez, ou seja
quando se mandar o valor 22, mande 022 (por exemplo).