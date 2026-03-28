#define TOUCH_PIN 4
#define LED_PIN 2

int touchVal;
bool ledStatus = false;

bool lastTouchState = false;
bool isTriggered = false;
unsigned long lastDebounceMs = 0;
const unsigned long debounceTime = 250;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledStatus);

  // 开机提示
  Serial.println("===== 触摸开关已启动 =====");
}

void loop() {
  // 读取触摸值
  touchVal = touchRead(TOUCH_PIN);
  Serial.print("触摸数值：");
  Serial.println(touchVal);

  bool touchedNow = (touchVal < 400);

  // 触摸自锁逻辑（优化防抖）
  if (touchedNow && !lastTouchState && !isTriggered) {
    if (millis() - lastDebounceMs > debounceTime) {
      ledStatus = !ledStatus;
      digitalWrite(LED_PIN, ledStatus);
      lastDebounceMs = millis();
      isTriggered = true;

      // 串口输出状态
      if (ledStatus) {
        Serial.println("✅ LED 已点亮");
      } else {
        Serial.println("❌ LED 已熄灭");
      }
    }
  }

  // 松开后重置触发
  if (!touchedNow) {
    isTriggered = false;
  }

  lastTouchState = touchedNow;
}