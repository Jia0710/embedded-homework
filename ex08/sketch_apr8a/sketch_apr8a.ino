#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "臣妾要告发熹贵妃私通";
const char* password = "060710,,gwj";

WebServer server(80);

const int ledPin = 2;      // D2
const int touchPin = T0;   // D4 (GPIO4)

bool isArmed = false;
bool isAlarming = false;

// 网页
const char* html = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
</head>
<body style="text-align:center; font-size:24px;">
<button onclick="fetch('/arm')" style="background:red;color:white;padding:20px 40px;font-size:20px;">布防</button>
<br><br>
<button onclick="fetch('/disarm')" style="background:green;color:white;padding:20px 40px;font-size:20px;">撤防</button>
</body>
</html>
)HTML";

void handleRoot() { server.send(200, "text/html", html); }
void handleArm()  { isArmed = true; isAlarming = false; digitalWrite(ledPin, LOW); server.send(200,"text/plain","ARM"); }
void handleDisarm(){ isArmed = false; isAlarming = false; digitalWrite(ledPin, LOW); server.send(200,"text/plain","DISARM"); }

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  // 开机亮1秒测试
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
}

void loop() {
  server.handleClient();

  // 布防状态检测触摸
  if (isArmed) {
    int v = touchRead(touchPin);
    Serial.print("触摸值："); Serial.println(v);

    // ====================== 修复在这里！阈值放大到 200！ ======================
    if (v < 500) {
      isAlarming = true;
      Serial.println("!!! 报警触发 !!!");
    }
  }

  // 报警闪烁
  if (isAlarming) {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
  }
}