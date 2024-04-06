# rang
Qt-based terminal file manager.

## Использование
Интерфейс в разработке, пока что можно насладиться следующим
примитивным набором команд:
- `:q` - выйти
- `:o <dirname>` - открыть папку dirname
- `:p <filename>` - предпросмотр файла filename
- `Enter` - обновить экран

Также есть пример remote-команды:
```shell
rang --client-mode --set-current-dir <dirname>
# Аналогично :o, но работает с уже запущенным приложением.
```


## Дорожная карта
- TODO
