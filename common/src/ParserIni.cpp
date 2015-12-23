#include "ParserIni.hh"
#include <algorithm>

ParserIni::ParserIni(const std::string& filename) : _nameFile(filename)
{
  std::fstream file(_nameFile, std::ios::in);

  if (!file)
    DEBUG_MSG("File couldn't be open");
  else {

    file.seekg(0);

    std::string currentCat;
    std::string line;

    while (std::getline(file, line)) {

      std::remove_if(line.begin(), line.end(), [] (char c) { return (c == ' '); });

      if (line.empty()) {
	continue ;
      }

      if (line.front() == '[' && line.back() == ']') {
	currentCat = std::string(line.begin() + 1, line.end() - 1);
      }
      else {

	if (currentCat.empty()) {
	  throw ParserException("catergory missing");
	}

	if (!std::count(line.begin(), line.end(), '=')) {
	  throw ParserException("Missing '=' token");
	}

	if (std::count(line.begin(), line.end(), '=') > 1) {
	  throw ParserException("Too much '=' token");
	}

	size_t equal = line.find("=");

	std::string var = line.substr(0, equal);
	std::string value = line.substr(equal + 1, std::string::npos);

	_values[currentCat][var] = value;
      }
    }

    for (auto &cat : _values) {

      for (auto &val : cat.second) {
	std::cout << "CAT: " << cat.first << std::endl;
	std::cout << "\t" << "VAL: " << val.first << std::endl;
	std::cout << "\t" << "VAR: " << val.second << std::endl;
      }
    }

    file.close();
  }
}

ParserIni::~ParserIni()
{
  DEBUG_MSG("ParserIni destructed");

  std::fstream file(_nameFile, std::ios::out);

  if (file.is_open()) {

    for (auto &cat : _values) {

      file << "[" << cat.first << "]" << std::endl;

      for (auto &val : cat.second) {
	file << val.first << "=" << val.second << std::endl;
      }

      file << std::endl;
    }

    file.close();
  }

}

const std::string &ParserIni::getData(const std::string& categorie, const std::string& variable)
{
  auto val_var = _values.find(categorie);

  if (val_var == _values.end()) {
    throw ParserUnavaibleException("Category doesn't exist");
  }

  auto value = val_var->second.find(variable);

  if (value == val_var->second.end()) {
    throw ParserUnavaibleException("Variable doesn't exist");
  }

  return (value->second);
}

int ParserIni::getValue(const std::string& categorie, const std::string& variable)
{
  return (std::stoi(getData(categorie, variable)));
}

const std::string &ParserIni::getText(const std::string& categorie, const std::string& variable)
{
  return (getData(categorie, variable));
}

void ParserIni::setValue(const std::string & categorie, const std::string& variable, int value)
{
  _values[categorie][variable] = std::to_string(value);
}

void ParserIni::setText(const std::string & categorie, const std::string& variable, const std::string & value)
{
  _values[categorie][variable] = value;
}
