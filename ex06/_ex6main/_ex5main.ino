// 作业6：警车双闪灯
// 引脚：黄灯=2，红灯=4

const int ledYellow = 2;
const int ledRed    = 4;

const int freq = 5000;
const int resolution = 8;
const int interval = 8;

int duty = 0;
int fadeStep = 1;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  ledcAttach(ledYellow, freq, resolution);
  ledcAttach(ledRed, freq, resolution);
  Serial.println("=== 警车双闪已启动 ===");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    duty += fadeStep;

    if (duty >= 255) {
      duty = 255;
      fadeStep = -1;
      Serial.println("黄灯亮，红灯暗");
    }

    if (duty <= 0) {
      duty = 0;
      fadeStep = 1;
      Serial.println("黄灯暗，红灯亮");
    }

    ledcWrite(ledYellow, duty);
    ledcWrite(ledRed, 255 - duty);
  }
}