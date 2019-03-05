#include "pch.h"
#include "scene_objects.h"

// локаль
Locale::Locale(const int& l)
{
	cp = GetConsoleCP();
	output_cp = GetConsoleOutputCP();
	SetConsoleCP(l);
	SetConsoleOutputCP(l);
}

Locale::~Locale()
{
	SetConsoleCP(cp);
	SetConsoleOutputCP(output_cp);
}


// входной/выходной объект
bool scene_object::init(int argc, char ** argv)
{
	for (int i(1); i < argc; i++)
	{
		if (!strcmp(argv[i], "-level"))
		{
			if (argc == ++i)
			{
				std::cout << "Неполный ключ -level. Укажите аргумент." << std::endl;
				return false;
			}
			else
				levelPostfix = argv[i];
		}
	}
}

bool scene_object::loadSceneObject()
{
	std::ifstream file(nameFile);
	if (!file)
	{
		std::cout << "Error open file " << nameFile << std::endl;
		return false;
	}
	std::string tmp;
	while (true) // пропускаем шапку
	{
		std::getline(file, tmp, '\n');
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		if (tmp.find("[object_") != -1) // нашли первую секцию - останавливаем проверку объектов
			break;
		firstData.push_back(tmp);
	}
	while (true) // грузим все секции 
	{
		section sc;
		tmp.resize(tmp.length() - 1);
		tmp.erase(0, 8);
		sc.section_number = tmp;
		std::getline(file, sc.clsid, '\n'); // clsid
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		std::getline(file, sc.co_flags, '\n'); // co_flags
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		std::getline(file, sc.flags, '\n'); // flags
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		std::getline(file, sc.name, '\n'); // name
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		std::getline(file, sc.position, '\n'); // position
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		std::getline(file, sc.reference_name, '\n'); // reference_name
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		std::getline(file, sc.rotation, '\n'); // rotation
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		std::getline(file, sc.scale, '\n'); // scale
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		std::getline(file, sc.version, '\n'); // version
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
		sect.push_back(sc); // добавляем секцию
		std::getline(file, tmp, '\n'); // пропускаем пробел

		std::getline(file, tmp, '\n'); // section number
		if (file.eof())
		{
			file.close();
			return true;
		}
		if (!file)
		{
			std::cout << "Error read file " << nameFile << std::endl;
			return false;
		}
	}
}

bool scene_object::loadSectionReplace(const std::string & name)
{
	std::ifstream file(name);
	if (!file)
	{
		std::cout << "Error open file " << name << std::endl;
		return false;
	}
	std::string key;
	std::string value;
	while (true) // сканируем файл на ссылки - заменители
	{
		std::getline(file, key, '=');
		if (file.eof())
		{
			file.close();
			return true;
		}
		if (!file)
		{
			std::cout << "Error read file " << name << std::endl;
			return false;
		}
		std::getline(file, value, '\n');
		if (!file)
		{
			std::cout << "Error read file " << name << std::endl;
			return false;
		}
		key.resize(key.length() - 1);
		references.insert({ key, {value, 0} });
	}
}

void scene_object::runReplace()
{
	int i(0);
	for (auto& s : sect)
	{
		auto key = s.reference_name.substr(s.reference_name.find("=") + 2);
		if (references.find(key) != references.end())
		{
			auto newReference = s.reference_name.substr(0, key.length());
			auto value = references[key];
			newReference += (" = " + value.first);
			s.name = s.name.substr(0, s.name.find("=") + 1);
			s.name += value.first;
		}
		std::stringstream ss;
		ss << "_" << std::setw(5) << std::setfill('0') << /*references[key].second++*/i++ << "_" << levelPostfix;
		s.name += ss.str();
		
	}
}

bool scene_object::writeNewSceneObject(const std::string & out_path)
{
	std::ofstream file(out_path);
	file.imbue(std::locale("rus_rus.1251"));
	if (!file)
	{
		std::cout << "Error create file " << out_path << std::endl;
		return false;
	}
	for (auto& data : this->firstData)
	{
		file << data << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
	}

	int y(0);
	for (auto& sc : this->sect) // записываем все секции 
	{
		file << "[object_" << sc.section_number << "]" << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
		file << sc.clsid << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
		file << sc.co_flags << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
		file << sc.flags << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
		file << sc.name << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
		file << sc.position << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
		file << sc.reference_name << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
		file << sc.rotation << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
		file << sc.scale << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}
		file << sc.version << std::endl << std::endl;
		if (!file)
		{
			std::cout << "Error write file " << out_path << std::endl;
			return false;
		}

	}
	file.close();
	return true;
}
