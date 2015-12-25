#ifndef PARSER_INI_HH_
# define PARSER_INI_HH_

# include <iostream>
# include <fstream>
# include <string>
# include <map>
# include "Debug.hh"

class ParserException : public std::logic_error
{
public:
  ParserException()
    : std::logic_error("Parser Exception")
    {
    }

  ParserException(const std::string &str)
    : std::logic_error(str)
    {
    }

  virtual ~ParserException()
    {
    }
};

class ParserUnavaibleException : public ParserException
{
public:
  ParserUnavaibleException()
    : ParserException("Parser Exception")
    {
    }

  ParserUnavaibleException(const std::string &str)
    : ParserException(str)
    {
    }

  virtual ~ParserUnavaibleException()
    {
    }
};

class ParserIni
{
public:
	ParserIni(const std::string& file);
	virtual ~ParserIni();

	// Parsing
	int getValue(const std::string& categorie, const std::string& variable);
	const std::string &getText(const std::string& categorie, const std::string& variable);

	void setValue(const std::string& categorie, const std::string& variable, int value);
	void setText(const std::string& categorie, const std::string& variable, const std::string& value);

private:
	std::string _nameFile;
	std::map<std::string, std::map<std::string, std::string>> _values;
	//       Category              Variable     Value

	const std::string &getData(const std::string& categorie, const std::string& variable);
};

# include <memory>

using ParserIni_SharedPtr = std::shared_ptr<ParserIni>;

#endif /* !PARSER_INI_HH_*/
