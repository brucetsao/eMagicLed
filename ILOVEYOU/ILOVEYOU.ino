//use Arduino nano w/ATMEGA 168

// Japanino POV by Musashinodenpa

#define LEDPIN 7     // どのピンからLEDをつなぐか
#define SWPIN 6      // スイッチをつなぐピン

// ビットマップ(画像)を定義
byte bitmap[] = {
0b00000000,
0b01000001,
0b01111111,
0b01000001,
0b00000000,
0b00000000,
0b00001110,
0b00011111,
0b00111111,
0b01111110,
0b00111111,
0b00011111,
0b00001110,
0b00000000,
0b00000000,
0b00111111,
0b01000000,
0b01000000,
0b00111111,
0b10000000   // 最後の行は0b10000000(つまり目印)
};


unsigned char pos = 0;  // 現在のビットマップ中の位置
unsigned char i = 0;


void setup() {
// LEDが接続されたピンを出力に設定します
for(char pin = LEDPIN; pin < LEDPIN + 7; pin++) {
  pinMode(pin, OUTPUT);
}
pinMode(SWPIN, INPUT);      // スイッチのピンを入力に
digitalWrite(SWPIN, HIGH);  // 内蔵プルアップ有効
}

void loop() {

if(digitalRead(SWPIN) == LOW) {  // スイッチがオンならば1回描画

  delay(6);  // すぐ始めると詰まって見えるのでちょっと待つ
  pos = 0;

  while(bitmap[++pos] != 0b10000000) {  // ビットマップの端まで繰り返し
    for(i = 0; i < 7; i++) {  // ビットマップの高さの分だけ繰り返し
      // ビットマップデータから1ビットを取り出してピンの状態に反映
      digitalWrite(LEDPIN + 6 - i, (bitmap[pos] >> i) & 0b00000001);
    }
    delay(1);  // LEDが光っている時間
  }

  for(i = LEDPIN; i < LEDPIN + 7; i++) {  // 全ドット、消灯
    digitalWrite(i, LOW);
  }
 }
}

