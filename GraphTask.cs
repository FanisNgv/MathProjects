using System;

namespace CGT_discrete_math_CS
{
    class WorkingWithGraph
    {        
        static int num_of_vertexes;      // Вершины графа, количество которых указывает пользователь
        static int[][] original_matrix;  // Исходная матрица, вводимая пользователем
        static int[][] resulting_matrix; // Результирующая матрица, которая получается при возведении 	матрицы в степень
        static string str;               // Строка для сохранения введенных пользователем данных
        static int num_of_edges = 0;     // Количество ребер нашего графа

        // 
        // Ниже приведена функция, которая умножает переданную матрицу на исходную матрицу
        //
        static int[][] multiply_to_original(int[][] matrix) 
        {
            int sum = 0; // Поле для хранения суммы перемножения элементов строки на элементы столбца
            int[][] answer = new int[num_of_vertexes][]; // Матрица, которая будет хранить рез-т умножения 	    матриц

            for (int i = 0; i < num_of_vertexes; i++) // Процесс умножения матриц
            {
                answer[i] = new int[num_of_vertexes]; // Выделение памяти для первой строки 

                for (int iter = 0; iter < num_of_vertexes; iter++) // Этот цикл нужен для переключения 		        столбца
                {
                    for (int j = 0; j < num_of_vertexes; j++)
                    {
                        sum += matrix[i][j] * original_matrix[j][iter]; // Суммируем соответствующие 			    произведения эле-ов
                    }    
                    
                    answer[i][iter] = sum; // Соотв-му элементу приравниваем полученную сумму  
                    sum = 0;               // Обнуляем сумму
                }
            }
            return answer; // Возврат результата умножения матриц
        }

        // 
        // Ниже приведена функция, которая ищет путь кратчайшей длины между двумя вершинами
        //

        static void min_lehgth_between_vertexes(int Vi, int Vj)
        {
            int counter = 1; // Счетчик для отслеживания степени, в которую возведена матрица

            if (resulting_matrix[Vi - 1][Vj - 1] != 0) // если интерес-ий нас элемент не равен нулю
            {
                Console.WriteLine($"Кратчайшее растояние между верщинами {Vi} и {Vj} равно {counter}");
            }
            // Если же не равен нулю, то возводим матрицу в соотв. степень,
            // пока инте-ий нас элемент не станет отличным от нуля
            // Если элемент стал отличным от нуля, то это наш результат
            else
            {
                while (resulting_matrix[Vi - 1][Vj - 1] == 0)
                {
                    resulting_matrix = multiply_to_original(resulting_matrix);
                    counter++;
                }
                Console.WriteLine($"Кратчайшее растояние между верщинами {Vi} и {Vj} равно {counter}");
                resulting_matrix = original_matrix; // Возвращаешм результирующую матрицу в исходное 		  	состояние
            }
            
        }

        // 
        // Ниже приведена функция, ищущая количество путей между интересующими нас вершинами с 	определенной длиной
        // 

        static void num_of_def_lehgth_between_vertexes(int a, int b)
        {
            int counter = 1; // Счетчик для отслеживания степени, в которую возведена матрица
            int def_length = num_of_edges - num_of_vertexes + 3; // Интресующая нас длина. См. исходный 		    граф
            if (counter == def_length) // Если степень, в которую возведена матрица, равна интере-ей нас 	    длине
            {
                Console.WriteLine($"Количество путей длины {def_length} между верщинами {a} и {b} равно 		 	{resulting_matrix[a - 1][b - 1]}");
            }
            else // если не равна, то возводим матрицу в степень, пока она не станет равна интере-ей нас 		длине
            {
                while (counter != def_length)
                {
                    resulting_matrix = multiply_to_original(resulting_matrix);
                    counter++;
                }
                Console.WriteLine($"Количество путей длины {def_length} между верщинами {a} и {b} равно 			{resulting_matrix[a - 1][b - 1]}");
                resulting_matrix = original_matrix;
            }    
            
        }
        //
        // Точка входа в программу. Функция Main
        
        static void Main(string[] args)
        {
            Console.WriteLine("Введите количество вершин в графе!"); // Просим ввести ко-во вершин

            num_of_vertexes =  int.Parse(Console.ReadLine());        // Считываем ко-во вершин

            original_matrix = new int[num_of_vertexes][];            // Выделяем память под исходную 	  	    матрицу
            resulting_matrix = new int[num_of_vertexes][];           // Выделяем память под результирующую 	    матрицу

            Console.WriteLine("Введите матрицу смежности");

            for (int i = 0; i < num_of_vertexes; i++)                // Построчно вводим матрцу
            {
                str = Console.ReadLine();                            // Считываем строку
                string[] mas_str = str.Split(" ");                   // Отправляем элементы в массив с 		 	разделением по пробелу

                original_matrix[i] = new int[num_of_vertexes];       // Выделяем память под первую строку 		исходной матрицы
                resulting_matrix[i] = new int[num_of_vertexes];      // Выделяем память под первую строку 		рез-ей матрицы

                for (int j = 0; j < num_of_vertexes; j++)            // Присваиваем одному из массивов 			массива введенную нами строку
                {
                    original_matrix[i][j] = int.Parse(mas_str[j]);
                    num_of_edges += original_matrix[i][j];           // Добавляем ребра
                }
                
                resulting_matrix[i] = original_matrix[i];             // Результирующая матрица изначальна 		равна исходной
            }            
            num_of_edges /= 2;                                        // Делим ко-во ребер пополам, т.к. 	    каждое ребро мы учли два раза
            
            Console.WriteLine("Введите номера вершин, между которыми нужно найти путь минимальной длины");
            str = Console.ReadLine();                                 // Считываем строку
            string[] mas_vertx = str.Split(" ");                      // Отправляем элементы в массив с 		    разделением по пробелу
            min_lehgth_between_vertexes(int.Parse(mas_vertx[0]), int.Parse(mas_vertx[1])); // Вызываем 		    функ-ю поиска пути минимальной длины между вершинами

            Console.WriteLine("Введите номера вершин таких, между которыми нужно найти количество путей 		    заданной длины");
            str = Console.ReadLine();                                 // Считываем строку
            mas_vertx = str.Split(" ");                               // Отправляем элементы в массив с 		    разделением по пробелу
            num_of_def_lehgth_between_vertexes(int.Parse(mas_vertx[0]), int.Parse(mas_vertx[1])); // 		    Вызываем функ-ю поиска количества путей определенной длины
        }     
    }
}
