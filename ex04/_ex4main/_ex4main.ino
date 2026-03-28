#define TOUCH_PIN 4    // 触摸引脚 = 4
#define LED_PIN   2    // LED引脚 = 2

// 触摸与LED变量
int touchVal;
bool ledStatus = false;

// 防抖变量
bool lastTouchState = false;
bool isTriggered = false;
unsigned long lastDebounceMs = 0;
const unsigned long debounceTime = 250;  // 防抖时间

void setup() {
  Serial.begin(115200);        // 开启串口
  pinMode(LED_PIN, OUTPUT);    // 设置LED为输出
  digitalWrite(LED_PIN, ledStatus);  // 初始关灯
}

void loop() {
  // 读取触摸值
  touchVal = touchRead(TOUCH_PIN);
  Serial.print("触摸数值：");
  Serial.println(touchVal);

  // 判断是否触摸
  bool touchedNow = (touchVal < 400);

  // 触摸触发自锁逻辑（防抖）
  if (touchedNow && !lastTouchState && !isTriggered) {
    if (millis() - lastDebounceMs > debounceTime) {
      ledStatus = !ledStatus;               // 翻转LED状态
      digitalWrite(LED_PIN, ledStatus);
      lastDebounceMs = millis();
      isTriggered = true;
    }
  }

  // 松开触摸后重置标志位
  if (!touchedNow) {
    isTriggered = false;
  }

  // 保存上一次状态
  lastTouchState = touchedNow;
}