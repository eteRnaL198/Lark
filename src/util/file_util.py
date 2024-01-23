from pathlib import Path
from shutil import copy2


def generate_abs_path(path: str):
    """絶対パスを生成

    Arg:
      path (str): プロジェクトのルートからのパス
      e.g. "/src/util/file_util.py"

    Return:
      str: 引数pathへの絶対パス
    """
    path.lstrip("/")  # 補完を効かせるため"/"付きで受け取り､内部で削除
    return Path(__file__).resolve().parents[2].joinpath(path)


def backup_file(path):
    """バックアップファイルを作成
    Args:
      path (str): ファイルのパス
    """
    backup_path = path + ".bak"
    copy2(path, backup_path)
