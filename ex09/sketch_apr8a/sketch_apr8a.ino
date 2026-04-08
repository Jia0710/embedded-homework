#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "臣妾要告发熹贵妃私通";
const char* password = "060710,,gwj";
// ===============================================

WebServer server(80);

const int touchPin = T0;  // D4 = GPIO4

// 主页面
const char* html = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>实时传感器仪表盘</title>
<style>
body{
    text-align:center;
    margin-top:60px;
    font-family:Arial;
}
.value{
    font-size:70px;
    color:#0066ff;
    font-weight:bold;
}
</style>
</head>
<body>
<h2>ESP32 实时触摸传感器仪表盘</h2>
<div class="value" id="val">0</div>

<script>
// 每100ms拉取一次传感器数据
setInterval(async function(){
  let res = await fetch("/data");
  let num = await res.text();
  document.getElementById("val").innerText = num;
}, 100);
</script>
</body>
</html>
)HTML";

// 首页
void handleRoot() {
  server.send(200, "text/html", html);
}

// 数据接口：返回触摸值
void handleData() {
  int val = touchRead(touchPin);
  server.send(200, "text/plain", String(val));
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi OK");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
}
