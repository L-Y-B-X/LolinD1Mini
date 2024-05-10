#include <U8g2lib.h>
#include <Wire.h>

#define SCL 5
#define SDA 4

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /*clock=*/SCL, /*data=*/SDA, /*reset=*/U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print(); // enable UTF8 support for the Arduino print() function
}

void loop() {
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 15); //指定显示位置
    u8g2.print("  Hello World!"); //使用print来显示字符串
  } while (u8g2.nextPage());
  delay(1000);
}
