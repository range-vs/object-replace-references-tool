#pragma once

#include "pch.h"

class Locale // ������
{
	UINT cp;
	UINT output_cp;
public:
	Locale(const int& l);
	~Locale();
};


class scene_object // �������/�������� ������
{
	struct section // ������ � ����� scene_objects.part
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

	std::string levelPostfix; // �������� �������
	std::string nameFile; // ��� ����� � ���������
	std::list<section> sect; // ������ ������
	std::vector<std::string> firstData; // ��������� ������, � ������ �����
	std::map<std::string, std::pair<std::string, int>> references; // ����� ������ - �����������
public:
	scene_object(const std::string& n) : nameFile(n) {}
	bool init(int argc, char** argv);
	bool loadSceneObject(); // ������ ���� � ��������
	bool loadSectionReplace(const std::string& file); // ������ ���� � �������� - ������������
	void runReplace(); // ��������� ������ ������(������) �� �������
	bool writeNewSceneObject(const std::string& out_path); // ������������� ����� ����
};