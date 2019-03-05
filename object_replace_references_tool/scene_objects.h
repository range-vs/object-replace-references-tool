#pragma once

#include "pch.h"

class Locale // локаль
{
	UINT cp;
	UINT output_cp;
public:
	Locale(const int& l);
	~Locale();
};


class scene_object // входной/выходной объект
{
	struct section // секция в файле scene_objects.part
	{
		std::string section_number;
		std::string clsid;
		std::string co_flags;
		std::string flags;
		std::string name;
		std::string position;
		std::string reference_name;
		std::string rotation;
		std::string scale;
		std::string version;
	};

	std::string levelPostfix; // постфикс локации
	std::string nameFile; // имя файла с объектами
	std::list<section> sect; // массив секций
	std::vector<std::string> firstData; // остальные данные, в начале файла
	std::map<std::string, std::pair<std::string, int>> references; // карта ссылок - заменителей
public:
	scene_object(const std::string& n) : nameFile(n) {}
	bool init(int argc, char** argv);
	bool loadSceneObject(); // грузим файл с секциями
	bool loadSectionReplace(const std::string& file); // грузим файл с секциями - заменителями
	void runReplace(); // выполняем замену секций(ссылок) на объекты
	bool writeNewSceneObject(const std::string& out_path); // перезаписывае новый файл
};