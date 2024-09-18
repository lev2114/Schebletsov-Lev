#include <cstring>
#include <iostream>

namespace {
const int kMaxMinutes = 60;
const int kMaxHours = 24;
const int kMin = 0;
const int kMorningbeg = 5;
const int kDaybeg = 12;
const int kEveningbeg = 18;
const int kNightbeg = 0;
const int kHighnoon = 12;
const int kHoursAndMinsNameChangeMin = 2;
const int kHoursAndMinsNameChangeMax = 4;
const int kHoursAndMinsSpecPoint = 1;
const int klastnumberdef = 10;
const int kminspeczonebeg = 12;
const int kminspeczoneend = 14;
const int kStrlength = 20;
}  // namespace
enum daytime {
    Midnight,
    High_noon,
    Morning,
    Day,
    Evening,
    Night,
};

int main(int, char**) {
    daytime Daytime{};
    char hourName[kStrlength]{};
    char minName[kStrlength]{};
    int hours{};
    int minutes{};

    std::cout << "Введите время: ";
    std::cin >> hours >> minutes;

    if ((hours >= kMaxHours or hours < kMin) or (minutes >= kMaxMinutes or minutes < kMin)) {
        std::cout << "Введены некорректные данные, перезапустите программу\n";
        return 0;
    }

    if (hours == kMin and minutes == kMin) {
        Daytime = Midnight;
    } else if (hours == kHighnoon and minutes == kMin) {
        Daytime = High_noon;
    } else if (hours >= kNightbeg and hours < kMorningbeg) {
        Daytime = Night;
    } else if (hours >= kMorningbeg and hours < kDaybeg) {
        Daytime = Morning;
    } else if (hours >= kDaybeg and hours < kEveningbeg) {
        Daytime = Day;
    } else if (hours >= kEveningbeg) {
        Daytime = Evening;
    }

    hours %= kHighnoon;

    if (hours == kHoursAndMinsSpecPoint) {
        std::strcpy(hourName, "час ");
    } else if (hours >= kHoursAndMinsNameChangeMin and hours <= kHoursAndMinsNameChangeMax) {
        std::strcpy(hourName, "часа ");
    } else {
        std::strcpy(hourName, "часов ");
    }

    if (minutes == kMin) {
        std::strcpy(minName, "ровно ");
    } else if (minutes >= kminspeczonebeg and minutes <= kminspeczoneend) {
        std::strcpy(minName, "минут ");
    } else if (minutes % klastnumberdef == kHoursAndMinsSpecPoint) {
        std::strcpy(minName, "минута ");
    } else if ((minutes % klastnumberdef >= kHoursAndMinsNameChangeMin) and (minutes % klastnumberdef <= kHoursAndMinsNameChangeMax)) {
        std::strcpy(minName, "минуты ");
    } else {
        std::strcpy(minName, "минут ");
    }

    if (minutes != kMin) {
        switch (Daytime) {
            case Midnight:
                std::cout << "Полночь\n";
                break;
            case High_noon:
                std::cout << "Полдень\n";
                break;
            case Morning:
                std::cout << hours << " " << hourName << minutes << " " << minName << "утра\n";
                break;
            case Day:
                std::cout << hours << " " << hourName << minutes << " " << minName << "дня\n";
                break;
            case Evening:
                std::cout << hours << " " << hourName << minutes << " " << minName << "вечера\n";
                break;
            case Night:
                std::cout << hours << " " << hourName << minutes << " " << minName << "ночи\n";
                break;
        }
    } else {
        switch (Daytime) {
            case Midnight:
                std::cout << "Полночь\n";
                break;
            case High_noon:
                std::cout << "Полдень\n";
                break;
            case Morning:
                std::cout << hours << " " << hourName << "утра" << minName;
                break;
            case Day:
                std::cout << hours << " " << hourName << "дня" << minName;
                break;
            case Evening:
                std::cout << hours << " " << hourName << "вечера" << minName;
                break;
            case Night:
                std::cout << hours << " " << hourName << "ночи" << minName;
                break;
        }
    }
    return 0;
}
