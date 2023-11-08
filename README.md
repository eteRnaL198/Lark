# Getting Started

- 実行環境

  ```
  python -V
  Python 3.8.18

  poetry -V
  Poetry (version 1.7.0)
  ```

- 仮想環境の構築

  ```bash
  python -m venv .venv
  source ./env/bin/activate
  ```

- パッケージのインストール

  ```bash
  poetry install
  ```

- 実行

  ```
  $ py src/translator.py /example/execution/greet.acc /example/execution/greet.c
  ```
