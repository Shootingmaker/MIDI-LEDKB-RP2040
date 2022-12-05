# MIDI-Lighting-Keyboard_APA102_RP2040

##　なにしたいの＞＞＞ MIDIピコピコLED

###　使用boardライブラリ：Raspberry Pi Pico /RP2040 by Eaele F.Philhower,III

###　使用ライブラリ
FastLED3.5　	： RP2040　PIO実装を手動マージ。正常に動作
Control Surface	：MIDIとかアナログINとかの便利なAPIみたいなやつ。今回はこれに沼っている

[Board選択]＞Raspberry Pi Pico /RP2040＞Raspberry Pi Pico（無印）


[書き込み注意]
書き込むときReset＆Boot同時押し。
UF.2boardをいちいち選択する必要あり。
 
◆現在の作業ファイル。
10_Note-FastLED-ColorMapper_APA102_Rpico


//やりたいこと　TODO

1.Reverse Array　LEDS
配列コピー、再度反転コピーにで実装済み。
しかし、midiled.getDirty()によって、配列の変化を検知され
発火するたびに再度、反転してしまう。


2.1-16 CHANNEL LISSEN　now only 
NoteRangeFastLEDによってリッスンできるチャンネルを増やしたい。要調査


3.add Color mode setting　光るパターンModeを追加したい。

3-1.ColorMode FASTLED Pre-defined color palletes :http://fastled.io/docs/3.1/colorpalettes_8cpp_source.html
チャンネルごとに、FastLEDのプリセットカラーを指定するモード


3-2.ColorMode RainbowColorMapper
レインボーを右から左。

3-3.ColorMode Synthetia :https://github.com/tttapa/Control-Surface/issues/676
チャンネルごとに、色設定できるやつの別プリセットVer

 Differentiate that if the note is received on channel 0, it lights up a White LED
 If the note is received on Channel 1-5,11. the LEDS for this light up in Green
 If the note is received on Channel 6-10,12. the LEDS for this light up in Blue
