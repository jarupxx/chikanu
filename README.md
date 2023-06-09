# chikanu
文字列置換U v0.4u by jarupxx

Windows 11/10専用

これより前のWindowsでは動作しません。

**ファイルを直接書き換えるので、必ずバックアップをとってから使って下さい。**

**本プログラムはUTF-8のテキスト向けです。Shift-JISにはオリジナルの[文字列置換](https://www.vector.co.jp/soft/win95/util/se271454.html)を使ってください。**

## 何をするもの？
ファイルの中の文字列を違う文字列に一括変換するためのコマンドラインプログラムです。

空白や改行も文字の一種なので、UNIXやMacintoshとの改行コードの変換や、空白の削除にも使えます。バイナリファイルでも使えます。ソースも添付します。

なお、メモリに読み込めないほど巨大なファイルは扱えません。

## どうやって使うの？
コマンドプロンプトから、
chikan 処理すべきファイル名 置換元文字列 置換先文字列
と打ち込んでください。改行や空白など、コマンドラインから打ち込みにくい文字は、次のように指定します。

```
/n 改行(/x0Aでも可)
/r 改行(/x0Dでも可)
/s 空白
// /
/m >
/h <
/d $
/= ~
/t タブ
/q ?
/a *
/X**=16進数指定
/x**=16進数指定
```

## 使用例

**例１：「chikan.txt」というファイル中の「ファイル」を「ふぁいる」に変更したい**
```
chikan chikan.txt ファイル ふぁいる
```
**例２：全ての改行の直前に「★」を入れたい。**
```
chikan chikan.txt /r/n ★/r/n
```
※Windowsファイルの改行は「/r/n」の2文字で成り立っていることに注意して下さい。

**例３：sample.txtというファイルの0x01を0x00に変換したい。**
```
chikan sample.txt /x01 /x00
```
**例４：多数の空白を一つの空白にしたい。**
```
chikan sample.txt /s/s /s
```
を何度か実行します。

**例５：バッチファイルの作成**
```
dir /b >tmp.bat

chikan tmp.bat /r/n moto/ssaki/r/nchikan/s
```
**例６：Linuxの改行をWindowsの改行に直す**
```
chikan sample.txt /n /r/n
```
**例７：メールファイルに引用符を付ける**
```
chikan sample.txt /r/n /r/n/m
```
## 制限
NULLへの置換はできません。対象先も対象元も、文字列は1以上の長さが必要です。また、ファイルを丸ごとメモリに読み込んでから作業するので、メモリに入りきらないような巨大ファイルは扱えません。ワイルドカードの展開は問題が多いので削除しました。例５のようにchikanを利用してchikanのバッチファイルを作ると便利です。以前のWindowsでは修正が反映されないため、Windows 10 バージョン 1903 (2019年5月の更新プログラム)以降必須です。

## 免責・転載条件
本ソフトウェアは星野香奈様制作の文字列置換に[UTF-8 コード ページを使用するマニフェスト](https://learn.microsoft.com/ja-jp/windows/apps/design/globalizing/use-utf8-code-page)を追加しただけですから、著作権は星野香奈様に帰属します。
転載改変は自由です。フリーソフトであり、自己責任で使ってください。何か問題が起こっても補償はできません。作者への連絡先は、
https://github.com/jarupxx/chikanu/issues です。
Visual Studio 2022でコンパイルしました。

## 謝辞
原作者の星野香奈様、バグレポート、機能拡張の提案をしてくださった皆様、ありがとうございます。
