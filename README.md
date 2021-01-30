このツールは旧 INFINITAS ランチャーにパスワードを自動で入力する目的で作成されたツールです
しかしその実態は単純にファイルに記載されたパスワードを自動でキー入力をするだけのツールなので FF などへの自動ログインにも使用できます

旧 INFINITAS での使い方

1. password.txt の 1 行目に INFINITAS のパスワードを設定します（password.txt はパスワードが書かれた一行のみのファイルになります）
1. INFINITAS Launcher をあらかじめ起動しておきます
1. 本ツール(SendPassword.exe) を実行します
1. 本ツール(SendPassword.exe) を実行後、3 秒以内に INFINITAS Launcher のパスワードの項目をクリックして、フォーカスを当てます
1. 本ツール(SendPassword.exe) を実行後、3 秒後に、INFINITAS Launcher のパスワードに password.txt の内容が入力されます

```
@echo off

start bm2dx_launcher.exe
SendPassword.exe
```

こんな bat ファイルを作っておくと更に便利だと思います。

補足
このツールは、起動してから 3 秒後に、password.txt の内容を、その時フォーカスが当たっているテキスト入力可能なエリアに自動で打ち込む作りになっています
そのため、ツール起動後 3 秒以内に、Launcher のパスワード欄をクリックしておくことで、その欄にテキストが自動で入力されます

作者：https://twitter.com/rekidai_info
お問い合わせは DM 等で受け付けております
