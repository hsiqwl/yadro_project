Этот репозиторий хранит в себе файлы небольшого проекта системы мониторинга компьютерного клуба. 
Для того чтобы скомпилировать проект необходимо:
- На Linux
``` 
$ mkdir build && cd build
$ cmake ..
$ make
```
- На Windows
```
$ cmake.exe -G "MinGW Makefiles" -S . -B .\build
$ cd build
$ mingw32-make.exe
```

Программа принимает в качестве аргумента имя файла, в котором содержаться все входные данные. 

В качестве примеров есть два файла: file.txt и error_file.txt. Первый файл удовлетворяет формату задания, а второй нет.

Архитектура проекта организована следующим образом: есть отдельно стоящие компоненты, которые никак друг от друга не зависят, они отвечают за поддержание состояния игровых станций, мониторинга игровых станций и клиентов. При желании любой может написать свои компоненты, отнаследовавшись от соответствующих классов. Проект построен как event-driven приложение. Есть отдельные системы реагирующие на определенные типы событий, в результате чего они обращаются к компонентам описанным ранее. Здесь применено сразу несколько паттернов: observer и visitor. Нотификация служб происходит по принципу "издатель извещает подписчика", а подписчик имеет механизмы обработки различных видов событий. Причем некорые службы являются одновременно и "издателем", и "подписчиком".
