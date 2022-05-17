#include <iostream> // библиотека за вход/изход в конзолата
#include <fstream> // библиотека за файлове
#include <unordered_map> // библиотека за речник
#include <algorithm> // библиотека за алгоритми 
int main() {
	std::string inputFileName, outputFileName; // входно и изходно име на файла
	std::cout << "Enter input file name:"; std::cin >> inputFileName; // въвеждаме името на входния файл

    std::fstream inputFile(inputFileName, std::ios::in); // зареждаме файла

    inputFileName.erase(inputFileName.end() - 4); // премахваме опашката което са последните 4 символа
    inputFileName.erase(inputFileName.end() - 3);
    inputFileName.erase(inputFileName.end() - 2);
    inputFileName.erase(inputFileName.end() - 1);

	outputFileName = inputFileName + ".output.txt"; // слагаме изходното име на файла да има .output.txt като опашка

	std::unordered_map<std::string, uint32_t> dictionary; // създаваме речник за думите
    dictionary.reserve(1000); // резервираме 1000 различни думи

    std::string word; // дума която е прочетена
    while (inputFile >> word) { // четем думи докато има във файла
        auto it = std::remove_if(word.begin(), word.end(), [](char const& c) { // взимаме позицията където трябва да се премахне
            return !std::isalnum(c);                                           // символ който не е буква или цифра
            });

        word.erase(it, word.end()); // премахваме ненужните символи 
        if (word.size() > 0) { // проверяваме дали думата има дължина по-голяма от 0
            if (dictionary.find(word) != dictionary.end()) // проверяваме дали думата не е вече добавена
                dictionary.emplace(word, 0); // добавяме думата в речника
            dictionary[word] += 1; // добавяме 1 към броят пъти в който сме срещнали думата 
        }
    }
    inputFile.close();  // затваряме входния файл

    std::fstream outputFile(outputFileName.data(), std::ios::out); // създаваме и зареждаме изходният файл
    for (auto& element : dictionary) // минаваме през всяка дума от речникът
    {
        outputFile << element.first << "," << element.second << "\n"; // записваме думата и броят във файлът
    }
    outputFile.flush(); // казваме че сме приключили със записването
    outputFile.close(); // затваряме изходният файл
	return 0;
}