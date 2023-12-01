#include <esp_now.h>
#include <WiFi.h>
#include <stdio.h>


// Rescrever endereÃ§o MAC com o do emissor da mensagem
uint8_t broadcastAddress[] = { 0xD8, 0xBC, 0x38, 0xE2, 0x48, 0x9C };
String Buffer[9];
int j;
// Estrutura example para enviar dados
// Must match the receiver structure
typedef struct struct_message {
  String S;
  String R;
} struct_message;

// Criar uma struct_message chamada myData
struct_message myData;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro iniciando ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(RecebeDados);
}

void loop() {
}

void RecebeDados(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes Recebidos:   ");
  Serial.println(len);
  Serial.print("Letra S:   ");
  Serial.println(myData.S);
  Serial.print("Letra R:   ");
  Serial.println(myData.R);

  for (int i = 0; i < 9; i++) {
    Serial.print("Buffer:   ");
    Serial.println(Buffer[j]);
    if (Buffer[i] != "a") {

      Buffer[i] = myData.R;
      Serial.print("Valor inserido na ");
      Serial.print(i);
      Serial.print(" posição do Buffer:   ");
      Serial.println(Buffer[i]);
      break;
    }
  }
}