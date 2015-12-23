#include "ParserIni.hh"

ParserIni::ParserIni(const std::string& file) : _nameFile(file), _file(_nameFile, std::ios::in | std::ios::out | std::ios::ate)
{
	if (!_file)
		DEBUG_MSG("File couldn't be open");
}

ParserIni::~ParserIni()
{
	_file.close();
}

int ParserIni::getValue(const std::string& categorie, const std::string& variable)
{
	std::string line;
	_file.seekg(0);

	while (std::getline(_file, line))
	{
		if (line == ("[" + categorie + "]"))
			break;
	}
	while (std::getline(_file, line) && line[0] != '\0')
	{
		if (line.compare(0, variable.size(), variable) == 0)
		{
			if (line.size() > variable.size() + 2)
			{
				line = line.substr(variable.size() + 1, line.size());
				return atoi(line.c_str());
			}
		}
	}
	return -1;
}

const std::string ParserIni::getText(const std::string& categorie, const std::string& variable)
{
	std::string line;
	_file.seekg(0);

	while (std::getline(_file, line))
	{
		if (line == ("[" + categorie + "]"))
			break;
	}
	while (std::getline(_file, line) && line[0] != '\0')
	{
		if (line.compare(0, variable.size(), variable) == 0)
		{
			if (line.size() > variable.size() + 2)
			{
				line = line.substr(variable.size() + 1, line.size());
				return line;
			}
		}
	}
	line.clear();
	return line;
}

void ParserIni::setValue(const std::string & categorie, const std::string& variable, int value)
{
	std::string line;
	_file.seekg(0);

	while (std::getline(_file, line))
	{
		if (line == ("[" + categorie + "]"))
			break;
	}
	while (std::getline(_file, line) && line[0] != '\0')
	{
		if (line.compare(0, variable.size(), variable) == 0)
		{
			if (line.size() > variable.size() + 1 && _file.is_open())
			{
				std::string s = std::to_string(value);
				std::string tmp = (variable + '=' + s);
				_file.write(tmp.c_str(), tmp.size());
			}
		}
	}
}

void ParserIni::setText(const std::string & categorie, const std::string& variable, const std::string & value)
{
	std::string line;
	_file.seekg(0);

	while (std::getline(_file, line))
	{
		if (line == ("[" + categorie + "]"))
			break;
	}
	while (std::getline(_file, line) && line[0] != '\0')
	{
		if (line.compare(0, variable.size(), variable) == 0)
		{
			if (line.size() > variable.size() + 1 && _file.is_open())
			{
				std::cout << _file.tellp() << std::endl;
				// _file.seekp((_file.tellp().seekpos() - line.size()), std::ios::beg);
				std::string tmp = (variable + '=' + value);
				_file.write(tmp.c_str(), tmp.size());
			}
		}
	}
}
