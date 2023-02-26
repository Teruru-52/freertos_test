# MicroMouse Control Module

マイクロマウス制御の実装のうち，モジュール化できる部分をまとめたC++ライブラリ．

--------------------------------------------------------------------------------

## 機能一覧

- 曲線加速の軌道生成 (ctrl::AccelDesigner)
- スラロームの軌道生成 (ctrl::slalom::Shape)
- 軌道追従制御器 (ctrl::TrajectoryTracker)
- フィードバック制御器 (ctrl::FeedbackController)

--------------------------------------------------------------------------------

## マイコンでの使用方法

- このライブラリは，C++ヘッダーファイルのみから構成されている．
- このリポジトリをダウンロードして， `include` ディレクトリからソースコードを参照して使用する．
- 必要に応じてコンパイルオプションに， `-std=c++14` を設定する．

--------------------------------------------------------------------------------

## コンピュータでの使用例

詳しくは [こちら](docs/computer.md)

--------------------------------------------------------------------------------

## C++クラス設計

詳しくは [こちら](docs/class_design.md)