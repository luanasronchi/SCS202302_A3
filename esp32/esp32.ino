#include <esp_now.h>
#include <WiFi.h>
#include <stdio.h>


// Rescrever endereÃ§o MAC com o do emissor da mensagem
uint8_t broadcastAddress[] = { 0xD8, 0xBC, 0x38, 0xE2, 0x48, 0x9C };
String Buffer[9] = {"null","null","null","null","null","null","null","null","null"};
int j;
String solicitacao;
SemaphoreHandle_t mutex = xSemaphoreCreateMutex();
// Estrutura example para enviar dados
// Must match the receiver structure

typedef struct {
  String emissor_S;
  String emissor_R;
} dado_emissor;


typedef struct {
  String recebedor_S;
  String recebedor_R;
} dado_recebedor;

dado_emissor dadoE;
dado_recebedor dadoR;


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

void RecebeDados(const uint8_t *mac_addr, const uint8_t *rxdata, int len){
  memcpy(&dadoR, rxdata, sizeof(dadoR));
  Serial.println("Recebido" );
  Serial.println(dadoR.recebedor_S);
  Serial.println(dadoR.recebedor_R);


  if(solicitacao == "entrada"){
  xSemaphoreTake(mutex, portMAX_DELAY);
    InsereBuffer(myData.R);
  xSemaphoreGive(mutex);
  }
  else if(solicitacao == "saida"){
  xSemaphoreTake(mutex, portMAX_DELAY);
    RetiraBuffer(myData.R);
  xSemaphoreGive(mutex);
  }

  
}
void InsereBuffer(String valor){
  for (int i = 0; i < 9; i++) {
      Serial.print("Buffer:   ");
      Serial.println(Buffer[i]);
      if (Buffer[i] == "null") {
        Buffer[i] = myData.R;
        Serial.print("Valor inserido na ");
        Serial.print(i);
        Serial.print(" posição do Buffer:   ");
        Serial.println(Buffer[i]);
        break;
      }
    }
}

void RetiraBuffer(String valor){
  for (int i = 0; i < 9; i++){
    Serial.print("Buffer:   ");
    Serial.println(Buffer[i]);
    if (Buffer[i] == letra) {
      Serial.print("Valor retirado da ");
      Serial.print(i);
      Serial.print(" posição do Buffer:   ");
      Serial.println(Buffer[i]);
      Buffer[i] = "null";
      
      break;
    }
  }
}

