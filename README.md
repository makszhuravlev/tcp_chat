# TCP чат by CyberConnect

Здравствуйе, мы участники хакатона от группы «Астра». В этом репозитории лежать файлы нашего собственного мессенджера. Мы очень старались!

## Содержание
- [Технологии](#технологии)
- [Начало работы](#начало-работы)
- [To do](#to-do)
- [Команда проекта](#команда-проекта)
- [Источники](#Источники)

## Технологии
- [postgresql](https://www.postgresql.org/)
- [pqxx](https://github.com/jtv/libpqxx)
- [nlohmann/json](https://github.com/nlohmann/json)
- [boost/websocket](https://github.com/boostorg)

## Начало-работы
Команды приведены для OS astra linux

### Установка

Установите необходимые пакеты с помощью утилиты apt-get:
```sh
$ apt-get install g++ cmake libpq-dev #libboost-all-dev б
```
Библиотеку boost нужно скомпилировать [самостоятельно](https://stackoverflow.com/questions/12578499/how-to-install-boost-on-ubuntu)

Выполните сборку:
```sh
cd tcp_chat
mkdir build && cd build
cmake ..
cmake --build .
```

Установка:
```sh
cmake --install .               #(По умолчанию в /opt)
```

запуск:
```sh
./opt/bin/server              #с установкой

или 

~/tcp_chat/build$ ./server    #без установки
```

### Зачем вы разработали этот проект?
Чтобы был.

## To do
- [x] Шифрование
- [x] Асинхронность
- [-] ...

## Команда проекта
Оставьте пользователям контакты и инструкции, как связаться с командой разработки.

- [Артём Шакиров](https://github.com/artemka-sh) — Beckend Engineer
- [Максим Журавлёв](https://github.com/makszhuravlev) — Front-End Engineer
- [Леонид Лопатин](https://github.com/MagentaNyashka) — Backend Developer
- [Александр Степанцов](https://github.com/sashok112) — Team Leader

## Источники
[How discord stores billions of messages](https://discord.com/blog/how-discord-stores-billions-of-messages)
