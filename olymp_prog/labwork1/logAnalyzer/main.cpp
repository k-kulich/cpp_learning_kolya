#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>

time_t parse_date(const std::string &date_str)
{
    std::string clean_date = date_str;
    if (!clean_date.empty() && clean_date.front() == '[')
    {
        clean_date = clean_date.substr(1);
    }

    std::tm tm = {};
    std::istringstream ss(clean_date);
    ss >> std::get_time(&tm, "%d/%b/%Y:%H:%M:%S");

    if (ss.fail())
    {
        return 0;
    }

    return std::mktime(&tm);
}

int main(int argc, char *argv[])
{
    std::string log_filename = "";
    std::string output_filename = "";
    int top_n = 0;
    int window_seconds = 0;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-s" || arg == "--stats")
        {
            if (i + 1 < argc)
            {
                top_n = std::stoi(argv[i + 1]);
                i++;
            }
        }
        else if (arg == "-o" || arg == "--output")
        {
            if (i + 1 < argc)
            {
                output_filename = argv[i + 1];
                i++;
            }
        }
        else if (arg == "-w" || arg == "--window")
        {
            if (i + 1 < argc)
            {
                window_seconds = std::stoi(argv[i + 1]);
                i++;
            }
        }
        else if (log_filename.empty())
        {
            log_filename = arg;
        }
    }

    if (log_filename.empty())
    {
        std::cout << "Ошибка: не указан лог-файл!\n";
        std::cout << "Использование: ./analyze <лог-файл> [-s N] [-w SECONDS] [-o output.txt]\n";
        return 1;
    }

    std::ifstream file(log_filename);
    if (!file.is_open())
    {
        std::cout << "Не удалось открыть файл " << log_filename << "\n";
        return 1;
    }

    std::cout << "Файл " << log_filename << " успешно открыт.\n";

    std::string line;
    size_t line_count = 0;
    std::unordered_map<std::string, int> failed_urls;
    std::vector<time_t> error_timestamps;

    while (std::getline(file, line))
    {
        line_count++;

        std::stringstream ss(line);
        std::string ip, dummy1, dummy2, date, tz, method, url, protocol;
        int status = 0;

        ss >> ip >> dummy1 >> dummy2 >> date >> tz >> method >> url >> protocol >> status;

        if (status >= 500 && status <= 599)
        {
            failed_urls[url]++;

            time_t t = parse_date(date);
            if (t > 0)
            {
                error_timestamps.push_back(t);
            }
        }
    }

    file.close();

    int max_errors_in_window = 0;
    if (window_seconds > 0 && !error_timestamps.empty())
    {
        std::sort(error_timestamps.begin(), error_timestamps.end());

        size_t left = 0;
        for (size_t right = 0; right < error_timestamps.size(); ++right)
        {
            while (error_timestamps[right] - error_timestamps[left] > window_seconds)
            {
                left++;
            }

            int current_window_errors = static_cast<int>(right - left + 1);
            if (current_window_errors > max_errors_in_window)
            {
                max_errors_in_window = current_window_errors;
            }
        }
    }

    std::vector<std::pair<std::string, int>> sorted_errors(failed_urls.begin(), failed_urls.end());
    std::sort(sorted_errors.begin(), sorted_errors.end(), [](const auto &a, const auto &b)
              { return a.second > b.second; });

    std::stringstream report;
    report << "\n--- Статистика по файлу: " << log_filename << " ---\n";
    report << "Всего строк обработано: " << line_count << "\n";

    if (window_seconds > 0)
    {
        report << "Максимум ошибок 5XX за " << window_seconds << " сек: " << max_errors_in_window << "\n";
    }

    report << "\n--- Топ ошибок 5XX (по частоте) ---\n";
    int printed_count = 0;

    for (const auto &entry : sorted_errors)
    {
        if (top_n > 0 && printed_count >= top_n)
        {
            break;
        }

        report << entry.first << " — " << entry.second << " раз(а)\n";
        printed_count++;
    }

    if (!output_filename.empty())
    {
        std::ofstream out(output_filename);
        if (out.is_open())
        {
            out << report.str();
            out.close();
            std::cout << "Отчёт успешно сохранён в файл: " << output_filename << "\n";
        }
        else
        {
            std::cout << "Ошибка: не удалось записать в файл " << output_filename << "\n";
        }
    }
    else
    {
        std::cout << report.str();
    }

    return 0;
}