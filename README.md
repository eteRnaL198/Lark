# Usage

```
pip install pecten-0.9.0.tar.gz
pecten aspect.acc base.c
```

# To Contribute

## Getting Started

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
  ```

- パッケージのインストール

  ```bash
  poetry install
  ```

- 実行

  ```
  $ poetry run pecten example/execution/greet.acc example/execution/greet.c
  ```

  または

  ```
  $ source ./venv/bin/activate
  $ py src/translator.py example/execution/greet.acc example/execution/greet.c
  ```

## Build

```
poetry build
```
