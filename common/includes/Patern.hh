//
// Patern.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Nov 13 00:35:06 2015 chapui_s
// Last update Fri Nov 13 00:35:06 2015 chapui_s
//

#ifndef PATERN_H_
# define PATERN_H_

# include <functional>

typedef std::function< uint8_t(uint8_t) > function;

class Patern
{
public: 
	Patern();
	Patern(const function& function);
	virtual ~Patern();

	void setPatern(const function& function);
	uint8_t applyPatern(uint8_t x);

private: 
	function patern;
};

uint8_t absPatern(uint8_t x);
uint8_t cosPatern(uint8_t x);
uint8_t sinPatern(uint8_t x);

#endif /* !PATERN_H_ */