print("НУЖЕН MATPLOTLIB")

import os
import matplotlib.pyplot as plt


menu_carrier = int(input("1 Сплайн или 2 сплайна: "))
if menu_carrier == 1:
    stock_filename = input("Файл с исходными точками: ")
    if not os.path.exists(stock_filename):
        exit("Файл с исходными точками указан неверно!")
    targt_filename = input("Файл с результатом интерполяции: ")
    if not os.path.exists(targt_filename):
        exit("Файл с результатом интерполяции указан неверно!")

    stock = open(stock_filename, "r")
    targt = open(targt_filename, "r")

    stock_x = []
    stock_y = []
    target_x = []
    target_y = []

    for line in stock.readlines()[1:]:
        x, y = line.split()
        stock_x.append(float(x))
        stock_y.append(float(y))

    for line in targt.readlines():
        x, y = line.split()
        target_x.append(float(x))
        target_y.append(float(y))


    plt.plot(target_x, target_y, label="Интерполяция", c="blue")
    plt.plot(stock_x, stock_y, "o", label="Исходные точки", c="red")
    plt.plot(stock_x, stock_y, label="Линейная интерполяция", c="green")
    plt.legend()
    plt.show()
elif menu_carrier == 2:
    f_stock_filename = input("Файл с исходными точками первого сплайна: ")
    if not os.path.exists(f_stock_filename): exit("Файл не найден!")
    f_target_filename = input("Файл с восстановленными точками первого сплайна: ")
    if not os.path.exists(f_target_filename): exit("Файл не найден!")
    s_stock_filename = input("Файл с исходными точками второго сплайна: ")
    if not os.path.exists(s_stock_filename): exit("Файл не найден!")
    s_target_filename = input("Файл с восстановленными точками второго сплайна: ")
    if not os.path.exists(s_target_filename): exit("Файл не найден!")


    f_stock_x = []
    f_stock_y = []
    with open(f_stock_filename, "r") as f:
        for line in f.readlines()[1:]:
            x, y = line.split()
            f_stock_x.append(float(x))
            f_stock_y.append(float(y))
    
    f_target_x = []
    f_target_y = []
    with open(f_target_filename, "r") as f:
        for line in f.readlines():
            x, y = line.split()
            f_target_x.append(float(x))
            f_target_y.append(float(y))

    s_stock_x = []
    s_stock_y = []
    with open(s_stock_filename, "r") as f:
        for line in f.readlines()[1:]:
            x, y = line.split()
            s_stock_x.append(float(x))
            s_stock_y.append(float(y))
    
    s_target_x = []
    s_target_y = []
    with open(s_target_filename, "r") as f:
        for line in f.readlines():
            x, y = line.split()
            s_target_x.append(float(x))
            s_target_y.append(float(y))

    plt.plot(f_stock_x, f_stock_y, "o", label="1st dots", c="red")
    plt.plot(f_target_x, f_target_y, label="1st spline", c="red")
    plt.plot(s_stock_x, s_stock_y, "o", label="2nd dots", c="blue")
    plt.plot(s_target_x, s_target_y, label="2nd spline", c="blue")
    plt.legend()
    plt.show()



            
