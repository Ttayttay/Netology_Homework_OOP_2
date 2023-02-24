#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

class address {
public:
    address(std::string, std::string, int, int) { }
    address() {}

    std::string get_output_address() {
        std::string a = std::to_string(house);
        std::string b = std::to_string(apartment);
        std::string out_add = (city + ", " + street + ", " + a + ", " + b);
        return out_add;
    }
    void set_all(std::string ci, std::string st, int hou, int apart) {
        city = ci;
        street = st;
        house = hou;
        apartment = apart;
    }

    std::string get_city() {
        return city;
    }

private:
    std::string city = { 0 }, street = { 0 };
    int house = 0; int apartment = 0;
};

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);

    std::ifstream fin;
    fin.open("in.txt");
    if (!fin.is_open()) {
        std::cout << "Error: файл не открыт " << "in.txt" << '\n';
        return -1;
    }

    int size = 0;
    fin >> size;
    if (size <= 0) {
        std::cout << "Ошибка: недопустимый размер  " << size << '\n';
        return -2;
    }

    address* add = new address[size];
    std::string cityName;
    std::string streetName;
    int buildingNum;
    int flatNum;

    for (int i = 0; i < size; ++i)
    {

        fin >> cityName >> streetName >> buildingNum >> flatNum;

        add[i].set_all(cityName, streetName, buildingNum, flatNum);

    }
    fin.close();

    address temp;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (add[j].get_city() > add[j + 1].get_city()) {
                temp = add[j];
                add[j] = add[j + 1];
                add[j + 1] = temp;
            }
        }
    }

    std::ofstream fout;
    fout.open("out.txt");
    if (!fout.is_open())
    {
        std::cout << "Error: unable to open file " << "out.txt" << " for writing" << '\n';
        return -3;
    }
    fout << size << std::endl;

    for (int i = 0; i < size; ++i)
    {
        fout << add[i].get_output_address() << std::endl;

    }

    fout.close();
    delete[] add;

}