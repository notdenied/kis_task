# Задача №5 / Алгоритмы - решатель для Пасьянса.
Решение отборочного задания на кафедру КИС 1С 13.10.24.

Сделанные предположения:
- В изначальной позиции нам передаётся 8 кучек по 9 карт ("карты раскладываются в 8 кучек по 9 карт").
- Убрать карты можно не только если в случае, если в куче 9 карт и все они расположены в одном и том же порядке, но и в том случае, если 9 "хороших" карт лежат сверху кучи.

Предложенный алгоритм:
Поскольку данная задача сама по себе сложна (и, по субъективным предположениям, NP-полна, но не суть), будем решать её приближённо с помощью алгоритма A*.
Выберем такую эвристику, что (здесь и далее x - конфигурация на игровом столе):
- h() = 0 <-> x = finish;
- h(x) >= 0;
- (нестрого) при приближении к ответу значение h уменьшается.

Заметим, что h(x) = f(x) + g(x), где f(x) - количество карт на столе, а g(x) - сумма числа инверсий в кучках на столе, подходит:
- Если h(x) = 0, то f(x) = g(x) = 0 -> на столе 0 карт -> x = finish;
- h(x) >= 0 - очевидно.
- Неформально: чем ближе мы к "победе", тем меньше карт на столе, а сами карты лежат более организованно (упорядоченно).

Поскольку точное решение не требуется (да и вряд ли какая-то метрика могла бы его дать), показывать оптимальность данной метрики не будем.

Если в какой-то момент очередь в алгоритме становится пуста, это значит, что все достижимые из стартовой позиции конфигурации были достигнуты, а ответ не найден, а значит решения не существует (то есть алгоритм совершил полный перебор).

Отсюда (и из свойства h(x) = 0 <=> x = finish) получаем, что алгоритм корректен (то есть выданный им ответ всегда верный), однако гарантировать оптимальное время его работы мы не можем.

Определим формат входных и выходных данных (формально). Будем работать только через stdin / stdout.
Алгоритм получает на вход 72 числа: 9 карт (числа от 0 до 9) в первой куче, 9 карт во второй и так далее (в порядке от самой нижней карты до самой верхней).
Алгоритм выдаёт конфигурации в следующем формате:
- Вердикт о существовании решения;
- Ходы (позиции) разделены между собой двойным переносом строки и выводятся с конца;
- Кучи выводятся одна за другой в лексикографическом порядке, при этом кучи разделены между собой одинарным переносом строки, а значения в пределах кучи - пробелом;
- Вместо пустой кучи выводится `empty_heap`;
- Вместо финальной позиции выводится `empty_position`.

В целях оптимизации работы алгоритма все позиции хранятся в отсортированном порядке.

Для запуска кода достаточно скомпилировать решение (если вы работаете в vscode - стандартными средствами, конфигурация загружена в репозиторий) и запустить его:
- `g++ main.cpp -o main -std=c++20 -O3`
- `./main`

Примеры входных данных есть в файле `example_inputs.txt`.

Выносить исходные файлы в отдельную папку и писать Makefile для удобства было решено отложить и опущено из-за нехватки времени.

Не все возможные оптимизации и решения были реализованы в рамках этого проекта. В частности, можно:
- Попробовать придумать метрику "получше";
- Заменить контейнер позиции на std::set или подобный (поскольку нам всё равно нужно хранить только отсортированные позиции); выбор std::vector - "легаси" (не было продумано заранее);
- См. комментарии в коде (и особенно TODO);
- Тесты;
- ...