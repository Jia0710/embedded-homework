#define LED_PIN 2
#define LED_PIN_R 4

// 用于记录时间的变量
unsigned long previousMillis = 0;
// 闪烁间隔 500ms（1秒亮、1秒灭 = 1Hz）
const long interval = 500;

// 记录LED当前状态
int ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
}

void loop() {
  // 获取当前时间
  unsigned long currentMillis = millis();

  // 判断：时间到了就翻转LED
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // 翻转LED状态
    ledState = !ledState;

    // 同时控制两个LED
    digitalWrite(LED_PIN, ledState);
    digitalWrite(LED_PIN_R, ledState);

    // 串口输出
    if (ledState == HIGH) {
      Serial.println("LED ON");
    } else {
      Serial.println("LED OFF");
    }
  }
}