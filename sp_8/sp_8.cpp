// sp_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>

int my_strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

void my_strncpy(char* dest, const char* src, int n) {
    int i = 0;
    while (i < n - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}


struct Product {
public:
    char name[50];
    double price;
    int quantity;
    Product* prev = nullptr;
    Product* next = nullptr;

    Product(const char* _name, double _price, int _quantity) {
        my_strncpy(name, _name, 50);
        price = _price;
        quantity = _quantity;

    }
};



class List
{
public:
    Product* head;
    Product* end;

    void Pop_middle(Product* rem)
    {
        if (rem == nullptr) return;

        if (rem->next == nullptr)
        {
            Pop_back();
            return;
        }
        if (rem->prev == nullptr)
        {
            Pop_front();
            return;
        }

        rem->next->prev = rem->prev;
        rem->prev->next = rem->next;

        delete rem;
    }


    List()
    {
        head = nullptr;
        end = nullptr;
    }



    void Push_beg(const char* name, double price, int quantity)
    {
        Product* new_nod = new Product(name, price, quantity);

        if (head == nullptr) {
            head = new_nod;
            end = new_nod;
            return;
        }

        head->prev = new_nod;
        new_nod->next = head;
        head = new_nod;
    }


    void Push_back(const char* name, double price, int quantity)
    {
        Product* new_nod = new Product(name, price, quantity);

        if (head == nullptr) {
            head = new_nod;
            end = new_nod;
            return;
        }

        new_nod->prev = end;
        end->next = new_nod;
        end = new_nod;
    }



    void Pop_front()
    {
        if (head == nullptr) {
            return;
        }

        Product* old = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            end = nullptr;
        }

        delete old;
    }





    void Pop_back()
    {
        if (end == nullptr) {
            return;
        }

        Product* old = end;
        end = end->prev;

        if (end != nullptr) {
            end->next = nullptr;
        }
        else {
            head = nullptr;
        }

        delete old;
    }



    void Display_forward()
    {
        if (head == nullptr) {
            return;
        }

        Product* print_nod = head;

        do {
            std::cout << print_nod->name << " " << print_nod->price << " " << print_nod->quantity << "\n";
            print_nod = print_nod->next;
        } while (print_nod != nullptr);
    }



    void Display_backward()
    {
        if (end == nullptr) {
            return;
        }

        Product* print_nod = end;

        do {
            std::cout << print_nod->name << " " << print_nod->price << " " << print_nod->quantity << "\n";
            print_nod = print_nod->prev;
        } while (print_nod != nullptr);
    }





    void Clear()
    {
        while (head != nullptr) {
            Pop_front();
        }
    }



    Product* Find_by_name(const char* search_name)
    {
        Product* curr = head;
        while (curr != nullptr) {
            if (my_strcmp(curr->name, search_name) == 0) {
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }





    void Remove_zero_quantity()
    {
        Product* curr = head;
        while (curr != nullptr) {
            Product* next_node = curr->next;
            if (curr->quantity == 0) {
                if (curr->prev != nullptr) {
                    curr->prev->next = curr->next;
                }
                else {
                    head = curr->next;
                }

                if (curr->next != nullptr) {
                    curr->next->prev = curr->prev;
                }
                else {
                    end = curr->prev;
                }
                delete curr;
            }
            curr = next_node;
        }
    }





    void Move_most_expensive_to_front()
    {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Product* max_node = head;
        Product* curr = head->next;

        while (curr != nullptr) {
            if (curr->price > max_node->price) {
                max_node = curr;
            }
            curr = curr->next;
        }

        if (max_node == head) {
            return;
        }

        if (max_node->prev != nullptr) {
            max_node->prev->next = max_node->next;
        }
        if (max_node->next != nullptr) {
            max_node->next->prev = max_node->prev;
        }
        else {
            end = max_node->prev;
        }

        max_node->next = head;
        max_node->prev = nullptr;
        head->prev = max_node;
        head = max_node;
    }

};


int main()
{
    setlocale(LC_ALL, "RUS");


    List list;

    while (true)
    {
        std::cout << "\n\n1 Добавить товар в начало\n";
        std::cout << "2 Добавить товар в конец\n";
        std::cout << "3 Удалить первый товар\n";
        std::cout << "4 Удалить последний товар\n";
        std::cout << "5 Вывести список (вперед)\n";
        std::cout << "6 Вывести список (назад)\n";
        std::cout << "7 Найти товар по названию\n";
        std::cout << "8 Удалить товары с нулевым количеством\n";
        std::cout << "9 Переместить самый дорогой товар в начало\n";
        std::cout << "10 Очистить список\n";
        std::cout << "11 Выход\n\n";

        int menu;
        std::cin >> menu;

        char name[50];
        double price;
        int quantity;
        char search_name[50];

        switch (menu)
        {
        case 1:
            std::cout << "Название: ";
            std::cin.getline(name, 50);
            std::cout << "Цена: ";
            std::cin >> price;
            std::cout << "Количество: ";
            std::cin >> quantity;
            list.Push_beg(name, price, quantity);
            break;

        case 2:
            std::cout << "Название: ";
            std::cin.ignore(10000, '\n');
            std::cin.getline(name, 50);
            std::cout << "Цена: ";
            std::cin >> price;
            std::cout << "Количество: ";
            std::cin >> quantity;
            list.Push_back(name, price, quantity);
            break;

        case 3:
            list.Pop_front();
            break;

        case 4:
            list.Pop_back();
            break;

        case 5:
            list.Display_forward();
            break;

        case 6:
            list.Display_backward();
            break;

        case 7:
            std::cout << "Введите название для поиска: ";
            std::cin.ignore(10000, '\n');
            std::cin.getline(search_name, 50);
            {
                Product* prod = list.Find_by_name(search_name);
                if (prod != nullptr) {
                    std::cout << "Найден: " << prod->name << " " << prod->price << " " << prod->quantity << "\n";
                }
                else {
                    std::cout << "Не найдено\n";
                }
            }
            break;

        case 8:
            list.Remove_zero_quantity();
            std::cout << "Удаление завершено\n";
            break;

        case 9:
            list.Move_most_expensive_to_front();
            std::cout << "Перемещение завершено\n";
            break;

        case 10:
            list.Clear();
            std::cout << "Список очищен\n";
            break;

        case 11:
            return 0;

        default:
            break;
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
