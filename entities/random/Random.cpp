//
// Created by Gabriel on 22/06/2023.
//
#include <iostream>
#include <random>
#include <cstring>
#include "Random.h"

const char* Random::cria_nome_aleatorio() {

    std::random_device rd;
    std::mt19937 rand(rd());
    std::uniform_int_distribution<int> tamanho(5, 20);

    int tam= tamanho(rand);
    std::string stringAleatoria;

    for (int i = 0; i < tam; ++i) {

        std::uniform_int_distribution<int> intervalo(0, 51);  // Intervalo para letras maiúsculas e minúsculas (A-Z, a-z)
        int indice = intervalo(rand);
        char caractere;
        if (indice < 26) {
            caractere = 'A' + static_cast<char>(indice);  // Letras maiúsculas
        } else {
            caractere = 'a' + static_cast<char>(indice - 26);  // Letras minúsculas
        }
        stringAleatoria += caractere;
    }

    static char nome_aleatorio[21];  // Tamanho máximo de 20 caracteres + 1 para o caractere nulo '\0'

    std::strcpy(nome_aleatorio, stringAleatoria.c_str());

    return nome_aleatorio;
}

const char* Random::cria_matricula_aleatoria() {

    std::random_device rd;
    std::mt19937 rand(rd());
    std::uniform_int_distribution<int> intervalo_ano(00, 23);  // Intervalo para o ano (xx)

    std::uniform_int_distribution<int> intervalo_mes(1, 2);   // Intervalo para o mês (x)
    std::uniform_int_distribution<int> intervalo_decimal(0000, 9999);  // Intervalo para o decimal (xxxx)

    int ano = intervalo_ano(rand);
    int mes = intervalo_mes(rand);
    int decimal = intervalo_decimal(rand);

    std::string ano_str = ( ano< 10) ? "0" + std::to_string(ano) : std::to_string(ano);
    std::string mes_str = (mes < 10) ? "0" + std::to_string(mes) : std::to_string(mes);

    std::string matricula = std::to_string(ano) + "." + mes_str + "." + std::to_string(decimal);

    static char matricula_aleatoria[10];  // Tamanho máximo de 10 caracteres + 1 para o caractere nulo '\0'

    std::strcpy(matricula_aleatoria, matricula.c_str());

    return matricula_aleatoria;
}

const char* Random::cria_data_aleatoria() {

    std::random_device rd;
    std::mt19937 gerador(rd());
    std::uniform_int_distribution<int> intervalo_dia(1, 31);     // Intervalo para o dia (xx)
    std::uniform_int_distribution<int> intervalo_mes(1, 12);     // Intervalo para o mês (xx)
    std::uniform_int_distribution<int> intervalo_ano(1900, 2100); // Intervalo para o ano (xxxx)

    int dia = intervalo_dia(gerador);
    int mes = intervalo_mes(gerador);
    int ano = intervalo_ano(gerador);

    std::string dia_str = (dia < 10) ? "0" + std::to_string(dia) : std::to_string(dia);
    std::string mes_str = (mes < 10) ? "0" + std::to_string(mes) : std::to_string(mes);

    std::string data = dia_str + "/" + mes_str + "/" + std::to_string(ano);

    static char data_aleatoria[11];

    std::strncpy(data_aleatoria, data.c_str(), 10);
    data_aleatoria[10] = '\0';

    return data_aleatoria;
}

double Random::cria_coeficiente_aleatorio() {

    std::random_device rd;
    std::mt19937 gerador(rd());
    std::uniform_real_distribution<double> intervalo(0.0, 9.9);

    double coeficiente = intervalo(gerador);

    return std::floor(coeficiente * 10) / 10;
}