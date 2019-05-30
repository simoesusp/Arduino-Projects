# COMANDOS AT

-> 0 BT do Bileky e' o HM10

WARNING: Alguns modulos tem que ligar NL + CR, em outros so' o  NR  e em outros NENHUM (o do Bileky e' nenhum)


Comandos:
AT   retorna OK
AT+HELP?  retorna o site com o manual

Mudar pra MASTER:
AT+ROLE?   retorna 0 (slave) ou 1 (Master)
AT+ROLE1   muda pra master
AT+IMME?      retorna 0 (comeca a trabalhar imediatamente!!!) ou 1 (Nao faz outra coisa ate receber comandos AT)
AT+IMME1

Depois de Mudar pra MASTER:
AT+DISC?   escaneia todos os modulos BT e retorna seus MACs
AT+CONN0   conecta-se ao primeiro modulo retornado no DISC 1, 2, 3... pra se conectar nos outros

