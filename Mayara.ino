#include <UIPEthernet.h>
#include <PubSubClient.h>

const int qtdeLEDs = 5;
const int pinosLEDs[] = {7,3,4,5,6};
const int pinoPotenc = 0;
int potenciometro = 0;
int bargraph = 0;

byte mac[] = {0xDE , 0xAD, 0xBE, 0xEF, 0xAA,  0xAB};

char* servidor_mqtt = "m14.cloudmqtt.com";
int porta_mqtt = 14072;

long lastReconnectAttempt = 0;

void mensagem_mqtt (char* topic, byte* payload, unsigned int length) {

  // pegar primeiro byte do payload
  byte msg = payload[0];
  msg = msg - '0';

  int ledsAAcender = 0;
  switch(msg) {
    case 1:
      ledsAAcender = 1;
    break;
    case 2:
      ledsAAcender = 2;
    break;
       case 3:
      ledsAAcender = 3;
    break;
      case 4:
      ledsAAcender = 4;
    break;
      case 5:
      ledsAAcender = 5;
    break;
  }

  for(int i = 0; i < qtdeLEDs; i++) {
    digitalWrite(pinosLEDs[i], i < ledsAAcender ? HIGH : LOW);
  }
}

EthernetClient ethernet_client;
PubSubClient pubsub(servidor_mqtt, porta_mqtt, mensagem_mqtt, ethernet_client);

boolean  reconnect()
{
  Serial.println("Reconectando ...");
  if (pubsub.connect("Murilo", "user", "123"))
  {

    Serial.println("Conetando");
    Serial.println("Enviando Temperatura");
    Serial.println("payload");
    pubsub.subscribe("estrelas");
    
  }

  return pubsub.connected();
}



void setup() {
  Serial.begin(9600);
for (int i=0; i<=qtdeLEDs; i++) {
    pinMode(pinosLEDs[i], OUTPUT);
  }
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Não pegou enrdereço via DHCP");
  }

  else
  {
    Serial.println("Pegou endereço via DHCP");
    Serial.println(Ethernet.localIP());

  }

 
                     if (pubsub.connect("Murilo", "user", "123"))
                   {
                     Serial.println("Conectado");
    pubsub.subscribe("estrelas");
                   }

                     else
                   {
                     Serial.println("MQTT Não esta conectado");
                   }
                   
}


void loop() {

  if (!pubsub.connected())
  {
    long now = millis();
    if (now - lastReconnectAttempt > 5000)
    {
      Serial.println("Reconectando ...");
      lastReconnectAttempt = now;
      if (reconnect())
      {
        lastReconnectAttempt = 0;
      }

    }
  }
  else
  {
    pubsub.loop();
  }
}
