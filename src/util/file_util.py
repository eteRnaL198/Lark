from pathlib import Path
from shutil import copy2


def generate_full_path(path):
    """絶対パスを生成

    Arg:
      path (str): プロジェクトのルートからの相対パス
      e.g. "acc/aspect.acc"

    Return:
      str: 引数pathへの絶対パス
    """
    return str(Path(__file__).parents[2]) + "/" + path


def backup_file(path):
    """バックアップファイルを作成
    Args:
      path (str): プロジェクトのルートからの相対パス
    """
    target_path = generate_full_path(path)
    backup_path = target_path + ".bak"
    copy2(target_path, backup_path)
