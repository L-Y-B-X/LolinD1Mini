#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Wi-Fi热点名称和密码
const char* ssid = "I713R";
const char* password = "OvOsia114514";

// 创建Web服务器对象
ESP8266WebServer server(80);

// GPIO引脚配置（例如D1 Mini的D1引脚对应GPIO5）
const int gpioPin = 16;

void handleToggle() {
    // 将引脚设置为高电平，保持1秒后恢复低电平
    digitalWrite(gpioPin, HIGH);
    delay(1000);
    digitalWrite(gpioPin, LOW);
    server.send(200, "text/plain", "GPIO has toggled!"); // 返回响应
}

void setup() {
    // 启动串口通信以进行调试
    Serial.begin(115200);
    Serial.println();

    // 配置GPIO引脚为输出
    pinMode(gpioPin, OUTPUT);
    digitalWrite(gpioPin, LOW);

    // 创建Wi-Fi热点
    WiFi.softAP(ssid, password);
    Serial.print("Access Point \"");
    Serial.print(ssid);
    Serial.println("\" started");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    // 设置Web服务器的URL路由
    server.on("/toggle", handleToggle);

    // 启动Web服务器
    server.begin();
    Serial.println("Web server started");
}

void loop() {
    // 处理客户端请求
    server.handleClient();

    // 检查是否有客户端连接
    if (WiFi.softAPgetStationNum() > 0) {
        // 若有客户端连接，则将GPIO引脚拉高1秒
        digitalWrite(gpioPin, HIGH);
        delay(1000);
        digitalWrite(gpioPin, LOW);
         ESP.restart();
    } else {
        // 若无客户端连接，则保持GPIO引脚为低电平
        digitalWrite(gpioPin, LOW);
    }
}
