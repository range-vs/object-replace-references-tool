# Object Replace References Tool

## English description
The program is designed to work with X-Ray SDK 0.7.
Manual replacement of LOD - sections.

### Use:
* Create any * .bat file, and write the startup command in it.
* Run * .bat file and wait for the operation to finish

### How it works?
Used when Lods Add could not find similar objects for some sections.
In this case, these sections (paths to the files) need to be written out in the configuration file - and the replacement values, selected in manual

### Description of commands:
* -level "name without space" - postfix, which will be added to the name **of each** section to exclude duplicates

### Directory structure:
If there are no directories, then you need to create next to the program.
* levels\in\ - here should be a file ** scene_object.part **, from which sections will be taken
* levels\out\ - this will create an output file ** scene_object.part ** that stores sections of two locations
* levels\references_replace\ - there should be a file ** references.txt **, which stores sections of two locations in the format:
object_path\object_which_replaceable = object_path_to_object\object_to_which_replaceable

The extension does not need to be specified. Example:
```
levels\darkscape\darkscape_lod0000 = trees\new_trees\trees_2_sux_01
```

### Example:
```
-level garbage_postfix
```

## Русское описание
Программа создана для работы с X-Ray SDK 0.7.
Ручная замена лод - секций.

### Использование:
* Создайте любой *.bat - файл, и в него запишите команду запуска.
* Запустите *.bat - файл и дождитесь окончания операции

### Как это работает?
Используется в том случае, если Lods Add не смог найти похожие объекты для некоторых секций.
В таком случае эти секции(пути до файлов) нужно выписать в конфигурационный файл - и значения для замены, подобранные в ручную

### Описание команд:
* -level "имя_без_пробелов" - постфикс, который будет добавлятть к имени **каждой** секции для исключения дубликатов

### Структура каталогов:
Если каталогов нет, то требуется создать рядом с программой.
* levels\in\ - здесь должен располагаться файл **scene_object.part**, из которого будут браться секции
* levels\out\ - здесь создастся выходной файл **scene_object.part**, хранящий секции двух локаций
* levels\references_replace\ - здесь должен располагаться файл **references.txt**, хранящий секции двух локаций в формате:
путь_до_объекта\объект_который_заменяем = путь_до_объекта\объект_на_который_заменяем

Расширение указывать не нужно. Пример:
```
levels\darkscape\darkscape_lod0000 = trees\new_trees\trees_2_sux_01
```

### Пример:
```
-level garbage_postfix
```
