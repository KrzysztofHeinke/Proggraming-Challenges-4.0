// OpenCV.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "LineIntersection.h"

int main()
{    
    int thresh = 1000;
    cv::Mat image = cv::imread("C:\\Users\\Krzysztof\\source\\repos\\OpenCV\\OpenCV\\2.jpg");
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::Mat lines_img;
    cv::Canny(image, lines_img, 10, 200);
    cv::namedWindow("OBRAZ", cv::WINDOW_NORMAL);
    std::vector<cv::Vec4i> lines;
    cv::HoughLinesP(lines_img, lines, 1, CV_PI / 180, 150, 1000, 1000);
    
    /*for (size_t i = 0; i < lines.size(); i++)
    {
        cv::Vec4i l = lines[i];
        //cv::line(image, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 0), 5, cv::LINE_8);
    }*/
    /*for (auto i = lines.begin(); i != lines.end(); i++)
    {
        std::cout << *i << std::endl;
        std::cout << i[0] << std::endl;
        std::cout << i[0][0] << std::endl;
        std::cout << i[0][1] << std::endl;
        std::cout << i[0][2] << std::endl;
        std::cout << i[0][3] << std::endl;
    }*/

    std::vector <LineIntersection> nodes;
    std::vector <LineIntersection> intersection_nodes;
    for (auto it_1 = lines.begin(); it_1 != lines.end(); it_1++)
    {
        for (auto it_2 = lines.begin(); it_2 != lines.end(); it_2++)
        {
            nodes.push_back(LineIntersection(&it_1[0], &it_2[0]));
        }
    }
    for (auto it = nodes.begin(); it != nodes.end(); it++)
    {
        if ( it->is_intersection() )
        {
            intersection_nodes.push_back(*it);
        }
    }
    for (auto it = intersection_nodes.begin(); it != intersection_nodes.end(); it++)
    {
        std::cout << "x: " << it->intersection.first << " y: " << it->intersection.second << std::endl;
    }
    if (intersection_nodes.empty())
    {
        std::cout << "YES" << std::endl;
    }
    
    
    /*
    LineIntersection abc(&lines[0], &lines[8]);
    std::cout << abc.source_equation.a << " " << abc.source_equation.b << std::endl;
    std::cout << abc.target_equation.a << " " << abc.target_equation.b << std::endl;
    //std::cout << abc.source_line_begin.y << " " << abc.source_line_end.y << std::endl;
    std::cout << abc.is_intersection() << std::endl;
    std::cout << "x: " << abc.intersection.first << " y: " << abc.intersection.second << std::endl;
    */
    for (size_t i = 0; i < intersection_nodes.size(); i++)
    {
        std::cout << "ELO";
        std::cout <<  *intersection_nodes[i].target << std::endl;
        //cv::line(image, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 0), 5, cv::LINE_8);
    }
    for (size_t i = 0; i < intersection_nodes.size(); i++)
    {
        cv::Vec4i l = *intersection_nodes[i].source;
        cv::line(image, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 0), 5, cv::LINE_8);
    }
    for (auto it = intersection_nodes.begin(); it != intersection_nodes.end(); it++)
    {
        cv::Point centerCircle2(it->intersection.first, it->intersection.second);
        cv::Scalar colorCircle2(0, 100, 0);
        int radiusCircle = 500;

        cv::circle(image, centerCircle2, radiusCircle, colorCircle2, 10);

    }
    cv::circle(image, cv::Point(0,100),500,cv::Scalar(0, 100, 0), 10);
    cv::imshow("OBRAZ", image);
    cv::waitKey(0);
   
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
