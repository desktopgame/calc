# calc
calc は bison による電卓の実装です  
beacon言語の一部の構文をテストするために作ったリポジトリ

# コマンドライン引数
一応ちゃんとした電卓としても使えるようにした  

## -t
実行時ディレクトリの .calc を Cプログラムに変換して実行します。
## -d 式
引数の式をASTとしてダンプします。
## -e 式
引数の式を計算して出力します。

# 対応する演算子
[【Ｃ言語講座】演算子一覧表](http://www.bohyoh.com/CandCPP/C/operator.html)に書いてあるのを参考に実装しています。  
関数呼び出しやメンバアクセスは未実装。