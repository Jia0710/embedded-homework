#define LED_PIN 2
#define LED_PIN_R 26

// 非阻塞延时变量
unsigned long previousMillis = 0;
// 闪烁间隔 500ms（1Hz 频率）
const long interval = 500;

// LED 当前状态
int ledState = LOW;

void setup() {
  // 初始化串口波特率
  Serial.begin(115200);
  // 设置LED引脚为输出模式
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);

  // 开机提示
  Serial.println("LED 闪烁程序已启动");
  Serial.println("使用 millis() 非阻塞延时");
}

void loop() {
  // 获取系统当前时间
  unsigned long currentMillis = millis();

  // 判断时间间隔是否到达
  if (currentMillis - previousMillis >= interval) {
    // 更新上一次触发时间
    previousMillis = currentMillis;
    // 翻转LED状态
    ledState = !ledState;

    // 控制两个LED同步亮灭
    digitalWrite(LED_PIN, ledState);
    digitalWrite(LED_PIN_R, ledState);

    // 串口输出状态信息
    if (ledState == HIGH) {
      Serial.println("LED 状态：ON → 已点亮");
    } else {
      Serial.println("LED 状态：OFF → 已熄灭");
    }
  }
}